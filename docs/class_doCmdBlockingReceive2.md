

```clike
int doCmdBlockingReceive(vscpEventEx *pEventEx, 
                        uint32_t timeout = 500)
```

### Parameters

#### pEventEx
Pointer to a VSCP event ex that will receive the event on success.

#### timeout
Time to wait for data, in milliseconds. The default is 500 milliseconds.

### Return Value
`VSCP_ERROR_SUCCESS` (`0`) indicates success. Possible error codes: `VSCP_ERROR_CONNECTION`,
`VSCP_ERROR_PARAMETER`, `VSCP_ERROR_ERROR`, `VSCP_ERROR_READ`, `VSCP_ERROR_INVALID_FRAME`,
`VSCP_ERROR_TIMEOUT`, `VSCP_ERROR_STOPPED`.

In binary mode, a nonzero error code from a server confirmation can also be returned.

### Description
Receive an event ex from the remote VSCP server. The receiveloop command must be issued before calling this method.



#### C++ example

With `client` already in a receive loop (see [doCmdEnterReceiveLoop](class_doCmdEnterReceiveLoop.md)) and `<iostream>` included:

```cpp
vscpEventEx event = {};
int result = client.doCmdBlockingReceive(&event, 1000);
if (result != VSCP_ERROR_SUCCESS) {
    std::cerr << "doCmdBlockingReceive failed (error " << result << ")\n";
} else {
    std::cout << "Class: " << event.vscp_class << '\n';
}
```

#### Python and JavaScript availability

The official bindings do not expose `VscpRemoteTcpIf` directly. Python applications can use the separate C helper wrappers; the current Node.js binding does not expose these methods. See [language bindings](bindings.md).

[filename](./bottom_copyright.md ':include')