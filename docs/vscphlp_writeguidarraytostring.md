


```clike
int vscphlp_writeGuidArrayToString( const unsigned char * pGUID, 
                                    char *strGUID,
                                    size_t len )
```

### Parameters

#### pGUID
A 16 byte GUID array.

#### strGUID
Pointer to buffer that can hold the GUID in string form.

#### len
Size of the string buffer.

### Return Value
`VSCP_ERROR_SUCCESS` (`0`) indicates success. Possible error codes: `VSCP_ERROR_ERROR`.

### Description
Write GUID from byte array to string. 

#### C example

```clike
if ( VSCP_ERROR_SUCCESS == vscphlp_writeGuidArrayToString( GUID2, strguid2, sizeof( strguid2 )-1 ) ) {
    printf( "GUID=%s\n", strguid2 );
}
else {
    printf( "Error: vscphlp_writeGuidArrayToString\n");
}
```




#### Python example

Using the official [Python helper binding](bindings.md#python):

```python
import vscp
import vscphelper

result, guid = vscphelper.getGuidFromStringToArray("FF:FF:FF:FF:FF:FF:FF:F5:00:00:00:00:00:00:00:01")
if result != vscp.VSCP_ERROR_SUCCESS:
    raise RuntimeError("getGuidFromStringToArray failed (error {})".format(result))
result, value = vscphelper.writeGuidArrayToString(guid)
if result != vscp.VSCP_ERROR_SUCCESS:
    raise RuntimeError("writeGuidArrayToString failed (error {})".format(result))
print(value)
```

#### JavaScript availability

The official [Node.js binding](bindings.md#nodejs) does not currently expose this helper API, so there is no equivalent JavaScript example.

[filename](./bottom_copyright.md ':include')