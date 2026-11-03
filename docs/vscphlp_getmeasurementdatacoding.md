

```clike
unsigned char vscphlp_getMeasurementDataCoding( const vscpEvent *pEvent )
```

### Parameters

#### pEvent
Event that the data coding is fetched from.


### Return Value
Data coding byte.

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

The official [Node.js binding](bindings.md#nodejs) does not currently expose this helper API, so there is no equivalent JavaScript example.

[filename](./bottom_copyright.md ':include')