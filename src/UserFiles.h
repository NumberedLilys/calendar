#pragma once
#include <string>   // for std::string
#include <iostream> // for std::istream and std::ostream
#include <vector>

class UserFiles {
private:
    struct User {
        std::string actual_username;
        std::string actual_password;
        std::string actual_email;
    };

    std::string userFile;

public:
    UserFiles(const std::string& filename);
    
    void getLoginDetails(std::istream& in, std::ostream& out,
                         std::string& username, std::string& password);

    void getSignupDetails(std::istream& in, std::ostream& out,
                          std::string& email, std::string& username, std::string& password);

    std::string createUser(std::istream& in, std::ostream& out);

    bool userLogin(std::istream& in, std::ostream& out);
};