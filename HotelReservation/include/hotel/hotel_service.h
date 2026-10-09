#pragma once

#include <vector>
#include <map>
#include <memory>
#include <mutex>
#include <string>

#include "hotel/room.h"
#include "hotel/reservation.h"
#include "hotel/availability_index.h"
#include "hotel/billing_strategy.h"

namespace hotel {

class HotelService {
private:
    std::vector<std::shared_ptr<Room>> rooms_;
    std::map<std::string, std::shared_ptr<Reservation>> reservations_;
    
    AvailabilityIndex availabilityIndex_;
    std::unique_ptr<BillingStrategy> billingStrategy_;
    
    std::mutex hotelMutex_; 
    int nextReservationId_;

public:
    explicit HotelService(std::unique_ptr<BillingStrategy> billingStrategy);

    void addRoom(std::shared_ptr<Room> room);

    std::vector<std::shared_ptr<Room>> searchRooms(RoomType type, const Date& from, const Date& to) const;

    std::string bookRoom(const Guest& guest, RoomType type, const Date& checkIn, const Date& checkOut);

    void checkIn(const std::string& reservationId);
    double checkOut(const std::string& reservationId);
    void cancelReservation(const std::string& reservationId);
    void logEvent(const std::string& message);
};

} 
