

```clike
int vscphlp_receiveEvent( long handle, 
                          vscpEvent *pEvent )
```


### Parameters

#### handle
Handle for the communication channel obtained from a call to [vscphlp_newsession](vscphlp_newsession.md).

#### pEvent
Pointer to a `vscpEvent` that receives the event on success. The structure is
defined in [vscp.h](https://github.com/grodansparadis/vscp_software/blob/master/src/vscp/common/vscp.h).

### Return Value
Returns VSCP_ERROR_SUCCESS on success or VSCP_ERROR_ERROR on failure. Returns VSCP_ERROR_CONNECTION if the connection is closed and VSCP_ERROR_PARAMETER if called while in a receive loop.

### Description
Receive one VSCP event from the remote VSCP server if there is one available in the server queue. Data for the event is dynamically allocated and must be deleted by the application. 

For Python, [vscphlp_receiveEventEx](vscphlp_receiveeventex.md) may be simpler
to use because there is no dynamically allocated data to manage.

#### C example

```clike
vscpEvent *event = NULL;
int result = vscphlp_newVSCPevent(&event);
if (result != VSCP_ERROR_SUCCESS || event == NULL) {
    fprintf(stderr, "Could not allocate event (error %d)\n", result);
} else {
    result = vscphlp_receiveEvent(handle, event);
    if (result == VSCP_ERROR_SUCCESS) {
        printf("class=%u type=%u size=%u\n",
               event->vscp_class, event->vscp_type, event->sizeData);
    } else {
        fprintf(stderr, "receiveEvent failed (error %d)\n", result);
    }
    vscphlp_deleteVSCPevent_v2(&event);
}
```

#### Python example

With an open session handle named `handle` (see the [TLS guide](tls.md#python-example)): The helper-allocated event and its data must be released.

```python
import vscp
import vscphelper

result, event_ptr = vscphelper.newVSCPevent()
if result != vscp.VSCP_ERROR_SUCCESS or not event_ptr:
    raise RuntimeError("Could not allocate an event (error {})".format(result))

try:
    result = vscphelper.receiveEvent(handle, event_ptr.contents)
    if result != vscp.VSCP_ERROR_SUCCESS:
        raise RuntimeError("receiveEvent failed (error {})".format(result))
    event = event_ptr.contents
    print("class={}, type={}".format(event.vscpclass, event.vscptype))
finally:
    vscphelper.deleteVSCPevent_v2(event_ptr)
```

#### JavaScript availability

The official [Node.js binding](bindings.md#nodejs) does not currently expose this helper API, so there is no equivalent JavaScript example.

### See Also
[vscphlp_receiveEventEx](vscphlp_receiveeventex.md)



[filename](./bottom_copyright.md ':include')