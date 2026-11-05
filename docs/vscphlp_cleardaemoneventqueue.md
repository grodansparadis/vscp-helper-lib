
```clike
int vscphlp_clearDaemonEventQueue( long handle )
```


### Parameters

#### handle
Handle for the communication channel obtained from a call to [vscphlp_newsession](vscphlp_newsession.md).

### Return Value
`VSCP_ERROR_SUCCESS` (`0`) indicates success. Possible error codes:
`VSCP_ERROR_INVALID_HANDLE`, `VSCP_ERROR_CONNECTION`, `VSCP_ERROR_PARAMETER`,
`VSCP_ERROR_ERROR`.

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

See the [Node.js binding](bindings.md#nodejs) for C API access and native library availability.

[filename](./bottom_copyright.md ':include')