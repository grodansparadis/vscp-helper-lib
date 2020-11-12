

```clike
int vscphlp_getRemoteVariableGUIDString( long handle,    
                                    const char *pName, 
                                    const char *pGUID, 
                                    size_t len ) 
```

### Parameters

#### handle
Handle for the communication channel obtained from a call to [vscphlp_newsession](vscphlp_newsession.md).

#### pName
Pointer to a string containing the name of the variable. This name should have a character a-z as its first character and is not case sensitive.

#### pGUID
Pointer to event variable that get the value of the GUID variable.

#### len
Size of buffer for GUID.

### Return Value
Return VSCP_ERROR_SUCCESS on success, VSCP_ERROR_ERROR on failure. If the connection is closed VSCP_ERROR_CONNECTION is returned. VSCP_ERROR_PARAMETER is returned if called while in a receive loop. 

### Description
Get variable value from GUID variable.

#### C example

```clike
// Read a value from a GUID variable - string type
if ( VSCP_ERROR_SUCCESS == 
         ( rv = vscphlp_getRemoteVariableGUIDString( handle1, "test_guidstr_variable", strGUID, sizeof(strGUID)-1 )  ) )  {
    printf( "Command success: vscphlp_getRemoteVariableGUIDString on channel 1\n" );
    printf(" Value = %s\n", strGUID );
}
else {
    printf("\aCommand error: vscphlp_getRemoteVariableGUIDString on channel 1  Error code=%d\n", rv);
}
```


### See Also
[vscphlp_setRemoteVariableGUIDString](vscphlp_setremotevariableguidstring.md)



[filename](./bottom_copyright.md ':include')