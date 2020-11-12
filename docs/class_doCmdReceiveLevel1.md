

```clike
int doCmdReceiveLevel1(canalMsg *pCanalMsg)
```

### Parameters

#### pCanalMsg
Pointer to a CANAL message that will receive the vent from the remote VSCP server queue if the call is successful.


### Return Value
CANAL_ERROR_SUCCESS on success or an error code on failure. 

### Description
Receive an VSCP Level I event from the VSCP remote server queue. The low eight bits of the CAN id is fetched from GUID[15], that is from the LSB of the GUID. 



[filename](./bottom_copyright.md ':include')