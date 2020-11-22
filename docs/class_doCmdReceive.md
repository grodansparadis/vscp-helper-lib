

```clike
int doCmdReceive(vscpEvent *pEvent)
```

### Parameters

#### pEvent
Pointer to VSCP event that will receive the event from the remote VSCP server queue if the call is successful.

### Return Value
CANAL_ERROR_SUCCESS on success or an error code on failure. 

### Description
Receive one event if one is available.



[filename](./bottom_copyright.md ':include')