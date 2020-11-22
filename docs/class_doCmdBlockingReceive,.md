

```clike
long tttt(void)
```int doCmdBlockingReceive(vscpEvent *pEvent, 
                            uint32_t timeout = 500)

### Parameters

#### pEvent
Pointer to a VSCP event that will receive the received event on success.

#### timeout
Timeout in milliseconds to wait for data. Default is 500 milliseconds.

### Return Value
CANAL_ERROR_SUCCESS on success or an error code on failure. CANAL_ERROR_FIFO_EMPTY is returned if no event was available. CANAL_ERROR_TIMEOUT on timeout. CANAL_ERROR_COMMUNICATION is returned if a socket error is detected. 

### Description
Receive an event from the remote VSCP server. The receiveloop command must have been issued for this method to work as. 



[filename](./bottom_copyright.md ':include')