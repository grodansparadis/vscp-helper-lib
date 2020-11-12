

```clike
int doCmdSendLevel1(const canalMsg *pMsg)
```

### Parameters

#### pMsg
A pointer to a CANAL message.

### Return Value
CANAL_ERROR_SUCCESS on success or an error code on failure. 

### Description
Send a Level I event to the VSCP remote server. The GUID of the interface will be used for the resulting VSCP event. 



[filename](./bottom_copyright.md ':include')