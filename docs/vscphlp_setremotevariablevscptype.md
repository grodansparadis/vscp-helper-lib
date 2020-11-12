

```clike
int vscphlp_setRemoteVariableVSCPtype( long handle, 
                            const char *pName, 
                            unsigned short vscp_type ) 
```

### Parameters

#### handle
Handle for the communication channel obtained from a call to [vscphlp_newsession](vscphlp_newsession.md).

#### pName
Pointer to a string containing the name of the variable. This name should have a character a-z as its first character and is not case sensitive.

#### vscp_type
Pointer to int that get the value of the type variable.

### Return Value
Return VSCP_ERROR_SUCCESS on success, VSCP_ERROR_ERROR on failure. If the connection is closed VSCP_ERROR_CONNECTION is returned. VSCP_ERROR_PARAMETER is returned if called while in a receive loop. 

### Description
Set variable value from type variable.

#### C example

```clike
// Write a value for VSCP type type
if ( VSCP_ERROR_SUCCESS == 
      ( rv = vscphlp_setRemoteVariableVSCPType( handle1, "test_vscp_type_variable", 22 ) ) ) {
    printf( "Command success: vscphlp_setRemoteVariableVSCPType on channel 1\n" );
}
else {
    printf("\aCommand error: vscphlp_setRemoteVariableVSCPType on channel 1  Error code=%d\n", rv);
}
```

### See Also
[vscphlp_getRemoteVariableVSCPtype](vscphlp_getremotevariablevscptype.md)



[filename](./bottom_copyright.md ':include')
