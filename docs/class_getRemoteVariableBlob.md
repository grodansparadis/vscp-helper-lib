

```clike
int getRemoteVariableBlob( const wxString& name, 
                            wxString& blob )
```

### Parameters

#### name
Name of remote variable to set value for.

#### blob
Reference to blob that get the value of the BASE64 encoded blob variable.

### Return Value
CANAL_ERROR_SUCCESS on success or an error code on failure. 

### Description
Get remote variable value from a base64 ENCODED blob variable. 



[filename](./bottom_copyright.md ':include')