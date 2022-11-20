/*!
    \file password_hashing_pbkdf2.h
    \brief 'PBKDF2' password hashing algorithm definition
    \author Ivan Shynkarenka
    \date 04.06.2019
    \copyright MIT License
*/

#ifndef CPPSECURITY_PASSWORD_HASHING_PBKDF2_H
#define CPPSECURITY_PASSWORD_HASHING_PBKDF2_H

#include "password_hashing.h"

namespace CppSecurity {

//! 'PBKDF2' algorithm
enum class PBKDF2
{
    HMAC_SHA1,      //!< HMAC-SHA1
    HMAC_SHA256,    //!< HMAC-SHA256
    HMAC_SHA512     //!< HMAC-SHA512
};

//! 'PBKDF2' password hashing algorithm
/*!
    'PBKDF2' (Password-Based Key Derivation Function 2) are key derivation functions with
    a sliding computational cost, used to reduce vulnerabilities to brute force attacks.

    'PBKDF2' is part of RSA Laboratories' Public-Key Cryptography Standards (PKCS) series,
    specifically PKCS #5 v2.0, also published as Internet Engineering Task Force's RFC 2898.
    It supersedes PBKDF1, which could only produce derived keys up to 160 bits long.
    RFC 8018, published in 2017, recommends PBKDF2 for password hashing.

    https://en.wikipedia.org/wiki/PBKDF2

    Thread-safe.
*/
class PBKDF2PasswordHashing : public PasswordHashing
{
public:
    //! Initialize 'PBKDF2' password hashing with required parameters
    /*!
        \param hash_length - Strong password hash length (default is 32)
        \param salt_length - Unique password salt length (default is 32)
        \param algorithm - 'PBKDF2' algorithm (default is PBKDF2::HMAC_SHA512)
        \param iterations - Count of 'PBKDF2' iterations (default is 1000)
    */
    PBKDF2PasswordHashing(size_t hash_length = 32, size_t salt_length = 32, PBKDF2 algorithm = PBKDF2::HMAC_SHA512, size_t iterations = 1000);
    PBKDF2PasswordHashing(const PBKDF2PasswordHashing&) = default;
    PBKDF2PasswordHashing(PBKDF2PasswordHashing&&) = default;
    ~PBKDF2PasswordHashing() = default;

    PBKDF2PasswordHashing& operator=(const PBKDF2PasswordHashing&) = default;
    PBKDF2PasswordHashing& operator=(PBKDF2PasswordHashing&&) = default;

    //! Get the 'PBKDF2' algorithm
    PBKDF2 algorithm() const noexcept { return _algorithm; }
    //! Get the count of 'PBKDF2' iterations
    size_t iterations() const noexcept { return _iterations; }

    // Implementation of PasswordHashing
    const std::string& name() const override { return _name; }
    std::string GenerateHash(std::string_view password, std::string_view salt) const override;
    bool Validate(std::string_view password, std::string_view hash, std::string_view salt) const override;

private:
    static std::string _name;
    PBKDF2 _algorithm;
    size_t _iterations;
};

/*! \example password_hashing_pbkdf2.cpp 'PBKDF2' password hashing example */

} // namespace CppSecurity

#endif // CPPSECURITY_PASSWORD_HASHING_PBKDF2_H
