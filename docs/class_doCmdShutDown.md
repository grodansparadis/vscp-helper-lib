

```clike
int doCmdShutDown(void)
```

### Parameters
None

### Return Value
`VSCP_ERROR_SUCCESS` (`0`) indicates success. Possible error codes: `VSCP_ERROR_CONNECTION`,
`VSCP_ERROR_ERROR`.

### Description
Shut down the remote VSCP server. This command requires elevated privileges on the server.




#### C++ example

With an authenticated `VscpRemoteTcpIf client` (see [TLS connections](tls.md)) and `<iostream>` included: This privileged command shuts down the server.

```cpp
int result = client.doCmdShutDown();
if (result != VSCP_ERROR_SUCCESS) {
    std::cerr << "doCmdShutDown failed (error " << result << ")\n";
}
```

#### Python and JavaScript availability

The official bindings do not expose `VscpRemoteTcpIf` directly. Python applications can use the separate C helper wrappers; the current Node.js binding does not expose these methods. See [language bindings](bindings.md).

[filename](./bottom_copyright.md ':include')
