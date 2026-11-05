

```clike
int vscphlp_setEventDateTimeBlockToNow( vscpEvent *pEvent )
```

### Parameters

#### pEvent
Pointer to the event whose datetime block will be set to **now**.

### Return Value
`VSCP_ERROR_SUCCESS` (`0`) indicates success. Possible error codes: `VSCP_ERROR_ERROR`.

### Description
Get date/time block for an event. 

#### C example

```clike
vscpEvent *pEvent;
vscphlp_setEventDateTimeBlockToNow( pEvent );
```
[vscphlp_setEventExDateTimeBlockToNow](vscphlp_seteventexdatetimeblocktonow.md)



#### Python example

Using the official [Python helper binding](bindings.md#python):

```python
import vscp
import vscphelper

event = vscp.vscpEvent()
result = vscphelper.setEventDateTimeBlockToNow(event)
if result != vscp.VSCP_ERROR_SUCCESS:
    raise RuntimeError("setEventDateTimeBlockToNow failed (error {})".format(result))
print("{:04d}-{:02d}-{:02d}".format(event.year, event.month, event.day))
```

#### JavaScript availability

See the [Node.js binding](bindings.md#nodejs) for C API access and native library availability.

[filename](./bottom_copyright.md ':include')