/*!
    \file password_hashing_scrypt.h
    \brief 'scrypt' password hashing algorithm definition
    \author Ivan Shynkarenka
    \date 04.06.2019
    \copyright MIT License
*/

#ifndef CPPSECURITY_PASSWORD_HASHING_SCRYPT_H
#define CPPSECURITY_PASSWORD_HASHING_SCRYPT_H

#include "password_hashing.h"

namespace CppCommon {

//! 'scrypt' password hashing algorithm
/*!
    'scrypt' key derivation function was originally developed for use in the Tarsnap
    online backup system and is designed to be far more secure against hardware
    brute-force attacks than alternative functions such as PBKDF2 or bcrypt.

    http://www.tarsnap.com/scrypt.html

    Thread-safe.
*/
class ScryptPasswordHashing : public PasswordHashing
{
public:
    ScryptPasswordHashing() = default;
    ScryptPasswordHashing(const ScryptPasswordHashing&) = default;
    ScryptPasswordHashing(ScryptPasswordHashing&&) = default;
    ~ScryptPasswordHashing() = default;

    ScryptPasswordHashing& operator=(const ScryptPasswordHashing&) = default;
    ScryptPasswordHashing& operator=(ScryptPasswordHashing&&) = default;

    //! Get the password hashing algorithm name
    const std::string& name() const { return "scrypt"; }

    //! Generate the strong password hash and unique salt for the given user password
    /*!
        \param password - User password
        \param hash_length - Strong password hash length (default is 32)
        \param salt_length - Unique password salt length (default is 32)
        \return Strong password hash and unique salt
    */
    std::pair<std::string, std::string> Generate(std::string_view password, size_t hash_length = 32, size_t salt_length = 32) const override;

    //! Validate the user password over the given strong password hash and unique salt
    /*!
        \param password - User password
        \param hash - Strong password hash
        \param salt - Unique password salt
        \return 'true' if the given user password is valid, 'false' if the given user password is invalid
    */
    bool Validate(std::string_view password, std::string_view hash, std::string_view salt) const override;
};

} // namespace CppCommon

#endif // CPPSECURITY_PASSWORD_HASHING_SCRYPT_H
