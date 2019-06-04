/*!
    \file password_hashing_scrypt.cpp
    \brief 'scrypt' password hashing algorithm implementation
    \author Ivan Shynkarenka
    \date 04.06.2019
    \copyright MIT License
*/

#include "security/password_hashing_scrypt.h"

#include "errors/exceptions.h"
#include "utility/countof.h"

#include <cassert>

#include <libscrypt.h>

namespace CppCommon {

std::pair<std::string, std::string> ScryptPasswordHashing::Generate(std::string_view password, size_t hash_length, size_t salt_length) const
{
    assert((hash_length >= 8) && "Hash length should be at least 8 bytes!");
    assert((salt_length >= 8) && "Salt length should be at least 8 bytes!");
    if (hash_length < 8)
        throwex SecurityException("Invalid hash length!");
    if (salt_length < 8)
        throwex SecurityException("Invalid salt length!");

    // Generate the unique password salt
    std::string salt(salt_length, 0);
#ifndef _MSC_VER
    if (libscrypt_salt_gen(salt.data(), salt.size()) != 0)
        throwex SecurityException("Cannot generate 'scrypt' salt!");
#else
    const char chars[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
    for (size_t i = 0; i < salt.size(); ++i)
        salt[i] = chars[i % CppCommon::countof(chars)];
#endif

    // Generate the strong password hash
    std::string hash(hash_length, 0);
    if (libscrypt_scrypt((const uint8_t*)password.data(), password.size(), (const uint8_t*)salt.data(), salt.size(), 1024, 8, 1, (uint8_t*)hash.data(), hash.size()) != 0)
        throwex SecurityException("Cannot generate 'scrypt' hash!");

    // Return successfully generated hash and salt pair
    return std::make_pair(hash, salt);
}

bool ScryptPasswordHashing::Validate(std::string_view password, std::string_view hash, std::string_view salt) const
{
    // Calculate the digest for the given password and salt
    std::string digest(hash.size(), 0);
    if (libscrypt_scrypt((const uint8_t*)password.data(), password.size(), (const uint8_t*)salt.data(), salt.size(), 1024, 8, 1, (uint8_t*)digest.data(), digest.size()) != 0)
        throwex SecurityException("Cannot calculate 'scrypt' hash!");

    // Compare the digest with the given hash
    return (digest == hash);
}

} // namespace CppCommon
