//
// Created by Ivan Shynkarenka on 10.06.2019
//

#include "test.h"

#include "security/password_generator.h"

using namespace CppSecurity;

TEST_CASE("Password generator", "[CppSecurity]")
{
    PasswordGenerator generator1(6, PasswordFlags::lower);
    std::password password1 = generator1.Generate();
    REQUIRE(!generator1.Validate(""));
    REQUIRE(!generator1.Validate("abc"));
    REQUIRE(!generator1.Validate("1234567890"));
    REQUIRE(generator1.Validate("abcdefghij"));
    REQUIRE(generator1.Validate("abcABC123^&%"));
    REQUIRE(generator1.Validate(password1));

    PasswordGenerator generator2(8, PasswordFlags::lower | PasswordFlags::upper);
    std::password password2 = generator2.Generate();
    REQUIRE(!generator2.Validate(""));
    REQUIRE(!generator2.Validate("abc"));
    REQUIRE(!generator2.Validate("1234567890"));
    REQUIRE(generator2.Validate("abcdeFGHIJ"));
    REQUIRE(generator2.Validate("abcABC123^&%"));
    REQUIRE(generator2.Validate(password2));

    PasswordGenerator generator3(10, PasswordFlags::lower | PasswordFlags::upper | PasswordFlags::digits);
    std::password password3 = generator3.Generate();
    REQUIRE(!generator3.Validate(""));
    REQUIRE(!generator3.Validate("abc"));
    REQUIRE(!generator3.Validate("1234567890"));
    REQUIRE(generator3.Validate("abcABC1230"));
    REQUIRE(generator3.Validate("abcABC123^&%"));
    REQUIRE(generator3.Validate(password3));

    PasswordGenerator generator4(10, PasswordFlags::lower | PasswordFlags::upper | PasswordFlags::digits | PasswordFlags::symbols);
    std::password password4 = generator4.Generate();
    REQUIRE(!generator4.Validate(""));
    REQUIRE(!generator4.Validate("abc"));
    REQUIRE(!generator4.Validate("1234567890"));
    REQUIRE(generator4.Validate("abcABC123^&%"));
    REQUIRE(generator4.Validate(password4));
}
