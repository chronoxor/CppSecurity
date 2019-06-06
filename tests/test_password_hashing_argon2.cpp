//
// Created by Ivan Shynkarenka on 05.06.2019
//

#include "test.h"

#include "security/password_hashing_argon2.h"

using namespace CppSecurity;

TEST_CASE("'Argon2d' password hashing", "[CppSecurity]")
{
    Argon2dPasswordHashing scrypt;

    // Generate digest
    std::string digest = scrypt.GenerateEncodedDigest("passw0rd");
    REQUIRE(digest.size() > 0);

    // Validate digest
    REQUIRE(!scrypt.ValidateEncodedDigest("password", digest));
    REQUIRE(scrypt.ValidateEncodedDigest("passw0rd", digest));
}

TEST_CASE("'Argon2i' password hashing", "[CppSecurity]")
{
    Argon2iPasswordHashing scrypt;

    // Generate digest
    std::string digest = scrypt.GenerateEncodedDigest("passw0rd");
    REQUIRE(digest.size() > 0);

    // Validate digest
    REQUIRE(!scrypt.ValidateEncodedDigest("password", digest));
    REQUIRE(scrypt.ValidateEncodedDigest("passw0rd", digest));
}

TEST_CASE("'Argon2id' password hashing", "[CppSecurity]")
{
    Argon2idPasswordHashing scrypt;

    // Generate digest
    std::string digest = scrypt.GenerateEncodedDigest("passw0rd");
    REQUIRE(digest.size() > 0);

    // Validate digest
    REQUIRE(!scrypt.ValidateEncodedDigest("password", digest));
    REQUIRE(scrypt.ValidateEncodedDigest("passw0rd", digest));
}
