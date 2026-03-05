#include <fstream>
#include <sstream>
#include <cassert>
#include <iostream>
#include "UserFiles.h"
#include "TestCases.h"

namespace { // create a local namespace to remain internal to this file and avoid conflicts with other files
    const std::string TEST_FILE = "database/test_users.txt";

    void resetTestFile() { // Helper function to reset the test file before each test case
        std::ofstream file(TEST_FILE, std::ios::trunc);
        file.close();
    }
}

void TestCases::testCreateUserSuccess() { // tests that a user can be created successfully with valid input

    resetTestFile();

    std::istringstream input( // Simulate user input for creating a new user
        "email@test.com"
        "user1"
        "1234"
        "1234"
    );

    std::ostringstream output; 

    UserFiles uf(TEST_FILE); 

    std::string result = uf.createUser(input, output); // Call createUser with test input and output streams

    assert(result == "User user1 created successfully!"); // Check that the result message is correct
}

void TestCases::testDuplicateUser() { // tests that creating a user with an email that already exists results in an error message

    resetTestFile();

    std::ofstream file(TEST_FILE); 
    file << "email@test.com user1 1234\n"; // Add a user to the test file to create a duplicate scenario
    file.close();

    std::istringstream input(
        "email@test.com\n"
        "user1\n"
        "1234\n"
        "1234\n"
    );

    std::ostringstream output; // Create an output stream to capture the output from createUser

    UserFiles uf(TEST_FILE); // Create a UserFiles instance with the test file

    std::string result = uf.createUser(input, output); // Call createUser with the same user details

    assert(result == "User already exists. Log in instead."); // Check that the result message indicates a duplicate user
}

void TestCases::testLoginSuccess() { // tests that a user can log in successfully with correct credentials
    
    resetTestFile();
    std::ofstream file(TEST_FILE); 
    file << "email@test.com user1 1234\n";
    file.close();

    std::istringstream input(
        "user1\n"
        "1234\n"
    );

    std::ostringstream output;

    UserFiles uf(TEST_FILE);

    bool success = uf.userLogin(input, output); // Call userLogin with correct credentials

    assert(success == true); // Check that the login was successful
}

void TestCases::testLoginFail() { // tests that a user cannot log in with incorrect credentials and receives an appropriate error message
    
    resetTestFile();
    std::ofstream file(TEST_FILE);
    file << "email@test.com user1 1234\n";
    file.close();

    std::istringstream input(
        "user1\n"
        "wrongpassword\n"
    );

    std::ostringstream output;

    UserFiles uf(TEST_FILE);

    bool success = uf.userLogin(input, output);

    assert(success == false);
}

void TestCases::testDuplicateEmail() {

    resetTestFile();
    std::ofstream file(TEST_FILE, std::ios::trunc);
    file << "email@test.com user1 1234\n";
    file.close();

    std::istringstream input(
        "email@test.com\n"   // same email
        "newuser\n"          // different username
        "pass\n"
        "pass\n"
    );

    std::ostringstream output;

    UserFiles uf(TEST_FILE);

    std::string result = uf.createUser(input, output);

    assert(result == "Email already in use. Try a different email.");
}

void TestCases::testDuplicateUsername() {

    resetTestFile();
    std::ofstream file(TEST_FILE, std::ios::trunc);
    file << "email@test.com user1 1234\n";
    file.close();

    std::istringstream input(
        "new@email.com\n"  // different email
        "user1\n"          // same username
        "pass\n"
        "pass\n"
    );

    std::ostringstream output;

    UserFiles uf(TEST_FILE);

    std::string result = uf.createUser(input, output);

    assert(result == "Username already exists. Try a different username.");
}