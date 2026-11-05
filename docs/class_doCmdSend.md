

```clike
int doCmdSend(const vscpEvent *pEvent)
```

### Parameters

#### pEvent
Pointer to the VSCP Level II event to send. If its GUID is all zeros, the GUID of the remote VSCP server interface (“-”) is used.

### Return Value
`VSCP_ERROR_SUCCESS` (`0`) indicates success. Possible error codes: `VSCP_ERROR_CONNECTION`,
`VSCP_ERROR_PARAMETER`, `VSCP_ERROR_ERROR`, `VSCP_ERROR_TIMEOUT`, `VSCP_ERROR_STOPPED`,
`VSCP_ERROR_INVALID_FRAME`, `VSCP_ERROR_READ`.

### Description
Send a VSCP Level II event to the VSCP remote server. 



#### C++ example

With an authenticated `VscpRemoteTcpIf client` (see [TLS connections](tls.md)) and `<iostream>` included:

```cpp
vscpEvent event = {};
unsigned char data[] = {138, 0, 6};
event.vscp_class = 10;
event.vscp_type = 6;
event.sizeData = sizeof(data);
event.pdata = data;
int result = client.doCmdSend(&event);
if (result != VSCP_ERROR_SUCCESS) {
    std::cerr << "doCmdSend failed (error " << result << ")\n";
}
```

#### Python and JavaScript availability

The official bindings do not expose `VscpRemoteTcpIf` directly. Python applications can use the separate C helper wrappers; the current Node.js binding does not expose these methods. See [language bindings](bindings.md).

[filename](./bottom_copyright.md ':include')