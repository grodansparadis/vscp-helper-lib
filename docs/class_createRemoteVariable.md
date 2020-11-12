

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
Name of remote variable to create. A user variable can not have a name that start with “vscp.”.

#### strType
Type of variable either in string or numeric form.

#### bPersistet
True if the variable should be persistent (default=false)

#### strUser
Owner of variable. Can be left empty in which case the logged in user will be set as owner.

#### rights
Access rights for variable.

#### strValue
Value for the remote variable.

#### strNote
Optional note for the remote variable.

### Return Value
CANAL_ERROR_SUCCESS on success or an error code on failure.

### Description
Create a new remote variable.



[filename](./bottom_copyright.md ':include')                                