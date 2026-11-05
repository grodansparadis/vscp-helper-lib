

```clike
void doClrInputQueue(void)
```

### Parameters
None

### Return Value
Returns no value or error code.

### Description
Clear the input queue 



#### C++ example

With an authenticated `VscpRemoteTcpIf client` (see [TLS connections](tls.md)) and `<iostream>` included:

```cpp
client.doClrInputQueue();
```

#### Python and JavaScript availability

The official bindings do not expose `VscpRemoteTcpIf` directly. Python and Node.js applications can use C helper wrappers where available; see [language bindings](bindings.md).

[filename](./bottom_copyright.md ':include')