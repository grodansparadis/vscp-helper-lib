
Deprecated: Use [vscphlp_convertEventExToString](vscphlp_converteventextostring.md)

```clike
int vscphlp_writeVscpEventExToString( const vscpEventEx     *pEvent, 
                                        char *pstr, 
                                        size_t len )
```

### Parameters

#### pEvent
The VSCP event which will be written to the string buffer.

#### pstr
Pointer to the string buffer that will receive the result.

#### len
Size of buffer.

### Return Value
`VSCP_ERROR_SUCCESS` (`0`) indicates success. Possible error codes: `VSCP_ERROR_ERROR`.

### Description
Write VSCP event ex content to a string. 

#### C example

With the helper-library headers and standard C headers included:

```clike
vscpEventEx event = {0};
event.vscp_class = 10;
event.vscp_type = 6;
for (unsigned i = 0; i < 16; ++i) event.GUID[i] = (uint8_t)i;
char text[4096] = {0};
int result = vscphlp_writeVscpEventExToString(&event, text, sizeof(text) - 1);
if (result != VSCP_ERROR_SUCCESS) {
    fprintf(stderr, "convertEventExToString failed (error %d)\n", result);
} else {
    printf("%s\n", text);
}
```

#### Python example

Using the official [Python helper binding](bindings.md#python):

```python
import vscp
import vscphelper

event = vscp.vscpEventEx()
event.vscpclass = 10
event.vscptype = 6
event.guid[:] = range(16)
result, text = vscphelper.convertEventExToString(event)
if result != vscp.VSCP_ERROR_SUCCESS:
    raise RuntimeError("convertEventExToString failed (error {})".format(result))
print(text)
```

#### JavaScript availability

The official [Node.js binding](bindings.md#nodejs) does not currently expose this helper API, so there is no equivalent JavaScript example.

### See Also
[vscphlp_writeVscpEventToString](vscphlp_writevscpeventtostring.md)



[filename](./bottom_copyright.md ':include')
