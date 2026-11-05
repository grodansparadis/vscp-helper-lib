

```clike
int doCmdReceive(vscpEvent *pEvent)
```

### Parameters

#### pEvent
Pointer to a VSCP event that will receive the event from the remote VSCP server queue on success.

### Return Value
`VSCP_ERROR_SUCCESS` (`0`) indicates success. Possible error codes: `VSCP_ERROR_CONNECTION`,
`VSCP_ERROR_PARAMETER`, `VSCP_ERROR_ERROR`, `VSCP_ERROR_MEMORY`, `VSCP_ERROR_READ`,
`VSCP_ERROR_INVALID_FRAME`, `VSCP_ERROR_TIMEOUT`, `VSCP_ERROR_STOPPED`.

In binary mode, a nonzero error code from a server confirmation can also be returned.

### Description
Receive one event if one is available.



#### C++ example

With an authenticated `VscpRemoteTcpIf client` (see [TLS connections](tls.md)) and `<iostream>` included:

```cpp
vscpEvent event = {};
int result = client.doCmdReceive(&event);
if (result != VSCP_ERROR_SUCCESS) {
    std::cerr << "doCmdReceive failed (error " << result << ")\n";
} else {
    std::cout << "Class: " << event.vscp_class << '\n';
}
delete[] event.pdata;
```

#### Python and JavaScript availability

The official bindings do not expose `VscpRemoteTcpIf` directly. Python and Node.js applications can use C helper wrappers where available; see [language bindings](bindings.md).

[filename](./bottom_copyright.md ':include')