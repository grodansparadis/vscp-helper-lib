

```clike
int fetchIterfaceGUID( const wxString& ifName, 
                        cguid& guid )
```

### Parameters

#### ifName
Real text name of the VSCP server interface.

#### guid
GUID for the interface if the named interface exist.

### Return Value
CANAL_ERROR_SUCCESS on success or an error code on failure. 

### Description
Fetch guid for a tcp/ip interface from it's name. 



[filename](./bottom_copyright.md ':include')