

```clike
int doCmdStatus(canalStatus *pStatus)
```

### Parameters

#### pStatus
Pointer to a canalStatus structure that will receive the remote VSCP server status.


### Return Value
Returns CANAL_ERROR_SUCCESS on success or an error code on failure.

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