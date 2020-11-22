

```clike
int vscphlp_deleteRemoteVariable( long handle, 
                                    const char *pName )
```

### Parameters

#### handle
Handle for the communication channel obtained from a call to [vscphlp_newsession](vscphlp_newsession.md).

#### pName
Pointer to a string containing the name of the variable. This name should have a character a-z as its first character and is not case sensitive.


### Return Value
Return VSCP_ERROR_SUCCESS on success, VSCP_ERROR_ERROR on failure. If the connection is closed VSCP_ERROR_CONNECTION is returned. VSCP_ERROR_PARAMETER is returned if called while in a receive loop. 

### Description
Delete a remote variable. 

#### C example

```clike
// Delete a variable
if ( VSCP_ERROR_SUCCESS == 
      ( rv = vscphlp_deleteRemoteVariable( handle1, 
                                       "test_of_create_variable" ) ) )  {
    printf( "Command success: vscphlp_deleteRemoteVariable on channel 1\n" );
}
else {
    printf("\aCommand error: vscphlp_deleteRemoteVariable on channel 1  Error code=%d\n", rv);
}
```



[filename](./bottom_copyright.md ':include')
