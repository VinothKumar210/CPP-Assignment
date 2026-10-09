#pragma once

#include <string>
#include <memory>
#include <vector>
#include "hotel/date.h"
#include "hotel/room.h"
#include "hotel/guest.h"
#include "hotel/enums.h"

namespace hotel {

class Reservation {
private:
    std::string reservationId_;
    std::shared_ptr<Room> room_;
    Guest guest_;
    Date checkIn_;
    Date checkOut_;
    ReservationStatus status_;
    std::vector<std::pair<std::string, double>> serviceCharges_; 

public:
    Reservation(std::string reservationId, std::shared_ptr<Room> room, const Guest& guest, const Date& checkIn, const Date& checkOut)
        : reservationId_(std::move(reservationId)),
          room_(std::move(room)),
          guest_(guest),
          checkIn_(checkIn),
          checkOut_(checkOut),
          status_(ReservationStatus::Pending) {}

    const std::string& getReservationId() const { return reservationId_; }
    std::shared_ptr<Room> getRoom() const { return room_; }
    const Guest& getGuest() const { return guest_; }
    const Date& getCheckIn() const { return checkIn_; }
    const Date& getCheckOut() const { return checkOut_; }
    ReservationStatus getStatus() const { return status_; }
    const std::vector<std::pair<std::string, double>>& getServiceCharges() const { return serviceCharges_; }

    void setStatus(ReservationStatus status) { status_ = status; }


    int nightsStayed() const {
        return checkIn_.daysBetween(checkOut_);
    }

    void addServiceCharge(const std::string& name, double amount) {
        serviceCharges_.push_back({name, amount});
    }

    double totalServiceCharges() const {
        double total = 0.0;
        for (const auto& charge : serviceCharges_) {
            total += charge.second;
        }
        return total;
    }

    bool overlaps(const Date& from, const Date& to) const {
        return (checkIn_ < to) && (from < checkOut_);
    }
};

}
