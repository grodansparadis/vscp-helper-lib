

```clike
int vscphlp_setVscpDataFromString( vscpEvent *pEvent, 
                                   const char *pstr )
```


### Parameters

#### pEvent
VSCP Event which will have its data set.

#### pstr
Pointer to a null-terminated string containing data in comma-separated form.

### Return Value
VSCP_ERROR_SUCCESS is returned on success. 

### Description
Set data in VSCP event from a string. 

#### C example

With the helper-library headers and standard C headers included:

```clike
vscpEvent *event = NULL;
int result = vscphlp_newVSCPevent(&event);
if (result != VSCP_ERROR_SUCCESS || event == NULL) {
    fprintf(stderr, "Could not allocate event (error %d)\n", result);
} else {
    result = vscphlp_setVscpDataFromString(event, "11,22,33");
    if (result != VSCP_ERROR_SUCCESS) {
        fprintf(stderr, "setVscpDataFromString failed (error %d)\n", result);
    } else {
        printf("data=%u,%u,%u\n", event->pdata[0], event->pdata[1], event->pdata[2]);
    }
    vscphlp_deleteVSCPevent_v2(&event);
}
```



#### Python example

Using the official [Python helper binding](bindings.md#python):

```python
import vscp
import vscphelper

text = "11,22,33"
result, event_ptr = vscphelper.newVSCPevent()
if result != vscp.VSCP_ERROR_SUCCESS or not event_ptr:
    raise RuntimeError("Could not allocate event (error {})".format(result))
event_ptr.contents.vscpclass = 0
event_ptr.contents.vscptype = 0
try:
    result = vscphelper.setVscpDataFromString(event_ptr.contents, text)
    if result != vscp.VSCP_ERROR_SUCCESS:
        raise RuntimeError("setVscpDataFromString failed (error {})".format(result))
    event = event_ptr.contents
    print(event.vscpclass, event.vscptype, list(event.pdata[:event.sizedata]))
finally:
    vscphelper.deleteVSCPevent_v2(event_ptr)
```

#### JavaScript availability

The official [Node.js binding](bindings.md#nodejs) does not currently expose this helper API, so there is no equivalent JavaScript example.

[filename](./bottom_copyright.md ':include')