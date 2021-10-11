
# VSCP Helper library API - Initialization

This part describes the main functionality and communication methods available in the library.




## vscphlp_newSession

Opens a new communication session. This is the first method that should be called before TCP/IP communication can be established. 

`<code="c">`
long vscphlp_newSession( void )
`</code>`

##### return

A session handle or zero if a session could not be created.

##### Example

`<code="c">`
    handle1 = vscphlp_newSession();
    if (0 != handle1 ) {
        printf( "Handle for channel 1 OK %d\n", handle1 );
    }
    else {
        printf("\aError: Failed to get handle for channel 1\n");
    }
`</code>`

## vscphlp_closeSession

Close an open session. This is the last operation that should be done after you are done with a TCP/IP session.

`<code="c">`
void vscphlp_closeSession( long handle )
`</code>`

##### return

Nothing



##### Example

This is a simple windows console example that log on to a server that is on the host 192.618.1.9 and standard port 9598 and issue the **NOOP** command and then terminates. You link to the **vscphelper.lib** library and make sure the **vscphelper.dll** is in the path.

`<code="c">`

#include "vscphelperlib.h"

int main(int argc, char* argv[])
{
    long handle;
    handle = vscphlp_newSession();

    vscphlp_open( handle, 
                 "127.0.0.1:9598",
                 "admin",
                 "secret" ); 
                 
    vscphlp_noop( handle );

    vscphlp_close( handle );
    vscphlp_closeSession( handle );
   
    return 0;
}
`</code>`


\\ 
----
{{  ::copyright.png?600  |}}

`<HTML>``<p style="color:red;text-align:center;">``<a href="https://www.grodansparadis.com">`the VSCP Project`</a>``</p>``</HTML>`
