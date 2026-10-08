#include "hotel/date.h"

#include <chrono>
#include <stdexcept>

namespace hotel {

// ── Constructor ───────────────────────────────────────────────────────────────

Date::Date(int year, int month, int day)
    : year_(year), month_(month), day_(day)
{
    if (!isValid()) {
        throw std::invalid_argument("Invalid date: " + toString());
    }
}

// ── Validation ────────────────────────────────────────────────────────────────

bool Date::isValid() const
{
    std::chrono::year_month_day ymd{
        std::chrono::year(year_),
        std::chrono::month(static_cast<unsigned>(month_)),
        std::chrono::day(static_cast<unsigned>(day_))
    };
    return ymd.ok();
}

// ── Date Arithmetic ───────────────────────────────────────────────────────────

int Date::daysBetween(const Date& other) const
{
    auto toSysDays = [](const Date& d) {
        return std::chrono::sys_days{
            std::chrono::year_month_day{
                std::chrono::year(d.getYear()),
                std::chrono::month(static_cast<unsigned>(d.getMonth())),
                std::chrono::day(static_cast<unsigned>(d.getDay()))
            }
        };
    };

    auto d1 = toSysDays(*this);
    auto d2 = toSysDays(other);
    return static_cast<int>((d2 - d1).count());
}

// ── Formatting ────────────────────────────────────────────────────────────────

std::string Date::toString() const
{
    std::string monthStr = std::to_string(month_);
    std::string dayStr   = std::to_string(day_);

    if (monthStr.length() == 1) monthStr = "0" + monthStr;
    if (dayStr.length() == 1)   dayStr   = "0" + dayStr;

    return std::to_string(year_) + "-" + monthStr + "-" + dayStr;
}

// ── Accessors ─────────────────────────────────────────────────────────────────

int Date::getYear()  const { return year_;  }
int Date::getMonth() const { return month_; }
int Date::getDay()   const { return day_;   }

// ── Static Factory ────────────────────────────────────────────────────────────

Date Date::today()
{
    auto now = std::chrono::system_clock::now();
    auto dp  = std::chrono::floor<std::chrono::days>(now);
    std::chrono::year_month_day ymd{dp};

    return Date{
        static_cast<int>(ymd.year()),
        static_cast<int>(static_cast<unsigned>(ymd.month())),
        static_cast<int>(static_cast<unsigned>(ymd.day()))
    };
}

} // namespace hotel