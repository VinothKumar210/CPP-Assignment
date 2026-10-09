# Hotel Reservation System

## 1. Project Overview

This project is a multi-threaded Hotel Reservation System developed using Modern C++20. It manages rooms, guests, reservations, and billing. The Strategy Pattern is used for flexible billing calculations, while the Facade Pattern simplifies hotel operations. Mutexes are used to handle concurrent bookings and prevent double booking.

## 2. Folder Structure

* **include/hotel/** – Header files defining classes and interfaces.
* **src/** – Source files containing the implementation.
* **tests/** – GoogleTest test cases for billing, availability, lifecycle, and end-to-end operations.
* **report/** – Project report and performance analysis.
* **CMakeLists.txt** – Build configuration and dependency management.

## 3. Tools and Technologies

* **Operating System:** Windows
* **Compiler:** GCC 16.1.0 (MSYS2 UCRT64)
* **Build System:** CMake 3.20 or newer
* **Language:** C++20
* **Testing Framework:** GoogleTest

## 4. Build and Run

Execute the following commands in PowerShell:

```powershell
$env:PATH += ";C:\msys64\ucrt64\bin"
cmake -B build
cmake --build build
.\build\hotel.exe
.\build\hotel_tests.exe
```

## 5. Results

### Simulation Output (hotel.exe)

    === Hotel Reservation System Simulator ===
    [Fri Oct  9] Online is attempting to book a Standard room for Alice Smith...
    [Fri Oct  9] Booking service is attempting to book a Standard room for Charlie Day...
    [Fri Oct  9] Booked: RES-1 for Alice Smith in Room 101
    [Fri Oct  9] Online SUCCESS: RES-1
    [Fri Oct  9] Check-In: RES-1
    [Fri Oct  9] In Person is attempting to book a Standard room for Bob Johnson...
    [Fri Oct  9] Check-Out: RES-1 | Bill: $340.000000
    [Fri Oct  9] Booked: RES-2 for Charlie Day in Room 102
    [Fri Oct  9] Booking service SUCCESS: RES-2
    [Fri Oct  9] In Person FAILED: Room 102 was double-booked!
    [Fri Oct  9] Check-In: RES-2
    [Fri Oct  9] Check-Out: RES-2 | Bill: $340.000000
    === Simulation Complete ===

Explanation:
- Three channels (Online, Booking service, In Person) attempt to book Standard rooms simultaneously.
- Online wins first and books Room 101 (RES-1). It checks in and out. Bill is $340 (3 nights with weekend surcharges applied by SeasonalWeekendBilling).
- Booking service wins second and books Room 102 (RES-2). Same bill of $340.
- In Person tries last but both rooms are already taken. The mutex inside AvailabilityIndex detects the conflict and safely rejects the booking. No room is double-booked.

### Test Suite Output (hotel_tests.exe)

    [==========] Running 16 tests from 4 test suites.
    [       OK ] EndToEndTest.SimulatedMonth (1 ms)
    [       OK ] LifecycleTest.SuccessfulLifecycle (0 ms)
    [       OK ] LifecycleTest.CheckoutWithoutCheckinFails (0 ms)
    [       OK ] LifecycleTest.CancelBeforeCheckin (0 ms)
    [       OK ] LifecycleTest.CancelAfterCheckinFails (0 ms)
    [       OK ] LifecycleTest.InvalidDatesFails (0 ms)
    [       OK ] AvailabilityTest.InitiallyAvailable (0 ms)
    [       OK ] AvailabilityTest.ExactOverlap (0 ms)
    [       OK ] AvailabilityTest.PartialOverlap (0 ms)
    [       OK ] AvailabilityTest.TouchingDatesAllowed (0 ms)
    [       OK ] AvailabilityTest.RemovalRestoresAvailability (0 ms)
    [       OK ] BillingTest.StandardBillingNoServices (0 ms)
    [       OK ] BillingTest.StandardBillingWithServices (0 ms)
    [       OK ] BillingTest.WeekendBillingOnWeekdays (0 ms)
    [       OK ] BillingTest.WeekendBillingSpanningWeekend (0 ms)
    [       OK ] BillingTest.WeekendBillingWithServices (0 ms)
    [  PASSED  ] 16 tests.

Explanation:
- EndToEndTest: Simulates a full month. Total revenue of $1300 matched the expected value exactly.
- LifecycleTest: Verified that check-in, check-out, and cancellation follow the correct order. Invalid transitions throw errors as expected.
- AvailabilityTest: Verified date overlap logic. Sequential stays (checkout = next check-in) correctly do NOT overlap.
- BillingTest: Verified that StandardBilling and SeasonalWeekendBilling compute mathematically correct totals, including service charges and weekend surcharges.
