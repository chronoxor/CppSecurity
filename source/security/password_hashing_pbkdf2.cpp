/*!
    \file password_hashing_pbkdf2.cpp
    \brief 'PBKDF2' password hashing algorithm implementation
    \author Ivan Shynkarenka
    \date 04.06.2019
    \copyright MIT License
*/

#include "security/password_hashing_pbkdf2.h"

#include <fastpbkdf2.h>

namespace CppSecurity {

std::string PBKDF2PasswordHashing::_name = "PBKDF2";

PBKDF2PasswordHashing::PBKDF2PasswordHashing(size_t hash_length, size_t salt_length, size_t iterations, PBKDF2 algorithm)
    : PasswordHashing(hash_length, salt_length),
      _iterations(iterations),
      _algorithm(algorithm)
{
}

std::string PBKDF2PasswordHashing::GenerateHash(std::string_view password, std::string_view salt) const
{
    // Generate the strong password hash
    std::string hash(hash_length(), 0);
    switch (algorithm())
    {
        case PBKDF2::HMAC_SHA1:
            fastpbkdf2_hmac_sha1((const uint8_t*)password.data(), password.size(), (const uint8_t*)salt.data(), salt.size(), (uint32_t)iterations(), (uint8_t*)hash.data(), hash.size());
            break;
        case PBKDF2::HMAC_SHA256:
            fastpbkdf2_hmac_sha256((const uint8_t*)password.data(), password.size(), (const uint8_t*)salt.data(), salt.size(), (uint32_t)iterations(), (uint8_t*)hash.data(), hash.size());
            break;
        case PBKDF2::HMAC_SHA512:
            fastpbkdf2_hmac_sha512((const uint8_t*)password.data(), password.size(), (const uint8_t*)salt.data(), salt.size(), (uint32_t)iterations(), (uint8_t*)hash.data(), hash.size());
            break;
    }
    return hash;
}

bool PBKDF2PasswordHashing::Validate(std::string_view password, std::string_view hash, std::string_view salt) const
{
    // Calculate the digest for the given password and salt
    std::string digest(hash.size(), 0);
    switch (algorithm())
    {
        case PBKDF2::HMAC_SHA1:
            fastpbkdf2_hmac_sha1((const uint8_t*)password.data(), password.size(), (const uint8_t*)salt.data(), salt.size(), (uint32_t)iterations(), (uint8_t*)digest.data(), digest.size());
            break;
        case PBKDF2::HMAC_SHA256:
            fastpbkdf2_hmac_sha256((const uint8_t*)password.data(), password.size(), (const uint8_t*)salt.data(), salt.size(), (uint32_t)iterations(), (uint8_t*)digest.data(), digest.size());
            break;
        case PBKDF2::HMAC_SHA512:
            fastpbkdf2_hmac_sha512((const uint8_t*)password.data(), password.size(), (const uint8_t*)salt.data(), salt.size(), (uint32_t)iterations(), (uint8_t*)digest.data(), digest.size());
            break;
    }

    // Compare the digest with the given hash
    return (digest == hash);
}

} // namespace CppSecurity
