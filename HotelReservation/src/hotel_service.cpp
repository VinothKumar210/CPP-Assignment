#include "hotel/hotel_service.h"
#include "hotel/exceptions.h"
#include <iostream>
#include <chrono>

namespace hotel {

HotelService::HotelService(std::unique_ptr<BillingStrategy> billingStrategy)
    : billingStrategy_(std::move(billingStrategy)), nextReservationId_(1) {}

void HotelService::addRoom(std::shared_ptr<Room> room) {
    std::lock_guard<std::mutex> lock(hotelMutex_);
    rooms_.push_back(room);
}

std::vector<std::shared_ptr<Room>> HotelService::searchRooms(RoomType type, const Date& from, const Date& to) const {
    return availabilityIndex_.findAvailableRooms(type, from, to, rooms_);
}

std::string HotelService::bookRoom(const Guest& guest, RoomType type, const Date& checkIn, const Date& checkOut) {
    if (checkOut <= checkIn) {
        throw InvalidDateException("Check-out must be after check-in.");
    }

    auto availableRooms = searchRooms(type, checkIn, checkOut);
    if (availableRooms.empty()) {
        throw RoomUnavailableException("No rooms available for the requested dates and type.");
    }


    auto selectedRoom = availableRooms.front(); 

    std::string resId;
    {
        std::lock_guard<std::mutex> lock(hotelMutex_);
        availabilityIndex_.addBooking(selectedRoom->getRoomNumber(), checkIn, checkOut);

        resId = "RES-" + std::to_string(nextReservationId_++);
        auto reservation = std::make_shared<Reservation>(resId, selectedRoom, guest, checkIn, checkOut);
        
        reservations_[resId] = reservation;
    }

    logEvent("Booked: " + resId + " for " + guest.getName() + " in Room " + std::to_string(selectedRoom->getRoomNumber()));
    return resId;
}

void HotelService::checkIn(const std::string& reservationId) {
    std::lock_guard<std::mutex> lock(hotelMutex_);
    
    auto it = reservations_.find(reservationId);
    if (it == reservations_.end()) {
        throw std::invalid_argument("Reservation not found: " + reservationId);
    }

    auto res = it->second;
    if (res->getStatus() != ReservationStatus::Pending) {
        throw std::logic_error("Cannot check in. Status is not Pending.");
    }

    res->setStatus(ReservationStatus::CheckedIn);
    res->getRoom()->setStatus(RoomStatus::Occupied);
    
    logEvent("Check-In: " + reservationId);
}

double HotelService::checkOut(const std::string& reservationId) {
    std::lock_guard<std::mutex> lock(hotelMutex_);
    
    auto it = reservations_.find(reservationId);
    if (it == reservations_.end()) {
        throw std::invalid_argument("Reservation not found: " + reservationId);
    }

    auto res = it->second;
    if (res->getStatus() != ReservationStatus::CheckedIn) {
        throw std::logic_error("Cannot check out. Status is not CheckedIn.");
    }

    double totalBill = billingStrategy_->computeBill(*res);

    res->setStatus(ReservationStatus::CheckedOut);
    res->getRoom()->setStatus(RoomStatus::Available);
    
    logEvent("Check-Out: " + reservationId + " | Bill: $" + std::to_string(totalBill));
    return totalBill;
}

void HotelService::cancelReservation(const std::string& reservationId) {
    std::lock_guard<std::mutex> lock(hotelMutex_);
    
    auto it = reservations_.find(reservationId);
    if (it == reservations_.end()) {
        throw std::invalid_argument("Reservation not found: " + reservationId);
    }

    auto res = it->second;
    if (res->getStatus() != ReservationStatus::Pending) {
        throw std::logic_error("Cannot cancel. Status is not Pending.");
    }

    res->setStatus(ReservationStatus::Cancelled);
    
    availabilityIndex_.removeBooking(res->getRoom()->getRoomNumber(), res->getCheckIn(), res->getCheckOut());
    
    logEvent("Cancelled: " + reservationId);
}

void HotelService::logEvent(const std::string& message) {
    static std::mutex logMutex;
    std::lock_guard<std::mutex> lock(logMutex);
    
    auto now = std::chrono::system_clock::now();
    std::time_t now_time = std::chrono::system_clock::to_time_t(now);
    
    std::string timeStr = std::ctime(&now_time);
    timeStr.pop_back(); 

    std::cout << "[" << timeStr << "] " << message << std::endl;
}

} 
