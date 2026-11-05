
```clike
int vscphlp_writeVscpDataToString( char *pstr,
                                       const vscpEvent *pEvent,
                                       size_t len,
                                       int bUseHtmlBreak )
```

### Parameters

#### pstr
Buffer that receives the formatted data.

#### pEvent
The event that contains the data to be written.

#### len
Size of the output buffer.

#### bUseHtmlBreak
Set to true (nonzero) to use “\<br\>” instead of “\n” as the line break in the string.


### Return Value
`VSCP_ERROR_SUCCESS` (`0`) indicates success. Possible error codes: `VSCP_ERROR_ERROR`.

### Description
Write VSCP data in readable form to a possibly multiline string.

#### C example

With the helper-library headers and standard C headers included:

```clike
uint8_t data[] = {11, 22, 33};
vscpEvent event = {0};
event.sizeData = sizeof(data); event.pdata = data;
char text[128] = {0};
int result = vscphlp_writeVscpDataToString(text, &event, sizeof(text) - 1, 0);
if (result != VSCP_ERROR_SUCCESS) {
    fprintf(stderr, "writeVscpDataToString failed (error %d)\n", result);
} else {
    printf("%s\n", text);
}
```

#### Python example

Using the official [Python helper binding](bindings.md#python):

```python
import vscp
import vscphelper

from ctypes import POINTER, c_ubyte, cast

event = vscp.vscpEvent()
data = (c_ubyte * 3)(11, 22, 33)
event.sizedata = len(data)
event.pdata = cast(data, POINTER(c_ubyte))
result, text = vscphelper.writeVscpDataToString(event)
if result != vscp.VSCP_ERROR_SUCCESS:
    raise RuntimeError("writeVscpDataToString failed (error {})".format(result))
print(text)
```

#### JavaScript availability

The official [Node.js binding](bindings.md#nodejs) does not currently expose this helper API, so there is no equivalent JavaScript example.

[filename](./bottom_copyright.md ':include')