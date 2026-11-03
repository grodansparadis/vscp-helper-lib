

```clike
int vscphlp_getMeasurementSensorIndex( const vscpEvent *pEvent )
```

### Parameters

#### pEvent
Pointer to a VSCP measurement event.

### Return Value
The sensor index is returned as a value from 0 to 7 for a Level I event or from 0 to 255 for a Level II event. Returns -1 if the event is invalid or is not a measurement event.

> **C API limitation:** The public header declares `vscphlp_getMeasuremenSensorIndex`, while the library exports `vscphlp_getMeasurementSensorIndex`. The Python wrapper resolves the exported name.

### Description
Get the sensor index for a measurement event. For events without a defined sensor index, zero is always returned.




#### Python example

Using the official [Python helper binding](bindings.md#python):

```python
import vscp
import vscphelper
from ctypes import POINTER, c_ubyte, cast

event = vscp.vscpEvent()
data = (c_ubyte * 5)(0x4A, ord('3'), ord('.'), ord('1'), ord('4'))
event.vscpclass = 10
event.vscptype = 6
event.sizedata = len(data)
event.pdata = cast(data, POINTER(c_ubyte))
print(vscphelper.getMeasurementSensorIndex(event))
```

#### JavaScript availability

The official [Node.js binding](bindings.md#nodejs) does not currently expose this helper API, so there is no equivalent JavaScript example.

[filename](./bottom_copyright.md ':include')