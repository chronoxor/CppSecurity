/*!
    \file password_hashing_pbkdf2.cpp
    \brief 'PBKDF2' password hashing algorithm implementation
    \author Ivan Shynkarenka
    \date 04.06.2019
    \copyright MIT License
*/

#include "security/password_hashing_pbkdf2.h"

#include <openssl/evp.h>

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
    const EVP_MD* md = nullptr;
    std::string hash(hash_length(), 0);
    switch (algorithm())
    {
        case PBKDF2::HMAC_SHA1:
            md = EVP_sha1();
            break;
        case PBKDF2::HMAC_SHA256:
            md = EVP_sha256();
            break;
        case PBKDF2::HMAC_SHA512:
            md = EVP_sha512();
            break;
    }
    if (PKCS5_PBKDF2_HMAC((const char*)password.data(), (int)password.size(), (const uint8_t*)salt.data(), (int)salt.size(), (int)iterations(), md, (int)hash.size(), (uint8_t*)hash.data()) == 0)
        throwex CppCommon::SecurityException("Cannot generate 'PBKDF2' hash!");
    return hash;
}

bool PBKDF2PasswordHashing::Validate(std::string_view password, std::string_view hash, std::string_view salt) const
{
    // Calculate the digest for the given password and salt
    const EVP_MD* md = nullptr;
    std::string digest(hash.size(), 0);
    switch (algorithm())
    {
        case PBKDF2::HMAC_SHA1:
            md = EVP_sha1();
            break;
        case PBKDF2::HMAC_SHA256:
            md = EVP_sha256();
            break;
        case PBKDF2::HMAC_SHA512:
            md = EVP_sha512();
            break;
    }
    if (PKCS5_PBKDF2_HMAC((const char*)password.data(), (int)password.size(), (const uint8_t*)salt.data(), (int)salt.size(), (int)iterations(), md, (int)digest.size(), (uint8_t*)digest.data()) == 0)
        throwex CppCommon::SecurityException("Cannot calculate 'PBKDF2' hash!");

    // Compare the digest with the given hash
    return (digest == hash);
}

} // namespace CppSecurity
