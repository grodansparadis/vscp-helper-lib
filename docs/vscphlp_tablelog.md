


```clike
int vscphlp_tableLog( const unsigned char *pName, 
                double value, 
                char *pdt )
```

### Parameters

#### tblName
Name of an existing table.

#### value
Value to log.

#### pdt
Pointer to date/time value. Can be NULL (or empty) and in which case the current date/time is used.

### Return Value
CANAL_ERROR_SUCCESS on success or an error code on failure. 

### Description
Log a value, date/time pair to a table. 


### See Also
[vscphlp_tableLogSQL](vscphlp_tablelogsql.md)



[filename](./bottom_copyright.md ':include')