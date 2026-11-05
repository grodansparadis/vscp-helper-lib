

```clike
int doCmdStatus(canalStatus *pStatus)
```

### Parameters

#### pStatus
Pointer to a canalStatus structure that will receive the remote VSCP server status.


### Return Value
`VSCP_ERROR_SUCCESS` (`0`) indicates success. Possible error codes: `VSCP_ERROR_CONNECTION`,
`VSCP_ERROR_PARAMETER`, `VSCP_ERROR_ERROR`, `VSCP_ERROR_GENERIC`.
The status pointer must be valid; it is not checked for null. The output
may be partially modified even when an error is returned; use it only on success.

### Description
Receive the CANAL status structure from the remote VSCP server. 



#### C++ example

With an authenticated `VscpRemoteTcpIf client` (see [TLS connections](tls.md)) and `<iostream>` included:

```cpp
canal_status_t status = {};
int result = client.doCmdStatus(&status);
if (result != VSCP_ERROR_SUCCESS) {
    std::cerr << "doCmdStatus failed (error " << result << ")\n";
} else {
    std::cout << "Last error: " << status.lasterrorcode << '\n';
}
```

#### Python and JavaScript availability

The official bindings do not expose `VscpRemoteTcpIf` directly. Python applications can use the separate C helper wrappers; the current Node.js binding does not expose these methods. See [language bindings](bindings.md).

[filename](./bottom_copyright.md ':include')