

```clike
bool checkReturnValue(bool bClear = false)
```

### Parameters

#### bClear
If true, the input queue array is cleared before the call.

### Return Value
Returns true if a positive response (+OK) is received from the remote VSCP server. Returns false for a negative response or a timeout.

### Description
Check the response from the remote VSCP server for an error or a successfully completed command.



#### C++ example

With a connected `client`, a reply pending, and `<iostream>` included:

```cpp
if (!client.checkReturnValue(false)) {
    std::cerr << "No successful reply received\n";
}
```

#### Python and JavaScript availability

The official bindings do not expose `VscpRemoteTcpIf` directly. Python applications can use the separate C helper wrappers; the current Node.js binding does not expose these methods. See [language bindings](bindings.md).

[filename](./bottom_copyright.md ':include')