cmake_minimum_required(VERSION 3.20)
project(HotelReservation)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
add_library(hotel_lib
    src/date.cpp
    src/availability_index.cpp
    src/hotel_service.cpp
)

target_include_directories(hotel_lib PUBLIC include)

add_executable(hotel src/main.cpp)
target_link_libraries(hotel PRIVATE hotel_lib)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(hotel_tests 
    tests/test_billing.cpp
    tests/test_availability.cpp
    tests/test_lifecycle.cpp
    tests/test_e2e.cpp
)

target_link_libraries(hotel_tests PRIVATE hotel_lib gtest_main)
