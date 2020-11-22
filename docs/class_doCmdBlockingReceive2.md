

```clike
int doCmdBlockingReceive(vscpEventEx *pEventEx, 
                        uint32_t timeout = 500)
```

### Parameters

#### pEventEx
Pointer to a VSCP event ex that will receive the received event on success.

#### timeout
Timeout in milliseconds to wait for data. Default is 500 milliseconds.

### Return Value
CANAL_ERROR_SUCCESS on success or an error code on failure. CANAL_ERROR_FIFO_EMPTY is returned if no event was available. CANAL_ERROR_TIMEOUT on timeout. CANAL_ERROR_COMMUNICATION is returned if a socket error is detected. 

### Description
Receive an event ex from the remote VSCP server. The receiveloop command must have been issued for this method to work as. 



[filename](./bottom_copyright.md ':include')