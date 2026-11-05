

```clike
int doCmdGetChannelID(uint32_t *pChannelID)
```

### Parameters

#### pChannelID
Pointer to a uint32 that will receive the channel ID.

### Return Value
`VSCP_ERROR_SUCCESS` (`0`) indicates success. Possible error codes: `VSCP_ERROR_CONNECTION`,
`VSCP_ERROR_PARAMETER`, `VSCP_ERROR_ERROR`.

### Description
Get Channel ID for the remote VSCP server interface channel. 



#### C++ example

With an authenticated `VscpRemoteTcpIf client` (see [TLS connections](tls.md)) and `<iostream>` included:

```cpp
uint32_t channel_id = 0;
int result = client.doCmdGetChannelID(&channel_id);
if (result != VSCP_ERROR_SUCCESS) {
    std::cerr << "doCmdGetChannelID failed (error " << result << ")\n";
} else {
    std::cout << "Channel ID: " << channel_id << '\n';
}
```

#### Python and JavaScript availability

The official bindings do not expose `VscpRemoteTcpIf` directly. Python and Node.js applications can use C helper wrappers where available; see [language bindings](bindings.md).

[filename](./bottom_copyright.md ':include')