

```clike
int vscphlp_getVSCPMeasurementAsDouble( const vscpEvent *pEvent, 
                                        double *pvalue)
```

### Parameters

#### pEvent
The event containing the measurement data.

#### pvalue
A pointer to a double that will receive the measurement result.


### Return Value
`VSCP_ERROR_SUCCESS` (`0`) indicates success. Possible error codes: `VSCP_ERROR_ERROR`.

### Description
This method returns a double representing the measurement data. It recognizes all data coding forms and returns an appropriate value.

#### C example

With the helper-library headers and standard C headers included:

```clike
uint8_t data[] = {0x4A, '3', '.', '1', '4'};
vscpEvent event = {0};
event.vscp_class = 10; event.vscp_type = 6;
event.sizeData = sizeof(data); event.pdata = data;
double value = 0;
int result = vscphlp_getVSCPMeasurementAsDouble(&event, &value);
if (result != VSCP_ERROR_SUCCESS) {
    fprintf(stderr, "getVSCPMeasurementAsDouble failed (error %d)\n", result);
} else {
    printf("%.2f\n", value);
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
result, value = vscphelper.getVSCPMeasurementAsDouble(event)
if result != vscp.VSCP_ERROR_SUCCESS:
    raise RuntimeError("getVSCPMeasurementAsDouble failed (error {})".format(result))
print(value)
```

#### JavaScript availability

See the [Node.js binding](bindings.md#nodejs) for C API access and native library availability.

[filename](./bottom_copyright.md ':include')