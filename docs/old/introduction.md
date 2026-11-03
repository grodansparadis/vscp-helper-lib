# VSCP Helper Library Introduction


The VSCP helper library provides tools for developing VSCP applications. It includes functions for working with Level I drivers (formerly called CANAL drivers), communicating with a remote VSCP daemon over TCP/IP, and performing other common tasks. It includes helper and communication functions and supports threads for receiving and transmitting events.


##### Error handling


*  A successful response from a driver is either an object or the integer **VSCP_ERROR_SUCCESS**.

*  A failed response from a driver is either NULL or the integer **VSCP_ERROR_ERROR**.

*  Other return codes are listed in [vscp.h](https///github.com/grodansparadis/vscp_software/blob/master/src/vscp/common/vscp.h).

\\ 
----
{{  ::copyright.png?600  |}}

`<HTML>``<p style="color:red;text-align:center;">``<a href="https://www.grodansparadis.com">`the VSCP Project`</a>``</p>``</HTML>`
