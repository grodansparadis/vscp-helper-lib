

```clike
int doCmdDataAvailable(void)
```

### Parameters
None

### Return Value
Returns the number of events available in the remote VSCP server queue, or a negative error code on failure.

### Description
Get the number of events in the input queue of this interface 



#### C++ example

With an authenticated `VscpRemoteTcpIf client` (see [TLS connections](tls.md)) and `<iostream>` included:

```cpp
int count = client.doCmdDataAvailable();
if (count < 0) {
    std::cerr << "doCmdDataAvailable failed (error " << count << ")\n";
} else {
    std::cout << "Available events: " << count << '\n';
}
```

#### Python and JavaScript availability

The official bindings do not expose `VscpRemoteTcpIf` directly. Python applications can use the separate C helper wrappers; the current Node.js binding does not expose these methods. See [language bindings](bindings.md).

[filename](./bottom_copyright.md ':include')