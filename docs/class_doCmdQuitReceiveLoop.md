

```clike
int doCmdQuitReceiveLoop(void)
```

### Parameters
None.

### Return Value
`VSCP_ERROR_SUCCESS` (`0`) indicates success. Possible error codes: `VSCP_ERROR_CONNECTION`,
`VSCP_ERROR_PARAMETER`, `VSCP_ERROR_TIMEOUT`.

### Description
Quit the receive loop. 

#### C++ example

With `client` already in a receive loop (see [doCmdEnterReceiveLoop](class_doCmdEnterReceiveLoop.md)) and `<iostream>` included:

```cpp
int result = client.doCmdQuitReceiveLoop();
if (result != VSCP_ERROR_SUCCESS) {
    std::cerr << "doCmdQuitReceiveLoop failed (error " << result << ")\n";
}
```

#### Python and JavaScript availability

The official bindings do not expose `VscpRemoteTcpIf` directly. Python and Node.js applications can use C helper wrappers where available; see [language bindings](bindings.md).

### See Also
[doCmdEnterReceiveLoop](class_doCmdEnterReceiveLoop.md)



[filename](./bottom_copyright.md ':include')