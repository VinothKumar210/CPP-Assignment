#pragma once

#include <string>
#include <stdexcept>
#include <tuple>


namespace hotel {

class Date {
private:
    int year_;
    int month_;
    int day_;

public:
    Date(int year, int month, int day);

    bool isValid() const;

    int daysBetween(const Date& other) const;

    std::string toString() const;

    int getYear() const;
    int getMonth() const;
    int getDay() const;

    static Date today();
};

bool isWeekend() const;

inline bool operator<(const Date& a, const Date& b) {
    return std::tuple{a.getYear(), a.getMonth(), a.getDay()} <
            std::tuple{b.getYear(), b.getMonth(), b.getDay()};
}

inline bool operator==(const Date& a, const Date& b) {
    return a.getYear() == b.getYear() &&
           a.getMonth() == b.getMonth() &&
           a.getDay() == b.getDay();
}

inline bool operator>(const Date& a, const Date& b) {
    return b < a;
}

inline bool operator<=(const Date& a, const Date& b) {
    return !(b < a);
}

inline bool operator>=(const Date& a, const Date& b) {
    return !(a < b);
}

inline bool operator!=(const Date& a, const Date& b) {
    return !(a == b);
}

}