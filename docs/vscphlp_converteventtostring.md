


```clike
int vscphlp_convertEventToString( const vscpEvent *pEvent, 
                                    char *pstr, 
                                    size_t len )
```

> Added in 14.0.2

### Parameters

#### pEvent
The VSCP event which will be written to the string buffer.

#### pstr
Pointer to the string buffer that will receive the result.

#### len
Size of buffer.

### Return Value
VSCP_ERROR_SUCCESS is returned on success. 

### Description
Write VSCP event content to a string. 

#### C example

With the helper-library headers and standard C headers included:

```clike
vscpEvent event = {0};
event.vscp_class = 10;
event.vscp_type = 6;
for (unsigned i = 0; i < 16; ++i) event.GUID[i] = (uint8_t)i;
char text[4096] = {0};
int result = vscphlp_convertEventToString(&event, text, sizeof(text) - 1);
if (result != VSCP_ERROR_SUCCESS) {
    fprintf(stderr, "convertEventToString failed (error %d)\n", result);
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
result, text = vscphelper.convertEventToString(event)
if result != vscp.VSCP_ERROR_SUCCESS:
    raise RuntimeError("convertEventToString failed (error {})".format(result))
print(text)
```

#### JavaScript availability

The official [Node.js binding](bindings.md#nodejs) does not currently expose this helper API, so there is no equivalent JavaScript example.

### See Also

[vscphlp_writeVscpEventExToString](vscphlp_writevscpeventextostring.md)



[filename](./bottom_copyright.md ':include')
