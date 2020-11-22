

```clike
int vscphlp_getGuidFromString( vscpEvent *pEvent, 
                            const char *pGUID )
```
### Parameters

#### pEvent
VSCP event.

#### pGUID
Pointer to GUID in string form.

### Return Value
VSCP_ERROR_SUCCESS on success.

### Description
Write GUID into VSCP event from a string. 

#### C example
mmmm

```clike
char strguid[64], strguid2[64];
 
if ( VSCP_ERROR_SUCCESS == vscphlp_getGuidFromString( pEvent, strguid ) )  { 
    vscphlp_writeGuidToString( pEvent, strguid2, sizeof( strguid2 )-1 );
    printf( "GUID=%s\n", strguid2 );
}
else {
    printf( "\aError: vscphlp_writeGuidArrayToString\n");
}
```

### See Also
[vscphlp_getGuidFromString](vscphlp_getguidfromstring.md)



[filename](./bottom_copyright.md ':include')