

```clike
int fetchIterfaceGUID( const std::string& ifName,
                        cguid& guid )
```

### Parameters

#### ifName
Real text name of the VSCP server interface.

#### guid
GUID of the interface, if the named interface exists.

### Return Value
Returns CANAL_ERROR_SUCCESS on success or an error code on failure.

### Description
Fetch the GUID of a TCP/IP interface by name.

> **Known limitation:** The pinned implementation can retry indefinitely when
> the interface-list request fails or returns no interfaces. Avoid calling
> this method until that behavior is corrected.



#### Python and JavaScript availability

The official bindings do not expose `VscpRemoteTcpIf` directly. Python applications can use the separate C helper wrappers; the current Node.js binding does not expose these methods. See [language bindings](bindings.md).

[filename](./bottom_copyright.md ':include')