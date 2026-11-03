

```clike
void vscphlp_copyVSCPFilter( vscpEventFilter *pToFilter, 
                    const vscpEventFilter *pFromFilter )
```

### Parameters

#### pToFilter
Pointer to VSCP filter structure that will receive data.

### pFromFilter
Pointer to VSCP filter structure that data will be copied from.


### Return Value
None

### Description
Copy VSCP filter from one to another. 

#### C example

```clike
vscphlp_clearVSCPFilter( pFilter )
```



#### Python example

Using the official [Python helper binding](bindings.md#python):

```python
import vscp
import vscphelper

source = vscp.vscpEventFilter()
source.filter_class = 10
destination = vscp.vscpEventFilter()
vscphelper.copyVSCPFilter(destination, source)
print(destination.filter_class)
```

#### JavaScript availability

The official [Node.js binding](bindings.md#nodejs) does not currently expose this helper API, so there is no equivalent JavaScript example.

[filename](./bottom_copyright.md ':include')