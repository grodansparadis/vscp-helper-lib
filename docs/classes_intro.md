# Use VSCP classes directly

VSCP use the [wxWidgets library](https://wxwidgets.org/). For most people this library is considered a graphical C++ UI library but it also have a lot of functionality in it's non graphical (base) version also and it is this version that is used in the VSCP project for all code except for the applications (VSCP Works) that actually is a graphical application.

wxWidgets is used to make it easier to create a package that works on different platforms. If the wxWidgets base directory can compile on a platform then the VSCP & Friends project will also build and work. This statement is not entirely true for all parts of the VSCP & Friends system. We try to minimize dependency’s as much as possible on small systems (embedded) and most of them don't have any other dependency’s at all to be usable on everything. wxWidgets is licensed under the wxWindows Library Licence which is an approved open source license. This is essentially a LGPL license with some added freedom.

This table lists the files that are needed to embed in a project to make a client for the VSCP daemon tcp/ip interface. When this is done most functionality of the VSCP daemon can be remotely controlled. 

File | License 
---- | -------
[vscpremotetcpif.h](https://github.com/grodansparadis/vscp/blob/master/src/vscp/common/vscpremotetcpif.h) / [vscpremotetcpif.cpp](https://github.com/grodansparadis/vscp/blob/master/src/vscp/common/vscpremotetcpif.cpp) | MIT License
[vscphelper.h](https://github.com/grodansparadis/vscp/blob/master/src/vscp/common/vscphelper.h) / [vscphelper.cpp](https://github.com/grodansparadis/vscp/blob/master/src/vscp/common/vscphelper.cpp) | MIT License
[crc8.h](https://github.com/grodansparadis/vscp/blob/master/src/common/crc8.h) / [crc8.c](https://github.com/grodansparadis/vscp/blob/master/src/common/crc8.c) | Public Domain
[crc.h](https://github.com/grodansparadis/vscp/blob/master/src/common/crc.h) / [crc.c](https://github.com/grodansparadis/vscp/blob/master/src/common/crc.c) | Public Domain
[guid.h](https://github.com/grodansparadis/vscp/blob/master/src/vscp/common/guid.h) / [guid.cpp](https://github.com/grodansparadis/vscp/blob/master/src/vscp/common/guid.cpp) | MIT License
[sockettcp.h](https://github.com/grodansparadis/vscp/blob/master/src/common/sockettcp.h) / [sockkettcp.h](https://github.com/grodansparadis/vscp/blob/master/src/common/sockettcp.h) | MIT License

[filename](./bottom_copyright.md ':include')