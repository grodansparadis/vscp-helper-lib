

```clike
int vscphlp_setEventExDateTimeBlockToNow( vscpEventEx *pEventEx )
```

### Parameters

#### pEventEx
Pointer to the event whose datetime block will be set to the current time.

### Return Value
`VSCP_ERROR_SUCCESS` (`0`) indicates success. Possible error codes: `VSCP_ERROR_ERROR`.

### Description
Get date/time block for an ex event. 

#### C example

```clike
vscpEventEx *pEventEx;
vscphlp_setEventExDateTimeBlockToNow( pEventEx );
```

#### Python example

Using the official [Python helper binding](bindings.md#python):

```python
import vscp
import vscphelper

event = vscp.vscpEventEx()
result = vscphelper.setEventExDateTimeBlockToNow(event)
if result != vscp.VSCP_ERROR_SUCCESS:
    raise RuntimeError("setEventExDateTimeBlockToNow failed (error {})".format(result))
print("{:04d}-{:02d}-{:02d}".format(event.year, event.month, event.day))
```

#### JavaScript availability

See the [Node.js binding](bindings.md#nodejs) for C API access and native library availability.

### See Also
[vscphlp_setEventDateTimeBlockToNow](vscphlp_seteventdatetimeblocktonow.md)



[filename](./bottom_copyright.md ':include')