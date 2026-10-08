#include <gtest/gtest.h>
#include "hotel/hotel_service.h"
#include "hotel/standard_billing.h"
#include "hotel/exceptions.h"

using namespace hotel;

class LifecycleTest : public ::testing::Test {
protected:
    std::unique_ptr<HotelService> service;
    Guest guest{"G1", "Test Guest", "555-1234", "test@example.com"};
    
    void SetUp() override {
        service = std::make_unique<HotelService>(std::make_unique<StandardBilling>());
        service->addRoom(std::make_shared<Room>(101, RoomType::Standard, 2, 100));
    }
};

TEST_F(LifecycleTest, SuccessfulLifecycle) {
    std::string resId = service->bookRoom(guest, RoomType::Standard, Date(2026, 1, 1), Date(2026, 1, 3));
    EXPECT_NO_THROW(service->checkIn(resId));
    EXPECT_EQ(service->checkOut(resId), 200.0);
}

TEST_F(LifecycleTest, CheckoutWithoutCheckinFails) {
    std::string resId = service->bookRoom(guest, RoomType::Standard, Date(2026, 1, 1), Date(2026, 1, 3));
    EXPECT_THROW(service->checkOut(resId), std::logic_error);
}

TEST_F(LifecycleTest, CancelBeforeCheckin) {
    std::string resId = service->bookRoom(guest, RoomType::Standard, Date(2026, 1, 1), Date(2026, 1, 3));
    EXPECT_NO_THROW(service->cancelReservation(resId));
    EXPECT_NO_THROW(service->bookRoom(guest, RoomType::Standard, Date(2026, 1, 1), Date(2026, 1, 3)));
}

TEST_F(LifecycleTest, CancelAfterCheckinFails) {
    std::string resId = service->bookRoom(guest, RoomType::Standard, Date(2026, 1, 1), Date(2026, 1, 3));
    service->checkIn(resId);
    EXPECT_THROW(service->cancelReservation(resId), std::logic_error);
}

TEST_F(LifecycleTest, InvalidDatesFails) {
    EXPECT_THROW(service->bookRoom(guest, RoomType::Standard, Date(2026, 1, 5), Date(2026, 1, 3)), InvalidDateException);
}
