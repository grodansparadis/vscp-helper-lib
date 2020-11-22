


```clike
int vscphlp_tableListInfo( const unsigned char *pName, 
                    unsigned char *pTableInfo, 
                    int bXML )
```

### Parameters

#### tblName
Name of an existing table.

#### pTableInfo
Pointer to string that on return woll contain information about the table. The list is allocated on the heap and must be freed by the user. If no result is returned set to a NULL pointer.

#### bXML
If TRUE (!=0) info will be returned as BASE64 encoded XML data.

### Return Value
CANAL_ERROR_SUCCESS on success or an error code on failure. 

### Description
Get table information.




[filename](./bottom_copyright.md ':include')