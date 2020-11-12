# VSCP Helper library Introduction


VSCP helper library is a software library for VSCP program development. This library includes most of the stuff that is needed by a programmer to interface Level I drivers (previously called CANAL drivers) and the talk to a VSCP daemon remotely over TCP/IP as well as a lot of other things. All helper functionality and all communication functionality is included in the library. Also ready to work with threads for receiving and transmitting events.


##### Error handling


*  A positive response form a driver is either an object or an integer **VSCP_ERROR_SUCCESS**

*  A negative response from a driver is either NULL or an integer **VSCP_ERROR_ERROR**

*  All other return code can be found in [vscp.h](https///github.com/grodansparadis/vscp_software/blob/master/src/vscp/common/vscp.h)

\\ 
----
{{  ::copyright.png?600  |}}

`<HTML>``<p style="color:red;text-align:center;">``<a href="https://www.grodansparadis.com">`Grodans Paradis AB`</a>``</p>``</HTML>`
