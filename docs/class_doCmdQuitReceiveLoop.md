

```clike
int doCmdQuitReceiveLoop(void)
```

### Parameters
None.

### Return Value
Returns CANAL_ERROR_SUCCESS on success or an error code on failure.

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

The official bindings do not expose `VscpRemoteTcpIf` directly. Python applications can use the separate C helper wrappers; the current Node.js binding does not expose these methods. See [language bindings](bindings.md).

### See Also
[doCmdEnterReceiveLoop](class_doCmdEnterReceiveLoop.md)



[filename](./bottom_copyright.md ':include')