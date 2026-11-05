


> **Availability:** `saveRemoteVariablesToDisk` is not present in the
> `VscpRemoteTcpIf` version pinned by this project. The signature below is
> historical and has no current C++ example.

```clike
int saveRemoteVariablesToDisk( const wxString& path, 
                        const int select=0, 
                        const wxString& regExp=_("") )
```

### Parameters

#### path
Path, including file name, to save variables to.

#### select
Select whether to write persistent variables, non-persistent variables, or both to the file.

- **1** to write only persistent variables.
- **2** to write only non-persistent variables.
- **3** or 0 to write both types.

#### regExp
Optional regular expression that selects which variables to write. By default, all variables are selected.

### Return Value
This method is not present in the pinned `VscpRemoteTcpIf` implementation, so
no return codes are available for this build.

### Description
Save (selected) variables to external disk space in XML format. 



#### Python and JavaScript availability

The official bindings do not expose `VscpRemoteTcpIf` directly. Python applications can use the separate C helper wrappers; the current Node.js binding does not expose these methods. See [language bindings](bindings.md).

[filename](./bottom_copyright.md ':include')
