

```clike
int vscphlp_isMeasurement( const vscpEvent *pEvent )
```

### Parameters

#### pEvent
Pointer to a VSCP measurement event.

### Return Value
Returns VSCP_ERROR_SUCCESS if the event is a measurement or VSCP_ERROR_ERROR if it is not.

### Description
Check if an event is a measurement. 




#### C example

With the helper-library headers and standard C headers included:

```clike
uint8_t data[] = {0x4A, '3', '.', '1', '4'};
vscpEvent event = {0};
event.vscp_class = 10; event.vscp_type = 6;
event.sizeData = sizeof(data); event.pdata = data;
int result = vscphlp_isMeasurement(&event);
if (result == VSCP_ERROR_SUCCESS) {
    printf("measurement\n");
} else {
    fprintf(stderr, "Not a supported measurement (error %d)\n", result);
}
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
result = vscphelper.isMeasurement(event)
if result == vscp.VSCP_ERROR_SUCCESS:
    print("measurement")
else:
    print("not a supported measurement (error {})".format(result))
```

#### JavaScript availability

The official [Node.js binding](bindings.md#nodejs) does not currently expose this helper API, so there is no equivalent JavaScript example.

[filename](./bottom_copyright.md ':include')