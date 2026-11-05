


```clike
unsigned long doCmdGetLevel(void)
```

### Parameters
Nothing.

### Return Value
Returns the constant `VSCP_LEVEL2`, not an error code.

### Description
Get the CANAL protocol level. Mainly used by the CANAL/VSCP combined subsystem. 



#### C++ example

With an authenticated `VscpRemoteTcpIf client` (see [TLS connections](tls.md)) and `<iostream>` included:

```cpp
std::cout << client.doCmdGetLevel() << '\n';
```

#### Python and JavaScript availability

The official bindings do not expose `VscpRemoteTcpIf` directly. Python applications can use the separate C helper wrappers; the current Node.js binding does not expose these methods. See [language bindings](bindings.md).

[filename](./bottom_copyright.md ':include')