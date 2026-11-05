
```clike
int vscphlp_blockingReceiveEventEx( long handle, 
                                vscpEventEx *Eventex, 
                                unsigned long timeout )
```


### Parameters

#### handle
Handle for the communication channel obtained from a call to [vscphlp_newsession](vscphlp_newsession.md).

#### pEvent (c/c++)
Pointer to an event that will receive the event data on success. See vscphlp_receiveEvent for a description.

#### pEvent (Python)
Event that will receive the event data on success. See vscphlp_receiveEvent for a description.

#### timeout
Maximum time to wait, in milliseconds. Use a positive value.


### Return Value
`VSCP_ERROR_SUCCESS` (`0`) indicates success. Possible error codes:
`VSCP_ERROR_INVALID_HANDLE`, `VSCP_ERROR_CONNECTION`, `VSCP_ERROR_PARAMETER`,
`VSCP_ERROR_ERROR`, `VSCP_ERROR_READ`, `VSCP_ERROR_INVALID_FRAME`, `VSCP_ERROR_TIMEOUT`,
`VSCP_ERROR_STOPPED`.

In binary mode, a nonzero error code from a server confirmation can also be returned.

### Description
Blocking receive of one VSCP event from the remote VSCP server. 

In [binary link mode](binary_link.md), no text receive loop is needed. The
call uses its explicit timeout, processes confirmations, validates event
CRCs, and acknowledges received events. Use raw frame reads for encrypted
frames or arbitrary command replies.

#### C example

With `handle` already in a receive loop:

```clike
vscpEventEx event = {0};
int result = vscphlp_blockingReceiveEventEx(handle, &event, 1000);
if (result == VSCP_ERROR_SUCCESS) {
    printf("class=%u type=%u\n", event.vscp_class, event.vscp_type);
} else if (result == VSCP_ERROR_TIMEOUT) {
    printf("No event arrived within one second\n");
} else {
    fprintf(stderr, "blockingReceiveEventEx failed (error %d)\n", result);
}
```

#### Python example

With `handle` already in a receive loop (see [vscphlp_enterReceiveLoop](vscphlp_enterreceiveloop.md)):

```python
import vscp
import vscphelper

event = vscp.vscpEventEx()
result = vscphelper.blockingReceiveEventEx(handle, event, 1000)
if result == vscp.VSCP_ERROR_TIMEOUT:
    print("No event arrived within one second")
elif result != vscp.VSCP_ERROR_SUCCESS:
    raise RuntimeError("blockingReceiveEventEx failed (error {})".format(result))
else:
    print("class={}, type={}".format(event.vscpclass, event.vscptype))
```

#### JavaScript availability

The official [Node.js binding](bindings.md#nodejs) does not currently expose this helper API, so there is no equivalent JavaScript example.

### See Also
[vscphlp_enterReceiveLoop](vscphlp_enterreceiveloop.md)   
[vscphlp_quitReceiveLoop](vscphlp_quitreceiveloop.md)   
[vscphlp_blockingReceiveEvent](vscphlp_blockingreceiveevent.md)



[filename](./bottom_copyright.md ':include')