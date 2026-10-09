# Hotel Reservation System - Project Report

## 1. Test Results
The project includes a comprehensive suite of tests using GoogleTest. All tests compile and pass successfully without any memory leaks or deadlocks.

### Unit Tests (15 Tests)
*   **Billing Tests (`test_billing.cpp`)**: 5 tests validating the Strategy Pattern. Verified correct baseline calculations for `StandardBilling` and precise mathematical correctness for `SeasonalWeekendBilling` (applying 20% surcharges specifically on weekends, crossing week boundaries, and summing service charges).
*   **Availability Tests (`test_availability.cpp`)**: 5 tests verifying the mathematical overlap logic of date ranges. Tested exact overlaps, partial overlaps, and non-overlapping sequential stays (where checkout date equals the next check-in date).
*   **Lifecycle Tests (`test_lifecycle.cpp`)**: 5 tests validating the `HotelService` state machine. Confirmed that invalid transitions (e.g., checking out before checking in) safely throw `std::logic_error`, and that cancellations immediately free the room in the index.

### End-to-End / Model Test (1 Test)
*   **Simulation Test (`test_e2e.cpp`)**: Simulated a full month of hotel operations with multiple guests, varying room categories (Standard, Deluxe), and overlapping timeframes.
*   **Verification**: The test correctly processed the lifecycle of all reservations. The final accumulated revenue matched the mathematically expected total of `$1300.00`, and queries for the following month confirmed all rooms were correctly released and returned to the available pool.

## 2. Observations
*   **Decoupling via Strategy Pattern**: Abstracting the billing logic into the `BillingStrategy` interface proved highly effective. When adding the complex `SeasonalWeekendBilling` logic, the core `Reservation` and `HotelService` classes required zero modifications, perfectly adhering to the Open/Closed Principle of software design.
*   **Facade Orchestration**: `HotelService` acted as an excellent Facade. It simplified the interaction for the testing and simulation layers, ensuring that external interfaces (like `main.cpp`) did not need to manually orchestrate the `AvailabilityIndex` and `Room` status flags.
*   **Concurrency Robustness**: Simulating race conditions in `main.cpp` demonstrated that `std::mutex` and `std::lock_guard` successfully prevented double-booking. When three threads attempted to book two available rooms simultaneously, exactly two succeeded and the third safely aborted with a custom `RoomUnavailableException`.

## 3. Performance Insights (Availability-Lookup Complexity)
The `AvailabilityIndex` utilizes a `std::map<int, std::vector<std::pair<Date, Date>>>` to track bookings.
*   **Space Complexity**: $O(R + B)$, where $R$ is the number of rooms and $B$ is the total number of active bookings across all rooms.
*   **Lookup Complexity (Single Room)**: To check if a specific room is available, the system performs a tree lookup to find the room in the map, which is $O(\log R)$ since `std::map` is implemented as a Red-Black tree. Then, it iterates through that room's existing bookings. If a room has $N$ future bookings, checking for overlaps takes $O(N)$ time. Thus, the total complexity is **$O(\log R + N)$**.
*   **Search Complexity (All Rooms)**: To find all available rooms for a given date range, the system must iterate over all $R$ rooms of the specified type, and for each, iterate over its $N$ bookings. The worst-case complexity is **$O(R \times N)$**.
*   **Optimization Potential**: While $O(R \times N)$ is exceptionally fast for a single hotel with a few hundred rooms, a massive, global booking system could optimize this further by using an **Interval Tree** or **Segment Tree** to store the dates, which would reduce the overlap check from $O(N)$ down to $O(\log N)$.

## 4. Challenges Faced
*   **Date Math & Overlap Logic**: C++20's `<chrono>` library is incredibly powerful but syntactically complex. Stripping the boilerplate `std::chrono::year_month_day` and `std::chrono::sys_days` logic into a clean `Date` wrapper class was necessary to keep the business logic readable. Determining date overlap required careful mathematical logic (`(CheckIn < ExistingOut) && (ExistingIn < CheckOut)`) to prevent edge-case off-by-one errors.
*   **Thread-Safe Data Structures**: Ensuring the `AvailabilityIndex` was thread-safe without causing a deadlock was challenging. Initially, there was a risk of a race condition if a thread checked availability, yielded execution, and then attempted to book. This was solved by ensuring the "double-check" and the "write" occurred inside the exact same `std::lock_guard` scope in the `addBooking` function.
*   **GoogleTest Integration**: Setting up a robust testing framework in C++ across different operating systems can be notoriously difficult. We solved this by utilizing CMake's `FetchContent` module to dynamically download, build, and link GoogleTest directly into our `CMakeLists.txt`, bypassing manual dependency installation and ensuring cross-platform compilation.
