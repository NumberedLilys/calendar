#include "CalendarLibraries.h"
#include "UserFiles.h"

UserFiles::UserFiles(const std::string& filename) : userFile(filename) {}

void UserFiles::getLoginDetails(std::istream& in,
                std::ostream& out,
                std::string& username,
                std::string& password){

    out << "Enter username: ";
    std::getline(in, username);
    out << "Enter password: ";
    std::getline(in, password);
}

void UserFiles::getSignupDetails(std::istream& in,
                std::ostream& out,
                std::string& email,
                std::string& username,
                std::string& password) {

    while (true) {
        out << "Enter email: ";
        std::getline(in, email);

        out << "Enter username: ";
        std::getline(in, username);

        out << "Enter password: ";
        std::getline(in, password);

        if (!email.empty() && !username.empty() && !password.empty()) {
            break;
        }

        out << "Error: All fields are required.\n\n";
    }
}

std::string UserFiles::createUser(std::istream& in, std::ostream& out) {
    std::string username;
    std::string password;
    std::string email;

    getSignupDetails(in, out, email, username, password); // initial account creation, requires email and username and password, with password confirmation.

    std::ifstream check_file(userFile);
    std::string line;
    if (check_file.is_open()) {
        while (std::getline(check_file, line)) {
            std::istringstream iss(line);
            std::string stored_email, stored_username, stored_password;
            iss >> stored_email >> stored_username >> stored_password;

            if (stored_email == email && stored_username == username && stored_password == password) {
                return "User already exists. Log in instead.";
            }

            if (stored_email == email) {
                return "Email already in use. Try a different email.";
            }

            if (stored_username == username) {
                return "Username already exists. Try a different username.";
            }

        }
    }

    out << "Please confirm your password: ";
    std::string confirm_password;
    std::getline(in, confirm_password);

    while (confirm_password != password) {
        out << "Passwords do not match. Please try again.\n";
        out << "Please confirm your password: ";

        if (!std::getline(in, confirm_password)) {
            return "Password confirmation failed.";
        }
    }
    
    std::ofstream user_file(userFile, std::ios::app);
    if (!user_file.is_open()) {
        return "Error opening user file.";
    }

    user_file << email << " " << username << " " << password << std::endl;
    user_file.close();

    return "User " + username + " created successfully!";
}

bool UserFiles::userLogin(std::istream& in, std::ostream& out) { 
    std::ifstream user_file(userFile); // Read user data from file
    std::string line;
    std::vector<User> users;

    if (!user_file.is_open()) { // Error handling for file opening
        out << "Error opening user file.\n";
        return false;
    } else {
        while (std::getline(user_file, line)) { // Read each line from file
            
            // Get data from file and store in vector of User structs, then check against input
            std::istringstream iss(line);
            User u;
            iss >> u.actual_email >> u.actual_username >> u.actual_password;
            users.push_back(u);
        }
    }

    std::string input_username;
    std::string input_password;
    getLoginDetails(in, out, input_username, input_password); // Get user input for login, only needs username/email and password

    for (const User& user : users) {
        if ((user.actual_username == input_username || user.actual_email == input_username) && user.actual_password == input_password) {
            out << "Login successful!" << std::endl;
            return true;
        }
    }
    
    out << "Login failed. Please check your username and password." << std::endl;
    return false;
}