/*!
    \file cipher.h
    \brief Cipher definition
    \author Ivan Shynkarenka
    \date 20.11.2022
    \copyright MIT License
*/

#ifndef CPPSECURITY_CIPHER_H
#define CPPSECURITY_CIPHER_H

#include "password.h"

#include <memory>

#include <openssl/evp.h>

namespace CppSecurity {

//! Cipher algorithm
enum class CipherAlgorithm
{
    AES128,
    AES192,
    AES256,
    ARIA128,
    ARIA192,
    ARIA256,
    Camellia128,
    Camellia192,
    Camellia256
};

//! Cipher
/*!
    Cipher allows to perform symmetric encode & decode data using a provided
    secret key and optional salt.

    https://en.wikipedia.org/wiki/Symmetric-key_algorithm

    Thread-safe.
*/
class Cipher
{
public:
    //! Initialize cipher with required algorithm
    /*!
        \param algorithm - Cipher algorithm (default is CipherAlgorithm::AES256)
        \param iterations - Count key hashing iterations (default is 1000)
    */
    Cipher(CipherAlgorithm algorithm = CipherAlgorithm::AES256, size_t iterations = 1000);
    //! Initialize cipher with the given secret key and required algorithm
    /*!
        \param secret - Secret key
        \param algorithm - Cipher algorithm (default is CipherAlgorithm::AES256)
        \param iterations - Count key hashing iterations (default is 1000)
    */
    Cipher(std::string_view secret, CipherAlgorithm algorithm = CipherAlgorithm::AES256, size_t iterations = 1000) : Cipher(algorithm, iterations) { Initialize(secret); }
    //! Initialize cipher with the given secret key, unique salt and required algorithm
    /*!
        \param secret - Secret key
        \param salt - Unique secret salt
        \param algorithm - Cipher algorithm (default is CipherAlgorithm::AES256)
        \param iterations - Count key hashing iterations (default is 1000)
    */
    Cipher(std::string_view secret, std::string_view salt, CipherAlgorithm algorithm = CipherAlgorithm::AES256, size_t iterations = 1000) : Cipher(algorithm, iterations) { Initialize(secret, salt); }
    Cipher(const Cipher&) = delete;
    Cipher(Cipher&&) = default;
    ~Cipher() = default;

    Cipher& operator=(const Cipher&) = delete;
    Cipher& operator=(Cipher&&) = default;

    //! Get the cipher algorithm
    CipherAlgorithm algorithm() const noexcept { return _algorithm; }
    //! Get the cipher algorithm name
    const std::string& name() const noexcept { return _name; }
    //! Get the count of key hashing iterations
    size_t iterations() const noexcept { return _iterations; }

    //! Generate the unique secret salt
    /*!
        \return Unique secret salt
    */
    static std::string GenerateSalt();

    //! Initialize the cipher with the given secret key
    /*!
        \param secret - Secret key
    */
    void Initialize(std::string_view secret);
    //! Initialize the cipher with the given secret key and unique salt
    /*!
        \param secret - Secret key
        \param salt - Unique secret salt
    */
    void Initialize(std::string_view secret, std::string_view salt);

    //! Encrypt the given string
    /*!
        \param str - String to encrypt
        \return Encrypted string
    */
    std::string Encrypt(std::string_view str);

    //! Decrypt the given string
    /*!
        \param str - String to decrypt
        \return Decrypted string
    */
    std::string Decrypt(std::string_view str);

private:
    CipherAlgorithm _algorithm;
    std::string _name{"<unknown>"};
    const EVP_CIPHER* _cipher{nullptr};
    size_t _iterations;
    uint8_t _key[EVP_MAX_KEY_LENGTH];
    uint8_t _iv[EVP_MAX_IV_LENGTH];
    std::unique_ptr<EVP_CIPHER_CTX, void (*)(EVP_CIPHER_CTX *)> _encrypt;
    std::unique_ptr<EVP_CIPHER_CTX, void (*)(EVP_CIPHER_CTX *)> _decrypt;

    //! Initialize the cipher context
    void InitializeContext();
};

/*! \example cipher_encrypt.cpp Cipher encrypt example */
/*! \example cipher_decrypt.cpp Cipher decrypt example */

} // namespace CppSecurity

#endif // CPPSECURITY_CIPHER_H
