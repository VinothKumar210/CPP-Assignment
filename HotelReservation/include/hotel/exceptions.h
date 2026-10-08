#pragma once
#include <stdexcept>
#include <string>

namespace hotel {
class HotelException : public std::runtime_error {
public:
    explicit HotelException(const std::string& message) : std::runtime_error(message) {}
};

class InvalidDateException : public HotelException {
public:
    explicit InvalidDateException(const std::string& message) : HotelException(message) {}
};

} 
