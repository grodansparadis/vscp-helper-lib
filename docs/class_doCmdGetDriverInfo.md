

```clike
const char *doCmdGetDriverInfo(void)
```

### Parameters
None

### Return Value
Returns a pointer to the local driver-information string, not an error code.

### Description
Get the driver information string from the remote VSCP server. This is intended for CANAL. 



#### C++ example

With an authenticated `VscpRemoteTcpIf client` (see [TLS connections](tls.md)) and `<iostream>` included:

```cpp
std::cout << client.doCmdGetDriverInfo() << '\n';
```

#### Python and JavaScript availability

The official bindings do not expose `VscpRemoteTcpIf` directly. Python and Node.js applications can use C helper wrappers where available; see [language bindings](bindings.md).

[filename](./bottom_copyright.md ':include')