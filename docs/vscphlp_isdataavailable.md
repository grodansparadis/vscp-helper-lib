

```clike
int vscphlp_isDataAvailable( long handle, 
                                unsigned int *pCount )
```


### Parameters

#### handle
Handle for the communication channel obtained from a call to [vscphlp_newsession](vscphlp_newsession.md).

### pCount (c/c++)
Pointer to variable that gets the number of events waiting in the queue on a successful call.

### count (Python)
Variable that gets the number of events waiting in the queue on a successful call.


### Return Value
Returns VSCP_ERROR_SUCCESS on success or VSCP_ERROR_ERROR on failure. Returns VSCP_ERROR_CONNECTION if the connection is closed and VSCP_ERROR_PARAMETER if called while in a receive loop.

### Description
Check the number of events (if any) that are available in the remote input queue. 

#### C example

```clike
// Check queue for events
if ( VSCP_ERROR_SUCCESS == (rv = vscphlp_isDataAvailable( handle2, &count ) ) ) {
     printf( "Command success: vscphlp_isDataAvailable on handle2\n" );
    printf( "count = %d\n", count );
        if ( 3 == count ) printf("Which is correct.\n");
}
else {
    printf("\aCommand error: vscphlp_isDataAvailable on channel 2  Error code=%d\n", rv);
}
```

#### Python example

With an open session handle named `handle` (see the [TLS guide](tls.md#python-example)):

```python
from ctypes import c_uint

import vscp
import vscphelper

count = c_uint()

result = vscphelper.isDataAvailable(handle, count)
if result != vscp.VSCP_ERROR_SUCCESS:
    raise RuntimeError("isDataAvailable failed (error {})".format(result))
print("Available events: {}".format(count.value))
```

#### JavaScript availability

The official [Node.js binding](bindings.md#nodejs) does not currently expose this helper API, so there is no equivalent JavaScript example.

[filename](./bottom_copyright.md ':include')