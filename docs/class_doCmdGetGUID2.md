


```clike
int doCmdGetGUID(cguid& ifguid)
```

### Parameters

#### ifguid
Reference to the GUID that will receive the information.

### Return Value
Returns CANAL_ERROR_SUCCESS on success or an error code on failure.

### Description
Get GUID for the remote VSCP server interface. 



#### C++ example

With an authenticated `VscpRemoteTcpIf client` (see [TLS connections](tls.md)) and `<iostream>` included:

```cpp
cguid guid;
int result = client.doCmdGetGUID(guid);
if (result != VSCP_ERROR_SUCCESS) {
    std::cerr << "doCmdGetGUID failed (error " << result << ")\n";
} else {
    std::cout << "Interface GUID retrieved\n";
}
```

#### Python and JavaScript availability

The official bindings do not expose `VscpRemoteTcpIf` directly. Python applications can use the separate C helper wrappers; the current Node.js binding does not expose these methods. See [language bindings](bindings.md).

[filename](./bottom_copyright.md ':include')