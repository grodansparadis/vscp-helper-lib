```clike
int doCmdNOOP(void)
```

### Parameters

None.

### Return Value
`VSCP_ERROR_SUCCESS` (`0`) indicates success. Possible error codes: `VSCP_ERROR_CONNECTION`,
`VSCP_ERROR_PARAMETER`, `VSCP_ERROR_ERROR`, `VSCP_ERROR_TIMEOUT`, `VSCP_ERROR_STOPPED`,
`VSCP_ERROR_INVALID_FRAME`, `VSCP_ERROR_READ`.

### Description

Send a NOOP command to check that the connected VSCP server responds.

#### C++ example

With an authenticated `VscpRemoteTcpIf client` (see [TLS connections](tls.md))
and `<iostream>` included:

```cpp
int result = client.doCmdNOOP();
if (result != VSCP_ERROR_SUCCESS) {
    std::cerr << "doCmdNOOP failed (error " << result << ")\n";
} else {
    std::cout << "NOOP succeeded\n";
}
```

#### Python and JavaScript availability

The official bindings do not expose `VscpRemoteTcpIf` directly. Python
applications can use [vscphlp_noop](vscphlp_noop.md); the current Node.js
binding does not expose these methods. See [language bindings](bindings.md).

[filename](./bottom_copyright.md ':include')
