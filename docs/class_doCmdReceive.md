

```clike
int doCmdReceive(vscpEvent *pEvent)
```

### Parameters

#### pEvent
Pointer to a VSCP event that will receive the event from the remote VSCP server queue on success.

### Return Value
Returns CANAL_ERROR_SUCCESS on success or an error code on failure.

### Description
Receive one event if one is available.



#### C++ example

With an authenticated `VscpRemoteTcpIf client` (see [TLS connections](tls.md)) and `<iostream>` included:

```cpp
vscpEvent event = {};
int result = client.doCmdReceive(&event);
if (result != VSCP_ERROR_SUCCESS) {
    std::cerr << "doCmdReceive failed (error " << result << ")\n";
} else {
    std::cout << "Class: " << event.vscp_class << '\n';
}
delete[] event.pdata;
```

#### Python and JavaScript availability

The official bindings do not expose `VscpRemoteTcpIf` directly. Python applications can use the separate C helper wrappers; the current Node.js binding does not expose these methods. See [language bindings](bindings.md).

[filename](./bottom_copyright.md ':include')