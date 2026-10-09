#pragma once

#include <string>
#include "hotel/enums.h"

namespace hotel {

class Room {
private:
    int roomNumber_;
    RoomType type_;
    int capacity_;
    double nightlyRate_;
    RoomStatus status_;

public:
    Room(int roomNumber, RoomType type, int capacity, double nightlyRate)
        : roomNumber_(roomNumber),
          type_(type),
          capacity_(capacity),
          nightlyRate_(nightlyRate),
          status_(RoomStatus::Available) {}


    int getRoomNumber() const { return roomNumber_; }
    RoomType getType() const { return type_; }
    int getCapacity() const { return capacity_; }
    double getNightlyRate() const { return nightlyRate_; }
    RoomStatus getStatus() const { return status_; }

    void setStatus(RoomStatus newStatus) { status_ = newStatus; }

    bool isAvailable() const { return status_ == RoomStatus::Available; }

    std::string toString() const {
        return "Room " + std::to_string(roomNumber_) + " (" + hotel::toString(type_) + ") - " + hotel::toString(status_);
    }
};

}
