


```clike
int getRemoteVariableVSCPdata( const wxString& name, 
                                uint8_t *psizeData, 
                                uint16_t *pData)
```

### Parameters

#### name
Name of remote variable to set value for.

#### psizeData
Pointer to unsigned char that will get the size of the data array.

#### pData
Pointer to VSCP data array variable (unsigned char [487] ) that get the value of the remote variable.

### Return Value
CANAL_ERROR_SUCCESS on success or an error code on failure. 

### Description
Get remote variable value from VSCP data variable. 



[filename](./bottom_copyright.md ':include')