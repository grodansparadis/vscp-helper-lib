
```clike
int vscphlp_clearDaemonEventQueue( long handle )
```


### Parameters

#### handle
Handle for the communication channel obtained from a call to [vscphlp_newsession](vscphlp_newsession.md).

### Return Value
Returns VSCP_ERROR_SUCCESS if the VSCP daemon clears the queue, or VSCP_ERROR_ERROR if it does not or no response arrives before the timeout expires. Returns VSCP_ERROR_CONNECTION if the communication channel is not open and VSCP_ERROR_INVALID_HANDLE if the handle is invalid.

### Description
Clear the receiving-side event queue on the VSCP daemon.

#### C example

```clike
// Clear event queue on VSCP daemon on handle1
if ( VSCP_ERROR_SUCCESS == (rv = vscphlp_clearDaemonEventQueue( handle1 ) ) ) {
    printf( "Command success: vscphlp_clearDaemonEventQueueon channel 1\n" );
}
else {
    printf("\aCommand error: vscphlp_clearDaemonEventQueueon channel 1  Error code=%d\n", rv);
}
```

#### Python example

With an open session handle named `handle` (see the [TLS guide](tls.md#python-example)): This clears the server-side event queue.

```python
import vscp
import vscphelper

result = vscphelper.clearDaemonEventQueue(handle)
if result != vscp.VSCP_ERROR_SUCCESS:
    raise RuntimeError("clearDaemonEventQueue failed (error {})".format(result))
```

#### JavaScript availability

The official [Node.js binding](bindings.md#nodejs) does not currently expose this helper API, so there is no equivalent JavaScript example.

[filename](./bottom_copyright.md ':include')