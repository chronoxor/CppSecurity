/*!
    \file password_hashing_argon2.cpp
    \brief 'Argon2' password hashing algorithm implementation
    \author Ivan Shynkarenka
    \date 05.06.2019
    \copyright MIT License
*/

#include "security/password_hashing_argon2.h"

#include "errors/exceptions.h"
#include "utility/countof.h"

#include <cassert>

#include <argon2.h>

namespace CppSecurity {

std::string Argon2dPasswordHashing::_name = "Argon2d";
std::string Argon2iPasswordHashing::_name = "Argon2i";
std::string Argon2idPasswordHashing::_name = "Argon2id";

Argon2dPasswordHashing::Argon2dPasswordHashing(size_t hash_length, size_t salt_length, uint32_t t, uint32_t m, uint32_t p)
    : PasswordHashing(hash_length, salt_length),
      _t(t), _m(m), _p(p)
{
}

std::pair<std::string, std::string> Argon2dPasswordHashing::Generate(std::string_view password) const
{
    // Generate the unique password salt
    std::string salt(salt_length(), 0);
    const char chars[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
    for (size_t i = 0; i < salt.size(); ++i)
        salt[i] = chars[i % CppCommon::countof(chars)];

    // Generate the strong password hash
    std::string hash(hash_length(), 0);
    if (argon2d_hash_raw(t(), m(), p(), password.data(), password.size(), salt.data(), salt.size(), hash.data(), hash.size()) != ARGON2_OK)
        throwex CppCommon::SecurityException("Cannot generate 'Argon2d' hash!");

    // Return successfully generated hash and salt pair
    return std::make_pair(hash, salt);
}

bool Argon2dPasswordHashing::Validate(std::string_view password, std::string_view hash, std::string_view salt) const
{
    // Calculate the digest for the given password and salt
    std::string digest(hash.size(), 0);
    if (argon2d_hash_raw(t(), m(), p(), password.data(), password.size(), salt.data(), salt.size(), digest.data(), digest.size()) != ARGON2_OK)
        throwex CppCommon::SecurityException("Cannot calculate 'Argon2d' hash!");

    // Compare the digest with the given hash
    return (digest == hash);
}

std::pair<std::string, std::string> Argon2iPasswordHashing::Generate(std::string_view password) const
{
    // Generate the unique password salt
    std::string salt(salt_length(), 0);
    const char chars[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
    for (size_t i = 0; i < salt.size(); ++i)
        salt[i] = chars[i % CppCommon::countof(chars)];

    // Generate the strong password hash
    std::string hash(hash_length(), 0);
    if (argon2i_hash_raw(t(), m(), p(), password.data(), password.size(), salt.data(), salt.size(), hash.data(), hash.size()) != ARGON2_OK)
        throwex CppCommon::SecurityException("Cannot generate 'Argon2i' hash!");

    // Return successfully generated hash and salt pair
    return std::make_pair(hash, salt);
}

bool Argon2iPasswordHashing::Validate(std::string_view password, std::string_view hash, std::string_view salt) const
{
    // Calculate the digest for the given password and salt
    std::string digest(hash.size(), 0);
    if (argon2i_hash_raw(t(), m(), p(), password.data(), password.size(), salt.data(), salt.size(), digest.data(), digest.size()) != ARGON2_OK)
        throwex CppCommon::SecurityException("Cannot calculate 'Argon2i' hash!");

    // Compare the digest with the given hash
    return (digest == hash);
}

std::pair<std::string, std::string> Argon2idPasswordHashing::Generate(std::string_view password) const
{
    // Generate the unique password salt
    std::string salt(salt_length(), 0);
    const char chars[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
    for (size_t i = 0; i < salt.size(); ++i)
        salt[i] = chars[i % CppCommon::countof(chars)];

    // Generate the strong password hash
    std::string hash(hash_length(), 0);
    if (argon2id_hash_raw(t(), m(), p(), password.data(), password.size(), salt.data(), salt.size(), hash.data(), hash.size()) != ARGON2_OK)
        throwex CppCommon::SecurityException("Cannot generate 'Argon2id' hash!");

    // Return successfully generated hash and salt pair
    return std::make_pair(hash, salt);
}

bool Argon2idPasswordHashing::Validate(std::string_view password, std::string_view hash, std::string_view salt) const
{
    // Calculate the digest for the given password and salt
    std::string digest(hash.size(), 0);
    if (argon2id_hash_raw(t(), m(), p(), password.data(), password.size(), salt.data(), salt.size(), digest.data(), digest.size()) != ARGON2_OK)
        throwex CppCommon::SecurityException("Cannot calculate 'Argon2id' hash!");

    // Compare the digest with the given hash
    return (digest == hash);
}

} // namespace CppSecurity
