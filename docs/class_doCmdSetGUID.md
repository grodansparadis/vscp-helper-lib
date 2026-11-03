

```clike
int doCmdSetGUID(const unsigned char *pGUID)
```

### Parameters

#### pGUID
Pointer to a 16-byte array containing the new GUID. The most significant byte is first.


### Return Value
Returns CANAL_ERROR_SUCCESS on success or an error code on failure.

### Description
Set GUID for the remote VSCP server interface. 




#### C++ example

With an authenticated `VscpRemoteTcpIf client` (see [TLS connections](tls.md)) and `<iostream>` included: Supply `new_guid` as a valid 16-byte GUID for the interface:

```cpp
int result = client.doCmdSetGUID(new_guid);
if (result != VSCP_ERROR_SUCCESS) {
    std::cerr << "doCmdSetGUID failed (error " << result << ")\n";
}
```

#### Python and JavaScript availability

The official bindings do not expose `VscpRemoteTcpIf` directly. Python applications can use the separate C helper wrappers; the current Node.js binding does not expose these methods. See [language bindings](bindings.md).

[filename](./bottom_copyright.md ':include')