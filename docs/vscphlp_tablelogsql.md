


```clike
int vscphlp_tableLogSQL( const unsigned char *pName, 
                const unsigned char *psql )
```

### Parameters

#### tblName
Name of an existing table.

#### psql
Pointer to string that contain SQL expression used to 
log data.


### Return Value
CANAL_ERROR_SUCCESS on success or an error code on failure. 

### Description
Log data to with a SQL expression.


### See Also
[vscphlp_tableLog](vscphlp_tablelog.md)



[filename](./bottom_copyright.md ':include')