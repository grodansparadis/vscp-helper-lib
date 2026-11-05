

```clike
int vscphlp_getMeasurementSubZone( const vscpEvent *pEvent )
```

### Parameters

#### pEvent
Pointer to a VSCP measurement event.

### Return Value
Returns the subzone (`0` to `255`) on success or `-1` (`VSCP_ERROR_ERROR`) for an invalid or
unsupported measurement. `255` denotes all subzones.

### Description
Get subzone for a measurement event. 

> **Known limitation:** For a Level I `MEASUREZONE` event with subzone 4, the
> current implementation returned 0. The example below uses a Level II string
> measurement, for which the tested subzone value was returned correctly.




#### C example

With the helper-library headers and standard C headers included:

```clike
uint8_t data[] = {2, 3, 4, 1, '3', '.', '1', '4'};
vscpEvent event = {0};
event.vscp_class = 1040; event.vscp_type = 6;
event.sizeData = sizeof(data); event.pdata = data;
printf("%d\n", vscphlp_getMeasurementSubZone(&event));
```

#### Python example

Using the official [Python helper binding](bindings.md#python):

```python
import vscp
import vscphelper
from ctypes import POINTER, c_ubyte, cast

event = vscp.vscpEvent()
data = (c_ubyte * 8)(2, 3, 4, 1, ord('3'), ord('.'), ord('1'), ord('4'))
event.vscpclass = 1040
event.vscptype = 6
event.sizedata = len(data)
event.pdata = cast(data, POINTER(c_ubyte))
print(vscphelper.getMeasurementSubZone(event))
```

#### JavaScript availability

See the [Node.js binding](bindings.md#nodejs) for C API access and native library availability.

[filename](./bottom_copyright.md ':include')