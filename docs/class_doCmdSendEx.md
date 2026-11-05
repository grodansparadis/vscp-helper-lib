


```clike
int doCmdSendEx(const vscpEventEx *pEventEx)
```

### Parameters

#### pEventEx
Pointer to the VSCP Level II event ex to send. If its GUID is all zeros, the GUID of the remote VSCP server interface (“-”) is used.

### Return Value
`VSCP_ERROR_SUCCESS` (`0`) indicates success. Possible error codes: `VSCP_ERROR_CONNECTION`,
`VSCP_ERROR_PARAMETER`, `VSCP_ERROR_ERROR`, `VSCP_ERROR_TIMEOUT`, `VSCP_ERROR_STOPPED`,
`VSCP_ERROR_INVALID_FRAME`, `VSCP_ERROR_READ`.

### Description
Send a VSCP Level II event ex to the VSCP remote server.

*A vscpEvent structure contains a pointer to the event data, while each vscpEventEx allocates storage for the maximum amount of data and can therefore use considerably more memory.*




#### C++ example

With an authenticated `VscpRemoteTcpIf client` (see [TLS connections](tls.md)) and `<iostream>` included:

```cpp
vscpEventEx event = {};
event.vscp_class = 10;
event.vscp_type = 6;
event.sizeData = 3;
event.data[0] = 138;
event.data[1] = 0;
event.data[2] = 6;
int result = client.doCmdSendEx(&event);
if (result != VSCP_ERROR_SUCCESS) {
    std::cerr << "doCmdSendEx failed (error " << result << ")\n";
}
```

#### Python and JavaScript availability

The official bindings do not expose `VscpRemoteTcpIf` directly. Python and Node.js applications can use C helper wrappers where available; see [language bindings](bindings.md).

[filename](./bottom_copyright.md ':include')