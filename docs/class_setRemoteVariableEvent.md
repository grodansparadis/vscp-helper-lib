



```clike
int setRemoteVariableEvent( const wxString& name, 
                            vscpEvent *pEvent)
```

### Parameters

#### name
Name of remote variable to set value for.

#### value
Pointer to VSCP event value that will be set to the remote variables value.

### Return Value
CANAL_ERROR_SUCCESS on success or an error code on failure.

### Description
Set remote variable value for VSCP event variable. 



[filename](./bottom_copyright.md ':include')