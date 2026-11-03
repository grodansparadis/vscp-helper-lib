


```clike
bool vscp_writeFilterToString( vscpEventFilter *pFilter, 
                                char *strFilter);
```

### Parameters

#### pFilter
Filter structure to which the filter will be written.

#### strFilter
Receives the filter in string form: priority,class,type,GUID. The buffer must be at least 65 bytes.

    filter-priority, filter-class, filter-type, filter-GUID

### Return Value
Returns VSCP_ERROR_SUCCESS on success.

### Description
Write a filter to a comma-separated string (priority,class,type,GUID).

#### C example

```clike
if ( VSCP_ERROR_SUCCESS != vscphlp_writeFilterToString( &filter, str ) ) {
    printf( "\aError: vscphlp_writeFilterToString\n");   
}
```

#### Python example

Using the official [Python helper binding](bindings.md#python):

```python
import vscp
import vscphelper

event_filter = vscp.vscpEventFilter()
event_filter.filter_class = 10
result, value = vscphelper.writeFilterToString(event_filter)
if result != vscp.VSCP_ERROR_SUCCESS:
    raise RuntimeError("writeFilterToString failed (error {})".format(result))
print(value)
```

#### JavaScript availability

The official [Node.js binding](bindings.md#nodejs) does not currently expose this helper API, so there is no equivalent JavaScript example.

### See Also
[vscphlp_readFilterFromString](vscphlp_readfilterfromstring.md)



[filename](./bottom_copyright.md ':include')