//
// Created by Ivan Shynkarenka on 05.06.2019
//

#include "benchmark/cppbenchmark.h"

#include "security/password_hashing_bcrypt.h"

using namespace CppSecurity;

BENCHMARK("'bcrypt' generate")
{
    static BcryptPasswordHashing bcrypt;
    std::string digest = bcrypt.GenerateDigest("passw0rd");
}

BENCHMARK("'bcrypt' validate")
{
    static BcryptPasswordHashing bcrypt;
    static std::string digest = bcrypt.GenerateDigest("passw0rd");
    bcrypt.ValidateDigest("passw0rd", digest);
}

BENCHMARK_MAIN()
