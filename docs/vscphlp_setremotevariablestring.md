

```clike
int vscphlp_setRemoteVariableString( long handle, 
                                    const char *pName, 
                                    char *pValue ) 
```

### Parameters

#### handle
Handle for the communication channel obtained from a call to [vscphlp_newsession](vscphlp_newsession.md).

#### pName
Pointer to a string containing the name of the variable. This name should have a character a-z as its first character and is not case sensitive.

#### pValue
Pointer to string that contains the value to be written to the string.

### Return Value
Return VSCP_ERROR_SUCCESS on success, VSCP_ERROR_ERROR on failure. If the connection is closed VSCP_ERROR_CONNECTION is returned. VSCP_ERROR_PARAMETER is returned if called while in a receive loop. 

### Description
Write a value to a string variable. If the variable does not exist it will be created.

#### C example

```clike
// Write a value to a string variable
if ( VSCP_ERROR_SUCCESS == 
        (rv = vscphlp_setRemoteVariableString( handle1, 
                            "test_sting_variable", 
                            "this is the value of the string variable" )  ) ) {
    printf( "Command success: vscphlp_setRemoteVariableString on channel 1\n" );
}
else {
    printf("Command error: vscphlp_setRemoteVariableString on channel 1  Error code=%d\n", rv);
}
```
## See Also
[vscphlp_getRemoteVariableString](vscphlp_getremotevariablestring.md)



[filename](./bottom_copyright.md ':include')