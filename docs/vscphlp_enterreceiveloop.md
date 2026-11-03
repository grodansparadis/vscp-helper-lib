

```clike
int vscphlp_enterReceiveLoop( long handle )
```


### Parameters

#### handle
Handle for the communication channel obtained from a call to [vscphlp_newsession](vscphlp_newsession.md).

### Return Value
Returns VSCP_ERROR_SUCCESS on success or VSCP_ERROR_ERROR on failure. Returns VSCP_ERROR_CONNECTION if the connection is closed and VSCP_ERROR_PARAMETER if called while in a receive loop.

### Description
Enter the receive loop. After this command, only vscphlp_quitReceiveLoop, vscphlp_Close, and the blocking receive methods [vscphlp_blockingReceiveEvent](vscphlp_blockingreceiveevent.md) and [vscphlp_blockingReceiveEventEx](vscphlp_blockingreceiveeventex.md) are available. This is intended for threaded communication in which one thread sends events and another receives them using blocking calls.

#### C example
```clike
// Enter receiveloop
if ( VSCP_ERROR_SUCCESS == (rv = vscphlp_enterReceiveLoop( handle2 ) ) ) {
    printf( "Command success: vscphlp_enterReceiveLoop on channel 2\n" );
}
else {
    printf("\aCommand error: vscphlp_enterReceiveLoop on channel 2  Error code=%d\n", rv);
}
```

#### Python example

With an open session handle named `handle` (see the [TLS guide](tls.md#python-example)): Call [quitReceiveLoop](vscphlp_quitreceiveloop.md) when finished receiving.

```python
import vscp
import vscphelper

result = vscphelper.enterReceiveLoop(handle)
if result != vscp.VSCP_ERROR_SUCCESS:
    raise RuntimeError("enterReceiveLoop failed (error {})".format(result))
```

#### JavaScript availability

The official [Node.js binding](bindings.md#nodejs) does not currently expose this helper API, so there is no equivalent JavaScript example.

### See Also
[vscphlp_quitReceiveLoop](vscphlp_quitreceiveloop.md)  
[vscphlp_blockingReceiveEvent](vscphlp_blockingreceiveevent.md)  
[vscphlp_blockingReceiveEventEx](vscphlp_blockingreceiveeventex.md)



[filename](./bottom_copyright.md ':include')