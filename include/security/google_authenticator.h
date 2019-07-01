/*!
    \file google_authenticator.h
    \brief Google Authenticator definition
    \author Ivan Shynkarenka
    \date 11.06.2019
    \copyright MIT License
*/

#ifndef CPPSECURITY_GOOGLE_AUTHENTICATOR_H
#define CPPSECURITY_GOOGLE_AUTHENTICATOR_H

#include "password.h"

#include "time/timestamp.h"

namespace CppSecurity {

//! Google Authenticator
/*!
    Google Authenticator allows to generate secrets and validate tokens registered in Google Authenticator
    software.

    Google Authenticator is a software-based authenticator that implements two-step verification services
    using the Time-based One-time Password Algorithm (TOTP; specified in RFC 6238) and HMAC-based One-time
    Password algorithm (HOTP; specified in RFC 4226), for authenticating users of mobile applications by Google.

    https://en.wikipedia.org/wiki/Google_Authenticator
    https://play.google.com/store/apps/details?id=com.google.android.apps.authenticator2

    Thread-safe.
*/
class GoogleAuthenticator
{
public:
    //! Initialize Google Authenticator with required parameters
    /*!
        \param secret_length - Secret length (default is 12)
        \param pin_length - Pin length (default is 6)
    */
    GoogleAuthenticator(size_t secret_length = 12, size_t pin_length = 6);
    GoogleAuthenticator(const GoogleAuthenticator&) = default;
    GoogleAuthenticator(GoogleAuthenticator&&) = default;
    ~GoogleAuthenticator() = default;

    GoogleAuthenticator& operator=(const GoogleAuthenticator&) = default;
    GoogleAuthenticator& operator=(GoogleAuthenticator&&) = default;

    //! Get the secret length
    size_t secret_length() const noexcept { return _secret_length; }
    //! Get the pin length
    size_t pin_length() const noexcept { return _pin_length; }

    //! Generate the unique password salt
    /*!
        \return Unique password salt
    */
    std::string GenerateSalt() const;

    //! Generate the Google Authenticator secret from the given user password
    /*!
        \param password - User password
        \return Generated Google Authenticator secret
    */
    std::password GenerateSecret(std::string_view password) const;
    //! Generate the Google Authenticator secret from the given user password and unique salt
    /*!
        \param password - User password
        \param salt - Unique password salt
        \return Generated Google Authenticator secret
    */
    std::password GenerateSecret(std::string_view password, std::string_view salt) const;

    //! Generate the Google Authenticator URL
    /*!
        \param identifier - Google Authenticator identifier
        \param secret - Google Authenticator secret
        \return Generated Google Authenticator URL
    */
    std::password GenerateURL(std::string_view identifier, std::string_view secret) const;

    //! Generate the Google Authenticator QR Code link
    /*!
        \param url - Google Authenticator URL
        \param width - QR Code width (default is 100)
        \param height - QR Code height (default is 100)
        \return Generated Google Authenticator QR Code link
    */
    std::password GenerateQRCodeLink(std::string_view url, size_t width = 100, size_t height = 100) const;

    //! Generate the Google Authenticator token for the given secret and UTC timestamp
    /*!
        \param secret - Google Authenticator secret
        \param timestamp - UTC timestamp (default is CppCommon::UtcTimestamp())
        \return Generated Google Authenticator token
    */
    size_t GenerateToken(std::string_view secret, const CppCommon::Timestamp& timestamp = CppCommon::UtcTimestamp()) const;

    //! Validate the Google Authenticator token over the given secret and UTC timestamp
    /*!
        \param token - Google Authenticator token
        \param secret - Google Authenticator secret
        \param timestamp - UTC timestamp (default is CppCommon::UtcTimestamp())
        \return 'true' if the given token is valid, 'false' if the given token is invalid
    */
    bool Validate(size_t token, std::string_view secret, const CppCommon::Timestamp& timestamp = CppCommon::UtcTimestamp()) const;

private:
    size_t _secret_length;
    size_t _pin_length;
};

/*! \example google_authenticator.cpp Google Authenticator example */

} // namespace CppSecurity

#endif // CPPSECURITY_GOOGLE_AUTHENTICATOR_H
