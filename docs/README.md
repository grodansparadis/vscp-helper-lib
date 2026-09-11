# ![](/assets/logo_100.png)

# The VSCP helper library

Author 2000-2026 Åke Hedman and contributors, [the VSCP Project](https://www.vscp.org);

**Document created**: *${/var/creation-time}*  
**Document version**: ${/var/document-version} 

The VSCP helper library is a collection of library tools for VSCP program development. This library includes most of the helper functionality that is needed by a programmer to interface Level I drivers (previously called CANAL drivers) and functionality to interface a local or remote VSCP daemon (Level II) over TCP/IP and a lot of other things. All helper functionality and all communication functionality is included in the library.

You can either use the library in binary form as a set of C exported functions delivered by a dynamically loaded library or by including a number of C++ classes in your project.

The library is currently available for

  * [c/c++](https://github.com/grodansparadis/vscp-helper-lib),
  * [python](https://github.com/grodansparadis/pyvscp)
  * [node.js](https://github.com/grodansparadis/node-vscp-helper)
  
and is available on Unix/Linux, Macintosh and Windows.

The library is licensed: under [the  MIT License](https://opensource.org/licenses/MIT) so it can be used freely in open and closed project.

Viewable/downloadable documentation for the VSCP helper library is available [here](https://docs.vscp.org/#vscphelper)

## About versioning

VSCP releases are versioned as year.month.patch where year is the last two digits of the year and month is the two digits of the month. Patch is an incremental number for each release within the same month.

For libraries, the versioning of the release follows this pattern as well. But for the library binaries another schema is used. The reason is that higher ens software that use the library should be able to use the versioning to now if the library is compatible with the version they depend on. So here a number built from major, minor and patch is used. A changed major number means that (possible) breaking features has been added to the library. A changed minor number means that only backward compatible bug fixes have been added. The patch number is incremented for each release within the same minor version.

So the package that ships the library on a specific platform will have a version based on the release date of the library it contains. The library itself will use the major.minor.patch versioning scheme described above.

[filename](./bottom_copyright.md ':include')

