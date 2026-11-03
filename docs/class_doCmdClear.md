

```clike
int doCmdClear(void)
```

### Parameters

#### handle
Handle for the communication channel obtained from a call to [vscphlp_newsession](vscphlp_newsession.md).

### Return Value
Returns CANAL_ERROR_SUCCESS on success or an error code on failure.

### Description
Clear input queue on the remote VSCP server. 



#### C++ example

With an authenticated `VscpRemoteTcpIf client` (see [TLS connections](tls.md)) and `<iostream>` included:

```cpp
int result = client.doCmdClear();
if (result != VSCP_ERROR_SUCCESS) {
    std::cerr << "doCmdClear failed (error " << result << ")\n";
}
```

#### Python and JavaScript availability

The official bindings do not expose `VscpRemoteTcpIf` directly. Python applications can use the separate C helper wrappers; the current Node.js binding does not expose these methods. See [language bindings](bindings.md).

[filename](./bottom_copyright.md ':include')