

```clike
int vscphlp_writeMaskToString( vscpEventFilter *pFilter, 
                                char * strMask )
```

### Parameters

#### pFilter
Filter structure to write mask from.

#### strMask
String buffer that will receive the mask in comma-separated form. It must be at least 65 bytes.

    mask-priority, mask-class, mask-type, mask-GUID

### Return Value
`VSCP_ERROR_SUCCESS` (`0`) indicates success. Possible error codes: `VSCP_ERROR_ERROR`.

The caller must provide a sufficiently large output buffer; this API has no capacity
argument.

### Description
Write the mask to a comma-separated string. If strMask is empty, the mask elements are set to zero.

#### C example

```clike
if ( VSCP_ERROR_SUCCESS != vscphlp_writeMaskToString( &filter, 
                "1,0x0000,0x0006,ff:ff:ff:ff:ff:ff:ff:01:00:00:00:00:00:00:00:00" ) ) {
    printf( "\aError: vscphlp_writeMaskToString\n");   
} 
```

#### Python example

Using the official [Python helper binding](bindings.md#python):

```python
import vscp
import vscphelper

event_filter = vscp.vscpEventFilter()
event_filter.mask_class = 10
result, value = vscphelper.writeMaskToString(event_filter)
if result != vscp.VSCP_ERROR_SUCCESS:
    raise RuntimeError("writeMaskToString failed (error {})".format(result))
print(value)
```

#### JavaScript availability

See the [Node.js binding](bindings.md#nodejs) for C API access and native library availability.

### See Also
[vscphlp_readMaskFromString](vscphlp_readmaskfromstring.md)




[filename](./bottom_copyright.md ':include')