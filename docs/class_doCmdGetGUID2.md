


```clike
int doCmdGetGUID(cguid& ifguid)
```

### Parameters

#### ifguid
Reference to the GUID that will receive the information.

### Return Value
`VSCP_ERROR_SUCCESS` (`0`) indicates success. Possible error codes: `VSCP_ERROR_CONNECTION`,
`VSCP_ERROR_PARAMETER`, `VSCP_ERROR_ERROR`.

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