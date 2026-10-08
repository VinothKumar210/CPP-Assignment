#include <gtest/gtest.h>
#include "hotel/standard_billing.h"
#include "hotel/seasonal_weekend_billing.h"
#include "hotel/reservation.h"

using namespace hotel;

class BillingTest : public ::testing::Test {
protected:
    Guest guest{"G1", "Test Guest", "555-1234", "test@example.com"};
    std::shared_ptr<Room> stdRoom = std::make_shared<Room>(101, RoomType::Standard, 2, 100);
    std::shared_ptr<Room> luxRoom = std::make_shared<Room>(201, RoomType::Suite, 4, 300);
};

TEST_F(BillingTest, StandardBillingNoServices) {
    Date checkIn(2026, 10, 5);
    Date checkOut(2026, 10, 8); 
    Reservation res("RES1", stdRoom, guest, checkIn, checkOut);
    
    StandardBilling billing;
    EXPECT_DOUBLE_EQ(billing.computeBill(res), 300.0);
}


TEST_F(BillingTest, StandardBillingWithServices) {
    Date checkIn(2026, 10, 5);
    Date checkOut(2026, 10, 6);
    Reservation res("RES2", stdRoom, guest, checkIn, checkOut);
    res.addServiceCharge("Room Service", 45.0);
    
    StandardBilling billing;
    EXPECT_DOUBLE_EQ(billing.computeBill(res), 145.0);
}

TEST_F(BillingTest, WeekendBillingOnWeekdays) {
    Date checkIn(2026, 10, 5); 
    Date checkOut(2026, 10, 7); 
    Reservation res("RES3", stdRoom, guest, checkIn, checkOut);
    
    SeasonalWeekendBilling billing;
    EXPECT_DOUBLE_EQ(billing.computeBill(res), 200.0);
}

TEST_F(BillingTest, WeekendBillingSpanningWeekend) {
    Date checkIn(2026, 10, 9); 
    Date checkOut(2026, 10, 12); 
    Reservation res("RES4", luxRoom, guest, checkIn, checkOut);
    
    SeasonalWeekendBilling billing;
    EXPECT_DOUBLE_EQ(billing.computeBill(res), 1020.0);
}
TEST_F(BillingTest, WeekendBillingWithServices) {
    Date checkIn(2026, 10, 10); 
    Date checkOut(2026, 10, 11); 
    Reservation res("RES5", stdRoom, guest, checkIn, checkOut);
    res.addServiceCharge("Spa", 100.0);
    
    SeasonalWeekendBilling billing;
    EXPECT_DOUBLE_EQ(billing.computeBill(res), 220.0);
}
