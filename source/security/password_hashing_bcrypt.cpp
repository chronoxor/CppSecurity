/*!
    \file password_hashing_bcrypt.cpp
    \brief 'bcrypt' password hashing algorithm implementation
    \author Ivan Shynkarenka
    \date 04.06.2019
    \copyright MIT License
*/

#include "security/password_hashing_bcrypt.h"

#include "errors/exceptions.h"

#include <libbcrypt.h>

namespace CppSecurity {

std::string BcryptPasswordHashing::_name = "bcrypt";

BcryptPasswordHashing::BcryptPasswordHashing(size_t workfactor)
    : PasswordHashing(64, 64),
      _workfactor(workfactor)
{
}

std::string BcryptPasswordHashing::GenerateSalt() const
{
    std::string salt(salt_length(), 0);
    if (bcrypt_gensalt((int)workfactor(), salt.data()) != 0)
        throwex CppCommon::SecurityException("Cannot generate 'bcrypt' salt!");
    return salt;
}

std::string BcryptPasswordHashing::GenerateHash(std::string_view password, std::string_view salt) const
{
    // Generate the strong password hash
    std::string hash(hash_length(), 0);
    if (bcrypt_hashpw(password.data(), salt.data(), hash.data()) != 0)
        throwex CppCommon::SecurityException("Cannot generate 'bcrypt' hash!");
    return hash;
}

std::string BcryptPasswordHashing::GenerateDigest(std::string_view password) const
{
    std::string salt = GenerateSalt();
    return GenerateHash(password, salt);
}

bool BcryptPasswordHashing::Validate(std::string_view password, std::string_view hash, std::string_view salt) const
{
    // Calculate the digest for the given password and salt
    std::string digest(hash.size(), 0);
    if (bcrypt_hashpw(password.data(), salt.data(), digest.data()) != 0)
        throwex CppCommon::SecurityException("Cannot calculate 'bcrypt' hash!");

    // Compare the digest with the given hash
    return (digest == hash);
}

bool BcryptPasswordHashing::ValidateDigest(std::string_view password, std::string_view digest) const
{
    // Check the digest size (must be hash + salt)
    if (digest.size() != hash_length())
        return false;

    // Perform the password validation
    return (bcrypt_checkpw(password.data(), digest.data()) == 0);
}

} // namespace CppSecurity
