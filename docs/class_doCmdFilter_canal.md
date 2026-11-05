

```clike
int doCmdFilter(uint32_t filter)
```

### Parameters

#### filter
CANAL 32-bit filter.

### Return Value
The method returns `CANAL_ERROR_SUCCESS` (`0`) and does not report a failure code.

The method is a no-op.

### Description
Dummy for required CANAL method. 




#### C++ example

With an authenticated `VscpRemoteTcpIf client` (see [TLS connections](tls.md)) and `<iostream>` included: This compatibility method is a no-op in the current class.

```cpp
int result = client.doCmdFilter(uint32_t{0});
if (result != CANAL_ERROR_SUCCESS) {
    std::cerr << "doCmdFilter failed (error " << result << ")\n";
}
```

#### Python and JavaScript availability

The official bindings do not expose `VscpRemoteTcpIf` directly. Python and Node.js applications can use C helper wrappers where available; see [language bindings](bindings.md).

[filename](./bottom_copyright.md ':include')