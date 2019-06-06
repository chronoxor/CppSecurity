/*!
    \file password_hashing.cpp
    \brief Password hashing interface implementation
    \author Ivan Shynkarenka
    \date 04.06.2019
    \copyright MIT License
*/

#include "security/password_hashing.h"

#include "errors/exceptions.h"
#include "memory/memory.h"
#include "string/encoding.h"

#include <cassert>

namespace CppSecurity {

PasswordHashing::PasswordHashing(size_t hash_length, size_t salt_length)
    : _hash_length(hash_length), _salt_length(salt_length)
{
    assert((hash_length >= 8) && "Hash length should be at least 8 bytes!");
    assert((salt_length >= 8) && "Salt length should be at least 8 bytes!");
    if (hash_length < 8)
        throwex CppCommon::SecurityException("Invalid hash length!");
    if (salt_length < 8)
        throwex CppCommon::SecurityException("Invalid salt length!");
}

std::string PasswordHashing::GenerateSalt() const
{
    std::string salt(salt_length(), 0);
    CppCommon::Memory::CryptoFill(salt.data(), salt.size());
    return salt;
}

std::pair<std::string, std::string> PasswordHashing::GenerateHashAndSalt(std::string_view password) const
{
    std::string salt = GenerateSalt();
    std::string hash = GenerateHash(password, salt);
    return std::make_pair(hash, salt);
}

std::string PasswordHashing::GenerateDigest(std::string_view password) const
{
    auto digest = GenerateHashAndSalt(password);
    return digest.first + digest.second;
}

std::string PasswordHashing::GenerateEncodedDigest(std::string_view password) const
{
    // Encode the digest into the Base64 encoding
    return CppCommon::Encoding::Base64Encode(GenerateDigest(password));
}

bool PasswordHashing::ValidateDigest(std::string_view password, std::string_view digest) const
{
    // Check the digest size (must be hash + salt)
    if (digest.size() != (hash_length() + salt_length()))
        return false;

    // Extract hash and salt from the digest
    std::string_view hash(digest.data(), hash_length());
    std::string_view salt(digest.data() + hash_length(), salt_length());

    // Perform the password validation
    return Validate(password, hash, salt);
}

bool PasswordHashing::ValidateEncodedDigest(std::string_view password, std::string_view digest) const
{
    // Decode the digest from the Base64 encoding
    return ValidateDigest(password, CppCommon::Encoding::Base64Decode(digest));
}

} // namespace CppSecurity
