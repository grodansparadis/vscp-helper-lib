

```clike
int vscphlp_makeStringMeasurementEvent( vscpEvent *pEvent, 
                                        float value,
                                        unsigned char unit,
                                        unsigned char sensoridx )
```

### Parameters

#### pEvent
Pointer to a VSCP event that will receive the result as its data.

#### value
Floating-point value to encode as a string.

#### unit
A unit value from 0 to 3.

#### sensoridx
A sensor index from 0 to 7.

### Return Value
`VSCP_ERROR_SUCCESS` (`0`) indicates success. Possible error codes: `VSCP_ERROR_ERROR`.

### Description
Make a string coded level I event from floating point data.

#### C example

With the helper-library headers and standard C headers included:

```clike
vscpEvent *event = NULL;
int result = vscphlp_newVSCPevent(&event);
if (result != VSCP_ERROR_SUCCESS || event == NULL) {
    fprintf(stderr, "Could not allocate event (error %d)\n", result);
} else {
    event->vscp_class = 10; event->vscp_type = 6;
    result = vscphlp_makeStringMeasurementEvent(event, 3.14f, 1, 2);
    double value = 0;
    if (result == VSCP_ERROR_SUCCESS) {
        result = vscphlp_getVSCPMeasurementAsDouble(event, &value);
    }
    if (result != VSCP_ERROR_SUCCESS) {
        fprintf(stderr, "Measurement conversion failed (error %d)\n", result);
    } else {
        printf("%.2f\n", value);
    }
    vscphlp_deleteVSCPevent_v2(&event);
}
```

#### Python example

Using the official [Python helper binding](bindings.md#python):

```python
import vscp
import vscphelper
from ctypes import POINTER, c_ubyte, cast

result, event_ptr = vscphelper.newVSCPevent()
if result != vscp.VSCP_ERROR_SUCCESS or not event_ptr:
    raise RuntimeError("Could not allocate event (error {})".format(result))
try:
    event = event_ptr.contents
    event.vscpclass, event.vscptype = 10, 6
    result = vscphelper.makeStringMeasurementEvent(event, 3.14, 1, 2)
    if result != vscp.VSCP_ERROR_SUCCESS:
        raise RuntimeError("makeStringMeasurementEvent failed (error {})".format(result))
    result, value = vscphelper.getVSCPMeasurementAsDouble(event)
    if result != vscp.VSCP_ERROR_SUCCESS:
        raise RuntimeError("getVSCPMeasurementAsDouble failed (error {})".format(result))
    print(value)
finally:
    vscphelper.deleteVSCPevent_v2(event_ptr)
```

#### JavaScript availability

See the [Node.js binding](bindings.md#nodejs) for C API access and native library availability.

[filename](./bottom_copyright.md ':include')