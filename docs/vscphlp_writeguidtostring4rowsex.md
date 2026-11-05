

```clike
int vscphlp_writeGuidToString4RowsEx( const vscpEventEx *pEvent, 
                                        char *strGUID,
                                        size_t len )
```

### Parameters

#### pEvent
VSCP event.

#### strGUID
String that receives the formatted GUID.

#### len
Size of the string buffer.

### Return Value
`VSCP_ERROR_SUCCESS` (`0`) indicates success. Possible error codes: `VSCP_ERROR_ERROR`.

### Description
Write GUID from VSCP event to string with four bytes on each row separated by “\r\n”. 

#### C example

With the helper-library headers and standard C headers included:

```clike
vscpEventEx event = {0};
for (unsigned i = 0; i < 16; ++i) event.GUID[i] = (uint8_t)i;
char text[128] = {0};
int result = vscphlp_writeGuidToString4RowsEx(&event, text, sizeof(text) - 1);
if (result != VSCP_ERROR_SUCCESS) {
    fprintf(stderr, "writeGuidToString4RowsEx failed (error %d)\n", result);
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
result, text = vscphelper.writeGuidToString4RowsEx(event)
if result != vscp.VSCP_ERROR_SUCCESS:
    raise RuntimeError("writeGuidToString4RowsEx failed (error {})".format(result))
print(text)
```

#### JavaScript availability

See the [Node.js binding](bindings.md#nodejs) for C API access and native library availability.

### See Also
[vscphlp_writeGuidToString4Rows](vscphlp_writeguidtostring4rows.md)



[filename](./bottom_copyright.md ':include')