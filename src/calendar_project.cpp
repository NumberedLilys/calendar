#include "CalendarLibraries.h" // All libraries needed in the Calendar.h file and main file
#include "Calendar.h"

// class TaskNotifications {
//     // Notification class, sends notifications for tasks/events. Put in .h file later
// };

int main() {

    // testCreateUserSuccess(); // Test cases for user creation and login, put in separate test file later, create them
    // testDuplicateUser();
    // testLoginSuccess();
    // testLoginFail();

    auto now = std::chrono::system_clock::now();
    Calendar calendar(2026, 1, 1);
    std::cout << "Current date: " << calendar.displayDate(now) << std::endl;

    // Create a simple user interface for account creation and login eventually

    std::cout << "Welcome to the Calendar App!\nSelect an option:";
    while (true) {
        std::cout << "\n1. Create Account\n2. Login\n3. Exit\nChoice: ";
        std::string choice;
        std::getline(std::cin, choice);

        if (choice == "1")
            std::cout << calendar.createUser() << std::endl;
        else if (choice == "2")
            calendar.userLogin();
        else if (choice == "3")
            break;
    }
    return 0;
}