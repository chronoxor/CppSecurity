//
// Created by Ivan Shynkarenka on 05.06.2019
//

#include "test.h"

#include "security/password_hashing_pbkdf2.h"

using namespace CppSecurity;

TEST_CASE("'PBKDF2' password hashing", "[CppSecurity]")
{
    PBKDF2PasswordHashing pbkdf2;

    // Generate digest
    std::string digest = pbkdf2.GenerateDigest("passw0rd");
    REQUIRE(digest.size() > 0);

    // Validate digest
    REQUIRE(!pbkdf2.Validate("password", digest));
    REQUIRE(pbkdf2.Validate("passw0rd", digest));
}
