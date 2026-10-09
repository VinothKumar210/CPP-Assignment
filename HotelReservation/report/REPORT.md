# Hotel Reservation System – Project Report

## 1. Test Results

In this project, I used GoogleTest (GTest) to create five test suites to verify the functionality of the Hotel Reservation System. All test cases were executed successfully and passed.

The tests covered billing calculations, room availability, reservation lifecycle, and overall system functionality. I verified standard billing, weekend surcharges, date overlaps, reservation cancellations, check-in, and checkout operations. The end-to-end simulation tested multiple guests and room categories. The total revenue was calculated as $1300.00, matching the expected result.

## 2. Observations

The Strategy Pattern helped separate billing logic from the main reservation system, making it easier to introduce different billing methods. The `HotelService` class simplified interactions between room management, availability checking, and reservations.

I also implemented thread synchronization using `std::mutex` and `std::lock_guard`. In the concurrency simulation, two bookings succeeded while the third was rejected because no rooms were available.

## 3. Performance Analysis

The `AvailabilityIndex` uses `std::map` to store room bookings. Its space complexity is O(R + B), where R represents rooms and B represents bookings. Checking availability for one room takes O(log R + N) time, where N is the number of bookings for that room.

## 4. Challenges Faced

The main challenges were handling date calculations using C++20, preventing race conditions, and integrating GoogleTest with CMake.

## 5. Conclusion

This project improved my understanding of C++20, object-oriented programming, design patterns, multithreading, and automated testing.
