/*!
    \file password_hashing_scrypt.cpp
    \brief 'scrypt' password hashing algorithm implementation
    \author Ivan Shynkarenka
    \date 04.06.2019
    \copyright MIT License
*/

#include "security/password_hashing_scrypt.h"

#include "errors/exceptions.h"

#include <libscrypt.h>

namespace CppSecurity {

std::string ScryptPasswordHashing::_name = "scrypt";

ScryptPasswordHashing::ScryptPasswordHashing(size_t hash_length, size_t salt_length, uint64_t n, uint32_t r, uint32_t p)
    : PasswordHashing(hash_length, salt_length),
      _n(n), _r(r), _p(p)
{
}

std::pair<std::string, std::string> ScryptPasswordHashing::GenerateHashAndSalt(std::string_view password) const
{
    // Generate the unique password salt
    std::string salt = GenerateSalt();

    // Generate the strong password hash
    std::string hash(hash_length(), 0);
    if (libscrypt_scrypt((const uint8_t*)password.data(), password.size(), (const uint8_t*)salt.data(), salt.size(), n(), r(), p(), (uint8_t*)hash.data(), hash.size()) != 0)
        throwex CppCommon::SecurityException("Cannot generate 'scrypt' hash!");

    // Return successfully generated hash and salt pair
    return std::make_pair(hash, salt);
}

bool ScryptPasswordHashing::Validate(std::string_view password, std::string_view hash, std::string_view salt) const
{
    // Calculate the digest for the given password and salt
    std::string digest(hash.size(), 0);
    if (libscrypt_scrypt((const uint8_t*)password.data(), password.size(), (const uint8_t*)salt.data(), salt.size(), n(), r(), p(), (uint8_t*)digest.data(), digest.size()) != 0)
        throwex CppCommon::SecurityException("Cannot calculate 'scrypt' hash!");

    // Compare the digest with the given hash
    return (digest == hash);
}

} // namespace CppSecurity
