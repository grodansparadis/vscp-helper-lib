

```clike
int doCmdReceiveLevel1(canalMsg *pCanalMsg)
```

### Parameters

#### pCanalMsg
Pointer to a CANAL message that will receive the event from the remote VSCP server queue on success.


### Return Value
`VSCP_ERROR_SUCCESS` (`0`) indicates success. Possible error codes: `VSCP_ERROR_CONNECTION`,
`VSCP_ERROR_PARAMETER`, `VSCP_ERROR_GENERIC`.

### Description
Receive a VSCP Level I event from the remote VSCP server queue. The low eight bits of the CAN ID are taken from GUID[15], the least significant byte of the GUID.



#### C++ example

With an authenticated `VscpRemoteTcpIf client` (see [TLS connections](tls.md)) and `<iostream>` included:

```cpp
canalMsg message = {};
int result = client.doCmdReceiveLevel1(&message);
if (result != VSCP_ERROR_SUCCESS) {
    std::cerr << "doCmdReceiveLevel1 failed (error " << result << ")\n";
} else {
    std::cout << "CAN ID: " << message.id << '\n';
}
```

#### Python and JavaScript availability

The official bindings do not expose `VscpRemoteTcpIf` directly. Python applications can use the separate C helper wrappers; the current Node.js binding does not expose these methods. See [language bindings](bindings.md).

[filename](./bottom_copyright.md ':include')