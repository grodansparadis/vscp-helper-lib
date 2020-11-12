

```clike
int doCmdEnterReceiveLoop(void)
```

### Parameters
None.

### Return Value
CANAL_ERROR_SUCCESS on success or an error code on failure. 

### Description
This command sets an open interface in the receive loop (RCVLOOP) state. It does nothing other then putting the interface in the loop mode and checking that it went there.

**Note!** The only way to terminate this receive loop is to close the session with doCmdClose (or just close the socket) or send the doQuitLoop command [doCmdQuitReceiveLoop](class_doCmdQuitReceiveLoop.md). 

### See Also
[doCmdQuitReceiveLoop](class_doCmdQuitReceiveLoop.md)



[filename](./bottom_copyright.md ':include')