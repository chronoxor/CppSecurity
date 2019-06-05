//
// Created by Ivan Shynkarenka on 05.06.2019
//

#include "test.h"

#include "security/password_hashing_scrypt.h"

using namespace CppSecurity;

TEST_CASE("'scrypt' password hashing", "[CppSecurity]")
{
    CppSecurity::ScryptPasswordHashing scrypt;

    // Generate digest
    std::string digest = scrypt.GenerateDigest("passw0rd");
    REQUIRE(digest.size() > 0);

    // Validate digest
    REQUIRE(!scrypt.ValidateDigest("password", digest));
    REQUIRE(scrypt.ValidateDigest("passw0rd", digest));
}
