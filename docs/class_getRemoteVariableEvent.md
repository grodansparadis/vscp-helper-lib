

```clike
int getRemoteVariableEvent( const wxString& name, 
                            vscpEvent *pEvent)
```

### Parameters

#### name
Name of remote variable to set value for.

#### value
Pointer to VSCP event value that the remote variables will be set to.

### Return Value
CANAL_ERROR_SUCCESS on success or an error code on failure. 

### Description
Set variable value for VSCP event remote variable. 



[filename](./bottom_copyright.md ':include')