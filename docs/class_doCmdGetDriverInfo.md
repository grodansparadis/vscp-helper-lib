

```clike
const char *doCmdGetDriverInfo(void)
```

### Parameters
None

### Return Value
Returns a pointer to a null-terminated string containing driver information in XML format, or a NULL pointer on failure.

### Description
Get the driver information string from the remote VSCP server. This is intended for CANAL. 



#### C++ example

With an authenticated `VscpRemoteTcpIf client` (see [TLS connections](tls.md)) and `<iostream>` included:

```cpp
std::cout << client.doCmdGetDriverInfo() << '\n';
```

#### Python and JavaScript availability

The official bindings do not expose `VscpRemoteTcpIf` directly. Python applications can use the separate C helper wrappers; the current Node.js binding does not expose these methods. See [language bindings](bindings.md).

[filename](./bottom_copyright.md ':include')