

```clike
int vscphlp_readMaskFromString( vscpEventFilter *pFilter, 
                                const char * strMask )
```

### Parameters

#### pFilter

Filter structure to which the mask will be written.

#### strMask

Mask in string form:

    mask-priority, mask-class, mask-type, mask-GUID

For example:

    1,0x00ff,0x00ff,ff:ff:ff:ff:ff:ff:ff:ff:ff:ff:ff:ff:ff:ff:ff:ff  

All values are optional, but those supplied must be in order. For example:

    1,0x00ff

is interpreted as:

    1,0x00ff,0x0000,00:00:00:00:00:00:00:00:00:00:00:00:00:00:00:00  



### Return Value
`VSCP_ERROR_SUCCESS` (`0`) indicates success. Possible error codes: `VSCP_ERROR_ERROR`.

### Description
Read a mask from a string. If strMask is empty, the mask elements are set to zero.

#### C example

```clike
if ( VSCP_ERROR_SUCCESS != vscphlp_readMaskFromString( &filter, 
                "1,0x0000,0x0006,ff:ff:ff:ff:ff:ff:ff:01:00:00:00:00:00:00:00:00" ) ) {
    printf( "\aError: vscphlp_readMaskFromString\n");   
}
```

#### See Also
* [vscphlp_writeMaskToString](vscphlp_writemasktostring.md)



#### Python example

Using the official [Python helper binding](bindings.md#python):

```python
import vscp
import vscphelper

event_filter = vscp.vscpEventFilter()
value = "1,0,6,FF:FF:FF:FF:FF:FF:FF:F5:00:00:00:00:00:00:00:01"
result = vscphelper.readMaskFromString(event_filter, value)
if result != vscp.VSCP_ERROR_SUCCESS:
    raise RuntimeError("readMaskFromString failed (error {})".format(result))
print(event_filter.mask_type)
```

#### JavaScript availability

The official [Node.js binding](bindings.md#nodejs) does not currently expose this helper API, so there is no equivalent JavaScript example.

[filename](./bottom_copyright.md ':include')