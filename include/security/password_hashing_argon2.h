/*!
    \file password_hashing_argon2.h
    \brief 'Argon2' password hashing algorithm definition
    \author Ivan Shynkarenka
    \date 05.06.2019
    \copyright MIT License
*/

#ifndef CPPSECURITY_PASSWORD_HASHING_ARGON2_H
#define CPPSECURITY_PASSWORD_HASHING_ARGON2_H

#include "password_hashing.h"

namespace CppSecurity {

//! 'Argon2d' password hashing algorithm
/*!
    'Argon2d' is a password-hashing function that summarizes the state of the art
    in the design of memory-hard functions and can be used to hash passwords for
    credential storage, key derivation, or other applications.

    Argon2d is faster and uses data-depending memory access, which makes it highly
    resistant against GPU cracking attacks and suitable for applications with no
    threats from side-channel timing attacks (eg. cryptocurrencies).

    https://github.com/P-H-C/phc-winner-argon2

    Thread-safe.
*/
class Argon2dPasswordHashing : public PasswordHashing
{
public:
    //! Initialize 'Argon2' password hashing with required parameters
    /*!
        \param hash_length - Strong password hash length (default is 32)
        \param salt_length - Unique password salt length (default is 32)
        \param t - Number of iterations (default is 3)
        \param m - Memory usage in kibibytes (default is 4096)
        \param p - Degree of parallelism (default is 1)
    */
    Argon2dPasswordHashing(size_t hash_length = 32, size_t salt_length = 32, uint32_t t = 4096, uint32_t m = 12, uint32_t p = 1);
    Argon2dPasswordHashing(const Argon2dPasswordHashing&) = default;
    Argon2dPasswordHashing(Argon2dPasswordHashing&&) = default;
    ~Argon2dPasswordHashing() = default;

    Argon2dPasswordHashing& operator=(const Argon2dPasswordHashing&) = default;
    Argon2dPasswordHashing& operator=(Argon2dPasswordHashing&&) = default;

    //! Get the number of iterations
    uint32_t t() const noexcept { return _t; }
    //! Get the memory usage in kibibytes
    uint32_t m() const noexcept { return _m; }
    //! Get the degree of parallelism
    uint32_t p() const noexcept { return _p; }

    // Implementation of PasswordHashing
    const std::string& name() const override { return _name; }
    std::pair<std::string, std::string> Generate(std::string_view password) const override;
    bool Validate(std::string_view password, std::string_view hash, std::string_view salt) const override;

private:
    static std::string _name;
    uint32_t _t;
    uint32_t _m;
    uint32_t _p;
};

//! 'Argon2i' password hashing algorithm
/*!
    'Argon2i' is a password-hashing function that summarizes the state of the art
    in the design of memory-hard functions and can be used to hash passwords for
    credential storage, key derivation, or other applications.

    Argon2i instead uses data-independent memory access, which is preferred for
    password hashing and password-based key derivation, but it is slower as it
    makes more passes over the memory to protect from tradeoff attacks.

    https://github.com/P-H-C/phc-winner-argon2

    Thread-safe.
*/
class Argon2iPasswordHashing : public Argon2dPasswordHashing
{
public:
    using Argon2dPasswordHashing::Argon2dPasswordHashing;

    // Implementation of PasswordHashing
    const std::string& name() const override { return _name; }
    std::pair<std::string, std::string> Generate(std::string_view password) const override;
    bool Validate(std::string_view password, std::string_view hash, std::string_view salt) const override;

private:
    static std::string _name;
};

//! 'Argon2id' password hashing algorithm
/*!
    'Argon2id' is a password-hashing function that summarizes the state of the art
    in the design of memory-hard functions and can be used to hash passwords for
    credential storage, key derivation, or other applications.

    Argon2id is a hybrid of Argon2i and Argon2d, using a combination of data-depending
    and data-independent memory accesses, which gives some of Argon2i's resistance to
    side-channel cache timing attacks and much of Argon2d's resistance to GPU cracking
    attacks.

    https://github.com/P-H-C/phc-winner-argon2

    Thread-safe.
*/
class Argon2idPasswordHashing : public Argon2dPasswordHashing
{
public:
    using Argon2dPasswordHashing::Argon2dPasswordHashing;

    // Implementation of PasswordHashing
    const std::string& name() const override { return _name; }
    std::pair<std::string, std::string> Generate(std::string_view password) const override;
    bool Validate(std::string_view password, std::string_view hash, std::string_view salt) const override;

private:
    static std::string _name;
};

} // namespace CppSecurity

#endif // CPPSECURITY_PASSWORD_HASHING_ARGON2_H
