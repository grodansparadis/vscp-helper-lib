

```clike
void vscphlp_clearVSCPFilter( vscpEventFilter *pFilter )
```

### Parameters

#### pFilter
Pointer to a VSCP filter structure.

### Return Value
Returns no value or error code.

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

See the [Node.js binding](bindings.md#nodejs) for C API access and native library availability.

[filename](./bottom_copyright.md ':include')