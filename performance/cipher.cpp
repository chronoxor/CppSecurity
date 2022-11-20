//
// Created by Ivan Shynkarenka on 20.11.2023
//

#include "benchmark/cppbenchmark.h"

#include "security/cipher.h"

using namespace CppSecurity;

BENCHMARK("Cipher encrypt")
{
    static Cipher cipher("passw0rd", Cipher::GenerateSalt());
    std::string encrypted = cipher.Encrypt("test");
}

BENCHMARK("Cipher decrypt")
{
    static Cipher cipher("passw0rd", Cipher::GenerateSalt());
    static std::string encrypted = cipher.Encrypt("test");
    std::string decrypted = cipher.Decrypt(encrypted);
}

BENCHMARK_MAIN()
