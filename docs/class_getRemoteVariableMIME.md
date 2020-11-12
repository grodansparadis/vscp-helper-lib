

```clike
int getRemoteVariableMIME( const wxString& name, 
                            wxString& mime )
```

### Parameters

#### name
Name of remote variable to set value for.

#### mime
Reference MIME data that get the value of the BASE64 encoded MIME variable.

### Return Value
CANAL_ERROR_SUCCESS on success or an error code on failure. 

### Description
Get remote variable value from a base64 ENCODED MIME variable.



[filename](./bottom_copyright.md ':include')