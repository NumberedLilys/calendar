// #include <iostream>
// #include <chrono>
// #include <ctime>
// #include <string>
// #include <sstream>

// #include <iomanip>
// #include <vector>
// #include <fstream>
// #include "Libraries.h"

class Calendar {
    private:
        int year;
        int month;
        int day;

    public:
        Calendar(int y, int m, int d): year(y), month(m), day(d) {};
        std::string displayDate(std::chrono::system_clock::time_point tp) {
            std::time_t t = std::chrono::system_clock::to_time_t(tp); // changes time_point to time_t   
            std::tm* now = std::localtime(&t); // Converts to local time

            std::ostringstream ss;
            ss << std::put_time(now, "%Y-%m-%d"); // Formats the date in YYYY-MM-DD format using stringstream
            return ss.str();


        }
        // Put into a .h file later, add extra functionalities. Mainly display and basics for the calendar application
        // Figure out how to get the proper date/time, maybe a library?
        std::string userDetails(std::string& email, std::string& username, std::string& password) { // Function to get user details, will be used for account creation and login eventually

            if (email == "login") { // If user is logging in, only ask for username and password, not email. Email is used as unique identifier for account creation, but not necessary for login.
                std::cout << "Enter username or email: ";
                std::getline(std::cin, email);
                username = ""; // username empty, login only needs one.

            } else { // If user is creating account, ask for email AND username
                std::cout << "Enter email: ";
                std::getline(std::cin, email);
                std::cout << "Enter username: ";
                std::getline(std::cin, username);
            }

            std::cout << "Enter password: "; // Password input for both login and account creation
            std::getline(std::cin, password);

            return username + " " + password + " " + email;
        }

        std::string createUser() {
            std::string username;
            std::string password;
            std::string email;

            userDetails(email, username, password); // initial account creation, requires email and username and password, with password confirmation.

            std::cout << "Please confirm your password: ";
            std::string confirm_password;
            std::getline(std::cin, confirm_password);

            while (confirm_password != password) {  // Password confirmation loop
                std::cout << "Passwords do not match. Please try again." << std::endl;
                std::cout << "Please confirm your password: ";
                std::getline(std::cin, confirm_password);
            }

            std::ofstream user_file("users.txt"); // Append user data to file in database. File will exist already
            user_file << email << " " << username << " " << password << std::endl; // Stores data in a file for later retrieval
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

                    // TEST CASE ==================
                    std::cout << line << std::endl; // DELETE LATER, just to check that we're reading the file correctly !!!!!!!!!!
                    // TEST CASE ==================
                    
                    // Get data from file and store in vector of User structs, then check against input
                    std::istringstream iss(line);
                    User u;
                    iss >> u.actual_email >> u.actual_username >> u.actual_password;
                    users.push_back(u);
                }
            }

            std::string input_username;
            std::string input_password;
            std::string input_email = "login"; // Set email to "login" to indicate that we're logging in, not creating account
            userDetails(input_email, input_username, input_password); // Get user input for login, only needs username/email and password

            for (const User& user : users) {
                if ((user.actual_username == input_username || user.actual_email == input_username) && user.actual_password == input_password) {
                    std::cout << "Login successful!" << std::endl;
                    return true;
                }
            }
            
            std::cout << "Login failed. Please check your username/email and password." << std::endl;
            return false;
        }

};