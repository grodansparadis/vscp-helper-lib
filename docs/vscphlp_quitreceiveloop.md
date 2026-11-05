

```clike
int vscphlp_quitReceiveLoop( long handle )
```


### Parameters

#### handle
Handle for the communication channel obtained from a call to [vscphlp_newsession](vscphlp_newsession.md).

### Return Value
`VSCP_ERROR_SUCCESS` (`0`) indicates success. Possible error codes:
`VSCP_ERROR_INVALID_HANDLE`, `VSCP_ERROR_CONNECTION`, `VSCP_ERROR_PARAMETER`,
`VSCP_ERROR_TIMEOUT`.

### Description
Quit the receive loop. 

#### C example

```clike
// Quit receiveloop
if ( VSCP_ERROR_SUCCESS == (rv = vscphlp_quitReceiveLoop( handle2 ) ) ) {
    printf( "Command success: vscphlp_quitReceiveLoop on channel 2\n" );
}
else {
    printf("Command error: vscphlp_quitReceiveLoop on channel 2  Error code=%d\n", rv);
}
```

#### Python example

With `handle` already in a receive loop (see [vscphlp_enterReceiveLoop](vscphlp_enterreceiveloop.md)):

```python
import vscp
import vscphelper

result = vscphelper.quitReceiveLoop(handle)
if result != vscp.VSCP_ERROR_SUCCESS:
    raise RuntimeError("quitReceiveLoop failed (error {})".format(result))
```

#### JavaScript availability

The official [Node.js binding](bindings.md#nodejs) does not currently expose this helper API, so there is no equivalent JavaScript example.

### See Also
[vscphlp_enterReceiveLoop](vscphlp_enterreceiveloop.md)  
[vscphlp_blockingReceiveEvent](vscphlp_blockingreceiveevent.md)  
[vscphlp_blockingReceiveEventEx](vscphlp_blockingreceiveeventex.md)



[filename](./bottom_copyright.md ':include')