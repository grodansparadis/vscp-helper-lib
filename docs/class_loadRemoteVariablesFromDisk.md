


> **Availability:** `loadRemoteVariablesFromDisk` is not present in the
> `VscpRemoteTcpIf` version pinned by this project. The signature below is
> historical and has no current C++ example.

```clike
int loadRemoteVariablesFromDisk( const wxString& path )
```

### Parameters

#### path
Path to load the remote variable XML file from.

### Return Value
Returns CANAL_ERROR_SUCCESS on success or an error code on failure.

### Description
Load remote variables from disk.



#### Python and JavaScript availability

The official bindings do not expose `VscpRemoteTcpIf` directly. Python applications can use the separate C helper wrappers; the current Node.js binding does not expose these methods. See [language bindings](bindings.md).

[filename](./bottom_copyright.md ':include')
