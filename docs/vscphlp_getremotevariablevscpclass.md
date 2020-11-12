

```clike
int vscphlp_getRemoteVariableVSCPclass( long handle, 
                                    const char *pName, 
                                    uint16_t *vscp_class ) 
```

### Parameters

#### handle
Handle for the communication channel obtained from a call to [vscphlp_newsession](vscphlp_newsession.md).

#### pName
Pointer to a string containing the name of the variable. This name should have a character a-z as its first character and is not case sensitive.

#### vscp_class
Pointer to int that get the value of the class variable.

### Return Value
Return VSCP_ERROR_SUCCESS on success, VSCP_ERROR_ERROR on failure. If the connection is closed VSCP_ERROR_CONNECTION is returned. VSCP_ERROR_PARAMETER is returned if called while in a receive loop. 

### Description
Get variable value from class variable.

#### C example

```clike
unsigned short vscpclass;
 
// Read a value from aVSCP class type
if ( VSCP_ERROR_SUCCESS == 
        ( rv = vscphlp_getRemoteVariableVSCPClass( handle1, "test_vscp_class_variable", &vscpclass ) ) )  {
    printf( "Command success: vscphlp_getRemoteVariableVSCPClass on channel 1\n" );
    printf(" Value = %d\n", vscpclass );
}
else {
    printf("\aCommand error: vscphlp_getRemoteVariableVSCPClass on channel 1  Error code=%d\n", rv);
}
```

### See Also
[vscphlp_setRemoteVariableVSCPclass](vscphlp_setremotevariablevscpclass.md)



[filename](./bottom_copyright.md ':include')