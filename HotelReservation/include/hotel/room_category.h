#pragma once
#include <string>
#include <vector>
#include "hotel/enums.h"

namespace hotel {

class RoomCategory {
private:
    RoomType type_;
    int defaultCapacity_;
    double baseRate_;
    std::vector<std::string> amenities_;

public:
    RoomCategory(RoomType type, int defaultCapacity, double baseRate, const std::vector<std::string>& amenities)
        : type_(type),
          defaultCapacity_(defaultCapacity),
          baseRate_(baseRate),
          amenities_(amenities) {}

    RoomType getType() const { return type_; }
    int getDefaultCapacity() const { return defaultCapacity_; }
    double getBaseRate() const { return baseRate_; }
    const std::vector<std::string>& getAmenities() const { return amenities_; }

    std::string getName() const {
        return toString(type_); 
    }
};

} 
