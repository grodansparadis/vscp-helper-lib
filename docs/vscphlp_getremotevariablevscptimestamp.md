

```clike
int vscphlp_getRemoteVariableVSCPTimestamp( long handle, 
                        const char *pName, 
                        unsigned long *vscp_timestamp )
```

### Parameters

#### handle
Handle for the communication channel obtained from a call to [vscphlp_newsession](vscphlp_newsession.md).

#### pName
Pointer to a string containing the name of the variable. This name should have a character a-z as its first character and is not case sensitive.

#### vscp_timestamp
Pointer to string that will get the value of the VSCP timestamp variable.

### Return Value
Return VSCP_ERROR_SUCCESS on success, VSCP_ERROR_ERROR on failure. If the connection is closed VSCP_ERROR_CONNECTION is returned. VSCP_ERROR_PARAMETER is returned if called while in a receive loop. 

### Description
Get variable value from VSCP timestamp variable.

#### C example

```clike
TODO
```

### See Also
[vscphlp_setRemoteVariableVSCPTimestamp](vscphlp_setremotevariablevscptimestamp.md)



[filename](./bottom_copyright.md ':include')