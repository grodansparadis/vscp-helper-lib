

```clike
int vscphlp_receiveEventEx( long handle, 
                            vscpEventEx *pEventEx )
```


### Parameters

#### handle
Handle for the communication channel obtained from a call to [vscphlp_newsession](vscphlp_newsession.md).

#### pEventEx
Pointer to VSCP ex data structure that will receive the event.


### Return Value
`VSCP_ERROR_SUCCESS` (`0`) indicates success. Possible error codes:
`VSCP_ERROR_INVALID_HANDLE`, `VSCP_ERROR_CONNECTION`, `VSCP_ERROR_PARAMETER`,
`VSCP_ERROR_ERROR`, `VSCP_ERROR_MEMORY`, `VSCP_ERROR_READ`, `VSCP_ERROR_INVALID_FRAME`,
`VSCP_ERROR_TIMEOUT`, `VSCP_ERROR_STOPPED`, `VSCP_ERROR_RCV_EMPTY`,
`VSCP_ERROR_INVALID_FORMAT`.

In binary mode, a nonzero error code from a server confirmation can also be returned.

### Description
Receive a VSCP event. Unlike vscphlp_receiveEvent, the vscphlp_vscpEventEx structure stores the data in the structure itself; vscpEvent contains a pointer to the data.

In [binary link mode](binary_link.md), this waits for an asynchronous event
using the session response timeout, without a text receive loop. It handles
confirmations, validates event CRCs, and acknowledges received events.
It can return `VSCP_ERROR_TIMEOUT` or `VSCP_ERROR_INVALID_FRAME`.
Use the raw frame API for encrypted frames and arbitrary command/reply frames.

#### C example

```clike
// Read event  -  Use vscpEventEx
vscpEventEx ex2;
if ( VSCP_ERROR_SUCCESS == (rv = vscphlp_receiveEventEx( handle2, &ex2 ) ) ) {
    printf( "Command success: vscphlp_receiveEventEx on handle2\n" );
    printf( "VSCP class=%d VSCP type=%d sizeData=%d\n", 
                    ex2.vscp_class,
                    ex2.vscp_type,
                    ex2.sizeData );
    printf("Data = ");
    for ( int i=0; i<ex2.sizeData; i++ ) {
        printf("%d ", ex2.data[i] );
    }
    printf("\n");
}
else {
    printf("\aCommand error: vscphlp_receiveEventEx on channel 2  Error code=%d\n", rv);
}
```

#### Python example

With an open session handle named `handle` (see the [TLS guide](tls.md#python-example)):

```python
import vscp
import vscphelper

event = vscp.vscpEventEx()

result = vscphelper.receiveEventEx(handle, event)
if result != vscp.VSCP_ERROR_SUCCESS:
    raise RuntimeError("receiveEventEx failed (error {})".format(result))
print("class={}, type={}, data={}".format(
    event.vscpclass, event.vscptype, list(event.data[:event.sizedata])))
```

#### JavaScript availability

See the [Node.js binding](bindings.md#nodejs) for C API access and native library availability.

### See Also
[vscphlp_receiveEvent](vscphlp_receiveevent.md)



[filename](./bottom_copyright.md ':include')