//
// Created by Ivan Shynkarenka on 05.06.2019
//

#include "benchmark/cppbenchmark.h"

#include "security/password_hashing_scrypt.h"

BENCHMARK("'scrypt' generate")
{
    static CppSecurity::ScryptPasswordHashing scrypt;
    std::string digest = scrypt.GenerateDigest("passw0rd");
}

BENCHMARK("'scrypt' validate")
{
    static CppSecurity::ScryptPasswordHashing scrypt;
    static std::string digest = scrypt.GenerateDigest("passw0rd");
    scrypt.ValidateDigest("passw0rd", digest);
}

BENCHMARK_MAIN()
