

```clike
int vscphlp_sendEvent( long handle, 
                        const vscpEvent *pEvent )
```


### Parameters

#### handle
Handle for the communication channel obtained from a call to [vscphlp_newsession](vscphlp_newsession.md).

#### pEvent
The level I or level II event to send. The `vscpEvent` structure is defined in
[vscp.h](https://github.com/grodansparadis/vscp_software/blob/master/src/vscp/common/vscp.h).

### Return Value
Returns VSCP_ERROR_SUCCESS on success or VSCP_ERROR_ERROR on failure. Returns VSCP_ERROR_CONNECTION if the connection is closed and VSCP_ERROR_PARAMETER if called while in a receive loop.

### Description
Send a VSCP event. Whether or not the call succeeds, the caller retains
ownership of the event and must release any dynamically allocated event data.

There is no need to calculate a CRC for the data; it is only a placeholder for less secure transfer mechanisms. In most cases, head, obid, the UTC time block, and timestamp can be set to zero. The server interface sets the time block and timestamp when it receives the event.

[vscphlp_sendEventEx](vscphlp_sendeventex.md) may be a better choice for Python because it stores event data in the structure. However, it uses more memory.

#### C example

```clike
vscpEvent event = {0};
uint8_t data[] = {138, 0, 6};
event.vscp_class = 10;
event.vscp_type = 6;
event.sizeData = sizeof(data);
event.pdata = data;

int result = vscphlp_sendEvent(handle, &event);
if (result != VSCP_ERROR_SUCCESS) {
    fprintf(stderr, "sendEvent failed (error %d)\n", result);
}
```

The event and its data use stack storage in this example; do not pass either
to `vscphlp_deleteVSCPevent`.

#### Python example

With an open session handle named `handle` (see the [TLS guide](tls.md#python-example)): Keep the Python-owned data buffer alive until the call returns.

```python
from ctypes import POINTER, c_ubyte, cast

import vscp
import vscphelper

event = vscp.vscpEvent()
event.vscpclass = 10
event.vscptype = 6
data = (c_ubyte * 3)(138, 0, 6)
event.sizedata = len(data)
event.pdata = cast(data, POINTER(c_ubyte))

result = vscphelper.sendEvent(handle, event)
if result != vscp.VSCP_ERROR_SUCCESS:
    raise RuntimeError("sendEvent failed (error {})".format(result))
```

#### JavaScript availability

The official [Node.js binding](bindings.md#nodejs) does not currently expose this helper API, so there is no equivalent JavaScript example.

### See Also
[vscphlp_sendEventEx](vscphlp_sendeventex.md)



[filename](./bottom_copyright.md ':include')