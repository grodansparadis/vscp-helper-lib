# ![](/assets/logo_100.png)

# The VSCP helper library

Author 2000-2026 Åke Hedman and contributors, [the VSCP Project](https://www.vscp.org);

**Document created**: *${/var/creation-time}*
**Document version**: ${/var/document-version}

!["VSCP Helper Library"](./images/libvscphelper.jpeg )

The VSCP helper library provides tools for developing VSCP applications. It includes functions for working with Level I drivers (formerly called CANAL drivers), communicating with a local or remote VSCP daemon (Level II) over TCP/IP, and performing other common tasks. The library includes both helper and communication functions.

You can use the library as a dynamically loaded binary that exports C functions, or include its C++ classes in your project.

The library is currently available for:

  * [C/C++](https://github.com/grodansparadis/vscp-helper-lib)
  * [Python](https://github.com/grodansparadis/pyvscp)
  * [Node.js](https://github.com/grodansparadis/node-vscp-helper)
  
It runs on Unix/Linux, macOS, and Windows.

The library is licensed under the [MIT License](https://opensource.org/licenses/MIT), so it can be used freely in open- and closed-source projects.

You can view or download the VSCP helper library documentation [here](https://docs.vscp.org/#vscphelper).

## About versioning

VSCP release versions use the format `year.month.patch`, where `year` is the last two digits of the year and `month` is the two-digit month. The patch number is incremented for each release within the same month.

Library releases follow the same pattern, but library binaries use a different scheme so that software using the library can determine whether it is compatible with the version it depends on. Binary versions use `major.minor.patch`. A change to the major number means potentially breaking features have been added. A change to the minor number means only backward-compatible bug fixes have been added. The patch number is incremented for each release within the same minor version.

A package that ships the library for a particular platform therefore has a version based on the release date of the library it contains. The library itself uses the `major.minor.patch` scheme described above.

[filename](./bottom_copyright.md ':include')
