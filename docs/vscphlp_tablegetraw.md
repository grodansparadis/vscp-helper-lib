

```clike
int vscphlp_tableGetRaw( const unsigned char *pName, 
                const char *pFrom, 
                const char *pTo,
                unsigned char **pResultArray )
```


### Parameters

#### tblName
Name of an existing table.

#### from
Datetime from which data should be fetched. Should be given on ISO 8601 format YY-MM-DDTHH:MM:SS.

#### to
Datetime up to which data is fetched. Should be given on ISO 8601 format YY-MM-DDTHH:MM:SS.

##### resultArray
List of null terminated strings that will get filled with rows (if any) from the table. The list is allocated on the heap and must be freed by the user. If no result is returned set to a NULL pointer.

    comma separated row of database columns<CR><LF>
    comma separated row of database columns<CR><LF>
    comma separated row of database columns<CR><LF>
    ...
    comma separated row of database columns<CR><LF>

### Return Value
CANAL_ERROR_SUCCESS on success or an error code on failure. 

### Description
Get data from a named table in a range to-from. All columns of the table is always returned.


### See Also
[vscphlp_tableGet](vscphlp_tableget.md)



[filename](./bottom_copyright.md ':include')