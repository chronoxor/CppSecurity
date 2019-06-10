//
// Created by Ivan Shynkarenka on 10.06.2019
//

#include "benchmark/cppbenchmark.h"

#include "security/password_generator.h"

using namespace CppSecurity;

BENCHMARK("Generate password")
{
    static PasswordGenerator generator;
    std::password password = generator.Generate();
}

BENCHMARK("Validate password")
{
    static PasswordGenerator generator;
    static std::password password = generator.Generate();
    generator.Validate(password);
}

BENCHMARK_MAIN()
