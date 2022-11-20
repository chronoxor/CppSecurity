/*!
    \file password_generator.inl
    \brief Password generator inline implementation
    \author Ivan Shynkarenka
    \date 10.06.2019
    \copyright MIT License
*/

namespace CppSecurity {

template <class TOutputStream>
inline TOutputStream& operator<<(TOutputStream& stream, PasswordFlags flags)
{
    bool first = true;
    if ((flags & PasswordFlags::lower) && ((flags & PasswordFlags::lower).value() == PasswordFlags::lower))
    {
        stream << (first ? "" : "|") << "lower";
        first = false;
    }
    if ((flags & PasswordFlags::upper) && ((flags & PasswordFlags::upper).value() == PasswordFlags::upper))
    {
        stream << (first ? "" : "|") << "upper";
        first = false;
    }
    if ((flags & PasswordFlags::digits) && ((flags & PasswordFlags::digits).value() == PasswordFlags::digits))
    {
        stream << (first ? "" : "|") << "digits";
        first = false;
    }
    if ((flags & PasswordFlags::symbols) && ((flags & PasswordFlags::symbols).value() == PasswordFlags::symbols))
    {
        stream << (first ? "" : "|") << "symbols";
        first = false;
    }
    return stream;
}

} // namespace CppSecurity
