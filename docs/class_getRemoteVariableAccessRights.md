

```clike
int getRemoteVariableAccessRights( const wxString& name, 
                                    uint16_t *pRights )
```

### Parameters

#### name
Name of remote variable to get information for.

#### pRights
Pointer to an uint16_t that will get the rights for the remote variable.

### Return Value
CANAL_ERROR_SUCCESS on success or an error code on failure. 

### Description
Get access rights for a remote variable. 




[filename](./bottom_copyright.md ':include')