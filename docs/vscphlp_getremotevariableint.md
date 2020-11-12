

```clike
int vscphlp_getRemoteVariableInt( long handle, const 
                                    char *pName, 
                                    int *value ) 
```

### Parameters

#### handle
Handle for the communication channel obtained from a call to [vscphlp_newsession](vscphlp_newsession.md).

#### pName
Pointer to a string containing the name of the variable. This name should have a character a-z as its first character and is not case sensitive.

#### value
Pointer to integer variable that get the value of the string variable.

### Return Value
Return VSCP_ERROR_SUCCESS on success, VSCP_ERROR_ERROR on failure. If the connection is closed VSCP_ERROR_CONNECTION is returned. VSCP_ERROR_PARAMETER is returned if called while in a receive loop. 

### Description
 Get variable value from integer variable.

#### C example

```clike
// Read a value from a int variable
int intValue;
if ( VSCP_ERROR_SUCCESS == 
            (rv = vscphlp_getRemoteVariableInt( handle1, "test_integer_variable", &intValue ) ) ) {
    printf( "Command success: vscphlp_getRemoteVariableInt on channel 1\n" );
    printf(" Value = %d\n", intValue );
}
else {
    printf("\aCommand error: vscphlp_getRemoteVariableInt on channel 1  Error code=%d\n", rv);
}
```


### See Also
[vscphlp_setRemoteVariableInt](vscphlp_setremotevariableint.md)



[filename](./bottom_copyright.md ':include')