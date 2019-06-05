/*!
    \file password_hashing_bcrypt.cpp
    \brief 'bcrypt' password hashing algorithm implementation
    \author Ivan Shynkarenka
    \date 04.06.2019
    \copyright MIT License
*/

#include "security/password_hashing_bcrypt.h"

#include "errors/exceptions.h"
#include "utility/countof.h"

#include <cassert>

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

std::pair<std::string, std::string> BcryptPasswordHashing::GenerateHashAndSalt(std::string_view password) const
{
    // Generate the unique password salt
    std::string salt = GenerateSalt();

    // Generate the strong password hash
    std::string hash(hash_length(), 0);
    if (bcrypt_hashpw(password.data(), salt.data(), hash.data()) != 0)
        throwex CppCommon::SecurityException("Cannot generate 'bcrypt' hash!");

    // Return successfully generated hash and salt pair
    return std::make_pair(hash, salt);
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

} // namespace CppSecurity
