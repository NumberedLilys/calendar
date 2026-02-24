#include "CalendarLibraries.h" // All libraries needed in the Calendar.h file and main file
#include "Calendar.h"
#include "UserFiles.h"
#include "TestCases.h"

// class TaskNotifications {
//     // Notification class, sends notifications for tasks/events. Put in .h file later
// };

// Run g++ -std=c++17 calendar_project.cpp UserFiles.cpp TestCases.cpp Calendar.cpp -o calendar_app to compile
// Then run calendar_app to execute

// OR, using makefile, mingw32-make to compile in terminal and mingw32-make run to run the program


int main() {

    TestCases::testCreateUserSuccess();
    TestCases::testDuplicateUser();
    TestCases::testLoginSuccess();
    TestCases::testLoginFail();

    auto now = std::chrono::system_clock::now();
    Calendar calendar(2026, 1, 1);
    std::cout << "Current date: " << calendar.displayDate(now) << std::endl;

    // Create a simple user interface for account creation and login eventually

    std::cout << "Welcome to the Calendar App!\nSelect an option:";
    while (true) {
        std::cout << "\n1. Create Account\n2. Login\n3. Exit\nChoice: ";
        std::string choice;
        std::getline(std::cin, choice);

        if (choice == "1"){
            UserFiles userFiles("users.txt");
            std::cout << userFiles.createUser(std::cin, std::cout) << std::endl;
        }
        else if (choice == "2"){
            UserFiles userFiles("users.txt");
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
    return 0;
}