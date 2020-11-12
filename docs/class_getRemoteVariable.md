

```clike
int getRemoteVariable( const wxString& name, 
                        wxString& strVariable )
```

### Parameters

#### name
Name of remote variable to get information for.

#### strVariable
String that will get variable information.

### Return Value
CANAL_ERROR_SUCCESS on success or an error code on failure. 

### Description
Get remote variable (full info).

Format is:

    "variable name";"type";"persistence";"user";"rights";"value";"note"



[filename](./bottom_copyright.md ':include')