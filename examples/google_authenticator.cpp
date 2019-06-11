/*!
    \file google_authenticator.cpp
    \brief Google Authenticator example
    \author Ivan Shynkarenka
    \date 11.06.2019
    \copyright MIT License
*/

#include "security/google_authenticator.h"

#include <iostream>

int main(int argc, char** argv)
{
    CppSecurity::GoogleAuthenticator authenticator;

    // Show the password
    std::password password = "passw0rd";
    std::cout << "Password: " << password << std::endl;

    // Generate the secret, URL and QR Code link
    std::password secret = authenticator.GenerateSecret(password);
    std::password url = authenticator.GenerateURL("test", secret);
    std::password qr = authenticator.GenerateQRCodeLink(url);
    std::cout << "Generated secret: " << secret << std::endl;
    std::cout << "Generated URL: " << url << std::endl;
    std::cout << "Generated QR Code link: " << qr << std::endl;

    std::cout << "Please enter Google Authenticator token to validate. Enter '0' to exit..." << std::endl;

    // Perform text input
    std::string line;
    while (getline(std::cin, line))
    {
        if (line.empty() || (line == "0"))
            break;

        size_t token = std::stoi(line);

        // Validate the token
        std::cout << (authenticator.Validate(token, secret) ? "Valid" : "Invalid") << std::endl;
    }

    return 0;
}
