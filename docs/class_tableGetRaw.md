



```clike
int tableGetRaw( const wxString& tblName, 
                    const wxDateTime& from, 
                    const wxDateTime& to,
                    wxArrayString& resultArray )
```

### Parameters

#### tblName
Name of an existing table.

#### from
Datetime from which data should be fetched. Should be given on ISO 8601 format YY-MM-DDTHH:MM:SS.

#### to
Datetime up to which data is fetched. Should be given on ISO 8601 format YY-MM-DDTHH:MM:SS.

#### resultArray
String array that is filled with resulting rows (if any) from the table. The format is

    'count' rows<CR><LF>
    comma separated row of database columns<CR><LF>
    comma separated row of database columns<CR><LF>
    comma separated row of database columns<CR><LF>
    ...
    comma separated row of database columns<CR><LF>
    +OK - Success.<CR><LF>

### Return Value
CANAL_ERROR_SUCCESS on success or an error code on failure. 

### Description
Get data from a named table in a range to-from. All columns of the table is always returned. 




[filename](./bottom_copyright.md ':include')