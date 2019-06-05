/*!
    \file password_hashing_bcrypt.cpp
    \brief 'bcrypt' password hashing example
    \author Ivan Shynkarenka
    \date 05.06.2019
    \copyright MIT License
*/

#include "security/password_hashing_bcrypt.h"

#include <iostream>

int main(int argc, char** argv)
{
    CppSecurity::BcryptPasswordHashing bcrypt;

    // Generate digest
    std::string digest = bcrypt.GenerateDigest("passw0rd");
    std::cout << "Generate 'passw0rd' digest: " << digest << std::endl;

    // Validate digest
    std::cout << "Validate 'password' digest: " << (bcrypt.Validate("password", digest) ? "valid" : "invalid") << std::endl;
    std::cout << "Validate 'passw0rd' digest: " << (bcrypt.Validate("passw0rd", digest) ? "valid" : "invalid") << std::endl;

    return 0;
}
