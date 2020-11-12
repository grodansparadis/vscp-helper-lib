

```clike
int doCmdSend(const vscpEvent *pEvent)
```

### Parameters

#### pEvent
Pointer to VSCP Level II event to send. If the event have a GUID all set to zero the GUID of the VSCP remote server interface (“-”) will be used.

### Return Value
CANAL_ERROR_SUCCESS on success or an error code on failure. 

### Description
Send a VSCP Level II event to the VSCP remote server. 



[filename](./bottom_copyright.md ':include')