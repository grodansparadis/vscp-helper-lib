

```clike
int vscphlp_getGuidFromStringToArray( uint8_t *pGUID, 
                                    const char * pStr )
```

### Parameters

#### pGUID
Pointer to VSCP GUID array to fill.

#### pStr
Pointer to a GUID in string form.


### Return Value
`VSCP_ERROR_SUCCESS` (`0`) indicates success. Possible error codes: `VSCP_ERROR_ERROR`.

### Description
Write GUID from string into array. 

#### C example

```clike
if ( VSCP_ERROR_SUCCESS == vscphlp_getGuidFromStringToArray( GUID2, strguid ) ) {
    vscphlp_writeGuidArrayToString( GUID2, strguid2, sizeof( strguid2 )-1 );
    printf( "GUID  after reverse = %s\n", strguid2 );
}
else {
    printf( "\aError: vscphlp_getGuidFromStringToArray\n");
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
print(list(guid))
```

#### JavaScript availability

See the [Node.js binding](bindings.md#nodejs) for C API access and native library availability.

[filename](./bottom_copyright.md ':include')
