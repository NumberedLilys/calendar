#include "CalendarLibraries.h" // All libraries needed in the Calendar.h file and main file
#include "calendar.h"
#include "UserFiles.h"
#include "TestCases.h"

// class TaskNotifications {
//     // Notification class, sends notifications for tasks/events. Put in .h file later
// };

// using makefile, mingw32-make to compile in terminal and mingw32-make run to run the program.
// E.g. cd calendar, mingw32-make, mingw32-make run in terminal

// to run tests, mingw32-make test in terminal, which compiles test_main.cpp and runs the tests


int main() {

    auto now = std::chrono::system_clock::now();
    Calendar calendar(2026, 1, 1);
    std::cout << "Current date: " << calendar.displayDate(now) << std::endl;

    std::cout << "Welcome to the Calendar App!\nSelect an option:";
    while (true) {
        std::cout << "\n1. Create Account\n2. Login\n3. Exit\nChoice: ";
        std::string choice;
        std::getline(std::cin, choice);

        if (choice == "1"){
            UserFiles userFiles("database/users.txt");
            std::cout << userFiles.createUser(std::cin, std::cout) << std::endl;
        }
        else if (choice == "2"){
            UserFiles userFiles("database/users.txt");
            userFiles.userLogin(std::cin, std::cout); // eventually redirect to calendar interface after successful login
        }
        else if (choice == "3"){
            std::cout << "Exiting the application. Goodbye!\n";
            break;
        }
        else {
            std::cout << "Invalid choice. Please try again.\n";
        }
    }
}
