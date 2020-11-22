


```clike
int doCmdSendEx(const vscpEventEx *pEventEx)
```

### Parameters

#### pEventEx
Pointer to VSCP Level II event ex to send. If the event have a GUID all set to zero the GUID of the VSCP remote server interface (“-”) will be used.

### Return Value
CANAL_ERROR_SUCCESS on success or an error code on failure. 

### Description
Send a VSCP Level II event ex to the VSCP remote server.

*A vscpEvent structure contains a pointer to the data part of the event, while the vscpEventEx have the max data storage allocated in every event and therefore waste a lot of memory that can be used in a better way.*




[filename](./bottom_copyright.md ':include')