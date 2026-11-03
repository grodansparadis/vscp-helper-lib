

```clike
int doCmdReceiveEx(vscpEventEx *pEventEx)
```

### Parameters

#### pEventEx
Pointer to a VSCP event ex that will receive the event from the remote VSCP server queue on success.

### Return Value
 * CANAL_ERROR_SUCCESS on success or an error code on failure. 
 * VSCP_ERROR_CONNECTION is returned if not connected to the server. 
 * VSCP_ERROR_PARAMETER is returned if the pointer to the event ex is NULL or if the interface is in the receive loop mode. 
 * VSCP_ERROR_ERROR is returned if the server returns an error. 
 * VSCP_ERROR_RCV_EMPTY if no event is available.
 * VSCP_ERROR_MEMORY if memory allocation fails. 
 * VSCP_ERROR_READ if the read operation to get event fails. 
 * VSCP_ERROR_CONVERSION if the conversion of the event fails.

### Description
Receive one event ex if one is available.



#### C++ example

With an authenticated `VscpRemoteTcpIf client` (see [TLS connections](tls.md)) and `<iostream>` included:

```cpp
vscpEventEx event = {};
int result = client.doCmdReceiveEx(&event);
if (result != VSCP_ERROR_SUCCESS) {
    std::cerr << "doCmdReceiveEx failed (error " << result << ")\n";
} else {
    std::cout << "Class: " << event.vscp_class << '\n';
}
```

#### Python and JavaScript availability

The official bindings do not expose `VscpRemoteTcpIf` directly. Python applications can use the separate C helper wrappers; the current Node.js binding does not expose these methods. See [language bindings](bindings.md).

[filename](./bottom_copyright.md ':include')