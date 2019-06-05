/*!
    \file password_hashing_argon2.cpp
    \brief 'Argon2' password hashing example
    \author Ivan Shynkarenka
    \date 05.06.2019
    \copyright MIT License
*/

#include "security/password_hashing_argon2.h"

#include <iostream>

int main(int argc, char** argv)
{
    CppSecurity::Argon2iPasswordHashing scrypt;

    // Generate digest
    std::string digest = scrypt.GenerateDigest("passw0rd");
    std::cout << "Generate 'passw0rd' digest: " << digest << std::endl;

    // Validate digest
    std::cout << "Validate 'password' digest: " << (scrypt.ValidateDigest("password", digest) ? "valid" : "invalid") << std::endl;
    std::cout << "Validate 'passw0rd' digest: " << (scrypt.ValidateDigest("passw0rd", digest) ? "valid" : "invalid") << std::endl;

    return 0;
}
