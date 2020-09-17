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
    * [Benchmark 1: Password generator](#benchmark-1-password-generator)
    * [Benchmark 2: Google Authenticator](#benchmark-2-google-authenticator)
    * [Benchmark 3: 'PBKDF2' password hashing algorithm](#benchmark-3-PBKDF2-password-hashing-algorithm)
    * [Benchmark 4: 'bcrypt' password hashing algorithm](#benchmark-4-bcrypt-password-hashing-algorithm)
    * [Benchmark 5: 'scrypt' password hashing algorithm](#benchmark-5-scrypt-password-hashing-algorithm)
    * [Benchmark 6: 'Argon2' password hashing algorithm](#benchmark-6-argon2-password-hashing-algorithm)

# Features
* Cross platform (Linux, OSX, Windows)
* Password generator
* [Google Authenticator](https://en.wikipedia.org/wiki/Google_Authenticator) support
* Password hashing algorithms ([PBKDF2](https://en.wikipedia.org/wiki/PBKDF2), [bcrypt](https://en.wikipedia.org/wiki/Bcrypt), [scrypt](https://en.wikipedia.org/wiki/Scrypt), [Argon2](https://en.wikipedia.org/wiki/Argon2))

# Requirements
* Linux (binutils-dev uuid-dev libssl-dev)
* OSX (openssl)
* Windows 10
* [cmake](https://www.cmake.org)
* [gcc](https://gcc.gnu.org)
* [git](https://git-scm.com)
* [gil](https://github.com/chronoxor/gil.git)
* [python3](https://www.python.org)

Optional:
* [clang](https://clang.llvm.org)
* [CLion](https://www.jetbrains.com/clion)
* [Cygwin](https://cygwin.com)
* [MSYS2](https://www.msys2.org)
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
unix.bat
```

### Windows (MSYS2)
```shell
cd build
unix.bat
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

## Benchmark 1: Password generator
Benchmark source file: [password_generator.cpp](https://github.com/chronoxor/CppSecurity/blob/master/performance/password_generator.cpp)

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
RAM free: 24.476 GiB
===============================================================================
OS version: Microsoft Windows 8 Enterprise Edition (build 9200), 64-bit
OS bits: 64-bit
Process bits: 64-bit
Process configuaraion: release
Local timestamp: Wed Jun 12 01:55:58 2019
UTC timestamp: Tue Jun 11 22:55:58 2019
===============================================================================
Benchmark: Generate password
Attempts: 5
Duration: 5 seconds
-------------------------------------------------------------------------------
Phase: Generate password
Average time: 73.490 mcs/op
Minimal time: 73.490 mcs/op
Maximal time: 76.286 mcs/op
Total time: 4.925 s
Total operations: 67019
Operations throughput: 13607 ops/s
===============================================================================
Benchmark: Validate password
Attempts: 5
Duration: 5 seconds
-------------------------------------------------------------------------------
Phase: Validate password
Average time: 19 ns/op
Minimal time: 19 ns/op
Maximal time: 20 ns/op
Total time: 1.944 s
Total operations: 97525818
Operations throughput: 50161060 ops/s
===============================================================================
```

## Benchmark 2: Google Authenticator
Benchmark source file: [google_authenticator.cpp](https://github.com/chronoxor/CppSecurity/blob/master/performance/google_authenticator.cpp)

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
RAM free: 24.470 GiB
===============================================================================
OS version: Microsoft Windows 8 Enterprise Edition (build 9200), 64-bit
OS bits: 64-bit
Process bits: 64-bit
Process configuaraion: release
Local timestamp: Wed Jun 12 01:57:37 2019
UTC timestamp: Tue Jun 11 22:57:37 2019
===============================================================================
Benchmark: Generate Google Authenticator secret
Attempts: 5
Duration: 5 seconds
-------------------------------------------------------------------------------
Phase: Generate Google Authenticator secret
Average time: 75.167 mcs/op
Minimal time: 75.167 mcs/op
Maximal time: 77.377 mcs/op
Total time: 4.882 s
Total operations: 64960
Operations throughput: 13303 ops/s
===============================================================================
Benchmark: Generate Google Authenticator token
Attempts: 5
Duration: 5 seconds
-------------------------------------------------------------------------------
Phase: Generate Google Authenticator token
Average time: 1.244 mcs/op
Minimal time: 1.244 mcs/op
Maximal time: 1.260 mcs/op
Total time: 4.847 s
Total operations: 3894253
Operations throughput: 803368 ops/s
===============================================================================
```

## Benchmark 3: 'PBKDF2' password hashing algorithm
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
RAM free: 17.1017 GiB
===============================================================================
OS version: Microsoft Windows 8 Enterprise Edition (build 9200), 64-bit
OS bits: 64-bit
Process bits: 64-bit
Process configuaraion: release
Local timestamp: Thu Jun  6 02:52:55 2019
UTC timestamp: Wed Jun  5 23:52:55 2019
===============================================================================
Benchmark: 'PBKDF2' generate
Attempts: 5
Duration: 5 seconds
-------------------------------------------------------------------------------
Phase: 'PBKDF2' generate
Average time: 491.718 mcs/op
Minimal time: 491.718 mcs/op
Maximal time: 507.445 mcs/op
Total time: 4.933 s
Total operations: 10034
Operations throughput: 2033 ops/s
===============================================================================
Benchmark: 'PBKDF2' validate
Attempts: 5
Duration: 5 seconds
-------------------------------------------------------------------------------
Phase: 'PBKDF2' validate
Average time: 403.262 mcs/op
Minimal time: 403.262 mcs/op
Maximal time: 412.173 mcs/op
Total time: 4.976 s
Total operations: 12341
Operations throughput: 2479 ops/s
===============================================================================
```

## Benchmark 4: 'bcrypt' password hashing algorithm
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
RAM free: 17.921 GiB
===============================================================================
OS version: Microsoft Windows 8 Enterprise Edition (build 9200), 64-bit
OS bits: 64-bit
Process bits: 64-bit
Process configuaraion: release
Local timestamp: Thu Jun  6 02:59:34 2019
UTC timestamp: Wed Jun  5 23:59:34 2019
===============================================================================
Benchmark: 'bcrypt' generate
Attempts: 5
Duration: 5 seconds
-------------------------------------------------------------------------------
Phase: 'bcrypt' generate
Average time: 950.807 mcs/op
Minimal time: 950.807 mcs/op
Maximal time: 960.204 mcs/op
Total time: 4.986 s
Total operations: 5245
Operations throughput: 1051 ops/s
===============================================================================
Benchmark: 'bcrypt' validate
Attempts: 5
Duration: 5 seconds
-------------------------------------------------------------------------------
Phase: 'bcrypt' validate
Average time: 862.694 mcs/op
Minimal time: 862.694 mcs/op
Maximal time: 867.637 mcs/op
Total time: 4.988 s
Total operations: 5783
Operations throughput: 1159 ops/s
===============================================================================
```

## Benchmark 5: 'scrypt' password hashing algorithm
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
RAM free: 18.052 GiB
===============================================================================
OS version: Microsoft Windows 8 Enterprise Edition (build 9200), 64-bit
OS bits: 64-bit
Process bits: 64-bit
Process configuaraion: release
Local timestamp: Thu Jun  6 02:42:32 2019
UTC timestamp: Wed Jun  5 23:42:32 2019
===============================================================================
Benchmark: 'scrypt' generate
Attempts: 5
Duration: 5 seconds
-------------------------------------------------------------------------------
Phase: 'scrypt' generate
Average time: 956.991 mcs/op
Minimal time: 956.991 mcs/op
Maximal time: 982.195 mcs/op
Total time: 4.983 s
Total operations: 5207
Operations throughput: 1044 ops/s
===============================================================================
Benchmark: 'scrypt' validate
Attempts: 5
Duration: 5 seconds
-------------------------------------------------------------------------------
Phase: 'scrypt' validate
Average time: 857.232 mcs/op
Minimal time: 857.232 mcs/op
Maximal time: 916.809 mcs/op
Total time: 4.781 s
Total operations: 5578
Operations throughput: 1166 ops/s
===============================================================================
```

## Benchmark 6: 'Argon2' password hashing algorithm
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
RAM free: 18.026 GiB
===============================================================================
OS version: Microsoft Windows 8 Enterprise Edition (build 9200), 64-bit
OS bits: 64-bit
Process bits: 64-bit
Process configuaraion: release
Local timestamp: Thu Jun  6 02:45:53 2019
UTC timestamp: Wed Jun  5 23:45:53 2019
===============================================================================
Benchmark: 'Argon2d' generate
Attempts: 5
Duration: 5 seconds
-------------------------------------------------------------------------------
Phase: 'Argon2d' generate
Average time: 824.018 mcs/op
Minimal time: 824.018 mcs/op
Maximal time: 844.418 mcs/op
Total time: 4.932 s
Total operations: 5986
Operations throughput: 1213 ops/s
===============================================================================
Benchmark: 'Argon2d' validate
Attempts: 5
Duration: 5 seconds
-------------------------------------------------------------------------------
Phase: 'Argon2d' validate
Average time: 744.765 mcs/op
Minimal time: 744.765 mcs/op
Maximal time: 791.891 mcs/op
Total time: 4.778 s
Total operations: 6416
Operations throughput: 1342 ops/s
===============================================================================
Benchmark: 'Argon2i' generate
Attempts: 5
Duration: 5 seconds
-------------------------------------------------------------------------------
Phase: 'Argon2i' generate
Average time: 851.280 mcs/op
Minimal time: 851.280 mcs/op
Maximal time: 921.955 mcs/op
Total time: 4.768 s
Total operations: 5601
Operations throughput: 1174 ops/s
===============================================================================
Benchmark: 'Argon2i' validate
Attempts: 5
Duration: 5 seconds
-------------------------------------------------------------------------------
Phase: 'Argon2i' validate
Average time: 747.924 mcs/op
Minimal time: 747.924 mcs/op
Maximal time: 764.430 mcs/op
Total time: 4.961 s
Total operations: 6634
Operations throughput: 1337 ops/s
===============================================================================
Benchmark: 'Argon2id' generate
Attempts: 5
Duration: 5 seconds
-------------------------------------------------------------------------------
Phase: 'Argon2id' generate
Average time: 828.117 mcs/op
Minimal time: 828.117 mcs/op
Maximal time: 858.997 mcs/op
Total time: 4.935 s
Total operations: 5960
Operations throughput: 1207 ops/s
===============================================================================
Benchmark: 'Argon2id' validate
Attempts: 5
Duration: 5 seconds
-------------------------------------------------------------------------------
Phase: 'Argon2id' validate
Average time: 738.366 mcs/op
Minimal time: 738.366 mcs/op
Maximal time: 791.300 mcs/op
Total time: 4.698 s
Total operations: 6363
Operations throughput: 1354 ops/s
===============================================================================
```
