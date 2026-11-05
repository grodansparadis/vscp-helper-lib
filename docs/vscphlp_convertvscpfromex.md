

```clike
int vscphlp_convertVSCPfromEx( vscpEvent *pEvent, 
                    const vscpEventEx *pEventEx )
```

### Parameters

#### pEvent
VSCP event to convert to.

#### pEventEx
VSCP event ex to convert from.

### Return Value
`VSCP_ERROR_SUCCESS` (`0`) indicates success. Possible error codes: `VSCP_ERROR_ERROR`.

### Description
Convert a VSCP event from ex form to standard form.

#### C example

With the helper-library headers and standard C headers included:

```clike
vscpEventEx extended = {0};
extended.vscp_class = 30; extended.vscp_type = 5; extended.sizeData = 3;
extended.data[0] = 1; extended.data[1] = 2; extended.data[2] = 3;
vscpEvent *event = NULL;
int result = vscphlp_newVSCPevent(&event);
if (result != VSCP_ERROR_SUCCESS || event == NULL) {
    fprintf(stderr, "Could not allocate event (error %d)\n", result);
} else {
    result = vscphlp_convertVSCPfromEx(event, &extended);
    if (result != VSCP_ERROR_SUCCESS) {
        fprintf(stderr, "convertVSCPfromEx failed (error %d)\n", result);
    } else {
        printf("class=%u type=%u data=%u,%u,%u\n",
               event->vscp_class, event->vscp_type,
               event->pdata[0], event->pdata[1], event->pdata[2]);
    }
    vscphlp_deleteVSCPevent_v2(&event);
}
```

#### Python example

Using the official [Python helper binding](bindings.md#python):

```python
import vscp
import vscphelper

extended = vscp.vscpEventEx()
extended.vscpclass, extended.vscptype = 30, 5
extended.sizedata = 3
extended.data[:3] = (1, 2, 3)
result, event_ptr = vscphelper.newVSCPevent()
if result != vscp.VSCP_ERROR_SUCCESS or not event_ptr:
    raise RuntimeError("Could not allocate event (error {})".format(result))
try:
    result = vscphelper.convertVSCPfromEx(event_ptr.contents, extended)
    if result != vscp.VSCP_ERROR_SUCCESS:
        raise RuntimeError("convertVSCPfromEx failed (error {})".format(result))
    event = event_ptr.contents
    print(event.vscpclass, event.vscptype, list(event.pdata[:event.sizedata]))
finally:
    vscphelper.deleteVSCPevent_v2(event_ptr)
```

#### JavaScript availability

The official [Node.js binding](bindings.md#nodejs) does not currently expose this helper API, so there is no equivalent JavaScript example.

### See Also
[vscphlp_convertVSCPtoEx](vscphlp_convertvscptoex.md)



[filename](./bottom_copyright.md ':include')