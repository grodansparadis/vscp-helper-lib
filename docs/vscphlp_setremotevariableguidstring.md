


```clike
int vscphlp_getRemoteVariableGUID( long handle, 
                            const char *pName, 
                            const char * pGUID ) 
```

### Parameters

#### handle
Handle for the communication channel obtained from a call to [vscphlp_newsession](vscphlp_newsession.md).

#### pName
Pointer to a string containing the name of the variable. This name should have a character a-z as its first character and is not case sensitive.

#### pGUID
Pointer to a string that contains the GUID on the string form “FF:FF:FF:FF:FF:FF:FF:FF:FF:FF:FF:FF:FF:FF:FF:FF”

### Return Value
Return VSCP_ERROR_SUCCESS on success, VSCP_ERROR_ERROR on failure. If the connection is closed VSCP_ERROR_CONNECTION is returned. VSCP_ERROR_PARAMETER is returned if called while in a receive loop. 

### Description
Set the value for GUID variable. 

#### C example

```clike
// Write a value to an GUID variable - string type
char strGUID[64];
strcpy( strGUID, "FF:FF:FF:FF:FF:FF:FF:00:00:00:00:7F:00:01:01:FD" );
 
if ( VSCP_ERROR_SUCCESS == 
        ( rv = vscphlp_setRemoteVariableGUIDString( handle1, "test_guidstr_variable", strGUID ) ) ) {
    printf( "Command success: vscphlp_setRemoteVariableGUIDString on channel 1\n" );
}
else {
     printf("\aCommand error: vscphlp_setRemoteVariableGUIDString on channel 1  Error code=%d\n", rv);
}
```

### See Also
[vscphlp_getRemoteVariableGUIDString](vscphlp_getremotevariableguidstring.md)



[filename](./bottom_copyright.md ':include')