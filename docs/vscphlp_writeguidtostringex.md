

```clike
int vscphlp_writeGuidToStringEx( const vscpEventEx *pEvent,
                                    char *pStr, 
                                    size_t len )
```

### Parameters

#### pEvent
VSCP event.

#### pStr
Pointer to a GUID in string form.

#### len
Size of the string buffer.

### Return Value
VSCP_ERROR_SUCCESS on success

### Description
Write GUID from VSCP event to string. 

#### C example

With the helper-library headers and standard C headers included:

```clike
vscpEventEx event = {0};
for (unsigned i = 0; i < 16; ++i) event.GUID[i] = (uint8_t)i;
char text[128] = {0};
int result = vscphlp_writeGuidToStringEx(&event, text, sizeof(text) - 1);
if (result != VSCP_ERROR_SUCCESS) {
    fprintf(stderr, "writeGuidToStringEx failed (error %d)\n", result);
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
event.guid[:] = range(16)
result, text = vscphelper.writeGuidToStringEx(event)
if result != vscp.VSCP_ERROR_SUCCESS:
    raise RuntimeError("writeGuidToStringEx failed (error {})".format(result))
print(text)
```

#### JavaScript availability

The official [Node.js binding](bindings.md#nodejs) does not currently expose this helper API, so there is no equivalent JavaScript example.

### See Also
[vscphlp_writeGuidToString](vscphlp_writeguidtostring.md)



[filename](./bottom_copyright.md ':include')