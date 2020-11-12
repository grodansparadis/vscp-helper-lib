

```clike
int vscphlp_getGuidFromStringToArray( uint8_t *pGUID, 
                                    const char * pStr )
```

### Parameters

#### pGUID
Pointer to VSCP GUID array to fill.

#### pStr
Pointer to GUID in string form.


### Return Value
VSCP_ERROR_SUCCESS on success. 

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



[filename](./bottom_copyright.md ':include')
