

```clike
int doCmdFilter(uint32_t filter)
```

### Parameters

#### filter
CANAL 32-bit filter.

### Return Value
Always returns CANAL_ERROR_SUCCESS.

### Description
Dummy for required CANAL method. 




#### C++ example

With an authenticated `VscpRemoteTcpIf client` (see [TLS connections](tls.md)) and `<iostream>` included: This compatibility method is a no-op in the current class.

```cpp
int result = client.doCmdFilter(uint32_t{0});
if (result != VSCP_ERROR_SUCCESS) {
    std::cerr << "doCmdFilter failed (error " << result << ")\n";
}
```

#### Python and JavaScript availability

The official bindings do not expose `VscpRemoteTcpIf` directly. Python applications can use the separate C helper wrappers; the current Node.js binding does not expose these methods. See [language bindings](bindings.md).

[filename](./bottom_copyright.md ':include')