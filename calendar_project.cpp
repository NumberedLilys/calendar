#include <iostream>
#include <chrono>
#include <ctime>
#include <string>
#include <sstream>
#include <iomanip>

class Calendar {
    private:
        int year;
        int month;
        int day;

    public:
        Calendar(int y, int m, int d): year(y), month(m), day(d) {};
        void displayDate() {
            std::cout << "Date: " << year << "-" << month << "-" << day << std::endl;
        }
        // Put into a .h file later, add extra functionalities. Mainly display and basics for the calendar application
        // Figure out how to get the proper date/time, maybe a library?

};

class TaskNotifications {
    // Notification class, sends notifications for tasks/events. Put in .h file later
};

std::string format_date(std::chrono::system_clock::time_point tp) {

    std::time_t t = std::chrono::system_clock::to_time_t(tp); // changes time_point to time_t
    
    std::tm* now = std::localtime(&t); // Converts to local time

    std::ostringstream ss;
    ss << std::put_time(now, "%Y-%m-%d"); // Formats the date in YYYY-MM-DD format using stringstream
    return ss.str();
}

int main() {
    auto now = std::chrono::system_clock::now();
    std::cout << "Current date: " << format_date(now) << std::endl;
    return 0;
}