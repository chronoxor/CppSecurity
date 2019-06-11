/*!
    \file google_authenticator.cpp
    \brief Google Authenticator implementation
    \author Ivan Shynkarenka
    \date 11.06.2019
    \copyright MIT License
*/

#include "security/google_authenticator.h"

#include "errors/exceptions.h"
#include "memory/memory.h"
#include "string/encoding.h"
#include "string/format.h"
#include "utility/countof.h"

#include <cassert>

#include <openssl/evp.h>
#include <openssl/hmac.h>
#include <openssl/sha.h>

namespace CppSecurity {

GoogleAuthenticator::GoogleAuthenticator(size_t secret_length, size_t pin_length)
    : _secret_length(secret_length), _pin_length(pin_length)
{
    assert((secret_length >= 6) && "Secret should be at least 6 bytes!");
    if (secret_length < 6)
        throwex CppCommon::SecurityException("Invalid secret length!");
    assert(((pin_length >= 3) && (pin_length <= 10)) && "Pin should be at least 3 digits and not more than 10 digits!");
    if ((pin_length < 3) || (pin_length > 10))
        throwex CppCommon::SecurityException("Invalid pin length!");
}

std::password GoogleAuthenticator::GenerateSecret() const
{
    std::password result(secret_length(), 0);
    CppCommon::Memory::CryptoFill(result.data(), result.size());
    return GenerateSecret(result);
}

std::password GoogleAuthenticator::GenerateSecret(std::string_view digest) const
{
    return std::password(CppCommon::Encoding::Base32Encode(digest));
}

std::password GoogleAuthenticator::GenerateURL(std::string_view identifier, std::string_view secret) const
{
    return std::password(CppCommon::Encoding::URLEncode("otpauth://totp/{}?secret={}"_format(identifier, secret)));
}

std::password GoogleAuthenticator::GenerateQRCodeLink(std::string_view url, size_t width, size_t height) const
{
    return std::password("https://chart.apis.google.com/chart?cht=qr&chs={}x{}&chl={}"_format(width, height, url));
}

size_t GoogleAuthenticator::Validate(std::string_view secret, const CppCommon::Timestamp& timestamp) const
{
    // Get the current timestamp in 30sec intervals
    uint64_t seconds = timestamp.seconds() / 30;

    // Perform big-endian timestamp conversion
    uint8_t challenge[8];
    for (size_t i = 8; i--; seconds >>= 8)
        challenge[i] = seconds & 0xFF;

    // Decode the secret from the Base32 encoding
    std::password key(CppCommon::Encoding::Base32Decode(secret));

    // Compute the HMAC-SHA1 of the secret and the challenge
    uint8_t hash[SHA_DIGEST_LENGTH];
    unsigned int size = SHA_DIGEST_LENGTH;
    HMAC_CTX* ctx = HMAC_CTX_new();
    HMAC_Init_ex(ctx, key.data(), (int)key.size(), EVP_sha1(), nullptr);
    HMAC_Update(ctx, challenge, CppCommon::countof(challenge));
    HMAC_Final(ctx, hash, &size);
    HMAC_CTX_free(ctx);

    // Pick the offset where to sample our hash value for the actual verification code
    size_t offset = hash[SHA_DIGEST_LENGTH - 1] & 0xF;

    // Compute the truncated hash in a byte-order independent loop
    size_t truncated = 0;
    for (size_t i = 0; i < 4; ++i)
    {
        truncated <<= 8;
        truncated |= hash[offset + i];
    }

    // Compute the pin scale
    size_t pin = 1;
    for (size_t i = 0; i < pin_length(); ++i)
        pin *= 10;

    // Truncate to a smaller number of digits
    truncated &= 0x7FFFFFFF;
    truncated %= pin;
    return truncated;
}

} // namespace CppSecurity
