//
// Created by Ivan Shynkarenka on 05.06.2019
//

#include "benchmark/cppbenchmark.h"

#include "security/password_hashing_pbkdf2.h"

using namespace CppSecurity;

BENCHMARK("'PBKDF2' generate")
{
    static PBKDF2PasswordHashing pbkdf2;
    std::string digest = pbkdf2.GenerateDigest("passw0rd");
}

BENCHMARK("'PBKDF2' validate")
{
    static PBKDF2PasswordHashing pbkdf2;
    static std::string digest = pbkdf2.GenerateDigest("passw0rd");
    pbkdf2.ValidateDigest("passw0rd", digest);
}

BENCHMARK_MAIN()
