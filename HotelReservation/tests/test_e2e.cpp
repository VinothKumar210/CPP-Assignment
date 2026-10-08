#include <gtest/gtest.h>
#include "hotel/hotel_service.h"
#include "hotel/standard_billing.h"

using namespace hotel;

TEST(EndToEndTest, SimulatedMonth) {
    auto billing = std::make_unique<StandardBilling>();
    HotelService service(std::move(billing));

    service.addRoom(std::make_shared<Room>(101, RoomType::Standard, 2, 100));
    service.addRoom(std::make_shared<Room>(102, RoomType::Standard, 2, 100));
    service.addRoom(std::make_shared<Room>(201, RoomType::Deluxe, 3, 200));

    Guest guest1("G1", "Alice", "123", "a@a.com");
    Guest guest2("G2", "Bob", "456", "b@b.com");
    Guest guest3("G3", "Charlie", "789", "c@c.com");

    double totalRevenue = 0.0;

    std::string res1 = service.bookRoom(guest1, RoomType::Standard, Date(2026, 10, 1), Date(2026, 10, 5)); // 4 nights = $400
    std::string res2 = service.bookRoom(guest2, RoomType::Deluxe, Date(2026, 10, 1), Date(2026, 10, 3)); // 2 nights = $400
    

    std::string res3 = service.bookRoom(guest3, RoomType::Standard, Date(2026, 10, 10), Date(2026, 10, 15)); // 5 nights = $500

    service.checkIn(res1);
    service.checkIn(res2);
    
    totalRevenue += service.checkOut(res2); 
    totalRevenue += service.checkOut(res1);

    service.checkIn(res3);
    totalRevenue += service.checkOut(res3);

    EXPECT_DOUBLE_EQ(totalRevenue, 1300.0);
    
    auto freeRooms = service.searchRooms(RoomType::Standard, Date(2026, 11, 1), Date(2026, 11, 5));
    EXPECT_EQ(freeRooms.size(), 2);
}
