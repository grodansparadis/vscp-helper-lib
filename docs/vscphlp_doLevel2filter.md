

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
Return true (non-zero) if the event is accepted by the filter. 

### Description
Check VSCP filter condition. 

#### C example

```clike
if ( vscphlp_doLevel2Filter( pEvent, &filter ) ) {
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

The official [Node.js binding](bindings.md#nodejs) does not currently expose this helper API, so there is no equivalent JavaScript example.

[filename](./bottom_copyright.md ':include')
