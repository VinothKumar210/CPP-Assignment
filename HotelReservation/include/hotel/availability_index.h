#pragma once

#include <map>
#include <vector>
#include <memory>
#include <mutex>
#include "hotel/date.h"
#include "hotel/room.h"

namespace hotel {

class AvailabilityIndex {
private:
    std::map<int, std::vector<std::pair<Date, Date>>> bookings_;
    
    mutable std::mutex mutex_;

public:
    AvailabilityIndex() = default;

    bool isAvailable(int roomNumber, const Date& from, const Date& to) const;

    void addBooking(int roomNumber, const Date& from, const Date& to);

    void removeBooking(int roomNumber, const Date& from, const Date& to);

    std::vector<std::shared_ptr<Room>> findAvailableRooms(
        RoomType type, 
        const Date& from, 
        const Date& to, 
        const std::vector<std::shared_ptr<Room>>& allRooms) const;
};

} 
