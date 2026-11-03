
> Deprecated: Use [vscphlp_convertStringToEvent](vscphlp_convertstringtoevent.md)



```clike
int vscphlp_setVscpEventFromString( vscpEvent *pEvent, 
                                    const char *pstr )
```

### Parameters

#### pEvent
The VSCP event which will be written to.

#### pstr
Pointer to a string buffer containing an event in string form:

    head,class,type,obid,datetime,timestamp,GUID,data1,data2,data3....

### Return Value
VSCP_ERROR_SUCCESS is returned on success. 

### Description
Set VSCP event from a string.

#### C example

With the helper-library headers and standard C headers included:

```clike
const char *text = "0,10,6,0,2020-11-24T17:28:11Z,4216090068,FF:FF:FF:FF:FF:FF:FF:F5:00:00:00:00:00:00:00:01,11,22,33";
vscpEvent *event = NULL;
int result = vscphlp_newVSCPevent(&event);
if (result != VSCP_ERROR_SUCCESS || event == NULL) {
    fprintf(stderr, "Could not allocate event (error %d)\n", result);
} else {
    result = vscphlp_setVscpEventFromString(event, text);
    if (result != VSCP_ERROR_SUCCESS) {
        fprintf(stderr, "setVscpEventFromString failed (error %d)\n", result);
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

text = "0,10,6,0,2020-11-24T17:28:11Z,4216090068,FF:FF:FF:FF:FF:FF:FF:F5:00:00:00:00:00:00:00:01,11,22,33"
result, event_ptr = vscphelper.newVSCPevent()
if result != vscp.VSCP_ERROR_SUCCESS or not event_ptr:
    raise RuntimeError("Could not allocate event (error {})".format(result))
event_ptr.contents.vscpclass = 0
event_ptr.contents.vscptype = 0
try:
    result = vscphelper.setVscpEventFromString(event_ptr.contents, text)
    if result != vscp.VSCP_ERROR_SUCCESS:
        raise RuntimeError("setVscpEventFromString failed (error {})".format(result))
    event = event_ptr.contents
    print(event.vscpclass, event.vscptype, list(event.pdata[:event.sizedata]))
finally:
    vscphelper.deleteVSCPevent_v2(event_ptr)
```

#### JavaScript availability

The official [Node.js binding](bindings.md#nodejs) does not currently expose this helper API, so there is no equivalent JavaScript example.

### See Also
[vscphlp_setVscpEventExFromString](vscphlp_setvscpeventexfromstring.md)



[filename](./bottom_copyright.md ':include')