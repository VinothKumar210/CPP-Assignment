#pragma once

#include "hotel/billing_strategy.h"
#include <chrono>

namespace hotel {

class SeasonalWeekendBilling : public BillingStrategy {
public:
    double computeBill(const Reservation& reservation) const override {
        double rate = reservation.getRoom()->getNightlyRate();
        double services = reservation.totalServiceCharges();
        double roomTotal = 0.0;

        Date currentDate = reservation.getCheckIn();
        Date checkOut = reservation.getCheckOut();

        while (currentDate < checkOut) {
            if (currentDate.isWeekend()) {
                roomTotal += (rate * 1.2);
            } else {
                roomTotal += rate;
            }

            currentDate = getNextDay(currentDate);
        }

        return roomTotal + services;
    }

private:
    Date getNextDay(const Date& d) const {
        std::chrono::sys_days sysDays = std::chrono::year_month_day{
            std::chrono::year(d.getYear()),
            std::chrono::month(static_cast<unsigned>(d.getMonth())),
            std::chrono::day(static_cast<unsigned>(d.getDay()))
        };
        
        sysDays += std::chrono::days{1};
        std::chrono::year_month_day nextYmd{sysDays};
        
        return Date(
            static_cast<int>(nextYmd.year()),
            static_cast<int>(static_cast<unsigned>(nextYmd.month())),
            static_cast<int>(static_cast<unsigned>(nextYmd.day()))
        );
    }
};

}
