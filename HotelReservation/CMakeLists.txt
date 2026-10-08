cmake_minimum_required(VERSION 3.20)
project(HotelReservation)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
add_library(hotel_lib
    src/date.cpp
    src/availability_index.cpp
)

target_include_directories(hotel_lib PUBLIC include)

add_executable(hotel src/main.cpp)
target_link_libraries(hotel PRIVATE hotel_lib)
