


```clike
int doCmdMask(uint32_t mask)
```

### Parameters

#### mask
CANAL 32-bit mask.

### Return Value
The method returns `CANAL_ERROR_SUCCESS` (`0`) and does not report a failure code.

The method is a no-op.

### Description
Dummy for required CANAL method. 




#### C++ example

With an authenticated `VscpRemoteTcpIf client` (see [TLS connections](tls.md)) and `<iostream>` included: This compatibility method is a no-op in the current class.

```cpp
int result = client.doCmdMask(0);
if (result != CANAL_ERROR_SUCCESS) {
    std::cerr << "doCmdMask failed (error " << result << ")\n";
}
```

#### Python and JavaScript availability

The official bindings do not expose `VscpRemoteTcpIf` directly. Python and Node.js applications can use C helper wrappers where available; see [language bindings](bindings.md).

[filename](./bottom_copyright.md ':include')