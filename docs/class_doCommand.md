

```clike
int doCommand(const std::string &cmd)
```

### Parameters

#### cmd
A VSCP remote server command that is terminated with \<CR\>\<LF\> (“\r\n”).


### Return Value
Returns VSCP_ERROR_SUCCESS if the command is sent successfully and a positive response (+OK) is received, or an error code otherwise.

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

The official bindings do not expose `VscpRemoteTcpIf` directly. Python applications can use the separate C helper wrappers; the current Node.js binding does not expose these methods. See [language bindings](bindings.md).

[filename](./bottom_copyright.md ':include')