/*!
    \file password.h
    \brief Password string definition
    \author Ivan Shynkarenka
    \date 04.06.2019
    \copyright MIT License
*/

#ifndef CPPSECURITY_STRING_PASSWORD_H
#define CPPSECURITY_STRING_PASSWORD_H

#include "memory/memory.h"

#include <string>

namespace CppSecurity {

//! Password allocator
template <class T>
class PasswordAllocator : public std::allocator<T>
{
public:
    typedef typename std::allocator<T>::value_type value_type;
    typedef typename std::allocator<T>::size_type size_type;
    typedef typename std::allocator<T>::difference_type difference_type;

    template<class U> struct rebind { typedef PasswordAllocator<U> other; };

    PasswordAllocator() throw() {}
    PasswordAllocator(const PasswordAllocator&) throw() {}
    template <class U> PasswordAllocator(const PasswordAllocator<U>&) throw() {}

    void deallocate(pointer p, size_type n)
    {
        CppCommon::Memory::ZeroFill(p, n * sizeof(T));
        std::allocator<T>::deallocate(p, n);
    }
};

} // namespace CppSecurity

namespace std {

//! Password string
/*!
    Password string extends std::string with a secure zero memory destructor
    which will fill string memory with zeros to avoid keep password in the
    wasted process memory.

    Not thread-safe.
*/
class password : public std::basic_string<char, std::char_traits<char>, CppSecurity::PasswordAllocator<char>>
{
public:
    using basic_string::basic_string;
    ~password() { clear(); }
    void clear() noexcept { CppCommon::Memory::ZeroFill(data(), size()); }
};

} // namespace std

#endif // CPPSECURITY_STRING_PASSWORD_H
