

```clike
int doCmdGetChannelInfo(VSCPChannelInfo *pChannelInfo)
```

### Parameters

#### pChannelInfo
Pointer to the channel information structure that will receive the result.

### Return Value
Returns CANAL_ERROR_SUCCESS on success or an error code on failure.

### Description
Get information about the remote VSCP server interface channel. 



#### C++ example

With an authenticated `VscpRemoteTcpIf client` (see [TLS connections](tls.md)) and `<iostream>` included:

```cpp
vscp_channel_info_t info = {};
int result = client.doCmdGetChannelInfo(&info);
if (result != VSCP_ERROR_SUCCESS) {
    std::cerr << "doCmdGetChannelInfo failed (error " << result << ")\n";
} else {
    std::cout << "Channel: " << info.channel << '\n';
}
```

#### Python and JavaScript availability

The official bindings do not expose `VscpRemoteTcpIf` directly. Python applications can use the separate C helper wrappers; the current Node.js binding does not expose these methods. See [language bindings](bindings.md).

[filename](./bottom_copyright.md ':include')