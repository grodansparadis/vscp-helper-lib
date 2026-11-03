

```clike
int doCmdInterfaceList(std::deque<std::string> &arrayIf)
```

### Parameters

#### arrayIf
An array that will receive descriptions of the interfaces available on the remote VSCP server.

### Return Value
Returns CANAL_ERROR_SUCCESS on success or an error code on failure.

### Description
Get available interfaces on the VSCP remote server. 




#### C++ example

With an authenticated `VscpRemoteTcpIf client` (see [TLS connections](tls.md)) and `<iostream>` included:

```cpp
std::deque<std::string> interfaces;
int result = client.doCmdInterfaceList(interfaces);
if (result != VSCP_ERROR_SUCCESS) {
    std::cerr << "doCmdInterfaceList failed (error " << result << ")\n";
} else {
    for (const auto &name : interfaces) std::cout << name << '\n';
}
```

#### Python and JavaScript availability

The official bindings do not expose `VscpRemoteTcpIf` directly. Python applications can use the separate C helper wrappers; the current Node.js binding does not expose these methods. See [language bindings](bindings.md).

[filename](./bottom_copyright.md ':include')