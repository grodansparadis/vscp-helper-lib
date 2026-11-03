

```clike
int vscphlp_convertEventToJSON( vscpEvent *pEvent, 
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
Returns VSCP_ERROR_SUCCESS on success or VSCP_ERROR_BUFFER_TO_SMALL if the supplied buffer is too small.

### Description
Write a VSCP event to a string in JSON format. The format is specified in [vscp.h](https://github.com/grodansparadis/vscp/blob/master/src/vscp/common/vscp.h).


#### C example

With the helper-library headers and standard C headers included:

```clike
vscpEvent event = {0};
event.vscp_class = 10;
event.vscp_type = 6;
for (unsigned i = 0; i < 16; ++i) event.GUID[i] = (uint8_t)i;
char text[4096] = {0};
int result = vscphlp_convertEventToJSON(&event, text, sizeof(text) - 1);
if (result != VSCP_ERROR_SUCCESS) {
    fprintf(stderr, "convertEventToJSON failed (error %d)\n", result);
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
result, text = vscphelper.convertEventToJSON(event)
if result != vscp.VSCP_ERROR_SUCCESS:
    raise RuntimeError("convertEventToJSON failed (error {})".format(result))
print(text)
```

#### JavaScript availability

The official [Node.js binding](bindings.md#nodejs) does not currently expose this helper API, so there is no equivalent JavaScript example.

### See Also
[vscphlp_convertEventExToJSON](vscphlp_converteventextojson.md)



[filename](./bottom_copyright.md ':include')