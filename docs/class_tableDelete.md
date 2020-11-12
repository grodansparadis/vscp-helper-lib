



```clike
int tableDelete( const wxString &tblName, 
                bool bDeleteFile=false )
```

### Parameters

#### tblName
Name of an existing table.

#### bDeleteFile
If true the database file also should be deleted. If not it will be reused if a table with the same name is created later.

### Return Value
CANAL_ERROR_SUCCESS on success or an error code on failure. 

### Description
Delete named table. 



[filename](./bottom_copyright.md ':include')
