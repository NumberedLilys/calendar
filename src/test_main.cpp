#include "TestCases.h"
#include <iostream>

int main() {
    // TestCases::testCreateUserSuccess();
    TestCases::testDuplicateUser();
    TestCases::testDuplicateEmail();
    TestCases::testDuplicateUsername();
    TestCases::testLoginSuccess();
    TestCases::testLoginFail();
    std::cout << "All tests passed successfully!" << std::endl;
    return 0;
}