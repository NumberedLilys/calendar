// Maybe include a list of libraries in a Libraries.h file and just #include "Libraries.h" at top of page?
// #include <iostream>
// #include <chrono>
// #include <ctime>
// #include <string>
// #include <sstream>
// #include <iomanip> // All in Calendar.h
#include "CalendarLibraries.h"
#include "Calendar.h"

// // class TaskNotifications {
// //     // Notification class, sends notifications for tasks/events. Put in .h file later
// // };

int main() {
    auto now = std::chrono::system_clock::now();
    Calendar calendar(2026, 1, 1);
    std::cout << "Current date: " << calendar.displayDate(now) << std::endl;

    // Create a simple user interface for account creation and login eventually

    std::cout << "Welcome to the Calendar App!" << "\n" << "Do you have an account? (y/n): ";
    std::string response;
    std::getline(std::cin, response);

    if (response == "n") {
        std::cout << "Account creation:" << std::endl;
        calendar.createUser();
    } else if (response == "y") {
        std::cout << "Login:" << std::endl;
        calendar.userLogin();
    }

    return 0;
}