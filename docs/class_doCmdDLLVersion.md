

```clike
unsigned long doCmdDLLVersion(void)
```

### Parameters

#### handle
Handle for the communication channel obtained from a call to [vscphlp_newsession](vscphlp_newsession.md).

### Return Value
Returns the local interface version constant, not an error code.

### Description
Get DL/DLL version. This is intended for CANAL. 



#### C++ example

With an authenticated `VscpRemoteTcpIf client` (see [TLS connections](tls.md)) and `<iostream>` included:

```cpp
std::cout << client.doCmdDLLVersion() << '\n';
```

#### Python and JavaScript availability

The official bindings do not expose `VscpRemoteTcpIf` directly. Python and Node.js applications can use C helper wrappers where available; see [language bindings](bindings.md).

[filename](./bottom_copyright.md ':include')