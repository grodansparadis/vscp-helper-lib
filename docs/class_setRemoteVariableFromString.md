



```clike
int setRemoteVariableFromString( const wxString& name, 
                        const wxString& strValue,
                        const bool bPersistent = false,
                        const uint32_t rights = 0x744 )
```

### Parameters

#### name
Name of remote variable to get information for.

#### strValue
Reference to string with value to set the remote variable to on string form.

#### bPersistent
True if the variable should be persistent.

#### rights
Access rights for the variable.

### Return Value
CANAL_ERROR_SUCCESS on success or an error code on failure.

### Description
Set a remote variable value from its string form. 



[filename](./bottom_copyright.md ':include')