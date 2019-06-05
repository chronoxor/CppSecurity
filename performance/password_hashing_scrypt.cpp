//
// Created by Ivan Shynkarenka on 05.06.2019
//

#include "benchmark/cppbenchmark.h"

#include "security/password_hashing_scrypt.h"

using namespace CppSecurity;

BENCHMARK("'scrypt' generate")
{
    static ScryptPasswordHashing scrypt;
    std::string digest = scrypt.GenerateDigest("passw0rd");
}

BENCHMARK("'scrypt' validate")
{
    static ScryptPasswordHashing scrypt;
    static std::string digest = scrypt.GenerateDigest("passw0rd");
    scrypt.Validate("passw0rd", digest);
}

BENCHMARK_MAIN()
