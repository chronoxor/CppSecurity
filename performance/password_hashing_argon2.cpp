//
// Created by Ivan Shynkarenka on 05.06.2019
//

#include "benchmark/cppbenchmark.h"

#include "security/password_hashing_argon2.h"

using namespace CppSecurity;

BENCHMARK("'Argon2d' generate")
{
    static Argon2dPasswordHashing scrypt;
    std::string digest = scrypt.GenerateDigest("passw0rd");
}

BENCHMARK("'Argon2d' validate")
{
    static Argon2dPasswordHashing scrypt;
    static std::string digest = scrypt.GenerateDigest("passw0rd");
    scrypt.ValidateDigest("passw0rd", digest);
}

BENCHMARK("'Argon2i' generate")
{
    static Argon2iPasswordHashing scrypt;
    std::string digest = scrypt.GenerateDigest("passw0rd");
}

BENCHMARK("'Argon2i' validate")
{
    static Argon2iPasswordHashing scrypt;
    static std::string digest = scrypt.GenerateDigest("passw0rd");
    scrypt.ValidateDigest("passw0rd", digest);
}

BENCHMARK("'Argon2id' generate")
{
    static Argon2idPasswordHashing scrypt;
    std::string digest = scrypt.GenerateDigest("passw0rd");
}

BENCHMARK("'Argon2id' validate")
{
    static Argon2idPasswordHashing scrypt;
    static std::string digest = scrypt.GenerateDigest("passw0rd");
    scrypt.ValidateDigest("passw0rd", digest);
}

BENCHMARK_MAIN()
