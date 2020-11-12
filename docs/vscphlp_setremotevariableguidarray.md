


```clike
int vscphlp_getRemoteVariableGUIDArray( long handle, 
                                const char *pName, 
                                const char * pGUID ) 
```

### Parameters

#### handle
Handle for the communication channel obtained from a call to [vscphlp_newsession](vscphlp_newsession.md).

#### pName
Pointer to a string containing the name of the variable. This name should have a character a-z as its first character and is not case sensitive.

#### pGUID
Pointer to an array forming a 16-byte GUID.

### Return Value
Return VSCP_ERROR_SUCCESS on success, VSCP_ERROR_ERROR on failure. If the connection is closed VSCP_ERROR_CONNECTION is returned. VSCP_ERROR_PARAMETER is returned if called while in a receive loop. 

### Description
Get variable value from GUID variable. This is a variant where the GUID is stored in an array. 

#### C example

```clike
// Write a value to an GUID variable - array type
unsigned char GUID[16];
memset( GUID, 0, 16 );
for ( int i=0;i<16; i++ ) {
    GUID[i] = i;
}
 
if ( VSCP_ERROR_SUCCESS == 
         ( rv = vscphlp_setRemoteVariableGUIDArray( handle1, "test_guidarray_variable", GUID ) ) ) {
    printf( "Command success: vscphlp_setRemoteVariableGUIDArray on channel 1\n" );
}
else {
    printf("\aCommand error: vscphlp_setRemoteVariableGUIDArray on channel 1  Error code=%d\n", rv);
}
```

### See Also
[vscphlp_getRemoteVariableGUIDArray](vscphlp_getremotevariableguidarray.md)



[filename](./bottom_copyright.md ':include')