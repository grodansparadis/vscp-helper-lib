

```clike
int vscphlp_getRemoteVariableVSCPtype( long handle, 
                            const char *pName, 
                            unsigned short *vscp_type ) 
```

### Parameters

#### handle
Handle for the communication channel obtained from a call to [vscphlp_newsession](vscphlp_newsession.md).

#### pName
Pointer to a string containing the name of the variable. This name should have a character a-z as its first character and is not case sensitive.

#### vscp_type
Pointer to int that get the value of the type variable.

### Return Value
rReturn VSCP_ERROR_SUCCESS on success, VSCP_ERROR_ERROR on failure. If the connection is closed VSCP_ERROR_CONNECTION is returned. VSCP_ERROR_PARAMETER is returned if called while in a receive loop. rr

### Description
Get variable value from type variable.

#### C example

```clike
unsigned short vscptype;
 
// Read a value from aVSCP type type
if ( VSCP_ERROR_SUCCESS == 
        ( rv = vscphlp_getRemoteVariableVSCPType( handle1, "test_vscp_type_variable", &vscptype ) ) )  {
    printf( "Command success: vscphlp_getRemoteVariableVSCPType on channel 1\n" );
    printf(" Value = %d\n", vscptype );
}
else {
    printf("\aCommand error: vscphlp_getRemoteVariableVSCPType on channel 1  Error code=%d\n", rv);
}
```

### See Also
[vscphlp_setRemoteVariableVSCPtype](vscphlp_setremotevariablevscptype.md)



[filename](./bottom_copyright.md ':include')