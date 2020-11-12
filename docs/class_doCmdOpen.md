


```clike
int doCmdOpen(const wxString& strInterface = (_("")), 
                uint32_t flags = 0L)
```

### Parameters

#### strInterface
Should be set to “username;password;ip-addr;port” if used. All values including port is optional and defaults to no username/password, server as “localhost” and port as “9598”

#### flags
Currently not used.

### Return Value
VSCP_ERROR_SUCCESS is returned if the connection to the remote VSCP server could be established. If not an error code will be returned. 

### Description
Open communication interface.

### See Also
[doCmdOpen](class_doCmdOpen2.md)



[filename](./bottom_copyright.md ':include')