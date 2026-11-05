


```cpp
int doCmdOpen(const std::string& strInterface = std::string(""),
              uint32_t flags = 0L);
```

### Parameters

#### strInterface
The endpoint and credentials in the form `host:port;username;password`.
Use `stcp://host:port;username;password` to select TLS by default, or use
`tcp://` or no prefix for plain TCP. A host and port are required. The
semicolon-separated format cannot escape semicolons in credentials; use the
[separate-argument overload](class_doCmdOpen2.md) if needed.

#### flags
Currently not used.

### Return Value
`VSCP_ERROR_SUCCESS` (`0`) indicates success. Possible error codes: `VSCP_ERROR_PARAMETER`,
`VSCP_ERROR_CONNECTION`, `VSCP_ERROR_TIMEOUT`, `VSCP_ERROR_USER`, `VSCP_ERROR_PASSWORD`.

### Description
Opens and logs in to the communication interface. The C++ class can override
prefix-based TLS selection and configure TLS options explicitly; see
[TLS connections](tls.md).

#### C++ example

With a `VscpRemoteTcpIf client`, `<iostream>` included, and `endpoint`, `username`, and `password` supplied as strings by the application (see [TLS connections](tls.md)):

```cpp
std::string interface = endpoint + ";" + username + ";" + password;
int result = client.doCmdOpen(interface);
if (result != VSCP_ERROR_SUCCESS) {
    std::cerr << "doCmdOpen failed (error " << result << ")\n";
}
```

#### Python and JavaScript availability

The official bindings do not expose `VscpRemoteTcpIf` directly. Python and Node.js applications can use C helper wrappers where available; see [language bindings](bindings.md).

### See Also
[doCmdOpen](class_doCmdOpen2.md)



[filename](./bottom_copyright.md ':include')