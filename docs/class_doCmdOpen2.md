

```cpp
int doCmdOpen(const std::string& strHostname,
              const std::string& strUsername,
              const std::string& strPassword);
```

### Parameters

#### strHostname
The `host:port` endpoint. By default, `stcp://host:port` selects TLS;
`tcp://host:port` or `host:port` selects plain TCP. TLS options configured
on the C++ class can override this prefix-based selection.

#### strUsername
Username for VSCP remote server account.

#### strPassword
Password for VSCP remote server account.

### Return Value
`VSCP_ERROR_SUCCESS` (`0`) indicates success. Possible error codes: `VSCP_ERROR_PARAMETER`,
`VSCP_ERROR_CONNECTION`, `VSCP_ERROR_TIMEOUT`, `VSCP_ERROR_USER`, `VSCP_ERROR_PASSWORD`.

### Description
Opens and logs in to the communication interface. See
[TLS connections](tls.md) for server verification and C++ TLS options.


#### C++ example

With a `VscpRemoteTcpIf client`, `<iostream>` included, and `endpoint`, `username`, and `password` supplied as strings by the application (see [TLS connections](tls.md)):

```cpp
int result = client.doCmdOpen(endpoint, username, password);
if (result != VSCP_ERROR_SUCCESS) {
    std::cerr << "doCmdOpen failed (error " << result << ")\n";
}
```

#### Python and JavaScript availability

The official bindings do not expose `VscpRemoteTcpIf` directly. Python and Node.js applications can use C helper wrappers where available; see [language bindings](bindings.md).

### See Also
[doCmdOpen](class_doCmdOpen.md)



[filename](./bottom_copyright.md ':include')