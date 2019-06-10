/*!
    \file password_generator.cpp
    \brief Password generator implementation
    \author Ivan Shynkarenka
    \date 10.06.2019
    \copyright MIT License
*/

#include "security/password_generator.h"

#include "errors/exceptions.h"
#include "memory/memory.h"

#include <cassert>

namespace CppSecurity {

PasswordGenerator::PasswordGenerator(size_t length, PasswordFlags flags)
    : _length(length), _flags(flags)
{
    assert((length >= 6) && "Password should be at least 6 symbols!");
    if (length < 6)
        throwex CppCommon::SecurityException("Invalid password length!");

    assert((flags != PasswordFlags::none) && "Password flags should not be empty!");
    if (flags == PasswordFlags::none)
        throwex CppCommon::SecurityException("Invalid password flags!");
}

std::password PasswordGenerator::Generate() const
{
    std::string cache;
    if ((flags() & PasswordFlags::lower) != 0)
        cache += "abcdefghijklmnopqrstuvwxyz";
    if ((flags() & PasswordFlags::upper) != 0)
        cache += "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    if ((flags() & PasswordFlags::digits) != 0)
        cache += "012345678901234567890123456789";
    if ((flags() & PasswordFlags::symbols) != 0)
        cache += "!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~";

    std::password result(length(), 0);
    CppCommon::Memory::CryptoFill(result.data(), result.size());
    for (size_t i = 0; i < result.size(); ++i)
        result[i] = cache[result[i] % cache.size()];
    return result;
}

bool PasswordGenerator::Validate(std::string_view password) const
{
    // Validate password length requirement
    if (password.size() < length())
        return false;

    // Collect password flags requirements
    bool lower = false;
    bool upper = false;
    bool digits = false;
    bool symbols = false;
    for (size_t i = 0; i < password.size(); ++i)
    {
        if ((password[i] >= 'a') && (password[i] <= 'z'))
            lower = true;
        else if ((password[i] >= 'A') && (password[i] <= 'Z'))
            upper = true;
        else if ((password[i] >= '0') && (password[i] <= '9'))
            digits = true;
        else if ((password[i] == '!') || (password[i] == '"') || (password[i] == '#') || (password[i] == '$') || (password[i] == '%') ||
                 (password[i] == '&') || (password[i] == '\'') || (password[i] == '(') || (password[i] == ')') || (password[i] == '*') ||
                 (password[i] == '+') ||(password[i] == ',') || (password[i] == '-') || (password[i] == '.') || (password[i] == '/') ||
                 (password[i] == ':') || (password[i] == ';') || (password[i] == '<') || (password[i] == '=') || (password[i] == '>') ||
                 (password[i] == '?') || (password[i] == '@') || (password[i] == '[') || (password[i] == '\\') || (password[i] == ']') ||
                 (password[i] == '^') || (password[i] == '_') || (password[i] == '`') || (password[i] == '{') || (password[i] == '|') ||
                 (password[i] == '}') || (password[i] == '~'))
            symbols = true;
        else
            return false;
    }

    // Validate password flags requirements
    if (lower && ((flags() & PasswordFlags::lower) == 0))
        return false;
    if (upper && ((flags() & PasswordFlags::upper) == 0))
        return false;
    if (digits && ((flags() & PasswordFlags::digits) == 0))
        return false;
    if (symbols && ((flags() & PasswordFlags::symbols) == 0))
        return false;

    return true;
}

} // namespace CppSecurity
