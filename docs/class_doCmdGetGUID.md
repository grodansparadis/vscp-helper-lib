


```clike
int doCmdGetGUID(unsigned char *pGUID)
```

### Parameters

#### pGUID
Pointer to a 16-byte array that will receive the GUID. The most significant byte is first.

### Return Value
`VSCP_ERROR_SUCCESS` (`0`) indicates success. Possible error codes: `VSCP_ERROR_CONNECTION`,
`VSCP_ERROR_PARAMETER`, `VSCP_ERROR_ERROR`, `VSCP_ERROR_GENERIC`.

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

The official bindings do not expose `VscpRemoteTcpIf` directly. Python and Node.js applications can use C helper wrappers where available; see [language bindings](bindings.md).

[filename](./bottom_copyright.md ':include')
