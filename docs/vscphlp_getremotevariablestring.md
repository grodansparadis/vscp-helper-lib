

```clike
int vscphlp_getRemoteVariableString( const char *pName, 
                                    char *pValue, 
                                    size_t len ) 
```

### Parameters

#### handle
Handle for the communication channel obtained from a call to [vscphlp_newsession](vscphlp_newsession.md).

#### pName
Pointer to a string containing the name of the variable. This name should have a character a-z as its first character and is not case sensitive.

#### pValue
Pointer to string that gets the value of the string variable.

#### len
Size of supplied buffer that will receive the value.


### Return Value
Return VSCP_ERROR_SUCCESS on success, VSCP_ERROR_ERROR on failure. If the connection is closed VSCP_ERROR_CONNECTION is returned. VSCP_ERROR_PARAMETER is returned if called while in a receive loop. 

### Description
Get value of string variable. 

#### C example

```clike
// Read a value from a string variable
char strBuf[32];
 
if ( VSCP_ERROR_SUCCESS == 
        ( rv = vscphlp_getRemoteVariableString( handle1, "test_string_variable", strBuf, sizeof( strBuf )-1 ) ) ) {
    printf( "Command success: vscphlp_getRemoteVariableString on channel 1\n" );
    printf(" Value = %s\n", strBuf );
}
else {
    printf("\aCommand error: vscphlp_getRemoteVariableString on channel 1  Error code=%d\n", rv);
}
```

#### See Also
[vscphlp_setRemoteVariableString](vscphlp_setremotevariablestring.md)



[filename](./bottom_copyright.md ':include')