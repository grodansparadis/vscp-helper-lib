# Introduction to direct use of VSCP classes

[HISTORY](vscp_class_usage_history)

Copyright © 2000-2019 Åke Hedman, [Grodans Paradis AB](https://www.grodansparadis.com), `<[akhe@grodansparadis.com](akhe@grodansparadis.com)>` 

VSCP use the [wxWidgets library](https://wxwidgets.org/). For most people this library is considered a graphical C++ UI library but it also have a lot of functionality in it's non graphical (base) version and it is this version that is used in the VSCP project for all code except for the applications ([VSCP Works](https://grodansparadis.gitbooks.io/vscp-works/?id=start/)) that actually is a graphical application.

wxWidgets is used to make it easier to create a package that works on different platforms. If the wxWidgets base directory can compile on a platform then the VSCP & Friends project will also build and work.  This statement is not entirely true for all parts of the VSCP & Friends system. We try to minimize dependency’s as much as possible on small systems (embedded) and most of them don't have any other dependency’s at all to be usable on everything. wxWidgets is licensed under the [wxWindows Library Licence](https://wxwidgets.org/about/licence/) which is an approved open source license. This is essentially a LGPL license.

VSCP & Friends also uses the [mongoose library](https///docs.cesanta.com/mongoose/master) from [Cesanta](https///www.cesanta.com/) for network tasks. This code is releases under GPL version 2 but can also be obtained with a commercial license from Cesanta. If you link the mongoose library with your own code you have to share your own code a well. We will remove this demand for libraries and classes in the future so that all code is either under the LGPL or MIT license.

## Needed files

This table lists the files that are needed to embed in a project to make a client for the VSCP daemon tcp/ip interface. When this is done most functionality of the VSCP daemon can be remotely controlled.

 | Files                                                                                                                                                                                                                     | Covered by License | 
 | -----                                                                                                                                                                                                                     | ------------------ | 
 | [vscpremotetcpif.h](https///github.com/grodansparadis/vscp/blob/master/src/vscp/common/vscpremotetcpif.h) / [vscpremotetcpif.cpp](https///github.com/grodansparadis/vscp/blob/master/src/vscp/common/vscpremotetcpif.cpp) | MIT License        | 
 | [vscphelper.h](https///github.com/grodansparadis/vscp/blob/master/src/vscp/common/vscphelper.h) / [vscphelper.cpp](https///github.com/grodansparadis/vscp/blob/master/src/vscp/common/vscphelper.cpp)                     | MIT License        | 
 | [crc8.h](https///github.com/grodansparadis/vscp/blob/master/src/common/crc8.h) / [crc8.c](https///github.com/grodansparadis/vscp/blob/master/src/common/crc8.c)                                                           | Public Domain      | 
 | [crc.h](https///github.com/grodansparadis/vscp/blob/master/src/common/crc.h) / [crc.c](https///github.com/grodansparadis/vscp/blob/master/src/common/crc.c)                                                               | Public Domain      | 
 | [guid.h](https///github.com/grodansparadis/vscp/blob/master/src/vscp/common/guid.h) / [guid.cpp](https///github.com/grodansparadis/vscp/blob/master/src/vscp/common/guid.cpp)                                             | MIT License        | 
 | [mongoose.h](https///github.com/cesanta/mongoose/blob/master/mongoose.h) / [mongoose.c](https///github.com/cesanta/mongoose/blob/master/mongoose.c)                                                                       | GPL version 2      | 

`<HTML>`
`<p style="color:red;text-align:center;">`The demand for the GPLv2 code of mongoose will be removed from the client code so that the files freely and without any risk of infection can be included also in commercial projects.`<p>`
`</HTML>`

\\ 
----
{{ ::copyright.png?600 |}}
`<HTML>``<br>``<p style="color:red;text-align:center;">``<a href="https://www.grodansparadis.com">`Grodans Paradis AB`</a>``</p>``</HTML>`


 


