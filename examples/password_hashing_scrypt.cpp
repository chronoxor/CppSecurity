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

    // Show the password
    std::password password = "passw0rd";
    std::cout << "Password: " << password << std::endl;

    // Generate the digest
    std::string digest = scrypt.GenerateEncodedDigest(password);
    std::cout << "Generated digest: " << digest << std::endl;

    // Validate the digest
    std::cout << "Validate digest: " << (scrypt.ValidateEncodedDigest(password, digest) ? "valid" : "invalid") << std::endl;

    return 0;
}
