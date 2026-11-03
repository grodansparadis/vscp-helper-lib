

```clike
int doCmdClose(void)
```

### Parameters
None

### Return Value
Returns CANAL_ERROR_SUCCESS on success or an error code on failure.

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

The official bindings do not expose `VscpRemoteTcpIf` directly. Python applications can use the separate C helper wrappers; the current Node.js binding does not expose these methods. See [language bindings](bindings.md).

[filename](./bottom_copyright.md ':include')