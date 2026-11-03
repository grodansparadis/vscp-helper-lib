

```clike
int vscphlp_writeGuidToString( const vscpEvent *pEvent, 
                                char *pStr, 
                                size_t len )
```

### Parameters

#### pEvent
VSCP event.

#### pStr
Pointer to a GUID in string form.

#### len
Size of the string buffer.


### Return Value
Returns VSCP_ERROR_SUCCESS on success.

### Description
Write GUID from VSCP event to string. 

#### C example


```clike
if ( VSCP_ERROR_SUCCESS == vscphlp_getGuidFromString( pEvent, strguid ) ) {
   vscphlp_writeGuidToString( pEvent, strguid2, sizeof( strguid2 )-1 );
   printf( "GUID=%s\n", strguid2 );
}
else {
    printf( "\aError: vscphlp_writeGuidArrayToString\n");
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
result, value = vscphelper.writeGuidToString(event)
if result != vscp.VSCP_ERROR_SUCCESS:
    raise RuntimeError("writeGuidToString failed (error {})".format(result))
print(value)
```

#### JavaScript availability

The official [Node.js binding](bindings.md#nodejs) does not currently expose this helper API, so there is no equivalent JavaScript example.

### See Also
[vscphlp_writeGuidToStringEx](vscphlp_writeguidtostringex.md)



[filename](./bottom_copyright.md ':include')