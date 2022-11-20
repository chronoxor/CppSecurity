/*!
    \file cipher.inl
    \brief Cipher inline implementation
    \author Ivan Shynkarenka
    \date 20.11.2022
    \copyright MIT License
*/

namespace CppSecurity {

template <class TOutputStream>
inline TOutputStream& operator<<(TOutputStream& stream, CipherAlgorithm algorithm)
{
    switch (algorithm)
    {
        case CipherAlgorithm::AES128:
            stream << "AES128";
            break;
        case CipherAlgorithm::AES192:
            stream << "AES192";
            break;
        case CipherAlgorithm::AES256:
            stream << "AES256";
            break;
        case CipherAlgorithm::ARIA128:
            stream << "ARIA128";
            break;
        case CipherAlgorithm::ARIA192:
            stream << "ARIA192";
            break;
        case CipherAlgorithm::ARIA256:
            stream << "ARIA256";
            break;
        case CipherAlgorithm::Camellia128:
            stream << "Camellia128";
            break;
        case CipherAlgorithm::Camellia192:
            stream << "Camellia192";
            break;
        case CipherAlgorithm::Camellia256:
            stream << "Camellia256";
            break;
        default:
            stream << "<unknown>";
            break;
    }
    return stream;
}

} // namespace CppSecurity
