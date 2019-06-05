/*!
    \file password_hashing.h
    \brief Password hashing interface definition
    \author Ivan Shynkarenka
    \date 04.06.2019
    \copyright MIT License
*/

#ifndef CPPSECURITY_PASSWORD_HASHING_H
#define CPPSECURITY_PASSWORD_HASHING_H

#include <string>

namespace CppCommon {

//! Password hashing interface
/*!
    Password hashing interface allows to generate strong password hash and salt
    to protect plain passwords from database access attack and validate the given
    password over the generated hash and salt.

    https://en.wikipedia.org/wiki/Key_derivation_function

    Thread-safe.
*/
class PasswordHashing
{
public:
    //! Initialize password hashing with required parameters
    /*!
        \param hash_length - Strong password hash length (default is 32)
        \param salt_length - Unique password salt length (default is 32)
    */
    PasswordHashing(size_t hash_length = 32, size_t salt_length = 32);
    PasswordHashing(const PasswordHashing&) = default;
    PasswordHashing(PasswordHashing&&) = default;
    ~PasswordHashing() = default;

    PasswordHashing& operator=(const PasswordHashing&) = default;
    PasswordHashing& operator=(PasswordHashing&&) = default;

    //! Get the strong password hash length
    size_t hash_length() const noexcept { return _hash_length; }
    //! Get the unique password salt length
    size_t salt_length() const noexcept { return _salt_length; }

    //! Get the password hashing algorithm name
    virtual const std::string& name() const = 0;

    //! Generate the strong password hash and unique salt for the given user password
    /*!
        \param password - User password
        \return Strong password hash and unique salt
    */
    virtual std::pair<std::string, std::string> Generate(std::string_view password) const = 0;
    //! Generate the secure Base64 digest string for the given user password
    /*!
        \param password - User password
        \return Secure Base64 digest string
    */
    std::string GenerateDigest(std::string_view password) const;

    //! Validate the user password over the given strong password hash and unique salt
    /*!
        \param password - User password
        \param hash - Strong password hash
        \param salt - Unique password salt
        \return 'true' if the given user password is valid, 'false' if the given user password is invalid
    */
    virtual bool Validate(std::string_view password, std::string_view hash, std::string_view salt) const = 0;
    //! Validate the user password over the given secure Base64 digest string
    /*!
        \param password - User password
        \param digest - Secure Base64 digest string
        \return 'true' if the given user password is valid, 'false' if the given user password is invalid
    */
    bool ValidateDigest(std::string_view password, std::string_view digest) const;

private:
    size_t _hash_length;
    size_t _salt_length;
};

} // namespace CppCommon

#endif // CPPSECURITY_PASSWORD_HASHING_H
