//
// Created by Ivan Shynkarenka on 20.11.2022
//

#include "test.h"

#include "security/cipher.h"

using namespace CppSecurity;

void TestCipher(CipherAlgorithm algorithm, size_t iterations)
{
    Cipher cipher("passw0rd", Cipher::GenerateSalt(), algorithm, iterations);

    // Encrypt string
    std::string encrypted = cipher.Encrypt("test");
    REQUIRE(encrypted.size() > 0);

    // Decrypt string
    std::string decrypted = cipher.Decrypt(encrypted);
    REQUIRE(decrypted.size() > 0);

    // Validate cipher
    REQUIRE(decrypted == "test");
}

TEST_CASE("Cipher", "[CppSecurity]")
{
    TestCipher(CipherAlgorithm::AES128, 1);
    TestCipher(CipherAlgorithm::AES192, 1);
    TestCipher(CipherAlgorithm::AES256, 1);
    TestCipher(CipherAlgorithm::ARIA128, 10);
    TestCipher(CipherAlgorithm::ARIA192, 10);
    TestCipher(CipherAlgorithm::ARIA256, 10);
    TestCipher(CipherAlgorithm::Camellia128, 100);
    TestCipher(CipherAlgorithm::Camellia192, 100);
    TestCipher(CipherAlgorithm::Camellia256, 100);
}
