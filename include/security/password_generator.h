/*!
    \file password_generator.h
    \brief Password generator definition
    \author Ivan Shynkarenka
    \date 10.06.2019
    \copyright MIT License
*/

#ifndef CPPSECURITY_PASSWORD_GENERATOR_H
#define CPPSECURITY_PASSWORD_GENERATOR_H

#include "password.h"

#include "common/flags.h"

namespace CppSecurity {

//! Password flags
enum class PasswordFlags
{
    none = 0x0,         //!< Empty password flags
    lower = 0x1,        //!< Password must contain alphabet characters in lower case (a-z)
    upper = 0x2,        //!< Password must contain alphabet characters in upper case (A-Z)
    digits = 0x4,       //!< Password must contain digits (0-9)
    symbols = 0x8,      //!< Password must contain punctuation symbols (!"#%&'()*+,-./:;<=>?@[\]^_`{|}~)
};

//! Stream output: Password flags
/*!
    \param stream - Output stream
    \param flags - Password flags
    \return Output stream
*/
template <class TOutputStream>
TOutputStream& operator<<(TOutputStream& stream, PasswordFlags flags);

} // namespace CppSecurity

// Register enum as flags to enable AND/OR/XOR logical operators with enum values!
ENUM_FLAGS(CppSecurity::PasswordFlags)

namespace CppSecurity {

//! Password generator
/*!
    Password generator allows to generate and validate secure passwords for other
    security components.

    Thread-safe.
*/
class PasswordGenerator
{
public:
    //! Initialize password generator with required parameters
    /*!
        \param length - Password length (default is 12)
        \param flags - Password flags (default is lower | upper | digits)
    */
    PasswordGenerator(size_t length = 12, PasswordFlags flags = PasswordFlags::lower | PasswordFlags::upper | PasswordFlags::digits);
    PasswordGenerator(const PasswordGenerator&) = default;
    PasswordGenerator(PasswordGenerator&&) = default;
    virtual ~PasswordGenerator() = default;

    PasswordGenerator& operator=(const PasswordGenerator&) = default;
    PasswordGenerator& operator=(PasswordGenerator&&) = default;

    //! Get the password length
    size_t length() const noexcept { return _length; }
    //! Get the password flags
    PasswordFlags flags() const noexcept { return _flags; }

    //! Generate the strong password with the current password requirements
    /*!
        \return Strong password
    */
    virtual std::password Generate() const;

    //! Validate the given password with the current password requirements
    /*!
        \param password - Strong password
        \return 'true' if the given user password is valid, 'false' if the given user password is invalid
    */
    virtual bool Validate(std::string_view password) const;

private:
    size_t _length;
    PasswordFlags _flags;
};

/*! \example password_generator.cpp Password generator example */

} // namespace CppSecurity

#include "password_generator.inl"

#endif // CPPSECURITY_PASSWORD_GENERATOR_H
