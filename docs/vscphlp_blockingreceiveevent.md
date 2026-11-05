

```clike
int vscphlp_blockingReceiveEvent( long handle, 
                                    vscpEvent *Event, 
                                    unsigned long timeout )
```


### Parameters
#### handle
Handle for the communication channel obtained from a call to [vscphlp_newsession](vscphlp_newsession.md).

#### pEvent
Pointer to an event that will receive the event data on success. See [vscphlp_receiveEvent](vscphlp_receiveevent.md) for a description.

#### timeout
Maximum time to wait, in milliseconds. Use a positive value.

### Return Value
`VSCP_ERROR_SUCCESS` (`0`) indicates success. Possible error codes:
`VSCP_ERROR_INVALID_HANDLE`, `VSCP_ERROR_CONNECTION`, `VSCP_ERROR_PARAMETER`,
`VSCP_ERROR_ERROR`, `VSCP_ERROR_READ`, `VSCP_ERROR_INVALID_FRAME`, `VSCP_ERROR_TIMEOUT`,
`VSCP_ERROR_STOPPED`.

In binary mode, a nonzero error code from a server confirmation can also be returned.

### Description
Blocking receive of one VSCP event from the remote VSCP server. Data for the event is dynamically allocated and must be deleted by the application.

For Python, [vscphlp_blockingReceiveEventEx](vscphlp_blockingreceiveeventex.md)
may be simpler to use because there is no dynamically allocated data to manage.

In [binary link mode](binary_link.md), no text receive loop is needed. The
call uses its explicit timeout, processes confirmations, validates event
CRCs, and acknowledges received events. Use raw frame reads for encrypted
frames or arbitrary command replies.

#### C example

With `handle` already in a receive loop:

```clike
vscpEvent *event = NULL;
int result = vscphlp_newVSCPevent(&event);
if (result != VSCP_ERROR_SUCCESS || event == NULL) {
    fprintf(stderr, "Could not allocate event (error %d)\n", result);
} else {
    result = vscphlp_blockingReceiveEvent(handle, event, 1000);
    if (result == VSCP_ERROR_SUCCESS) {
        printf("class=%u type=%u\n", event->vscp_class, event->vscp_type);
    } else if (result == VSCP_ERROR_TIMEOUT) {
        printf("No event arrived within one second\n");
    } else {
        fprintf(stderr, "blockingReceiveEvent failed (error %d)\n", result);
    }
    vscphlp_deleteVSCPevent_v2(&event);
}
```

#### Python example

With `handle` already in a receive loop (see [vscphlp_enterReceiveLoop](vscphlp_enterreceiveloop.md)): The helper-allocated event and its data must be released.

```python
import vscp
import vscphelper

result, event_ptr = vscphelper.newVSCPevent()
if result != vscp.VSCP_ERROR_SUCCESS or not event_ptr:
    raise RuntimeError("Could not allocate an event (error {})".format(result))

try:
    result = vscphelper.blockingReceiveEvent(handle, event_ptr.contents, 1000)
    if result == vscp.VSCP_ERROR_TIMEOUT:
        print("No event arrived within one second")
    elif result != vscp.VSCP_ERROR_SUCCESS:
        raise RuntimeError("blockingReceiveEvent failed (error {})".format(result))
    else:
        event = event_ptr.contents
        print("class={}, type={}".format(event.vscpclass, event.vscptype))
finally:
    vscphelper.deleteVSCPevent_v2(event_ptr)
```

#### JavaScript availability

The official [Node.js binding](bindings.md#nodejs) does not currently expose this helper API, so there is no equivalent JavaScript example.

### See Also
[vscphlp_enterReceiveLoop](vscphlp_enterreceiveloop.md)   
[vscphlp_quitReceiveLoop](vscphlp_quitreceiveloop.md)   
[vscphlp_blockingReceiveEventEx](vscphlp_blockingreceiveeventex.md)



[filename](./bottom_copyright.md ':include')