


```clike
int tableLog( const wxString& tblName, 
                double value, 
                wxDateTime *pdt = NULL )
```

### Parameters

#### tblName
Name of an existing table.

#### value
Value to log.

#### pdt
Pointer to date/time value. Can be NULL and in which case the current date/time is used.

### Return Value
CANAL_ERROR_SUCCESS on success or an error code on failure. 

### Description
Log a value, date/time pair to a table. 




[filename](./bottom_copyright.md ':include')