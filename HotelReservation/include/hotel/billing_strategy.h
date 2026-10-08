#pragma once

#include "hotel/reservation.h"

namespace hotel {

class BillingStrategy {
public:
    virtual ~BillingStrategy() = default;
    
    virtual double computeBill(const Reservation& reservation) const = 0;
};

}   
