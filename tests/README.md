# Unittests for the VSCP helper< library

Unittests for the vscp helper library code.

Use 

```
mkdir build
cd build
cmake .. -G "Visual Studio 16 2019" -DVCPKG_TARGET_TRIPLET=x64-windows  -DCMAKE_TOOLCHAIN_FILE=C:\Users\Administrator\Desktop\Development\vcpkg\scripts\buildsystems\vcpkg.cmake
```

in each test folder to create a makefile. Then do

```
cmake --build . --config Release
```

or 

```
msbuild libvscphelper.sln /p:Configuration=Release
```

to build the unittest.   Run the test with

```
./unittest
```

## Local TCP/TLS transport tests

The transport tests use the pinned VSCP project's loopback test servers and do
not require a running VSCP daemon. They require Google Test, Python 3.7 or
later, and the `openssl` command.

They exercise the exported C API's TLS options, including explicit CA files
and directories, mutual TLS with an encrypted client key, verification
failures, transport-mode precedence, per-session isolation, and reconnects.
Certificates and loopback ports are created temporarily by the test runner.

Binary-link tests cover negotiation, mode/reset behavior, raw reads/writes
over TCP and TLS, 1-byte and 65,535-byte transport boundaries, coalesced frames,
partial-prefix/payload timeouts, malformed/disconnected streams, library-owned
receive buffers, and existing event APIs operating in binary mode.

Authenticated framing tests cover all three AES key sizes, an independently
published deterministic AES/HMAC vector, wrong/tampered records, version and
algorithm downgrade rejection, partial/coalesced records, maximum plaintext
length, and encrypted event confirmations. The Python peer uses OpenSSL's CLI
for AES and Python's `hmac` module independently of the library implementation.
No additional Python packages are needed.

The client transport patch is applied only to a build-local copy.
`test_dependency_fetch` also checks that fetched source files remain unchanged.

From the repository root, run:

```bash
cmake -S . -B build -DBUILD_ALLTEST=ON
cmake --build build --target test_tcp_transport
```

To check that the dependency configuration works without a Mongoose source
checkout or network access, run:

```bash
cmake --build build --target test_dependency_fetch
```

## Version metadata tests

From the repository root, run:

```bash
python3 -B -m unittest discover -s tests -p 'test_versioning.py'
```

To test the exported library-version function without a running VSCP daemon:

```bash
cmake -S . -B build -DBUILD_ALLTEST=ON
cmake --build build --target unittest
cd build/tests/alltest
../../unittest 1 --gtest_filter='LibraryVersion.*'
```
