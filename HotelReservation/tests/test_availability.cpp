#include <gtest/gtest.h>
#include "hotel/availability_index.h"
#include "hotel/exceptions.h"

using namespace hotel;

class AvailabilityTest : public ::testing::Test {
protected:
    AvailabilityIndex index;
    int roomNum = 101;
};

TEST_F(AvailabilityTest, InitiallyAvailable) {
    EXPECT_TRUE(index.isAvailable(roomNum, Date(2026, 1, 1), Date(2026, 1, 5)));
}

TEST_F(AvailabilityTest, ExactOverlap) {
    index.addBooking(roomNum, Date(2026, 1, 1), Date(2026, 1, 5));
    EXPECT_FALSE(index.isAvailable(roomNum, Date(2026, 1, 1), Date(2026, 1, 5)));
    EXPECT_THROW(index.addBooking(roomNum, Date(2026, 1, 1), Date(2026, 1, 5)), RoomUnavailableException);
}

TEST_F(AvailabilityTest, PartialOverlap) {
    index.addBooking(roomNum, Date(2026, 1, 5), Date(2026, 1, 10));
    EXPECT_FALSE(index.isAvailable(roomNum, Date(2026, 1, 8), Date(2026, 1, 12)));
}

TEST_F(AvailabilityTest, TouchingDatesAllowed) {
    index.addBooking(roomNum, Date(2026, 1, 5), Date(2026, 1, 10));
    EXPECT_TRUE(index.isAvailable(roomNum, Date(2026, 1, 10), Date(2026, 1, 15)));
    EXPECT_TRUE(index.isAvailable(roomNum, Date(2026, 1, 1), Date(2026, 1, 5)));
}

TEST_F(AvailabilityTest, RemovalRestoresAvailability) {
    index.addBooking(roomNum, Date(2026, 1, 1), Date(2026, 1, 5));
    EXPECT_FALSE(index.isAvailable(roomNum, Date(2026, 1, 1), Date(2026, 1, 5)));
    index.removeBooking(roomNum, Date(2026, 1, 1), Date(2026, 1, 5));
    EXPECT_TRUE(index.isAvailable(roomNum, Date(2026, 1, 1), Date(2026, 1, 5)));
}
