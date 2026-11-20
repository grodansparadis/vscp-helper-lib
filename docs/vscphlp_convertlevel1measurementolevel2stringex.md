

```clike
int vscphlp_convertLevel1MeasurementToLevel2StringEx( vscpEventEx *pEventEx )
```

### Parameters

#### pEvent
Pointer to a VSCP event ex.

### Return Value
`VSCP_ERROR_SUCCESS` (`0`) indicates success. Possible error codes: `VSCP_ERROR_ERROR`.

> The misspelled `vscphlp_convertLevel1MeasuremenToLevel2StringEx` is still exported as an alias for older code; use `vscphlp_convertLevel1MeasurementToLevel2StringEx`.

### Description
Convert Level I measurement to a Level II string measurement event [CLASS2.MEASUREMENT_STRING). 

#### Python example

Using the official [Python helper binding](bindings.md#python):

```python
import vscp
import vscphelper
from ctypes import POINTER, c_ubyte, cast

event = vscp.vscpEventEx()
event.vscpclass, event.vscptype = 10, 6
event.sizedata = 5
event.data[:5] = (0x4A, ord('3'), ord('.'), ord('1'), ord('4'))
result = vscphelper.convertLevel1MeasuremenToLevel2StringEx(event)
if result != vscp.VSCP_ERROR_SUCCESS:
    raise RuntimeError("convertLevel1MeasuremenToLevel2StringEx failed (error {})".format(result))
print(event.vscpclass, bytes(event.data[4:event.sizedata]).decode('ascii'))
```

#### JavaScript availability

See the [Node.js binding](bindings.md#nodejs) for C API access and native library availability.

### See Also
[vscphlp_convertLevel1MeasurementToLevel2String](vscphlp_convertlevel1measurementolevel2string.md)
[vscphlp_convertLevel1MeasurementToLevel2Double](vscphlp_convertlevel1measurementolevel2double.md)
[vscphlp_convertLevel1MeasurementToLevel2DoubleEx](vscphlp_convertlevel1measurementolevel2doubleex.md)



[filename](./bottom_copyright.md ':include')

