#include "calendar.h"
#include "CalendarLibraries.h"

bool Calendar::isLeapYear(int y) {
    return ((y % 4 == 0) && (y % 100 != 0)) || (y % 400 == 0);
}

int Calendar::daysInMonth(int y, int m) {
    static const int daysPerMonth[12] = {
        31, // Jan
        28, // Feb (adjusted below for leap years)
        31, // Mar
        30, // Apr
        31, // May
        30, // Jun
        31, // Jul
        31, // Aug
        30, // Sep
        31, // Oct
        30, // Nov
        31  // Dec
    };

    if (m < 1 || m > 12) {
        return 30; // sensible fallback
    }

    if (m == 2 && isLeapYear(y)) {
        return 29;
    }

    return daysPerMonth[m - 1];
}

void Calendar::setDate(int y, int m, int d) {
    year = y;
    month = m;
    int maxDay = daysInMonth(year, month);
    if (d < 1) {
        day = 1;
    } else if (d > maxDay) {
        day = maxDay;
    } else {
        day = d;
    }
}

void Calendar::changeMonth(int deltaMonths) {
    int totalMonths = (year * 12 + (month - 1)) + deltaMonths;
    if (totalMonths < 0) {
        totalMonths = 0;
    }
    int newYear = totalMonths / 12;
    int newMonth = (totalMonths % 12) + 1;

    int maxDay = daysInMonth(newYear, newMonth);
    if (day > maxDay) {
        day = maxDay;
    }

    year = newYear;
    month = newMonth;
}

int Calendar::getDaysInMonth() const {
    return daysInMonth(year, month);
}

int Calendar::getStartDayOfWeek() const {
    std::tm tmDate{};
    tmDate.tm_year = year - 1900;
    tmDate.tm_mon = month - 1;
    tmDate.tm_mday = 1;

    // mktime normalises and fills tm_wday: 0 = Sunday, 6 = Saturday
    std::mktime(&tmDate);
    return tmDate.tm_wday;
}

std::string Calendar::getMonthName() const {
    static const char* monthNames[12] = {
        "January", "February", "March",     "April",
        "May",     "June",     "July",      "August",
        "September","October", "November",  "December"
    };

    if (month < 1 || month > 12) {
        return "Unknown";
    }
    return monthNames[month - 1];
}

std::string Calendar::displayDate(std::chrono::system_clock::time_point tp) {
    std::time_t t = std::chrono::system_clock::to_time_t(tp);
    std::tm now;
    
    #ifdef _WIN32
    localtime_s(&now, &t);  // Windows takes (Destination, Source)
    #else
    localtime_r(&t, &now);  // Linux takes (Source, Destination)
    #endif

    std::ostringstream ss;
    ss << std::put_time(&now, "%Y-%m-%d");
    return ss.str();
}