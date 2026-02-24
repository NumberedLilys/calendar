#include <fstream>
#include <sstream>
#include <cassert>
#include <iostream>
#include "UserFiles.h"
#include "TestCases.h"

void TestCases::testCreateUserSuccess() { // tests that a user can be created successfully with valid input

    std::ofstream("database/test_users.txt", std::ios::trunc).close(); // trunc static method clear test file before running test

    std::istringstream input( 
        "email@test.com\n"
        "user1\n"
        "1234\n"
        "1234\n"
    );

    std::ostringstream output; 

    UserFiles uf("database/test_users.txt"); 

    std::string result = uf.createUser(input, output); // Call createUser with test input and output streams

    assert(result == "User user1 created successfully!"); // Check that the result message is correct
}

void TestCases::testDuplicateUser() { // tests that creating a user with an email that already exists results in an error message

    std::ofstream file("database/test_users.txt"); 
    file << "email@test.com user1 1234\n"; // Add a user to the test file to create a duplicate scenario
    file.close();

    std::istringstream input(
        "email@test.com\n"
        "user1\n"
        "1234\n"
        "1234\n"
    );

    std::ostringstream output; 

    UserFiles uf("database/test_users.txt");

    std::string result = uf.createUser(input, output); // Call createUser with the same user details

    assert(result == "User already exists."); // Check that the result message indicates a duplicate user
}

void TestCases::testLoginSuccess() { // tests that a user can log in successfully with correct credentials
    std::ofstream file("database/test_users.txt");
    file << "email@test.com user1 1234\n";
    file.close();

    std::istringstream input(
        "user1\n"
        "1234\n"
    );

    std::ostringstream output;

    UserFiles uf("database/test_users.txt");

    bool success = uf.userLogin(input, output); // Call userLogin with correct credentials

    assert(success == true); // Check that the login was successful
}

void TestCases::testLoginFail() { // tests that a user cannot log in with incorrect credentials and receives an appropriate error message
    std::ofstream file("database/test_users.txt");
    file << "email@test.com user1 1234\n";
    file.close();

    std::istringstream input(
        "user1\n"
        "wrongpassword\n"
    );

    std::ostringstream output;

    UserFiles uf("database/test_users.txt");

    bool success = uf.userLogin(input, output);

    assert(success == false);
}