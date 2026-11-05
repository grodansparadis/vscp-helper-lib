

```clike
int doCmdSetGUID(cguid &ifGUID)
```

### Parameters

#### ifGUID
Reference to the GUID containing the new value.

### Return Value
`VSCP_ERROR_SUCCESS` (`0`) indicates success. Possible error codes: `VSCP_ERROR_CONNECTION`,
`VSCP_ERROR_PARAMETER`, `VSCP_ERROR_ERROR`.

### Description
Set GUID for the remote VSCP server interface. 




#### C++ example

With an authenticated `VscpRemoteTcpIf client` (see [TLS connections](tls.md)) and `<iostream>` included: Supply `new_cguid` as the desired interface `cguid`:

```cpp
int result = client.doCmdSetGUID(new_cguid);
if (result != VSCP_ERROR_SUCCESS) {
    std::cerr << "doCmdSetGUID failed (error " << result << ")\n";
}
```

#### Python and JavaScript availability

The official bindings do not expose `VscpRemoteTcpIf` directly. Python applications can use the separate C helper wrappers; the current Node.js binding does not expose these methods. See [language bindings](bindings.md).

[filename](./bottom_copyright.md ':include')