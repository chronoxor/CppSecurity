/*!
    \file cipher.cpp
    \brief Cipher implementation
    \author Ivan Shynkarenka
    \date 20.11.2022
    \copyright MIT License
*/

#include "security/cipher.h"

#include "errors/exceptions.h"
#include "string/format.h"
#include "utility/countof.h"

namespace CppSecurity {

Cipher::Cipher(CipherAlgorithm algorithm, size_t iterations)
    : _algorithm(algorithm),
      _iterations(iterations),
      _encrypt(EVP_CIPHER_CTX_new(), EVP_CIPHER_CTX_free),
      _decrypt(EVP_CIPHER_CTX_new(), EVP_CIPHER_CTX_free)
{
    switch (algorithm)
    {
        case CipherAlgorithm::AES128:
            _name = "AES-128";
            _cipher = EVP_aes_128_cbc();
            break;
        case CipherAlgorithm::AES192:
            _name = "AES-192";
            _cipher = EVP_aes_192_cbc();
            break;
        case CipherAlgorithm::AES256:
            _name = "AES-256";
            _cipher = EVP_aes_256_cbc();
            break;
        case CipherAlgorithm::ARIA128:
            _name = "ARIA-128";
            _cipher = EVP_aria_128_cbc();
            break;
        case CipherAlgorithm::ARIA192:
            _name = "ARIA-192";
            _cipher = EVP_aria_192_cbc();
            break;
        case CipherAlgorithm::ARIA256:
            _name = "ARIA-256";
            _cipher = EVP_aria_256_cbc();
            break;
        case CipherAlgorithm::Camellia128:
            _name = "Camellia-128";
            _cipher = EVP_camellia_128_cbc();
            break;
        case CipherAlgorithm::Camellia192:
            _name = "Camellia-192";
            _cipher = EVP_camellia_192_cbc();
            break;
        case CipherAlgorithm::Camellia256:
            _name = "Camellia-256";
            _cipher = EVP_camellia_256_cbc();
            break;
    }

    // Validate cipher algorithm
    assert((_cipher != nullptr) && "Unknown cipher algorithm!");
    if (_cipher == nullptr)
        throwex CppCommon::SecurityException("Unknown cipher algorithm!");

    // Validate cipher encrypt context
    assert((_encrypt != nullptr) && "Invalid cipher encrypt context!");
    if (_encrypt == nullptr)
        throwex CppCommon::SecurityException("Invalid cipher encrypt context!");

    // Validate cipher decrypt context
    assert((_decrypt != nullptr) && "Invalid cipher decrypt context!");
    if (_decrypt == nullptr)
        throwex CppCommon::SecurityException("Invalid cipher decrypt context!");
}

std::string Cipher::GenerateSalt() const
{
    std::string result(8, 0);
    CppCommon::Memory::CryptoFill(result.data(), result.size());
    return result;
}

void Cipher::Initialize(std::string_view secret)
{
    int result = EVP_BytesToKey(_cipher, EVP_sha1(), nullptr, (const uint8_t*)secret.data(), (int)secret.size(), (int)_iterations, _key, _iv);
    if (result == 0)
        throwex CppCommon::SecurityException(CppCommon::format("Cannot initialize key and IV for {} cipher!", _name));
    InitializeContext();
}

void Cipher::Initialize(std::string_view secret, std::string_view salt)
{
    uint8_t salta[8];
    std::memcpy(salta, salt.data(), std::min(salt.size(), CppCommon::countof(salta)));
    int result = EVP_BytesToKey(_cipher, EVP_sha1(), salta, (const uint8_t*)secret.data(), (int)secret.size(), (int)_iterations, _key, _iv);
    if (result == 0)
        throwex CppCommon::SecurityException(CppCommon::format("Cannot initialize key and IV for {} cipher!", _name));
    InitializeContext();
}

void Cipher::InitializeContext()
{
    // Initialize encrypt context
    EVP_CIPHER_CTX_init(_encrypt.get());
    if (EVP_EncryptInit_ex(_encrypt.get(), _cipher, nullptr, _key, _iv) == 0)
        throwex CppCommon::SecurityException(CppCommon::format("Cannot initialize encrypt context for {} cipher!", _name));

    // Initialize decrypt context
    EVP_CIPHER_CTX_init(_decrypt.get());
    if (EVP_DecryptInit_ex(_decrypt.get(), _cipher, nullptr, _key, _iv) == 0)
        throwex CppCommon::SecurityException(CppCommon::format("Cannot initialize decrypt context for {} cipher!", _name));
}

std::string Cipher::Encrypt(std::string_view str)
{
    std::string result(str.size() + EVP_MAX_BLOCK_LENGTH, 0);

    // Initialize encrypt context
    if (EVP_EncryptInit_ex(_encrypt.get(), nullptr, nullptr, nullptr, nullptr) == 0)
        throwex CppCommon::SecurityException(CppCommon::format("Cannot initialize encrypt context for {} cipher!", _name));

    // Update encrypt context with plane data
    int cur_length = 0;
    if (EVP_EncryptUpdate(_encrypt.get(), (uint8_t*)result.data(), &cur_length, (const uint8_t*)str.data(), (int)str.size()) == 0)
        throwex CppCommon::SecurityException(CppCommon::format("Cannot encrypt data with {} cipher!", _name));

    // Finalize the encrypted context
    int fin_length = 0;
    if (EVP_EncryptFinal_ex(_encrypt.get(), (uint8_t*)result.data() + cur_length, &fin_length) == 0)
        throwex CppCommon::SecurityException(CppCommon::format("Cannot finalize encrypted data with {} cipher!", _name));

    // Return the encrypted data
    result.resize(cur_length + fin_length);
    return result;
}

std::string Cipher::Decrypt(std::string_view str)
{
    std::string result(str.size(), 0);

    // Initialize decrypt context
    if (EVP_DecryptInit_ex(_decrypt.get(), nullptr, nullptr, nullptr, nullptr) == 0)
        throwex CppCommon::SecurityException(CppCommon::format("Cannot initialize decrypt context for {} cipher!", _name));

    // Update decrypt context with encrypted data
    int cur_length = 0;
    if (EVP_DecryptUpdate(_decrypt.get(), (uint8_t*)result.data(), &cur_length, (const uint8_t*)str.data(), (int)str.size()) == 0)
        throwex CppCommon::SecurityException(CppCommon::format("Cannot decrypt data with {} cipher!", _name));

    // Finalize the decrypted data
    int fin_length = 0;
    if (EVP_DecryptFinal_ex(_decrypt.get(), (uint8_t*)result.data() + cur_length, &fin_length) == 0)
        throwex CppCommon::SecurityException(CppCommon::format("Cannot finalize decrypted data with {} cipher!", _name));

    // Return the decrypted data
    result.resize(cur_length + fin_length);
    return result;
}

} // namespace CppSecurity
