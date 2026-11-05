

```clike
int vscphlp_convertEventToHTML( vscpEvent *pEvent, 
                                char *pBuffer, 
                                size_t len )
```

### Parameters

#### pEvent
Pointer to an event.

#### pBuffer
Buffer that will receive the resulting string.

#### len
Size of the string buffer.

### Return Value
`VSCP_ERROR_SUCCESS` (`0`) indicates success. Possible error codes:
`VSCP_ERROR_BUFFER_TO_SMALL`.

The conversion helper's own success/failure result is not checked by this wrapper.

### Description
Write a VSCP event to a string in HTML format. The format is specified in [vscp.h](https://github.com/grodansparadis/vscp/blob/master/src/vscp/common/vscp.h).


#### C example

With the helper-library headers and standard C headers included:

```clike
vscpEvent event = {0};
event.vscp_class = 10;
event.vscp_type = 6;
for (unsigned i = 0; i < 16; ++i) event.GUID[i] = (uint8_t)i;
char text[4096] = {0};
int result = vscphlp_convertEventToHTML(&event, text, sizeof(text) - 1);
if (result != VSCP_ERROR_SUCCESS) {
    fprintf(stderr, "convertEventToHTML failed (error %d)\n", result);
} else {
    printf("%s\n", text);
}
```

#### Python example

Using the official [Python helper binding](bindings.md#python):

```python
import vscp
import vscphelper

event = vscp.vscpEvent()
event.vscpclass = 10
event.vscptype = 6
event.guid[:] = range(16)
result, text = vscphelper.convertEventToHTML(event)
if result != vscp.VSCP_ERROR_SUCCESS:
    raise RuntimeError("convertEventToHTML failed (error {})".format(result))
print(text)
```

#### JavaScript availability

See the [Node.js binding](bindings.md#nodejs) for C API access and native library availability.

### See Also
[vscphlp_convertEventExToHTML](vscphlp_converteventextohtml.md)



[filename](./bottom_copyright.md ':include')