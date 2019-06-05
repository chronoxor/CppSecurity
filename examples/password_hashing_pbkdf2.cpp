/*!
    \file password_hashing_pbkdf2.cpp
    \brief 'PBKDF2' password hashing example
    \author Ivan Shynkarenka
    \date 05.06.2019
    \copyright MIT License
*/

#include "security/password_hashing_pbkdf2.h"

#include <iostream>

int main(int argc, char** argv)
{
    CppSecurity::PBKDF2PasswordHashing pbkdf2;

    // Generate digest
    std::string digest = pbkdf2.GenerateDigest("passw0rd");
    std::cout << "Generate 'passw0rd' digest: " << digest << std::endl;

    // Validate digest
    std::cout << "Validate 'password' digest: " << (pbkdf2.Validate("password", digest) ? "valid" : "invalid") << std::endl;
    std::cout << "Validate 'passw0rd' digest: " << (pbkdf2.Validate("passw0rd", digest) ? "valid" : "invalid") << std::endl;

    return 0;
}
