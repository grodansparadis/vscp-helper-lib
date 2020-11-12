
```clike
int vscphlp_tableDelete( const unsigned char *pName, 
                            int bDeleteFile )
```

### Parameters

#### tblName
Name of an existing table.

#### bDeleteFile
If TRUE (!=0) the database file also should be deleted. If not it will be reused if a table with the same name is created later.


### Return Value
CANAL_ERROR_SUCCESS on success or an error code on failure. 

### Description
Delete named table.


### See Also
[vscphlp_tableCreate](vscphlp_tablecreate.md)



[filename](./bottom_copyright.md ':include')