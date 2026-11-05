

```clike
int doCmdFilter(const vscpEventFilter *pFilter)
```

### Parameters

#### pFilter
Pointer to VSCP filter structure to set.

### Return Value
`VSCP_ERROR_SUCCESS` (`0`) indicates success. Possible error codes: `VSCP_ERROR_CONNECTION`,
`VSCP_ERROR_PARAMETER`, `VSCP_ERROR_ERROR`.

### Description
Set the receive filter on the remote VSCP server to select which events to receive. For more complex setups, you can open several channels and set a filter on each one.



#### C++ example

With an authenticated `VscpRemoteTcpIf client` (see [TLS connections](tls.md)) and `<iostream>` included:

```cpp
vscpEventFilter filter = {};
filter.filter_class = 10;
filter.mask_class = 0xFFFF;
int result = client.doCmdFilter(&filter);
if (result != VSCP_ERROR_SUCCESS) {
    std::cerr << "doCmdFilter failed (error " << result << ")\n";
}
```

#### Python and JavaScript availability

The official bindings do not expose `VscpRemoteTcpIf` directly. Python and Node.js applications can use C helper wrappers where available; see [language bindings](bindings.md).

[filename](./bottom_copyright.md ':include')