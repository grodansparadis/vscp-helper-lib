

```clike
int doCommand(const std::string &cmd)
```

### Parameters

#### cmd
A VSCP remote server command that is terminated with \<CR\>\<LF\> (“\r\n”).


### Return Value
`VSCP_ERROR_SUCCESS` (`0`) indicates success. Possible error codes: `VSCP_ERROR_CONNECTION`,
`VSCP_ERROR_PARAMETER`, `VSCP_ERROR_ERROR`, `VSCP_ERROR_TIMEOUT`, `VSCP_ERROR_STOPPED`,
`VSCP_ERROR_INVALID_FRAME`, `VSCP_ERROR_READ`.

### Description
Send any command to the remote VSCP server.



#### C++ example

With an authenticated `VscpRemoteTcpIf client` (see [TLS connections](tls.md)) and `<iostream>` included:

```cpp
int result = client.doCommand("NOOP\r\n");
if (result != VSCP_ERROR_SUCCESS) {
    std::cerr << "doCommand failed (error " << result << ")\n";
}
```

#### Python and JavaScript availability

The official bindings do not expose `VscpRemoteTcpIf` directly. Python and Node.js applications can use C helper wrappers where available; see [language bindings](bindings.md).

[filename](./bottom_copyright.md ':include')