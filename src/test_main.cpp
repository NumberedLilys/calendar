#include "TestCases.h"

int main() {
    TestCases::testCreateUserSuccess();
    TestCases::testDuplicateUser();
    TestCases::testLoginSuccess();
    TestCases::testLoginFail();

    return 0;
}