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