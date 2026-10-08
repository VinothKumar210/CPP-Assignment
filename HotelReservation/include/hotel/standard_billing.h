#pragma once

#include "hotel/billing_strategy.h"

namespace hotel {

class StandardBilling : public BillingStrategy {
public:
    double computeBill(const Reservation& reservation) const override {
        int nights = reservation.nightsStayed();
        double rate = reservation.getRoom()->getNightlyRate();
        double services = reservation.totalServiceCharges();

        return (nights * rate) + services;
    }
};

} 
