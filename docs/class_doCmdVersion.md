

```clike
int doCmdVersion(uint8_t *pMajorVer,
                     uint8_t *pMinorVer,
                     uint8_t *pSubMinorVer)
```

### Parameters

#### pMajorVer
Major version of VSCP remote server interface.

#### pMinorVer
Minor version of VSCP remote server interface.

#### pSubMinorVer
Sub version of VSCP remote server interface.

### Return Value
CANAL_ERROR_SUCCESS on success or an error code on failure. 

### Description
Get the interface version from the remote VSCP server. 



[filename](./bottom_copyright.md ':include')