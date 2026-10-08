#include <iostream>
#include "hotel/date.h"

int main() {
    std::cout << "Hotel Reservation System - starting up\n";

    hotel::Date today = hotel::Date::today();
    std::cout << "Today: " << today.toString() << "\n";

    return 0;
}
