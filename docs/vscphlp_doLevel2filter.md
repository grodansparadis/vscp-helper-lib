

```clike
int vscphlp_doLevel2Filter( const vscpEvent *pEvent, 
                            const vscpEventFilter *pFilter )
```

### Parameters

#### pEvent
Pointer to event that should be filtered.

#### pFilter
Filter/mask to use for the filtering.

### Return Value
`VSCP_ERROR_SUCCESS` (`0`) means the event passes the filter; `VSCP_ERROR_ERROR` (`-1`)
means the helper did not accept it. This return convention is a status, not a true/false
result.

### Description
Check VSCP filter condition. 

#### C example

```clike
if ( VSCP_ERROR_SUCCESS == vscphlp_doLevel2Filter( pEvent, &filter ) ) {
    printf( "Event pass:  vscphlp_doLevel2Filter\n");
}
else {
   printf( "Event does NOT pass:  vscphlp_doLevel2Filter\n");
}
```



#### Python example

Using the official [Python helper binding](bindings.md#python):

```python
import vscp
import vscphelper

event = vscp.vscpEvent()
event.vscpclass = 10
event_filter = vscp.vscpEventFilter()
result = vscphelper.doLevel2Filter(event, event_filter)
if result == vscp.VSCP_ERROR_SUCCESS:
    print("Event accepted")
else:
    print("Event filtered out")
```

#### JavaScript availability

See the [Node.js binding](bindings.md#nodejs) for C API access and native library availability.

[filename](./bottom_copyright.md ':include')
