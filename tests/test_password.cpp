//
// Created by Ivan Shynkarenka on 04.06.2019
//

#include "test.h"

#include "security/password.h"

#include <cstring>

using namespace CppSecurity;

TEST_CASE("Password", "[CppSecurity]")
{
    char* raw = nullptr;
    {
        std::password password("password");
        raw = password.data();
        REQUIRE(std::strcmp(raw, "password") == 0);
    }
    REQUIRE(std::strcmp(raw, "password") != 0);
}
