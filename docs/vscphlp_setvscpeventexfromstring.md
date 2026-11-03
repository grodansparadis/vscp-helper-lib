> Deprecated: Use [vscphlp_convertStringToEventEx](vscphlp_convertstringtoeventex.md)

```clike
int vscphlp_setVscpEventExFromString( vscpEventEx *pEvent, 
                                        const char *pstr )
```

### Parameters

#### pEvent
The VSCP event ex which will be written to.

#### pstr
Pointer to a string buffer containing an event in string form:

    head,class,type,obid,datetime,timestamp,GUID,data1,data2,data3....



### Return Value
VSCP_ERROR_SUCCESS is returned on success. 

### Description
Set VSCP event ex from a string. 

#### C example

With the helper-library headers and standard C headers included:

```clike
const char *text = "0,10,6,0,2020-11-24T17:28:11Z,4216090068,FF:FF:FF:FF:FF:FF:FF:F5:00:00:00:00:00:00:00:01,11,22,33";
vscpEventEx event = {0};
int result = vscphlp_setVscpEventExFromString(&event, text);
if (result != VSCP_ERROR_SUCCESS) {
    fprintf(stderr, "setVscpEventExFromString failed (error %d)\n", result);
} else {
    printf("class=%u type=%u data=%u,%u,%u\n",
           event.vscp_class, event.vscp_type,
           event.data[0], event.data[1], event.data[2]);
}
```

#### Python example

Using the official [Python helper binding](bindings.md#python):

```python
import vscp
import vscphelper

event = vscp.vscpEventEx()
text = "0,10,6,0,2020-11-24T17:28:11Z,4216090068,FF:FF:FF:FF:FF:FF:FF:F5:00:00:00:00:00:00:00:01,11,22,33"
result = vscphelper.setVscpEventExFromString(event, text)
if result != vscp.VSCP_ERROR_SUCCESS:
    raise RuntimeError("setVscpEventExFromString failed (error {})".format(result))
print(event.vscpclass, event.vscptype, list(event.data[:event.sizedata]))
```

#### JavaScript availability

The official [Node.js binding](bindings.md#nodejs) does not currently expose this helper API, so there is no equivalent JavaScript example.

### See Also
[vscphlp_setVscpEventFromString](vscphlp_setvscpeventfromstring.md)



[filename](./bottom_copyright.md ':include')