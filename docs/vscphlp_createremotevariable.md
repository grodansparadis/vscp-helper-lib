

```clike
int vscphlp_createRemoteVariable( long handle, 
                                    const char *pName,
                                    const char* pType,
                                    const char* pValue,
                                    int bPersistent )
```

### Parameters

#### handle
Handle for the communication channel obtained from a call to [vscphlp_newsession](vscphlp_newsession.md).

#### pName
Pointer to a string containing the name of the variable. This name should have a character a-z as its first character and is not case sensitive.

#### pType
Pointer to the type of the variable either as its symbolic name “string”, “long” etc or to it's numerical code “1”, “6”. Note that the numerical types are also in string form. The different variable types is described here.

#### pValue
Pointer to string that contains the value of the string variable.


#### bPersistent
If non zero the variable will be set to be persistent. This means that is will be saved to disk and will be available also in the future as long as it is not deleted.


### Return Value
Return VSCP_ERROR_SUCCESS on success, VSCP_ERROR_ERROR on failure. If the connection is closed VSCP_ERROR_CONNECTION is returned. VSCP_ERROR_PARAMETER is returned if called while in a receive loop. 

### Description
Create a variable of a specific type. All the write methods below also create a variable if it does not exist but this method also allows to set the persistence. 

#### C example

```clike
// Create a variable
char strBuf[32];
if ( VSCP_ERROR_SUCCESS == 
       (rv = vscphlp_createRemoteVariable( handle1, 
                                      "test_of_create_variable",
                                      "string",
                                      "Carpe Diem",
                                      1 ) ) )  {
    printf( "Command success: vscphlp_createRemoteVariable on channel 1\n" );
}
else {
    printf("\aCommand error: vscphlp_createRemoteVariable on channel 1  Error code=%d\n", rv);
}
 
if ( VSCP_ERROR_SUCCESS == 
        ( rv = vscphlp_getRemoteVariableString( handle1, 
                                             "test_of_create_variable", 
                                             strBuf, 
                                             sizeof( strBuf )-1 ) ) ) {
    printf( "Command success: vscphlp_getRemoteVariableString on channel 1\n" );
    printf(" Value = %s\n", strBuf );
}
else {
    printf("\aCommand error: vscphlp_getRemoteVariableString on channel 1  Error code=%d\n", rv);
}
```



[filename](./bottom_copyright.md ':include')