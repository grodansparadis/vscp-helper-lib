

```clike
int doCmdVersion(uint8_t *pMajorVer,
                     uint8_t *pMinorVer,
                     uint8_t *pSubMinorVer)
```

### Parameters

#### pMajorVer
Major version of VSCP remote server interface.

#### pMinorVer
Minor version of VSCP remote server interface.

#### pSubMinorVer
Sub version of VSCP remote server interface.

### Return Value
`VSCP_ERROR_SUCCESS` (`0`) indicates success. Possible error codes: `VSCP_ERROR_CONNECTION`,
`VSCP_ERROR_PARAMETER`, `VSCP_ERROR_ERROR`.
All three version pointers must be valid; they are not checked for null.
`VSCP_ERROR_PARAMETER` indicates that the operation is not allowed in the
current receive-loop mode, not a null-pointer check.

### Description
Get the interface version from the remote VSCP server. 



#### C++ example

With an authenticated `VscpRemoteTcpIf client` (see [TLS connections](tls.md)) and `<iostream>` included:

```cpp
uint8_t major = 0, minor = 0, patch = 0;
int result = client.doCmdVersion(&major, &minor, &patch);
if (result != VSCP_ERROR_SUCCESS) {
    std::cerr << "doCmdVersion failed (error " << result << ")\n";
} else {
    std::cout << static_cast<unsigned>(major) << '.'
              << static_cast<unsigned>(minor) << '.'
              << static_cast<unsigned>(patch) << '\n';
}
```

#### Python and JavaScript availability

The official bindings do not expose `VscpRemoteTcpIf` directly. Python applications can use the separate C helper wrappers; the current Node.js binding does not expose these methods. See [language bindings](bindings.md).

[filename](./bottom_copyright.md ':include')