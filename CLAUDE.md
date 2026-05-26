# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Repository purpose

CppSecurity is a C++23 static library (`libcppsecurity`) that wraps OpenSSL and three bundled primitives (Argon2, libbcrypt, libscrypt) behind a single `CppSecurity::` namespace. It offers:

- `PasswordGenerator` and `std::password` (a `std::string` subclass with a zero-fill destructor and `PasswordAllocator` for secure scrubbing).
- A `PasswordHashing` interface with concrete `PasswordHashingPBKDF2`, `PasswordHashingBcrypt`, `PasswordHashingScrypt`, and `PasswordHashing{Argon2d,Argon2i,Argon2id}` subclasses.
- `Cipher` — symmetric AES/ARIA/Camellia (128/192/256) over OpenSSL EVP.
- `GoogleAuthenticator` — TOTP (RFC 6238) / HOTP (RFC 4226).

## Working with submodules

External code is **not** checked into git. `modules/` is empty until populated by [gil](https://github.com/chronoxor/gil) (`pip3 install gil`, then `gil update` at the repo root) following the recipe in `.gitlinks`. CMake configure fails until this is done because `modules/CMakeLists.txt` expects `Argon2/`, `Catch2/`, `CppBenchmark/`, `CppCommon/`, `libbcrypt/`, `libscrypt/`, `OpenSSL/` to exist. The `build/` and `cmake/` directories are likewise gil-managed submodules (see their own `CLAUDE.md` files for their contracts).

`.gitignore` excludes `modules/*` except `CMakeLists.txt` and the `*.cmake` shims — don't commit anything inside a module subdirectory from this repo.

## Build, test, run

The top-level wrappers chain configure → build → ctest → install into `temp/` and `temp/install/`, with binaries also copied to `bin/`:

```sh
cd build && ./unix.sh           # Linux / MacOS
cd build && unix.bat            # Windows (Cygwin/MSYS2)
cd build && mingw.bat           # Windows (MinGW)
cd build && vs.bat              # Windows (Visual Studio, RelWithDebInfo x64)
```

Individual steps (run from inside the toolchain directory — the scripts do `cd ../..`):

```sh
cd build/Unix && ./01-generate.sh   # cmake configure into ../../temp
cd build/Unix && ./02-build.sh      # build all targets
cd build/Unix && ./03-tests.sh      # ctest -V (tolerates failures on Unix)
cd build/Unix && ./07-coverage.sh   # reconfigure with -DCODE_COVERAGE=ON, gcovr, opens HTML
```

The Catch2 test binary supports filtered and single-test runs:

```sh
./bin/cppsecurity-tests --list-tests
./bin/cppsecurity-tests "[CppSecurity]"
./bin/cppsecurity-tests "Password"           # exact test-case name
./bin/cppsecurity-tests --durations yes --order lex
```

Examples and benchmarks build as separate executables under `bin/cppsecurity-example-*` and `bin/cppsecurity-performance-*` — run them directly.

## Architecture

The library has one CMake target (`cppsecurity`) with a flat layout:

- `include/security/*.h` + `.inl` — public headers, all under `namespace CppSecurity` (except `std::password` which is intentionally injected into `std`).
- `source/security/*.cpp` — implementations matched 1:1 to headers.
- `tests/`, `examples/`, `performance/` — each `*.cpp` becomes its own executable target (globbed in [CMakeLists.txt](CMakeLists.txt)). Adding a new file is enough; no manifest to update.
- `modules/` — bundled dependencies linked into `cppsecurity`: `Argon2`, `libbcrypt`, `libscrypt`, plus header-only `CppCommon` and the OpenSSL find shim.

The `PasswordHashing` base class implements `GenerateSalt`, `GenerateHashAndSalt`, `GenerateDigest` (with Base64 variant) and `Validate(password, digest)`; subclasses only override `name()` and `GenerateHash(password, salt)`. When adding a new algorithm, follow this contract and link the underlying crypto library in `CMakeLists.txt:76` (`target_link_libraries(cppsecurity ...)`).

OpenSSL discovery is platform-branched in `CMakeLists.txt:31-46`: APPLE uses `/usr/local/opt/openssl@3`, MinGW/MSVC use vendored static libs from `modules/OpenSSL/`, Cygwin uses system `.dll.a`. When touching this block, mirror the static-vs-dynamic intent across platforms.

`std::password` (in [password.h](include/security/password.h)) is the canonical type for passing plaintext passwords through APIs — its destructor zero-fills the buffer via `CppCommon::Memory::ZeroFill`. Prefer it over `std::string` in any new API surface that takes a password.

Compile flags come from sibling submodule `cmake/`: `PEDANTIC_COMPILE_FLAGS` (set by `SetCompilerWarnings.cmake`) is applied to every target in this repo — treat warnings as errors when editing.

## CI

`.github/workflows/build-{linux-gcc,linux-clang,macos,windows-*}.yml` run the matching toolchain wrapper. `doxygen.yml` publishes API docs from `documents/` to `gh-pages` (step `05-doxygen` — has real remote side effects, don't invoke locally while iterating).
