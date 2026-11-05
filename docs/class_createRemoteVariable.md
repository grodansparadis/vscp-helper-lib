

> **Availability:** `createRemoteVariable` is not present in the
> `VscpRemoteTcpIf` version pinned by this project. The signature below is
> historical and has no current C++ example.

```clike
int createRemoteVariable( const wxString& name, 
                                const wxString& strType,
                                const bool bPersistent,
                                const wxString& strUser,
                                const uint32_t rights,
                                const wxString& strValue,
                                const wxString& strNote = _("") )
```

### Parameters

#### name
Name of the remote variable to create. A user variable name cannot start with “vscp.”.

#### strType
Type of the variable, in string or numeric form.

#### bPersistet
True if the variable should be persistent (default: false).

#### strUser
Owner of the variable. If left empty, the logged-in user becomes the owner.

#### rights
Access rights for the variable.

#### strValue
Value for the remote variable.

#### strNote
Optional note for the remote variable.

### Return Value
This method is not present in the pinned `VscpRemoteTcpIf` implementation, so
no return codes are available for this build.

### Description
Create a new remote variable.



#### Python and JavaScript availability

The official bindings do not expose `VscpRemoteTcpIf` directly. Python and Node.js applications can use C helper wrappers where available; see [language bindings](bindings.md).

[filename](./bottom_copyright.md ':include')
