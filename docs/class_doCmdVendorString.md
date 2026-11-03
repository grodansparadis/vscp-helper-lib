

```clike
const char *doCmdVendorString(void)
```

### Parameters

#### handle
Handle for the communication channel obtained from a call to [vscphlp_newsession](vscphlp_newsession.md).

### Return Value
Returns a pointer to a null-terminated string containing vendor information, or a NULL pointer on failure.

### Description
Get the vendor (maker of DL/DLL) string. This is intended for CANAL. 



#### C++ example

With an authenticated `VscpRemoteTcpIf client` (see [TLS connections](tls.md)) and `<iostream>` included:

```cpp
std::cout << client.doCmdVendorString() << '\n';
```

#### Python and JavaScript availability

The official bindings do not expose `VscpRemoteTcpIf` directly. Python applications can use the separate C helper wrappers; the current Node.js binding does not expose these methods. See [language bindings](bindings.md).

[filename](./bottom_copyright.md ':include')