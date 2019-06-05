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

namespace CppSecurity {

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
    //! Initialize 'scrypt' password hashing with required parameters
    /*!
        \param hash_length - Strong password hash length (default is 32)
        \param salt_length - Unique password salt length (default is 32)
        \param N - CPU AND RAM cost (default is 1024)
        \param r - RAM Cost (default is 8)
        \param p - Degree of parallelism (default is 1)
    */
    ScryptPasswordHashing(size_t hash_length = 32, size_t salt_length = 32, uint64_t N = 1024, uint32_t r = 8, uint32_t p = 1);
    ScryptPasswordHashing(const ScryptPasswordHashing&) = default;
    ScryptPasswordHashing(ScryptPasswordHashing&&) = default;
    ~ScryptPasswordHashing() = default;

    ScryptPasswordHashing& operator=(const ScryptPasswordHashing&) = default;
    ScryptPasswordHashing& operator=(ScryptPasswordHashing&&) = default;

    //! Get the CPU AND RAM cost
    uint64_t N() const noexcept { return _N; }
    //! Get the RAM Cost
    uint32_t r() const noexcept { return _r; }
    //! Get the degree of parallelism
    uint32_t p() const noexcept { return _p; }

    // Implementation of PasswordHashing
    const std::string& name() const override { return _name; }
    std::pair<std::string, std::string> Generate(std::string_view password) const override;
    bool Validate(std::string_view password, std::string_view hash, std::string_view salt) const override;

private:
    static std::string _name;
    uint64_t _N;
    uint32_t _r;
    uint32_t _p;
};

} // namespace CppSecurity

#endif // CPPSECURITY_PASSWORD_HASHING_SCRYPT_H
