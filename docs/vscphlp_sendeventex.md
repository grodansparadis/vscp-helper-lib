
```clike
int vscphlp_sendEventEx( long handle, 
                            const vscpEventEx *pEvent )
```


### Parameters

#### handle
Handle for the communication channel obtained from a call to [vscphlp_newsession](vscphlp_newsession.md).

#### pEvent

The level I or level II event to send. The `vscpEventEx` structure is defined
in [vscp.h](https://github.com/grodansparadis/vscp_software/blob/master/src/vscp/common/vscp.h).

### Return Value
`VSCP_ERROR_SUCCESS` (`0`) indicates success. Possible error codes:
`VSCP_ERROR_INVALID_HANDLE`, `VSCP_ERROR_CONNECTION`, `VSCP_ERROR_PARAMETER`,
`VSCP_ERROR_ERROR`, `VSCP_ERROR_INVALID_FRAME`, `VSCP_ERROR_TIMEOUT`, `VSCP_ERROR_STOPPED`.

### Description
Send a VSCP event. Whether or not the call succeeds, the caller retains
ownership of the event.

The library handles binary frame CRCs; the application does not need to
calculate them. In most cases, head, obid, the UTC time block, and timestamp
can be set to zero. The server interface sets the time block and timestamp
when it receives the event.

In [binary link mode](binary_link.md), this sends a binary event
and returns after writing, without waiting for server confirmation. Event
receives process asynchronous confirmations; use the raw frame API for
encrypted frames or arbitrary commands/replies.

Frames are unencrypted by default. With [frame security](frame_security.md)
configured, this function automatically encrypts/authenticates the event
and its later confirmations follow the same policy.

#### C example

```clike
vscpEventEx event = {0};
event.vscp_class = 10;
event.vscp_type = 6;
event.sizeData = 3;
event.data[0] = 138;
event.data[1] = 0;
event.data[2] = 6;

int result = vscphlp_sendEventEx(handle, &event);
if (result != VSCP_ERROR_SUCCESS) {
    fprintf(stderr, "sendEventEx failed (error %d)\n", result);
}
```

#### Python example

With an open session handle named `handle` (see the [TLS guide](tls.md#python-example)):

```python
import vscp
import vscphelper

event = vscp.vscpEventEx()
event.vscpclass = 10
event.vscptype = 6
event.sizedata = 3
event.data[:3] = (138, 0, 6)

result = vscphelper.sendEventEx(handle, event)
if result != vscp.VSCP_ERROR_SUCCESS:
    raise RuntimeError("sendEventEx failed (error {})".format(result))
```

#### JavaScript availability

The official [Node.js binding](bindings.md#nodejs) does not currently expose this helper API, so there is no equivalent JavaScript example.

### See Also
[vscphlp_sendEvent](vscphlp_sendevent.md)



[filename](./bottom_copyright.md ':include')