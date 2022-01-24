# vscp-helper-lib

![License](https://img.shields.io/badge/license-MIT-blue.svg)
![Linux Build](https://github.com/grodansparadis/vscp-helper-lib/actions/workflows/build.yml/badge.svg) 
![Windows Build](https://github.com/grodansparadis/vscp-helper-lib/actions/workflows/msbuild.yml/badge.svg)
[![Project Status: Active – The project has reached a stable, usable state and is being actively developed.](https://www.repostatus.org/badges/latest/active.svg)](https://www.repostatus.org/#active)


Helper functionality packed in a shared library for [VSCP](https://www.vscp.org)

<img src="https://vscp.org/images/logo.png" width="100">

**Available for**: Linux, Windows

Full documentation is [here](https://docs.vscp.org/#vscphelper).

Wrapper for Python is [here](https://github.com/grodansparadis/pyvscp)

Wrapper for node.js is [here](https://github.com/grodansparadis/node-vscp-helper).

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
The VSCP helper lib is built using a standard cmake build.

```bash
  git clone https://github.com/grodansparadis/vscp.git
  git clone https://github.com/grodansparadis/vscp-helper-lib.git
```
The two projects should be cloned on the same directory level. vscp-helper-lib is the main project and use code from the main VSCP project. If you absolutely want to have them installed on separate places you can use the _-DVSCP_PATH="path to vscp" .._ option to set the path to the VSCP project.

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

### Install Visual Studio 2019 Buildtools

You can install them from: https://visualstudio.microsoft.com/en/downloads. You find them in the _Tools for Visual Studio 2019_ on the lower part of the page. 

In the Visual Studio Installer, select:
  
  - Tab "Workloads": Buildtools for the universal windows platform

### Install the latest cmake

You find it here https://cmake.org/install/

### Install git

You find it here https://gitforwindows.org/
### Install the vcpkg package manager

Open a Visual Studio 2019 command prompt (_x64 Native Tools Command Prompt_) window and type:
    
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
  git clone https://github.com/grodansparadis/vscp.git
  git clone https://github.com/grodansparadis/vscp-helper-lib.git
```
The two projects should be cloned on the same directory level. vscp-helper-lib is the main project and use code from the main VSCP project. If you absolutely want to have them installed on separate places you can use the _-DVSCP_PATH="path to vscp" .._ option to set the path to the VSCP project.

### Build vscp-helper-lib

```bash
  cd vscp-helper-lib
  mkdir build
  cd build
  cmake .. -G "Visual Studio 16 2019" -DVCPKG_TARGET_TRIPLET=x64-windows  -DCMAKE_TOOLCHAIN_FILE=C:\Users\Administrator\Desktop\Development\vcpkg\scripts\buildsystems\vcpkg.cmake
```

The path to the vspkg build script is obviously different in your case.

Now use

```bash
  cmake --build .
```

to build the dynamic library. An alternative is to use

```bash
  msbuild libvscphelper.sln /p:Configuration=Release
```

You can also open the _vscphelper.sln_ in Visual Studio 2019 and work with it there.

Now you can use 

```bash
cpack
```

to build an installation package for windows.