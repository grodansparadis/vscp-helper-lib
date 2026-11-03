

```clike
void vscphlp_clearVSCPFilter( vscpEventFilter *pFilter )
```

### Parameters

#### pFilter
Pointer to a VSCP filter structure.

### Return Value
None

### Description
Clear VSCP filter. 

#### C example

```clike
vscphlp_clearVSCPFilter( pFilter )
```




#### Python example

Using the official [Python helper binding](bindings.md#python):

```python
import vscp
import vscphelper

event_filter = vscp.vscpEventFilter()
event_filter.filter_class = 10
event_filter.mask_class = 0xFFFF
vscphelper.clearVSCPFilter(event_filter)
print(event_filter.filter_class, event_filter.mask_class)
```

#### JavaScript availability

The official [Node.js binding](bindings.md#nodejs) does not currently expose this helper API, so there is no equivalent JavaScript example.

[filename](./bottom_copyright.md ':include')