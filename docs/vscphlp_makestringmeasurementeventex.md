

```clike
int vscphlp_makeStringMeasurementEventEx( vscpEventEx *pEventEx,
                                        float value,
                                        unsigned char unit,
                                        unsigned char sensoridx )
```

### Parameters

#### pEventEx
Pointer to a VSCP event ex that will receive the result as its data.

#### value
Floating-point value to encode as a string.

#### unit
A unit value from 0 to 3.

#### sensoridx
A sensor index from 0 to 7.

### Return Value
`VSCP_ERROR_SUCCESS` (`0`) indicates success. Possible error codes: `VSCP_ERROR_ERROR`.

> **C API limitation:** The public header declares the event parameter as `vscpEvent *`, but the implementation requires `vscpEventEx *`. Do not call it through this declaration until the header is corrected.

### Description
Make a string coded level I event from floating point data.

#### Python example

Using the official [Python helper binding](bindings.md#python):

```python
import vscp
import vscphelper
from ctypes import POINTER, c_ubyte, cast

event = vscp.vscpEventEx()
event.vscpclass, event.vscptype = 10, 6
result = vscphelper.makeStringMeasurementEventEx(event, 3.14, 1, 2)
if result != vscp.VSCP_ERROR_SUCCESS:
    raise RuntimeError("makeStringMeasurementEventEx failed (error {})".format(result))
print(bytes(event.data[1:event.sizedata]).decode('ascii'))
```

#### JavaScript availability

See the [Node.js binding](bindings.md#nodejs) for C API access and native library availability.

[filename](./bottom_copyright.md ':include')