#pragma once

namespace hotel {   
    enum class RoomStatus {Available, Occupied, Reserved, Maintenance};
    enum class RoomType {Standard, Suite, Deluxe};
    enum class ReservationStatus {Pending, CheckedIn, CheckedOut, Cancelled};
    
        inline const char* toString(RoomStatus status) {
            switch (status) {
                case RoomStatus::Available:   return "Available";
                case RoomStatus::Occupied:    return "Occupied";
                case RoomStatus::Reserved:    return "Reserved";
                case RoomStatus::Maintenance: return "Maintenance";
            }
            return "Unknown";
        }
    
        inline const char* toString(RoomType type) {
            switch (type) {
                case RoomType::Standard: return "Standard";
                case RoomType::Deluxe:   return "Deluxe";
                case RoomType::Suite:    return "Suite";
            }
            return "Unknown";
        }
    
        inline const char* toString(ReservationStatus status) {
            switch (status) {
                case ReservationStatus::Pending:   return "Pending";
                case ReservationStatus::CheckedIn:  return "CheckedIn";
                case ReservationStatus::CheckedOut: return "CheckedOut";
                case ReservationStatus::Cancelled:  return "Cancelled";
            }
            return "Unknown";
        }
} 
