//
// Created by Ivan Shynkarenka on 11.06.2019
//

#include "benchmark/cppbenchmark.h"

#include "security/google_authenticator.h"

using namespace CppSecurity;

BENCHMARK("Generate Google Authenticator secret")
{
    static GoogleAuthenticator authenticator;
    std::password secret = authenticator.GenerateSecret();
}

BENCHMARK("Generate Google Authenticator token")
{
    static GoogleAuthenticator authenticator;
    static std::password secret = authenticator.GenerateSecret();
    authenticator.GenerateToken(secret);
}

BENCHMARK_MAIN()
