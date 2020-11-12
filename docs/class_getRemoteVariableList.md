

```clike
int getRemoteVariableList( wxArrayString& arrayVars, 
                        const wxString regexp = _(""),
                        const int type = 0 )
```

### Parameters

#### arrayVars
A reference to a string array that Will be filed with names of VSCP remote variables.

#### regexp
Regular expression used to select variables. Leave blank to return all variables.

#### type
Variable type that should be listed or 0 for all variable types.

### Return Value
CANAL_ERROR_SUCCESS on success or an error code on failure. 

### Description
Get a list of defined variables on remote VSCP server. 



[filename](./bottom_copyright.md ':include')