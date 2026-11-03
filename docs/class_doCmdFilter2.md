

```clike
int doCmdFilter(const std::string &filter, const std::string &mask)
```

### Parameters

#### filter
Filter to set, in string form (“priority,class,type,guid”).

#### mask
Mask to set, in string form (“priority,class,type,guid”).

### Return Value
Returns CANAL_ERROR_SUCCESS on success or an error code on failure.

### Description
Set the receive filter on the remote VSCP server to select which events to receive. For more complex setups, you can open several channels and set a filter on each one.



#### C++ example

With an authenticated `VscpRemoteTcpIf client` (see [TLS connections](tls.md)) and `<iostream>` included:

```cpp
const std::string filter = "0,10,0,00:00:00:00:00:00:00:00:00:00:00:00:00:00:00:00";
const std::string mask = "0,65535,0,00:00:00:00:00:00:00:00:00:00:00:00:00:00:00:00";
int result = client.doCmdFilter(filter, mask);
if (result != VSCP_ERROR_SUCCESS) {
    std::cerr << "doCmdFilter failed (error " << result << ")\n";
}
```

#### Python and JavaScript availability

The official bindings do not expose `VscpRemoteTcpIf` directly. Python applications can use the separate C helper wrappers; the current Node.js binding does not expose these methods. See [language bindings](bindings.md).

[filename](./bottom_copyright.md ':include')
