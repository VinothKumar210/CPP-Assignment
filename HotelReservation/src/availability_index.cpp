#include "hotel/availability_index.h"
#include "hotel/exceptions.h"
#include <algorithm>

namespace hotel {

bool AvailabilityIndex::isAvailable(int roomNumber, const Date& from, const Date& to) const {
    std::lock_guard<std::mutex> lock(mutex_);

    auto it = bookings_.find(roomNumber);
    if (it == bookings_.end()) {
        return true; 
    }

    for (const auto& booking : it->second) {
        const Date& bookedFrom = booking.first;
        const Date& bookedTo = booking.second;

        bool overlaps = (bookedFrom < to) && (from < bookedTo);
        if (overlaps) {
            return false;
        }
    }

    return true;
}

void AvailabilityIndex::addBooking(int roomNumber, const Date& from, const Date& to) {
    std::lock_guard<std::mutex> lock(mutex_);

    auto it = bookings_.find(roomNumber);
    if (it != bookings_.end()) {
        for (const auto& booking : it->second) {
            if ((booking.first < to) && (from < booking.second)) {
                throw RoomUnavailableException(
                    "Room " + std::to_string(roomNumber) + " was double-booked!"
                );
            }
        }
    }

    bookings_[roomNumber].push_back({from, to});
}

void AvailabilityIndex::removeBooking(int roomNumber, const Date& from, const Date& to) {
    std::lock_guard<std::mutex> lock(mutex_);

    auto it = bookings_.find(roomNumber);
    if (it != bookings_.end()) {
        auto& roomBookings = it->second;

        auto removeIt = std::find_if(roomBookings.begin(), roomBookings.end(),
            [&](const std::pair<Date, Date>& b) {
                return b.first == from && b.second == to;
            });

        if (removeIt != roomBookings.end()) {
            roomBookings.erase(removeIt);
        }
    }
}

std::vector<std::shared_ptr<Room>> AvailabilityIndex::findAvailableRooms(
    RoomType type, 
    const Date& from, 
    const Date& to, 
    const std::vector<std::shared_ptr<Room>>& allRooms) const 
{
    std::vector<std::shared_ptr<Room>> availableRooms;

    for (const auto& room : allRooms) {
        if (room->getType() == type && room->isAvailable()) {
            if (isAvailable(room->getRoomNumber(), from, to)) {
                availableRooms.push_back(room);
            }
        }
    }

    return availableRooms;
}

} 
