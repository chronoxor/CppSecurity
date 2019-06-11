/*!
    \file password_generator.cpp
    \brief Password generator example
    \author Ivan Shynkarenka
    \date 10.06.2019
    \copyright MIT License
*/

#include "security/password_generator.h"

#include <iostream>

int main(int argc, char** argv)
{
    CppSecurity::PasswordGenerator genertor;

    // Generate passwords
    std::cout << "Generate '" << genertor.flags() << "' password: " << genertor.Generate() << std::endl;
    std::cout << "Generate '" << genertor.flags() << "' password: " << genertor.Generate() << std::endl;
    std::cout << "Generate '" << genertor.flags() << "' password: " << genertor.Generate() << std::endl;

    // Validate passwords
    std::cout << "Validate 'SomeCoolPaSsw0rd' password: " << (genertor.Validate("SomeCoolPaSsw0rd") ? "valid" : "invalid") << std::endl;
    std::cout << "Validate 'NotCoolPaSsw[0]rd' password: " << (genertor.Validate("NotCoolPaSsw[0]rd") ? "valid" : "invalid") << std::endl;
    std::cout << "Validate 'NotCoolPaSsw[0]rd' password: " << (genertor.Validate("NotCoolPaSsw0rd") ? "valid" : "invalid") << std::endl;

    return 0;
}
