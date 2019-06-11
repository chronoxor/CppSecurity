//
// Created by Ivan Shynkarenka on 11.06.2019
//

#include "test.h"

#include "security/google_authenticator.h"

using namespace CppSecurity;

TEST_CASE("Google Authenticator", "[CppSecurity]")
{
    GoogleAuthenticator authenticator;

    // Generate secret
    std::password password = "passw0rd";
    std::password secret = authenticator.GenerateSecret(password);
    std::password url = authenticator.GenerateURL("test", secret);
    std::password qr = authenticator.GenerateQRCodeLink(url, 123, 456);
    REQUIRE(secret == "OBQXG43XGBZGI===");
    REQUIRE(url == "otpauth%3A//totp/test%3Fsecret%3DOBQXG43XGBZGI%3D%3D%3D");
    REQUIRE(qr == "https://chart.apis.google.com/chart?cht=qr&chs=123x456&chl=otpauth%3A//totp/test%3Fsecret%3DOBQXG43XGBZGI%3D%3D%3D");

    // Validate secret over different UTC timestamps
    REQUIRE(authenticator.Validate(secret, CppCommon::UtcTimestamp(0)) == 166471);
    REQUIRE(authenticator.Validate(secret, CppCommon::UtcTimestamp(946684800000000000)) == 126720);
}
