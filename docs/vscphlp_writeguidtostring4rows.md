

```clike
int vscphlp_writeGuidToString4Rows( const vscpEvent *pEvent, 
                                      char *strGUID,
                                      size_t len )
```

### Parameters

#### pEvent
VSCP event.

#### strGUID
String that receives the formatted GUID.

#### len
Size of the string buffer.

### Return Value
Returns VSCP_ERROR_SUCCESS on success.

### Description
Write GUID from VSCP event to string with four bytes on each row separated by “\r\n”. 

#### C example

```clike
if ( VSCP_ERROR_SUCCESS == vscphlp_writeGuidToString4Rows( pEvent, strguid2, sizeof( strguid2 )-1 ) ) {
    printf( "GUID\n%s\n", strguid2 );
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

event = vscp.vscpEvent()
result = vscphelper.getGuidFromString(event, "FF:FF:FF:FF:FF:FF:FF:F5:00:00:00:00:00:00:00:01")
if result != vscp.VSCP_ERROR_SUCCESS:
    raise RuntimeError("getGuidFromString failed (error {})".format(result))
result, value = vscphelper.writeGuidToString4Rows(event)
if result != vscp.VSCP_ERROR_SUCCESS:
    raise RuntimeError("writeGuidToString4Rows failed (error {})".format(result))
print(value)
```

#### JavaScript availability

The official [Node.js binding](bindings.md#nodejs) does not currently expose this helper API, so there is no equivalent JavaScript example.

### See Also
[vscphlp_writeGuidToString4RowsEx](vscphlp_writeguidtostring4rowsex.md)



[filename](./bottom_copyright.md ':include')