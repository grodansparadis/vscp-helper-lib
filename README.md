# vscp-helper-lib

![License](https://img.shields.io/badge/license-MIT-blue.svg)
![Linux Build](https://github.com/grodansparadis/vscp-helper-lib/actions/workflows/build.yml/badge.svg) 
[![macOS Build](https://github.com/grodansparadis/vscp-helper-lib/actions/workflows/macos.yml/badge.svg)](https://github.com/grodansparadis/vscp-helper-lib/actions/workflows/macos.yml)
[![Raspberry Pi ARM64 Build](https://github.com/grodansparadis/vscp-helper-lib/actions/workflows/arm64.yml/badge.svg)](https://github.com/grodansparadis/vscp-helper-lib/actions/workflows/arm64.yml)
[![Raspberry Pi ARMHF Build](https://github.com/grodansparadis/vscp-helper-lib/actions/workflows/armhf.yml/badge.svg)](https://github.com/grodansparadis/vscp-helper-lib/actions/workflows/armhf.yml)
![Windows Build](https://github.com/grodansparadis/vscp-helper-lib/actions/workflows/msbuild.yml/badge.svg)
[![Project Status: Active – The project has reached a stable, usable state and is being actively developed.](https://www.repostatus.org/badges/latest/active.svg)](https://www.repostatus.org/#active)

![VSCP Helper Library](./docs/images/libvscphelper.jpeg)


Helper functionality packed in a shared library for [VSCP](https://www.vscp.org)

**Available for**: Linux, Raspberry Pi,  Windows, Macintosh

  - Full documentation is [here](https://docs.vscp.org/#vscphelper).
  - Wrapper for Python is [here](https://github.com/grodansparadis/pyvscp)
  - Wrapper for node.js is [here](https://github.com/grodansparadis/node-vscp-helper).

## How to install on Linux

Download the latest Debian install file(s) for your system from the release section of this repository. If you just want to use a binary that depend on this library there is no need to download the dev version. If you, on the other hand, expect to use the library for development you should download and install both (the dev version holds header files etc).

```bash
> sudo apt install ./libvscphelper14_14.0.0-1_amd64.deb
> ./libvscphelper14-dev_14.0.0-1_amd64.deb
```

If you get 

*couldn't be accessed by user '_apt'. - pkgAcquire::Run (13: Permission denied)* 

it is good to know that it is a [known apt problem](https://forums.linuxmint.com/viewtopic.php?t=280054) that you safely can ignore. If it feels bad use *apt-get* to install instead.

or 

```bash
> sudo dpkg -i ./libvscphelper14_14.0.0-1_amd64.deb
> sudo dpkg -i ./libvscphelper14-dev_14.0.0-1_amd64.deb
```

## How to install on Windows
Install using the windows installation script available in the release section och this repository.

## How to build on Linux
The VSCP helper lib is built using a standard cmake build (cmake 3.14 or later).

```bash
  git clone https://github.com/grodansparadis/vscp-helper-lib.git
```

Third party code (the [VSCP main project](https://github.com/grodansparadis/vscp), [spdlog](https://github.com/gabime/spdlog) and [nlohmann JSON](https://github.com/nlohmann/json)) is downloaded automatically by cmake (FetchContent) when the project is configured, so no submodules or separate clones are needed. Pinned versions are set in _cmake/VscpHelperDependencies.cmake_. To use a local checkout instead of downloading, use for example _-DFETCHCONTENT_SOURCE_DIR_VSCP="path to vscp"_.

Use a fresh build directory after an earlier Mongoose-based build; CMake does
not remove previously downloaded sources or build artifacts.

TLS connections (`stcp://host:port`) verify server certificates and hostnames by default. For a private CA, configure OpenSSL's trust store or use `SSL_CERT_FILE` or `SSL_CERT_DIR`.

For the ssl build, additional openssl is necessary:

```bash
apt-get install libssl-dev
```

Now do 

```
  cd vscp-helper-lib
  mkdir build
  cd build
  cmake ..
  make
  make install
```


## How to build on Windows

### Install Visual Studio 2022 Buildtools

You can install them from: https://visualstudio.microsoft.com/en/downloads. You find them in the _Tools for Visual Studio 2022_ on the lower part of the page. 

In the Visual Studio Installer, select:
  
  - Tab "Workloads": Buildtools for the universal windows platform

### Install the latest cmake

You find it here https://cmake.org/install/

### Install git

You find it here https://gitforwindows.org/
### Install the vcpkg package manager

Open a Visual Studio 2022 command prompt (_x64 Native Tools Command Prompt_) window and type:
    
```bash    
  git clone https://github.com/microsoft/vcpkg.git
  cd vcpkg
  bootstrap-vcpkg.bat
``` 
  
### Integrate vcpkg with Visual Studio 

``` bash
  vcpkg integrate install
```
  
###  Install needed vspkg packages

```bash
  vcpkg install dlfcn-win32:x64-windows
  vcpkg install expat:x64-windows
  vcpkg install openssl:x64-windows
  vcpkg install pthreads:x64-windows
```

### Clone needed VSCP code

```bash
  git clone https://github.com/grodansparadis/vscp-helper-lib.git
```
Third party code (VSCP main project, spdlog and nlohmann JSON) is downloaded automatically by cmake when the project is configured.

### Build vscp-helper-lib

```bash
  cd vscp-helper-lib
  mkdir build
  cd build

  cmake .. -G "Visual Studio 17 2022" -DVCPKG_TARGET_TRIPLET=x64-windows -D CMAKE_BUILD_TYPE=Release -DVCPKG_ROOT=G:/vcpkg/-DCMAKE_TOOLCHAIN_FILE=g:\vcpkg\scripts\buildsystems\vcpkg.cmake

```

The path to the vspkg build script (_E:\vcpkg\scripts\buildsystems.._) is obviously different in your case.

Now use

```bash
  cmake --build . --config Release
```

to build the dynamic library (Relase or Debug). 

An alternative is to use

```bash
  msbuild libvscphelper.sln /p:Configuration=Release
```

You can also open the _vscphelper.sln_ in Visual Studio 2019 and work with it there.

Now you can use 

```bash
cpack
```

to build an installation package for windows.