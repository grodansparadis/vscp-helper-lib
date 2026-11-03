

```clike
int vscphlp_getMeasurementZone( const vscpEvent *pEvent )
```

### Parameters

#### pEvent
Pointer to a VSCP measurement event.

### Return Value
The zone is returned as a value from 0 to 255, where 255 means “all zones”. Returns -1 if the event is invalid or is not a measurement event.

> **Known limitation:** For a Level II measurement with zone 3 and subzone 4,
> the current implementation returns 4 instead of 3. For a Level I
> `MEASUREZONE` event with the same values, it returned 0. Do not rely on this
> helper for those zone values until the implementation is corrected.

### Description
Get the zone for a measurement event. For events without a defined zone, zero is always returned.



#### C example

With the helper-library headers and standard C headers included:

```clike
uint8_t data[] = {0x4A, '3', '.', '1', '4'};
vscpEvent event = {0};
event.vscp_class = 10; event.vscp_type = 6;
event.sizeData = sizeof(data); event.pdata = data;
printf("%d\n", vscphlp_getMeasurementZone(&event));
```

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
print(vscphelper.getMeasurementZone(event))
```

#### JavaScript availability

The official [Node.js binding](bindings.md#nodejs) does not currently expose this helper API, so there is no equivalent JavaScript example.

[filename](./bottom_copyright.md ':include')