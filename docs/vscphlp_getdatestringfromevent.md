

```clike
int vscphlp_getDateStringFromEvent( char *buf, 
                            size_t buf_len, 
                            vscpEvent *pEvent )
```

### Parameters

#### buf
Buffer that will receive the date string from the event.

Example result: “2003-11-02T12:23:10Z”

#### buf_len
Length of the buffer.

#### pEvent
Event from which to get the date string.

### Return Value
Returns VSCP_ERROR_SUCCESS on success.

### Description
Extract an ISO date string from the datetime block of an event.

#### C example

With the helper-library headers and standard C headers included:

```clike
vscpEvent event = {0};
event.year = 2020; event.month = 11; event.day = 24;
event.hour = 17; event.minute = 28; event.second = 11;
char text[64] = {0};
int result = vscphlp_getDateStringFromEvent(text, sizeof(text), &event);
if (result != VSCP_ERROR_SUCCESS) {
    fprintf(stderr, "getDateStringFromEvent failed (error %d)\n", result);
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
event.year, event.month, event.day = 2020, 11, 24
event.hour, event.minute, event.second = 17, 28, 11
result, text = vscphelper.getDateStringFromEvent(event)
if result != vscp.VSCP_ERROR_SUCCESS:
    raise RuntimeError("getDateStringFromEvent failed (error {})".format(result))
print(text)
```

#### JavaScript availability

The official [Node.js binding](bindings.md#nodejs) does not currently expose this helper API, so there is no equivalent JavaScript example.

### See Also
[vscphlp_getDateStringFromEventEx](vscphlp_getdatestringfromeventex.md)



[filename](./bottom_copyright.md ':include')