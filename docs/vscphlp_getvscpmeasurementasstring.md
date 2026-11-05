

```clike
int vscphlp_getVSCPMeasurementAsString( const vscpEvent *pEvent, 
                                        char *pResult, 
                                        size_t len )
```

### Parameters

#### pEvent
The event the measurement string should be collected from.

#### pResult
The resulting measurement in string form.

#### len
Size for the buffer in which the resulting string is written.

### Return Value
`VSCP_ERROR_SUCCESS` (`0`) indicates success. Possible error codes: `VSCP_ERROR_ERROR`.

> **Known limitation:** For a Level II floating-point measurement containing 3.14, the current implementation returned `0.000000` instead of the measurement value.

### Description
This method returns a string representing the measurement data. It recognizes all data coding forms and returns an appropriate value.

#### C example

With the helper-library headers and standard C headers included:

```clike
uint8_t data[] = {0x4A, '3', '.', '1', '4'};
vscpEvent event = {0};
event.vscp_class = 10; event.vscp_type = 6;
event.sizeData = sizeof(data); event.pdata = data;
char value[64] = {0};
int result = vscphlp_getVSCPMeasurementAsString(&event, value, sizeof(value) - 1);
if (result != VSCP_ERROR_SUCCESS) {
    fprintf(stderr, "getVSCPMeasurementAsString failed (error %d)\n", result);
} else {
    printf("%s\n", value);
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
result, value = vscphelper.getVSCPMeasurementAsString(event)
if result != vscp.VSCP_ERROR_SUCCESS:
    raise RuntimeError("getVSCPMeasurementAsString failed (error {})".format(result))
print(value)
```

#### JavaScript availability

The official [Node.js binding](bindings.md#nodejs) does not currently expose this helper API, so there is no equivalent JavaScript example.

[filename](./bottom_copyright.md ':include')