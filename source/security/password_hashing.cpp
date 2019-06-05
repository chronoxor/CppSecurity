/*!
    \file password_hashing.cpp
    \brief Password hashing interface implementation
    \author Ivan Shynkarenka
    \date 04.06.2019
    \copyright MIT License
*/

#include "security/password_hashing.h"

#include "errors/exceptions.h"
#include "string/encoding.h"

#include <cassert>

namespace CppCommon {

PasswordHashing::PasswordHashing(size_t hash_length, size_t salt_length)
    : _hash_length(hash_length), _salt_length(salt_length)
{
    assert((hash_length >= 8) && "Hash length should be at least 8 bytes!");
    assert((salt_length >= 8) && "Salt length should be at least 8 bytes!");
    if (hash_length < 8)
        throwex SecurityException("Invalid hash length!");
    if (salt_length < 8)
        throwex SecurityException("Invalid salt length!");
}

std::string PasswordHashing::GenerateDigest(std::string_view password) const
{
    // Generate the digest
    auto digest = Generate(password);

    // Encode the digest into Base64 encoding
    return CppCommon::Encoding::Base64Encode(digest.first + digest.second);
}

bool PasswordHashing::ValidateDigest(std::string_view password, std::string_view digest) const
{
    // Decode the given digest from Base64 encoding
    auto decoded = CppCommon::Encoding::Base64Decode(password);

    // Check the decoded digest size (must be hash + salt)
    if (decoded.size() != (hash_length() + salt_length()))
        return false;

    // Extract hash and salt from the decoded digest
    std::string_view hash(decoded.data(), hash_length());
    std::string_view salt(decoded.data() + hash_length(), salt_length());

    // Perform the password validation
    return Validate(password, hash, salt);
}

} // namespace CppCommon
