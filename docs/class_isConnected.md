


```clike
bool isConnected(void)
```

### Parameters
None

### Return Value
Returns true if we are connected, false otherwise.

### Description
Check if connected to remote VSCP server. 




#### C++ example

With an authenticated `VscpRemoteTcpIf client` (see [TLS connections](tls.md)) and `<iostream>` included:

```cpp
if (!client.isConnected()) {
    std::cerr << "Client is not connected\n";
} else {
    std::cout << "Client is connected\n";
}
```

#### Python and JavaScript availability

The official bindings do not expose `VscpRemoteTcpIf` directly. Python applications can use the separate C helper wrappers; the current Node.js binding does not expose these methods. See [language bindings](bindings.md).

[filename](./bottom_copyright.md ':include')
