

```clike
unsigned char vscphlp_getMeasurementDataCoding( const vscpEvent *pEvent )
```

### Parameters

#### pEvent
Event that the data coding is fetched from.


### Return Value
Returns the data-coding byte, not an error code. `255` (`0xff`) is returned for missing data
or an unsupported event class; it is an unsigned-byte sentinel.

### Description
Get the [measurement data coding byte](https://grodansparadis.gitbooks.io/the-vscp-specification/vscp_data_coding.html) from an event. The measurement data coding byte specifies how the data in the event should be interpreted. 

#### C example

With the helper-library headers and standard C headers included:

```clike
uint8_t data[] = {0x4A, '3', '.', '1', '4'};
vscpEvent event = {0};
event.vscp_class = 10; event.vscp_type = 6;
event.sizeData = sizeof(data); event.pdata = data;
printf("%d\n", vscphlp_getMeasurementDataCoding(&event));
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
print(vscphelper.getMeasurementDataCoding(event))
```

#### JavaScript availability

See the [Node.js binding](bindings.md#nodejs) for C API access and native library availability.

[filename](./bottom_copyright.md ':include')