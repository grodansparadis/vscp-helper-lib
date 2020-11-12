

```clike
int vscphlp_setRemoteVariableDouble( long handle, 
                                    const char *pName, 
                                    double value ) 
```

### Parameters

#### handle
Handle for the communication channel obtained from a call to [vscphlp_newsession](vscphlp_newsession.md).

#### pName
Pointer to a string containing the name of the variable. This name should have a character a-z as its first character and is not case sensitive.

#### value
Pointer to double variable that get the value of the string variable.

### Return Value
Return VSCP_ERROR_SUCCESS on success, VSCP_ERROR_ERROR on failure. If the connection is closed VSCP_ERROR_CONNECTION is returned. VSCP_ERROR_PARAMETER is returned if called while in a receive loop. 

### Description
Set variable value from double variable. 

#### C example

```clike
// Write a value to an float variable
if ( VSCP_ERROR_SUCCESS == 
        ( rv = vscphlp_setRemoteVariableDouble( handle1, "test_float_variable", 1.2345001 )  ) ) {
    printf( "Command success: vscphlp_setRemoteVariableDouble on channel 1\n" );
}
else {
    printf("\aCommand error: vscphlp_setRemoteVariableDouble on channel 1  Error code=%d\n", rv);
}
```

### See Also
[vscphlp_getRemoteVariableDouble](vscphlp_getremotevariabledouble.md)



[filename](./bottom_copyright.md ':include')