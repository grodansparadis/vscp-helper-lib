

```clike
int doCmdEnterReceiveLoop(void)
```

### Parameters
None.

### Return Value
`VSCP_ERROR_SUCCESS` (`0`) indicates success. Possible error codes: `VSCP_ERROR_CONNECTION`,
`VSCP_ERROR_PARAMETER`, `VSCP_ERROR_ERROR`, `VSCP_ERROR_READ`.

### Description
This command puts an open interface into the receive loop (RCVLOOP) state and checks that it entered that state.

**Note:** To terminate the receive loop, close the session with doCmdClose (or close the socket), or send the [doCmdQuitReceiveLoop](class_doCmdQuitReceiveLoop.md) command.

#### C++ example

With an authenticated `VscpRemoteTcpIf client` (see [TLS connections](tls.md)) and `<iostream>` included: Leave the loop with `doCmdQuitReceiveLoop` when finished.

```cpp
int result = client.doCmdEnterReceiveLoop();
if (result != VSCP_ERROR_SUCCESS) {
    std::cerr << "doCmdEnterReceiveLoop failed (error " << result << ")\n";
}
```

#### Python and JavaScript availability

The official bindings do not expose `VscpRemoteTcpIf` directly. Python applications can use the separate C helper wrappers; the current Node.js binding does not expose these methods. See [language bindings](bindings.md).

### See Also
[doCmdQuitReceiveLoop](class_doCmdQuitReceiveLoop.md)



[filename](./bottom_copyright.md ':include')