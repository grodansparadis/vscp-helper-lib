

```clike
int doCmdSetBaudrate(uint32_t baudrate)
```

### Parameters

#### baudrate
CANAL baudrate.

### Return Value
The method returns `CANAL_ERROR_SUCCESS` (`0`) and does not report a failure code.

The method is a no-op.

### Description
Dummy for required CANAL method. 




#### C++ example

With an authenticated `VscpRemoteTcpIf client` (see [TLS connections](tls.md)) and `<iostream>` included: This compatibility method is a no-op in the current class.

```cpp
int result = client.doCmdSetBaudrate(0);
if (result != CANAL_ERROR_SUCCESS) {
    std::cerr << "doCmdSetBaudrate failed (error " << result << ")\n";
}
```

#### Python and JavaScript availability

The official bindings do not expose `VscpRemoteTcpIf` directly. Python applications can use the separate C helper wrappers; the current Node.js binding does not expose these methods. See [language bindings](bindings.md).

[filename](./bottom_copyright.md ':include')