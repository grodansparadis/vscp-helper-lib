

```clike
int getRemoteVariableEventEx( const wxString& name, 
                                vscpEventEx *pEventEx)
```

### Parameters

#### name
Name of remote variable to set value for.

#### pEventEx
Pointer to VSCP event ex value that the remote variables will be set to.

### Return Value
CANAL_ERROR_SUCCESS on success or an error code on failure.

### Description
Set variable value for VSCP event ex remote variable. 



[filename](./bottom_copyright.md ':include')