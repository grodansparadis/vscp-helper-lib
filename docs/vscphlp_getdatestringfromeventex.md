

```clike
int vscphlp_getDateStringFromEventEx( char *buf, 
                                size_t buf_len, 
                                vscpEventEx *pEventEx )
```

### Parameters

#### buf
Buffer that will receive the date string from the event ex.

Example result: “2003-11-02T12:23:10Z”

#### buf_len
Length of the buffer.

#### pEventEx
Event from which to get the date string.

### Return Value
`VSCP_ERROR_SUCCESS` (`0`) indicates success. Possible error codes: `VSCP_ERROR_ERROR`,
`VSCP_ERROR_PARAMETER`.

### Description
Extract an ISO date string from the datetime block of an event.

#### C example

With the helper-library headers and standard C headers included:

```clike
vscpEventEx event = {0};
event.year = 2020; event.month = 11; event.day = 24;
event.hour = 17; event.minute = 28; event.second = 11;
char text[64] = {0};
int result = vscphlp_getDateStringFromEventEx(text, sizeof(text), &event);
if (result != VSCP_ERROR_SUCCESS) {
    fprintf(stderr, "getDateStringFromEventEx failed (error %d)\n", result);
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
event.year, event.month, event.day = 2020, 11, 24
event.hour, event.minute, event.second = 17, 28, 11
result, text = vscphelper.getDateStringFromEventEx(event)
if result != vscp.VSCP_ERROR_SUCCESS:
    raise RuntimeError("getDateStringFromEventEx failed (error {})".format(result))
print(text)
```

#### JavaScript availability

See the [Node.js binding](bindings.md#nodejs) for C API access and native library availability.

### See Also
[vscphlp_getDateStringFromEvent](vscphlp_getdatestringfromevent.md)



[filename](./bottom_copyright.md ':include')