

```clike
int doCmdReceiveEx(vscpEventEx *pEventEx)
```

### Parameters

#### pEventEx
Pointer to VSCP event ex that will receive the event ex from the remote VSCP server queue if the call is successful.

### Return Value
CANAL_ERROR_SUCCESS on success or an error code on failure. 

### Description
Receive one event ex if one is available.



[filename](./bottom_copyright.md ':include')