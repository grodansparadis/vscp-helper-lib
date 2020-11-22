


```clike
int saveRemoteVariablesToDisk( const wxString& path, 
                        const int select=0, 
                        const wxString& regExp=_("") )
```

### Parameters

#### path
Path, including file name, to save variables to.

#### select
Select if persistent, non-persistent or both types of variables should be written out to the file.

- **1** for only writing persistent variables. 
- **2** only write non-persistent variables. 
- **3** or 0 for writing both types.

#### regExp
Optional regular expression that selects which variables to write. Default is all.

### Return Value
CANAL_ERROR_SUCCESS on success or an error code on failure. 

### Description
Save (selected) variables to external disk space in XML format. 



[filename](./bottom_copyright.md ':include')