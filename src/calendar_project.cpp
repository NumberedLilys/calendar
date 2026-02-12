// #include <iostream>
// #include <chrono>
// #include <ctime>
// #include <string>
// #include <sstream>
// #include <iomanip> // All in Calendar.h

// Maybe include a list of libraries in a Libraries.h file and just #include "Libraries.h" at top of page?

#include "Calendar.h"

#include <vector>
#include <fstream>


class TaskNotifications {
    // Notification class, sends notifications for tasks/events. Put in .h file later
};

std::string createUser() {
    std::string username;
    std::string password;
    std::string email;

    std::cout << "Enter email: ";
    std::getline(std::cin, email);
    std::cout << "Enter username: ";
    std::getline(std::cin, username);
    std::cout << "Enter password: ";
    std::getline(std::cin, password);

    std::cout << "Please confirm your password: ";
    std::string confirm_password;
    std::getline(std::cin, confirm_password);

    while (confirm_password != password) {  // Password confirmation loop
        std::cout << "Passwords do not match. Please try again." << std::endl;
        std::cout << "Please confirm your password: ";
        std::getline(std::cin, confirm_password);
    }

    std::ofstream user_file("users.txt"); // Append user data to file
    user_file << email << " " << username << " " << password << std::endl;
    user_file.close();
    return "User created successfully!" + username;
}

struct User { // Struct to hold user data
    std::string actual_username;
    std::string actual_password;
    std::string actual_email;
};

bool userLogin() { 
    std::ifstream user_file("users.txt"); // Read user data from file
    std::string line;
    std::vector<User> users;

    if (!user_file.is_open()) { // Error handling for file opening
        std::cerr << "Error opening user file." << std::endl;
        return false;
    } else {
        while (std::getline(user_file, line)) { // Read each line from file
            std::cout << line << std::endl;
            // Get data from file and store in vector of User structs, then check against input
            std::istringstream iss(line);
            User u;
            iss >> u.actual_email >> u.actual_username >> u.actual_password;
            users.push_back(u);
        }
    }

    std::string input_username;
    std::string input_password;
    std::cout << "Enter username or email: ";
    std::getline(std::cin, input_username);
    std::cout << "Enter password: ";
    std::getline(std::cin, input_password);

    for (const User& user : users) {
        if ((user.actual_username == input_username || user.actual_email == input_username) && user.actual_password == input_password) {
            std::cout << "Login successful!" << std::endl;
            return true;
        }
    }
    
    std::cout << "Login failed. Please check your username/email and password." << std::endl;
    return false;
}

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
        createUser();
    } else if (response == "y") {
        std::cout << "Login:" << std::endl;
        userLogin();
    }

    return 0;
}