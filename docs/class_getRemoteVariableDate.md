

```clike
int getRemoteVariableDate( const wxString& name, 
                            wxDateTime& date )
```

### Parameters

#### name
Name of remote variable to set value for.

#### date
Pointer to date wxDateTime class that get the value of the VSCP date variable.

### Return Value
CANAL_ERROR_SUCCESS on success or an error code on failure. 

### Description
Get remote variable value from VSCP date variable. 



[filename](./bottom_copyright.md ':include')