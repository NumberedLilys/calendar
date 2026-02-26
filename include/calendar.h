#pragma once

#include <string>
#include <chrono>

class Calendar {
private:
    int year;
    int month; // 1-12
    int day;   // 1-31

    static bool isLeapYear(int y);
    static int daysInMonth(int y, int m);

public:
    Calendar(int y, int m, int d) : year(y), month(m), day(d) {}

    int getYear() const { return year; }
    int getMonth() const { return month; }
    int getDay() const { return day; }

    void setDate(int y, int m, int d);

    // Adjust month by delta (e.g. -1 = previous month, +1 = next month, ±12 = year jumps)
    void changeMonth(int deltaMonths);

    // Number of days in the current month, respecting leap years
    int getDaysInMonth() const;

    // Day-of-week index for the 1st of the current month: 0 = Sunday, 1 = Monday, ... 6 = Saturday
    int getStartDayOfWeek() const;

    // Convenience: Month name in English (e.g. "January")
    std::string getMonthName() const;

    // Existing API for formatting a time_point as YYYY-MM-DD
    std::string displayDate(std::chrono::system_clock::time_point tp);
};

