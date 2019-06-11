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

    // Show the password
    std::password password = "passw0rd";
    std::cout << "Password: " << password << std::endl;

    // Generate the digest
    std::string digest = pbkdf2.GenerateEncodedDigest(password);
    std::cout << "Generated digest: " << digest << std::endl;

    // Validate the digest
    std::cout << "Validate digest: " << (pbkdf2.ValidateEncodedDigest(password, digest) ? "valid" : "invalid") << std::endl;

    return 0;
}
