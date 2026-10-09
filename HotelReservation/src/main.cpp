#include <iostream>
#include <thread>
#include <vector>
#include <chrono>

#include "hotel/hotel_service.h"
#include "hotel/standard_billing.h"
#include "hotel/seasonal_weekend_billing.h"
#include "hotel/exceptions.h"

using namespace hotel;

void simulateBookingChannel(HotelService& service, const std::string& channelName, const Guest& guest) {
    try {
        service.logEvent(channelName + " is attempting to book a Standard room for " + guest.getName() + "...");
        
        Date checkIn = Date::today();
        
        Date checkOut = Date(checkIn.getYear(), checkIn.getMonth(), checkIn.getDay() + 3); 
        
        std::string resId = service.bookRoom(guest, RoomType::Standard, checkIn, checkOut);
        
        service.logEvent(channelName + " SUCCESS: " + resId);
        
        service.checkIn(resId);
        service.checkOut(resId);

    } catch (const HotelException& e) {
        service.logEvent(channelName + " FAILED: " + e.what());
    }
}

int main() {
    std::cout << "=== Hotel Reservation System Simulator ===" << std::endl;

    auto billing = std::make_unique<SeasonalWeekendBilling>();
    HotelService service(std::move(billing));

    service.addRoom(std::make_shared<Room>(101, RoomType::Standard, 2, 100)); 
    service.addRoom(std::make_shared<Room>(102, RoomType::Standard, 2, 100));
    service.addRoom(std::make_shared<Room>(201, RoomType::Deluxe,   3, 200));
    service.addRoom(std::make_shared<Room>(301, RoomType::Suite,    4, 400));

    Guest guest1("G1", "Alice Smith", "555-0101", "alice@example.com");
    Guest guest2("G2", "Bob Johnson", "555-0202", "bob@example.com");
    Guest guest3("G3", "Charlie Day", "555-0303", "charlie@example.com");


    std::vector<std::thread> threads;
    
    threads.push_back(std::thread(simulateBookingChannel, std::ref(service), "Online", guest1));
    threads.push_back(std::thread(simulateBookingChannel, std::ref(service), "In Person", guest2));
    threads.push_back(std::thread(simulateBookingChannel, std::ref(service), "Booking service", guest3));
    for (auto& t : threads) {
        t.join();
    }

    std::cout << "\n=== Simulation Complete ===" << std::endl;
    return 0;
}
