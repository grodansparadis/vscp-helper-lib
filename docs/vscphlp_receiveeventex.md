

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
Returns VSCP_ERROR_SUCCESS on success or VSCP_ERROR_ERROR on failure. Returns VSCP_ERROR_CONNECTION if the connection is closed and VSCP_ERROR_PARAMETER if called while in a receive loop.

### Description
Receive a VSCP event. Unlike vscphlp_receiveEvent, the vscphlp_vscpEventEx structure stores the data in the structure itself; vscpEvent contains a pointer to the data.

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

The official [Node.js binding](bindings.md#nodejs) does not currently expose this helper API, so there is no equivalent JavaScript example.

### See Also
[vscphlp_receiveEvent](vscphlp_receiveevent.md)



[filename](./bottom_copyright.md ':include')