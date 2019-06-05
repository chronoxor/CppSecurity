/*!
    \file password_hashing_scrypt.cpp
    \brief 'scrypt' password hashing example
    \author Ivan Shynkarenka
    \date 05.06.2019
    \copyright MIT License
*/

#include "security/password_hashing_scrypt.h"

#include <iostream>

int main(int argc, char** argv)
{
    CppSecurity::ScryptPasswordHashing scrypt;

    // Generate digest
    std::string digest = scrypt.GenerateDigest("passw0rd");
    std::cout << "Generate 'passw0rd' digest: " << digest << std::endl;

    // Validate digest
    std::cout << "Validate 'password' digest: " << (scrypt.Validate("password", digest) ? "valid" : "invalid") << std::endl;
    std::cout << "Validate 'passw0rd' digest: " << (scrypt.Validate("passw0rd", digest) ? "valid" : "invalid") << std::endl;

    return 0;
}
