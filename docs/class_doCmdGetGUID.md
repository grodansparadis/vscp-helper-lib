


```clike
int doCmdGetGUID(unsigned char *pGUID)
```

### Parameters

#### pGUID
Pointer to a 16-byte array that will receive the GUID. The most significant byte is first.

### Return Value
Returns CANAL_ERROR_SUCCESS on success or an error code on failure.

### Description
Get GUID for the remote VSCP server interface. 



#### C++ example

With an authenticated `VscpRemoteTcpIf client` (see [TLS connections](tls.md)) and `<iostream>` included:

```cpp
unsigned char guid[16] = {};
int result = client.doCmdGetGUID(guid);
if (result != VSCP_ERROR_SUCCESS) {
    std::cerr << "doCmdGetGUID failed (error " << result << ")\n";
} else {
    std::cout << "Last GUID byte: " << static_cast<unsigned>(guid[15]) << '\n';
}
```

#### Python and JavaScript availability

The official bindings do not expose `VscpRemoteTcpIf` directly. Python applications can use the separate C helper wrappers; the current Node.js binding does not expose these methods. See [language bindings](bindings.md).

[filename](./bottom_copyright.md ':include')
