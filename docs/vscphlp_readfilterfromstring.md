

```clike
int vscphlp_readFilterFromString( vscpEventFilter *pFilter, 
                            char *strFilter )
```

### Parameters

#### pFilter
Filter structure to which the filter will be written.

#### strFilter
Filter in string form:

    filter-priority, filter-class, filter-type, filter-GUID

For example:

    1,0x0000,0x0006,ff:ff:ff:ff:ff:ff:ff:01:00:00:00:00:00:00:00:00

All values are optional, but those supplied must be in order. For example:

    1,0x0000,0x0006

This sets the GUID to all zeros.


### Return Value
`VSCP_ERROR_SUCCESS` (`0`) indicates success. Possible error codes: `VSCP_ERROR_ERROR`.

### Description
Read a filter from a string. If strFilter is empty, all filter elements are set to zero. The arguments are:

    priority,class,type,GUID 

All arguments are optional, but those supplied must be in order.

#### C example

```clike
if ( VSCP_ERROR_SUCCESS != vscphlp_readFilterFromString( &filter, 
                "1,0x0000,0x0006,ff:ff:ff:ff:ff:ff:ff:01:00:00:00:00:00:00:00:00" ) ) {
    printf( "\aError: vscphlp_readFilterFromString\n");   
}
```

#### Python example

Using the official [Python helper binding](bindings.md#python):

```python
import vscp
import vscphelper

event_filter = vscp.vscpEventFilter()
value = "1,0,6,FF:FF:FF:FF:FF:FF:FF:F5:00:00:00:00:00:00:00:01"
result = vscphelper.readFilterFromString(event_filter, value)
if result != vscp.VSCP_ERROR_SUCCESS:
    raise RuntimeError("readFilterFromString failed (error {})".format(result))
print(event_filter.filter_type)
```

#### JavaScript availability

See the [Node.js binding](bindings.md#nodejs) for C API access and native library availability.

### See Also
[vscphlp_writeFilterToString](vscphlp_writefiltertostring.md)



[filename](./bottom_copyright.md ':include')