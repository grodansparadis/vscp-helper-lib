

```clike
bool checkReturnValue(bool bClear = false)
```

### Parameters

#### bClear
If true, the input queue array is cleared before the call.

### Return Value
`true` means a positive server response was received; `false` covers a negative response,
timeout, read failure, or binary mode. It does not return an error code.

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

The official bindings do not expose `VscpRemoteTcpIf` directly. Python and Node.js applications can use C helper wrappers where available; see [language bindings](bindings.md).

[filename](./bottom_copyright.md ':include')