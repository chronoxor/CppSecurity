/*!
    \file password_hashing_bcrypt.h
    \brief 'bcrypt' password hashing algorithm definition
    \author Ivan Shynkarenka
    \date 04.06.2019
    \copyright MIT License
*/

#ifndef CPPSECURITY_PASSWORD_HASHING_BCRYPT_H
#define CPPSECURITY_PASSWORD_HASHING_BCRYPT_H

#include "password_hashing.h"

namespace CppSecurity {

//! 'bcrypt' password hashing algorithm
/*!
    'bcrypt' is a password hashing function designed by Niels Provos and David Mazières,
    based on the Blowfish cipher, and presented at USENIX in 1999. Besides incorporating
    a salt to protect against rainbow table attacks, bcrypt is an adaptive function: over
    time, the iteration count can be increased to make it slower, so it remains resistant
    to brute-force search attacks even with increasing computation power.

    The bcrypt function is the default password hash algorithm for OpenBSD and other systems
    including some Linux distributions such as SUSE Linux.

    https://en.wikipedia.org/wiki/Bcrypt

    Thread-safe.
*/
class BcryptPasswordHashing : public PasswordHashing
{
public:
    //! Initialize 'bcrypt' password hashing with required parameters
    /*!
        \param workfactor - Work factor (default is 4)
    */
    BcryptPasswordHashing(size_t workfactor = 4);
    BcryptPasswordHashing(const BcryptPasswordHashing&) = default;
    BcryptPasswordHashing(BcryptPasswordHashing&&) = default;
    ~BcryptPasswordHashing() = default;

    BcryptPasswordHashing& operator=(const BcryptPasswordHashing&) = default;
    BcryptPasswordHashing& operator=(BcryptPasswordHashing&&) = default;

    //! Get the work factor
    size_t workfactor() const noexcept { return _workfactor; }

    // Implementation of PasswordHashing
    const std::string& name() const override { return _name; }
    std::string GenerateSalt() const override;
    std::string GenerateHash(std::string_view password, std::string_view salt) const override;
    std::string GenerateDigest(std::string_view password) const override;
    bool Validate(std::string_view password, std::string_view hash, std::string_view salt) const override;
    bool ValidateDigest(std::string_view password, std::string_view digest) const override;

private:
    static std::string _name;
    size_t _workfactor;
};

/*! \example password_hashing_bcrypt.cpp 'bcrypt' password hashing example */

} // namespace CppSecurity

#endif // CPPSECURITY_PASSWORD_HASHING_BCRYPT_H
