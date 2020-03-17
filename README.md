# vscp-helper-lib

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

it is good to know that it is a [known apt problem](https://forums.linuxmint.com/viewtopic.php?t=280054) that you safely can ignore.

or 

```bash
> sudo dpkg -i ./libvscphelper14_14.0.0-1_amd64.deb
> sudo dpkg -i ./libvscphelper14-dev_14.0.0-1_amd64.deb
```

## How to install on Windows
Install using the windows installation script available in the release section och this repository.

## How to build on Linux
The VSCP helper lib is built using a standard autoconf build

```bash
./configure
git submodule foreach git pull origin master
make
make install
```

## How to build on Windows
tbd


