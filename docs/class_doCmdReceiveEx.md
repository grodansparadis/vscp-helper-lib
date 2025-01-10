

```clike
int doCmdReceiveEx(vscpEventEx *pEventEx)
```

### Parameters

#### pEventEx
Pointer to VSCP event ex that will receive the event ex from the remote VSCP server queue if the call is successful.

### Return Value
 * CANAL_ERROR_SUCCESS on success or an error code on failure. 
 * VSCP_ERROR_CONNECTION is returned if not connected to the server. 
 * VSCP_ERROR_PARAMETER is returned if the pointer to the event ex is NULL or if the interface is in the receive loop mode. 
 * VSCP_ERROR_ERROR is returned if the server returns an error. 
 * VSCP_ERROR_RCV_EMPTY if no event is available.
 * VSCP_ERROR_MEMORY if memory allocation fails. 
 * VSCP_ERROR_READ if the read operation to get event fails. * VSCP_ERROR_CONVERSION if the conversion of the event fails.

### Description
Receive one event ex if one is available.



[filename](./bottom_copyright.md ':include')