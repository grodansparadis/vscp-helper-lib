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
