


```clike
int tableListInfo( const wxString &tblName, 
                    wxString &tableInfo, 
                    bool bXML = true )
```

### Parameters

#### tblName
Name of an existing table.

#### tableInfo
Parameter that will get the information about the table.

#### bXML
If true info will be returnd as BASE64 encoded XML data.

### Return Value
CANAL_ERROR_SUCCESS on success or an error code on failure. 

### Description
Delete named table. 



[filename](./bottom_copyright.md ':include')