

```clike
int doCmdBlockingReceive(vscpEventEx *pEventEx, 
                        uint32_t timeout = 500)
```

### Parameters

#### pEventEx
Pointer to a VSCP event ex that will receive the event on success.

#### timeout
Time to wait for data, in milliseconds. The default is 500 milliseconds.

### Return Value
Returns CANAL_ERROR_SUCCESS on success or an error code on failure. CANAL_ERROR_FIFO_EMPTY indicates that no event was available, CANAL_ERROR_TIMEOUT indicates a timeout, and CANAL_ERROR_COMMUNICATION indicates a socket error.

### Description
Receive an event ex from the remote VSCP server. The receiveloop command must be issued before calling this method.



#### C++ example

With `client` already in a receive loop (see [doCmdEnterReceiveLoop](class_doCmdEnterReceiveLoop.md)) and `<iostream>` included:

```cpp
vscpEventEx event = {};
int result = client.doCmdBlockingReceive(&event, 1000);
if (result != VSCP_ERROR_SUCCESS) {
    std::cerr << "doCmdBlockingReceive failed (error " << result << ")\n";
} else {
    std::cout << "Class: " << event.vscp_class << '\n';
}
```

#### Python and JavaScript availability

The official bindings do not expose `VscpRemoteTcpIf` directly. Python applications can use the separate C helper wrappers; the current Node.js binding does not expose these methods. See [language bindings](bindings.md).

[filename](./bottom_copyright.md ':include')