/*!
    \file password_hashing_pbkdf2.inl
    \brief 'PBKDF2' password hashing algorithm inline implementation
    \author Ivan Shynkarenka
    \date 04.06.2019
    \copyright MIT License
*/

namespace CppSecurity {

template <class TOutputStream>
inline TOutputStream& operator<<(TOutputStream& stream, PBKDF2 algorithm)
{
    switch (algorithm)
    {
        case PBKDF2::HMAC_SHA1:
            stream << "HMAC-SHA1";
            break;
        case PBKDF2::HMAC_SHA256:
            stream << "HMAC-SHA256";
            break;
        case PBKDF2::HMAC_SHA512:
            stream << "HMAC-SHA512";
            break;
        default:
            stream << "<unknown>";
            break;
    }
    return stream;
}

} // namespace CppSecurity
