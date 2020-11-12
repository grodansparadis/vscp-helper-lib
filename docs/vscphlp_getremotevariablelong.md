

```clike
int vscphlp_getRemoteVariableLong( long handle, const 
                                    char *pName, 
                                    long *value ) 
```

### Parameters

#### handle
Handle for the communication channel obtained from a call to [vscphlp_newsession](vscphlp_newsession.md).

#### pName
Pointer to a string containing the name of the variable. This name should have a character a-z as its first character and is not case sensitive.

#### value
Pointer to long variable that get the value of the string variable.

### Return Value
Return VSCP_ERROR_SUCCESS on success, VSCP_ERROR_ERROR on failure. If the connection is closed VSCP_ERROR_CONNECTION is returned. VSCP_ERROR_PARAMETER is returned if called while in a receive loop. 

### Description
Get variable value from long variable.

#### C example

```clike
// Read a value from a long variable
long longValue;
if ( VSCP_ERROR_SUCCESS == 
         ( rv = vscphlp_getRemoteVariableLong( handle1, "test_long_variable", &longValue ) ) ) {
    printf( "Command success: vscphlp_getRemoteVariableLong on channel 1\n" );
    printf(" Value = %lu\n", longValue );
}
else {
    printf("\aCommand error: vscphlp_getRemoteVariableLong on channel 1  Error code=%d\n", rv);
}
```

### See Also
[vscphlp_setRemoteVariableLong](vscphlp_setremotevariablelong.md)



[filename](./bottom_copyright.md ':include')