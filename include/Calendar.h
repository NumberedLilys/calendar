#pragma once
#include <string>
#include <chrono>

class Calendar {
    private:
        int year;
        int month;
        int day;
    public:
        Calendar(int y, int m, int d): year(y), month(m), day(d) {};
        
        int getYear() const { return year; }
        int getMonth() const { return month; }
        int getDay() const { return day; }

        std::string displayDate(std::chrono::system_clock::time_point tp);
};