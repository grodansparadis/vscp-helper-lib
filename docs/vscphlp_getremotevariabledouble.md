

```clike
int vscphlp_getRemoteVariableDouble( long handle, const 
                                    char *pName, 
                                    double *value ) 
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
Get variable value from double variable.

#### C example

```clike
// Read a value from a float variable
double floatValue;
if ( VSCP_ERROR_SUCCESS == 
        ( rv = vscphlp_getRemoteVariableDouble( handle1, "test_float_variable", &floatValue ) ) ) {
    printf( "Command success: vscphlp_getRemoteVariableDouble on channel 1\n" );
    printf(" Value = %f\n", floatValue );
}
else {
    printf("\aCommand error: vscphlp_getRemoteVariableDouble on channel 1  Error code=%d\n", rv);
}
```

### See Also
[vscphlp_setRemoteVariableDouble](vscphlp_setremotevariabledouble.md)



[filename](./bottom_copyright.md ':include')