

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
Get variable value from GUID variable. Array type.

#### C example

```clike
// Read a value from a GUID variable - array type
if ( VSCP_ERROR_SUCCESS == 
      ( rv = vscphlp_getRemoteVariableGUIDArray( handle1, "test_guidarray_variable", GUID  ) ) )  {
    printf( "Command success: vscphlp_getRemoteVariableGUIDArray on channel 1\n" );
    printf(" Value = " );
    for ( int i=0; i<16; i++ ) {
        printf("%d ", GUID[i] );    
    }
    printf("\n");
}
else {
    printf("\aCommand error: vscphlp_getRemoteVariableGUIDArray on channel 1  Error code=%d\n", rv);
}
```


### See Also
[vscphlp_setRemoteVariableGUIDArray](vscphlp_setremotevariableguidarray.md)



[filename](./bottom_copyright.md ':include')