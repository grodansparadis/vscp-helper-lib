

```clike
int vscphlp_newVSCPevent( vscpEvent **ppEvent )
```

### Parameters

#### ppEvent
Pointer to pointer to a VSCP event.

### Return Value
`VSCP_ERROR_SUCCESS` (`0`) indicates success. Possible error codes: `VSCP_ERROR_ERROR`.

### Description
Creates a new VSCP event and initializes its data pointer and size. Initialize
other event fields before reading them. Release the event and any helper-owned
data with [vscphlp_deleteVSCPevent_v2](vscphlp_deletevscpevent_v2.md).

#### C example

```clike
vscpEvent *event = NULL;
int result = vscphlp_newVSCPevent(&event);
if (result != VSCP_ERROR_SUCCESS || event == NULL) {
    fprintf(stderr, "Could not allocate event (error %d)\n", result);
} else {
    event->vscp_class = 10;
    printf("class=%u\n", event->vscp_class);
    vscphlp_deleteVSCPevent_v2(&event);
}
```


#### Python example

Using the official [Python helper binding](bindings.md#python):

```python
import vscp
import vscphelper

result, event = vscphelper.newVSCPevent()
if result != vscp.VSCP_ERROR_SUCCESS or not event:
    raise RuntimeError("Could not allocate an event (error {})".format(result))
try:
    event.contents.vscpclass = 10
    print(event.contents.vscpclass)
finally:
    vscphelper.deleteVSCPevent_v2(event)
```

#### JavaScript availability

See the [Node.js binding](bindings.md#nodejs) for C API access and native library availability.

### See Also
[vscphlp_deleteVSCPevent](vscphlp_deletevscpevent.md)  
[vscphlp_deleteVSCPevent_v2](vscphlp_deletevscpevent_v2.md)



[filename](./bottom_copyright.md ':include')