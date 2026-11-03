

```clike
int doCmdSendLevel1(const canalMsg *pMsg)
```

### Parameters

#### pMsg
A pointer to a CANAL message.

### Return Value
Returns CANAL_ERROR_SUCCESS on success or an error code on failure.

### Description
Send a Level I event to the VSCP remote server. The GUID of the interface will be used for the resulting VSCP event. 



#### C++ example

With an authenticated `VscpRemoteTcpIf client` (see [TLS connections](tls.md)) and `<iostream>` included:

```cpp
canalMsg message = {};
message.flags = CANAL_IDFLAG_EXTENDED;
message.id = 0x123;
message.sizeData = 1;
message.data[0] = 42;
int result = client.doCmdSendLevel1(&message);
if (result != VSCP_ERROR_SUCCESS) {
    std::cerr << "doCmdSendLevel1 failed (error " << result << ")\n";
}
```

#### Python and JavaScript availability

The official bindings do not expose `VscpRemoteTcpIf` directly. Python applications can use the separate C helper wrappers; the current Node.js binding does not expose these methods. See [language bindings](bindings.md).

[filename](./bottom_copyright.md ':include')