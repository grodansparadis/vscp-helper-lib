

```clike
int doCmdReceiveEx(vscpEventEx *pEventEx)
```

### Parameters

#### pEventEx
Pointer to a VSCP event ex that will receive the event from the remote VSCP server queue on success.

### Return Value
`VSCP_ERROR_SUCCESS` (`0`) indicates success. Possible error codes: `VSCP_ERROR_CONNECTION`,
`VSCP_ERROR_PARAMETER`, `VSCP_ERROR_ERROR`, `VSCP_ERROR_MEMORY`, `VSCP_ERROR_READ`,
`VSCP_ERROR_INVALID_FRAME`, `VSCP_ERROR_TIMEOUT`, `VSCP_ERROR_STOPPED`,
`VSCP_ERROR_RCV_EMPTY`, `VSCP_ERROR_INVALID_FORMAT`.

In binary mode, a nonzero error code from a server confirmation can also be returned.

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