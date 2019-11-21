# vscp-helper-lib

Helper functionality for VSCP packed in a library

<img src="https://vscp.org/images/logo.png" width="100">

**Available for**: Linux, Windows

Full documentation is [here](https://grodansparadis.gitbooks.io/the-vscp-helper-library/).


## How to install on Linux

> sudo dpkg -i libvscphelper14-14.0.0.deb

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