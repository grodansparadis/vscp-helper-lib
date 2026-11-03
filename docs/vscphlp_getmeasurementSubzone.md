

```clike
int vscphlp_getMeasurementSubZone( const vscpEvent *pEvent )
```

### Parameters

#### pEvent
Pointer to a VSCP measurement event.

### Return Value
The subzone is returned as a value from 0 to 255, where 255 means “all subzones”. Returns -1 if the event is invalid or is not a measurement event. For events without a defined subzone, zero is always returned.

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

The official [Node.js binding](bindings.md#nodejs) does not currently expose this helper API, so there is no equivalent JavaScript example.

[filename](./bottom_copyright.md ':include')