

```clike
void vscphlp_closeSession( long handle )
```

#### handle
Handle for the communication channel obtained from a call to [vscphlp_newsession](vscphlp_newsession.md).


### Return Value
Nothing

### Description
Close an open session. This is the last operation that should be done after you are done with a TCP/IP session. 

<!-- tabs:start -->

#### ** C example **

This is a simple windows console example that log on to a server that is on the host 192.618.1.9 and standard port 9598 and issue the NOOP command and then terminates. You link to the vscphelper.lib library and make sure the vscphelper.dll is in the path. 

```clike
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
```

#### ** Python example **
There is no Python sample yet

```python

```

<!-- tabs:end -->

###See Also
[vscphlp_closeSession](vscphlp_newsession.md)



[filename](./bottom_copyright.md ':include')