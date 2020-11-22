

```clike
int vscphlp_setRemoteVariableBool( long handle, const 
                                    char *pName, 
                                    bool bValue ) 
```

### Parameters

#### handle
Handle for the communication channel obtained from a call to [vscphlp_newsession](vscphlp_newsession.md).

#### pName
Pointer to a string containing the name of the variable. This name should have a character a-z as its first character and is not case sensitive.

#### bValue
Pointer to boolean variable that get the value of the string variable.

### Return Value
Return VSCP_ERROR_SUCCESS on success, VSCP_ERROR_ERROR on failure. If the connection is closed VSCP_ERROR_CONNECTION is returned. VSCP_ERROR_PARAMETER is returned if called while in a receive loop. 

### Description
Get variable value from boolean variable 

#### C example

```clike
// Write a value (false) to a boolean variable
if ( VSCP_ERROR_SUCCESS == 
        ( rv = vscphlp_setRemoteVariableBool( handle1, "test_bool_variable", 0 )  ) ) {
    printf( "Command success: vscphlp_setRemoteVariableBool on channel 1\n" );
}
else {
    printf("\aCommand error: vscphlp_setRemoteVariableBool on channel 1  Error code=%d\n", rv);
}
```

### See Also
[vscphlp_setRemoteVariableString](vscphlp_setremotevariablestring.md)



[filename](./bottom_copyright.md ':include')