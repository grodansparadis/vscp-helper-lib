

```clike
int getRemoteVariableDateTime( const wxString& name, 
                                wxDateTime& datetime )
```

### Parameters

#### name
Name of remote variable to set value for.

#### datetime
Pointer to date wxDateTime class that get the value of the VSCP datetime variable.

### Return Value
CANAL_ERROR_SUCCESS on success or an error code on failure. 

### Description
Get remote variable value from VSCP datetime variable. 



[filename](./bottom_copyright.md ':include')