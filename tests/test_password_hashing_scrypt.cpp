//
// Created by Ivan Shynkarenka on 05.06.2019
//

#include "test.h"

#include "security/password_hashing_scrypt.h"

using namespace CppSecurity;

TEST_CASE("'scrypt' password hashing", "[CppSecurity]")
{
    ScryptPasswordHashing scrypt;

    // Generate digest
    std::string digest = scrypt.GenerateEncodedDigest("passw0rd");
    REQUIRE(digest.size() > 0);

    // Validate digest
    REQUIRE(!scrypt.ValidateEncodedDigest("password", digest));
    REQUIRE(scrypt.ValidateEncodedDigest("passw0rd", digest));
}
