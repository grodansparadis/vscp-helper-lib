

```clike
int doCmdClose(void)
```

### Parameters
None

### Return Value
The method returns `VSCP_ERROR_SUCCESS` (`0`) and does not report a failure code.

### Description
Close connection to remote VSCP server. 



#### C++ example

With an authenticated `VscpRemoteTcpIf client` (see [TLS connections](tls.md)) and `<iostream>` included:

```cpp
int result = client.doCmdClose();
if (result != VSCP_ERROR_SUCCESS) {
    std::cerr << "doCmdClose failed (error " << result << ")\n";
}
```

#### Python and JavaScript availability

The official bindings do not expose `VscpRemoteTcpIf` directly. Python and Node.js applications can use C helper wrappers where available; see [language bindings](bindings.md).

[filename](./bottom_copyright.md ':include')