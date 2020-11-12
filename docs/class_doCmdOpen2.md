

```clike
int doCmdOpen(const wxString& strHostname,
                    const wxString& strUsername,
                    const wxString& strPassword)
```

### Parameters

#### strHostname
Host to connect to.

#### strUsername
Username for VSCP remote server account.

#### strPassword
Password for VSCP remote server account.

### Return Value
VSCP_ERROR_SUCCESS is returned if the connection to the remote VSCP server could be established. If not an error code will be returned. 

### Description
Open communication interface. 


### See Also
[doCmdOpen](class_doCmdOpen.md)



[filename](./bottom_copyright.md ':include')