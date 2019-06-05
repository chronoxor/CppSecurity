# CppSecurity

[![Linux build status](https://img.shields.io/travis/chronoxor/CppSecurity/master.svg?label=Linux)](https://travis-ci.org/chronoxor/CppSecurity)
[![OSX build status](https://img.shields.io/travis/chronoxor/CppSecurity/master.svg?label=OSX)](https://travis-ci.org/chronoxor/CppSecurity)
[![Cygwin build status](https://img.shields.io/appveyor/ci/chronoxor/CppSecurity/master.svg?label=Cygwin)](https://ci.appveyor.com/project/chronoxor/CppSecurity)
[![MinGW build status](https://img.shields.io/appveyor/ci/chronoxor/CppSecurity/master.svg?label=MinGW)](https://ci.appveyor.com/project/chronoxor/CppSecurity)
[![Windows build status](https://img.shields.io/appveyor/ci/chronoxor/CppSecurity/master.svg?label=Windows)](https://ci.appveyor.com/project/chronoxor/CppSecurity)

C++ Security Library contains initial templates for a new C++ library project.

[CppSecurity API reference](https://chronoxor.github.io/CppSecurity/index.html)

# Contents
  * [Features](#features)
  * [Requirements](#requirements)
  * [How to build?](#how-to-build)
  * [Security benchmarks](#security-benchmarks)
    * [Benchmark 1: 'PBKDF2' password hashing algorithm](#benchmark-1-PBKDF2-password-hashing-algorithm)
    * [Benchmark 2: 'bcrypt' password hashing algorithm](#benchmark-2-bcrypt-password-hashing-algorithm)
    * [Benchmark 3: 'scrypt' password hashing algorithm](#benchmark-3-scrypt-password-hashing-algorithm)
    * [Benchmark 4: 'Argon2' password hashing algorithm](#benchmark-4-argon2-password-hashing-algorithm)

# Features
* Cross platform (Linux, OSX, Windows)
* Benchmarks
* Examples
* Tests
* [Doxygen](http://www.doxygen.org) API documentation
* Continuous integration ([Travis CI](https://travis-ci.com), [AppVeyor](https://www.appveyor.com))

# Requirements
* Linux (binutils-dev uuid-dev)
* OSX
* Windows 10
* [cmake](https://www.cmake.org)
* [gcc](https://gcc.gnu.org)
* [git](https://git-scm.com)
* [gil](https://github.com/chronoxor/gil.git)

Optional:
* [clang](https://clang.llvm.org)
* [CLion](https://www.jetbrains.com/clion)
* [Cygwin](https://cygwin.com)
* [MinGW](https://mingw-w64.org/doku.php)
* [Visual Studio](https://www.visualstudio.com)

# How to build?

### Install [gil (git links) tool](https://github.com/chronoxor/gil)
```shell
pip3 install gil
```

### Setup repository
```shell
git clone https://github.com/chronoxor/CppSecurity.git
cd CppSecurity
gil update
```

### Linux
```shell
cd build
./unix.sh
```

### OSX
```shell
cd build
./unix.sh
```

### Windows (Cygwin)
```shell
cd build
cygwin.bat
```

### Windows (MinGW)
```shell
cd build
mingw.bat
```

### Windows (Visual Studio)
```shell
cd build
vs.bat
```

# Security benchmarks

## Benchmark 1: 'PBKDF2' password hashing algorithm
Benchmark source file: [password_hashing_pbkdf2.cpp](https://github.com/chronoxor/CppSecurity/blob/master/performance/password_hashing_pbkdf2.cpp)

Benchmark report is the following:
```
===============================================================================
CppBenchmark report. Version 1.0.0.0
===============================================================================
CPU architecutre: Intel(R) Core(TM) i7-4790K CPU @ 4.00GHz
CPU logical cores: 8
CPU physical cores: 4
CPU clock speed: 3.998 GHz
CPU Hyper-Threading: enabled
RAM total: 31.962 GiB
RAM free: 18.634 GiB
===============================================================================
OS version: Microsoft Windows 8 Enterprise Edition (build 9200), 64-bit
OS bits: 64-bit
Process bits: 64-bit
Process configuaraion: release
Local timestamp: Thu Jun  6 01:41:13 2019
UTC timestamp: Wed Jun  5 22:41:13 2019
===============================================================================
Benchmark: 'PBKDF2' generate
Attempts: 5
Duration: 5 seconds
-------------------------------------------------------------------------------
Phase: 'PBKDF2' generate
Average time: 40.037 ms/op
Minimal time: 40.037 ms/op
Maximal time: 47.907 ms/op
Total time: 4.404 s
Total operations: 110
Operations throughput: 24 ops/s
===============================================================================
Benchmark: 'PBKDF2' validate
Attempts: 5
Duration: 5 seconds
-------------------------------------------------------------------------------
Phase: 'PBKDF2' validate
Average time: 39.656 ms/op
Minimal time: 39.656 ms/op
Maximal time: 44.473 ms/op
Total time: 4.481 s
Total operations: 113
Operations throughput: 25 ops/s
===============================================================================
```

## Benchmark 2: 'bcrypt' password hashing algorithm
Benchmark source file: [password_hashing_bcrypt.cpp](https://github.com/chronoxor/CppSecurity/blob/master/performance/password_hashing_bcrypt.cpp)

Benchmark report is the following:
```
===============================================================================
CppBenchmark report. Version 1.0.0.0
===============================================================================
CPU architecutre: Intel(R) Core(TM) i7-4790K CPU @ 4.00GHz
CPU logical cores: 8
CPU physical cores: 4
CPU clock speed: 3.998 GHz
CPU Hyper-Threading: enabled
RAM total: 31.962 GiB
RAM free: 18.631 GiB
===============================================================================
OS version: Microsoft Windows 8 Enterprise Edition (build 9200), 64-bit
OS bits: 64-bit
Process bits: 64-bit
Process configuaraion: release
Local timestamp: Thu Jun  6 01:50:08 2019
UTC timestamp: Wed Jun  5 22:50:08 2019
===============================================================================
Benchmark: 'bcrypt' generate
Attempts: 5
Duration: 5 seconds
-------------------------------------------------------------------------------
Phase: 'bcrypt' generate
Average time: 184.043 ms/op
Minimal time: 184.043 ms/op
Maximal time: 185.843 ms/op
Total time: 4.785 s
Total operations: 26
Operations throughput: 5 ops/s
===============================================================================
Benchmark: 'bcrypt' validate
Attempts: 5
Duration: 5 seconds
-------------------------------------------------------------------------------
Phase: 'bcrypt' validate
Average time: 185.383 ms/op
Minimal time: 185.383 ms/op
Maximal time: 230.264 ms/op
Total time: 3.893 s
Total operations: 21
Operations throughput: 5 ops/s
===============================================================================
```

## Benchmark 3: 'scrypt' password hashing algorithm
Benchmark source file: [password_hashing_scrypt.cpp](https://github.com/chronoxor/CppSecurity/blob/master/performance/password_hashing_scrypt.cpp)

Benchmark report is the following:
```
===============================================================================
CppBenchmark report. Version 1.0.0.0
===============================================================================
CPU architecutre: Intel(R) Core(TM) i7-4790K CPU @ 4.00GHz
CPU logical cores: 8
CPU physical cores: 4
CPU clock speed: 3.998 GHz
CPU Hyper-Threading: enabled
RAM total: 31.962 GiB
RAM free: 18.143 GiB
===============================================================================
OS version: Microsoft Windows 8 Enterprise Edition (build 9200), 64-bit
OS bits: 64-bit
Process bits: 64-bit
Process configuaraion: release
Local timestamp: Thu Jun  6 02:06:41 2019
UTC timestamp: Wed Jun  5 23:06:41 2019
===============================================================================
Benchmark: 'scrypt' generate
Attempts: 5
Duration: 5 seconds
-------------------------------------------------------------------------------
Phase: 'scrypt' generate
Average time: 929.820 mcs/op
Minimal time: 929.820 mcs/op
Maximal time: 950.750 mcs/op
Total time: 4.929 s
Total operations: 5302
Operations throughput: 1075 ops/s
===============================================================================
Benchmark: 'scrypt' validate
Attempts: 5
Duration: 5 seconds
-------------------------------------------------------------------------------
Phase: 'scrypt' validate
Average time: 846.707 mcs/op
Minimal time: 846.707 mcs/op
Maximal time: 882.812 mcs/op
Total time: 4.926 s
Total operations: 5819
Operations throughput: 1181 ops/s
===============================================================================
```

## Benchmark 4: 'Argon2' password hashing algorithm
Benchmark source file: [password_hashing_argon2.cpp](https://github.com/chronoxor/CppSecurity/blob/master/performance/password_hashing_argon2.cpp)

Benchmark report is the following:
```
===============================================================================
CppBenchmark report. Version 1.0.0.0
===============================================================================
CPU architecutre: Intel(R) Core(TM) i7-4790K CPU @ 4.00GHz
CPU logical cores: 8
CPU physical cores: 4
CPU clock speed: 3.998 GHz
CPU Hyper-Threading: enabled
RAM total: 31.962 GiB
RAM free: 18.088 GiB
===============================================================================
OS version: Microsoft Windows 8 Enterprise Edition (build 9200), 64-bit
OS bits: 64-bit
Process bits: 64-bit
Process configuaraion: release
Local timestamp: Thu Jun  6 01:58:59 2019
UTC timestamp: Wed Jun  5 22:58:59 2019
===============================================================================
Benchmark: 'Argon2d' generate
Attempts: 5
Duration: 5 seconds
-------------------------------------------------------------------------------
Phase: 'Argon2d' generate
Average time: 21.976 ms/op
Minimal time: 21.976 ms/op
Maximal time: 24.577 ms/op
Total time: 4.725 s
Total operations: 215
Operations throughput: 45 ops/s
===============================================================================
Benchmark: 'Argon2d' validate
Attempts: 5
Duration: 5 seconds
-------------------------------------------------------------------------------
Phase: 'Argon2d' validate
Average time: 24.346 ms/op
Minimal time: 24.346 ms/op
Maximal time: 26.231 ms/op
Total time: 4.796 s
Total operations: 197
Operations throughput: 41 ops/s
===============================================================================
Benchmark: 'Argon2i' generate
Attempts: 5
Duration: 5 seconds
-------------------------------------------------------------------------------
Phase: 'Argon2i' generate
Average time: 35.866 ms/op
Minimal time: 35.866 ms/op
Maximal time: 37.678 ms/op
Total time: 4.806 s
Total operations: 134
Operations throughput: 27 ops/s
===============================================================================
Benchmark: 'Argon2i' validate
Attempts: 5
Duration: 5 seconds
-------------------------------------------------------------------------------
Phase: 'Argon2i' validate
Average time: 36.342 ms/op
Minimal time: 36.342 ms/op
Maximal time: 39.705 ms/op
Total time: 4.724 s
Total operations: 130
Operations throughput: 27 ops/s
===============================================================================
Benchmark: 'Argon2id' generate
Attempts: 5
Duration: 5 seconds
-------------------------------------------------------------------------------
Phase: 'Argon2id' generate
Average time: 22.421 ms/op
Minimal time: 22.421 ms/op
Maximal time: 23.605 ms/op
Total time: 4.820 s
Total operations: 215
Operations throughput: 44 ops/s
===============================================================================
Benchmark: 'Argon2id' validate
Attempts: 5
Duration: 5 seconds
-------------------------------------------------------------------------------
Phase: 'Argon2id' validate
Average time: 21.772 ms/op
Minimal time: 21.772 ms/op
Maximal time: 23.773 ms/op
Total time: 4.768 s
Total operations: 219
Operations throughput: 45 ops/s
===============================================================================
```
