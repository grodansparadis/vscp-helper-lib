

```clike
int vscphlp_convertLevel1MeasuremenToLevel2String( vscpEvent *pEvent )
```

### Parameters

#### pEvent
Pointer to a VSCP event.

### Return Value
`VSCP_ERROR_SUCCESS` (`0`) indicates success. Possible error codes: `VSCP_ERROR_ERROR`.

> **C API limitation:** The header declares this name with `Measuremen`, but the library exports it with `Measurement`. The Python wrapper resolves the exported name.

### Description
Convert Level I measurement to a Level II string measurement event [CLASS2.MEASUREMENT_STRING). 

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
    result = vscphelper.setVscpDataFromString(event, "74,51,46,49,52")
    if result != vscp.VSCP_ERROR_SUCCESS:
        raise RuntimeError("setVscpDataFromString failed (error {})".format(result))
    result = vscphelper.convertLevel1MeasuremenToLevel2String(event)
    if result != vscp.VSCP_ERROR_SUCCESS:
        raise RuntimeError("convertLevel1MeasuremenToLevel2String failed (error {})".format(result))
    print(event.vscpclass, bytes(event.pdata[4:event.sizedata]).decode('ascii'))
finally:
    vscphelper.deleteVSCPevent_v2(event_ptr)
```

#### JavaScript availability

The official [Node.js binding](bindings.md#nodejs) does not currently expose this helper API, so there is no equivalent JavaScript example.

### See Also
[vscphlp_convertLevel1MeasuremenToLevel2StringEx](vscphlp_convertlevel1measurementolevel2stringex.md)
[vscphlp_convertLevel1MeasuremenToLevel2Double](vscphlp_convertlevel1measurementolevel2double.md)
[vscphlp_convertLevel1MeasuremenToLevel2DoubleEx](vscphlp_convertlevel1measurementolevel2doubleex.md)



[filename](./bottom_copyright.md ':include')

