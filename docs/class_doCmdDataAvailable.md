

```clike
int doCmdDataAvailable(void)
```

### Parameters
None

### Return Value
Returns a nonnegative event count, or `VSCP_ERROR_ERROR` (`-1`) if disconnected, in a
receive loop, or the command fails. The count is a value, not a success code.
The response is parsed without strict validation: an empty or nonnumeric
response can appear as `0`, and a negative numeric response can be returned
as a negative value.

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