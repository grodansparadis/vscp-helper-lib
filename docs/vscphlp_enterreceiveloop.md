

```clike
int vscphlp_enterReceiveLoop( long handle )
```


### Parameters

#### handle
Handle for the communication channel obtained from a call to [vscphlp_newsession](vscphlp_newsession.md).

### Return Value
`VSCP_ERROR_SUCCESS` (`0`) indicates success. Possible error codes:
`VSCP_ERROR_INVALID_HANDLE`, `VSCP_ERROR_CONNECTION`, `VSCP_ERROR_PARAMETER`,
`VSCP_ERROR_ERROR`.

### Description
Enter the receive loop. By default, commands and the receive loop use separate
connections. To use one connection for both, configure
[single-channel mode](vscphlp_setsinglechannelreceiveloop.md) before entering
the loop. In that mode, `SEND`, `NOOP`, `CLRA`, and `QUITLOOP` are the only
supported commands while receiving. Other commands return
`VSCP_ERROR_PARAMETER`.

#### C example

```c
int result = vscphlp_setSingleChannelReceiveLoop(handle, 1);
if (result == VSCP_ERROR_SUCCESS) {
    result = vscphlp_enterReceiveLoop(handle);
}
if (result != VSCP_ERROR_SUCCESS) {
    fprintf(stderr, "Could not enter single-channel receive loop (error %d)\n", result);
}
```

See [single-channel TCP/IP receive loop](single_channel.md) for a threaded
send/receive example and server requirements.

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