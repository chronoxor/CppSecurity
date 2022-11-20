//
// Created by Ivan Shynkarenka on 05.06.2019
//

#include "test.h"

#include "security/password_hashing_pbkdf2.h"

using namespace CppSecurity;

void TestPBKDF2(size_t hash_length, size_t salt_length, PBKDF2 algorithm, size_t iterations)
{
    PBKDF2PasswordHashing pbkdf2(hash_length, salt_length, algorithm, iterations);

    // Generate digest
    std::string digest = pbkdf2.GenerateEncodedDigest("passw0rd");
    REQUIRE(digest.size() > 0);

    // Validate digest
    REQUIRE(!pbkdf2.ValidateEncodedDigest("password", digest));
    REQUIRE(pbkdf2.ValidateEncodedDigest("passw0rd", digest));
}

TEST_CASE("'PBKDF2' password hashing", "[CppSecurity]")
{
    TestPBKDF2(8, 8, PBKDF2::HMAC_SHA1, 1);
    TestPBKDF2(8, 8, PBKDF2::HMAC_SHA256, 1);
    TestPBKDF2(8, 8, PBKDF2::HMAC_SHA512, 1);
    TestPBKDF2(16, 16, PBKDF2::HMAC_SHA1, 10);
    TestPBKDF2(16, 16, PBKDF2::HMAC_SHA256, 10);
    TestPBKDF2(16, 16, PBKDF2::HMAC_SHA512, 10);
    TestPBKDF2(32, 32, PBKDF2::HMAC_SHA1, 100);
    TestPBKDF2(32, 32, PBKDF2::HMAC_SHA256, 100);
    TestPBKDF2(32, 32, PBKDF2::HMAC_SHA512, 100);
    TestPBKDF2(64, 64, PBKDF2::HMAC_SHA1, 1000);
    TestPBKDF2(64, 64, PBKDF2::HMAC_SHA256, 1000);
    TestPBKDF2(64, 64, PBKDF2::HMAC_SHA512, 1000);
}
