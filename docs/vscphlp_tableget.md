


```clike
int vscphlp_tableGet( const unsigned char *pName, 
                const char *pFrom, 
                const char *pTo,
                unsigned char **pResultArray,
                BOOL bFull )
```

### Parameters

#### tblName
Name of an existing table.

#### from
Datetime from which data should be fetched. Should be given on ISO 8601 format YY-MM-DDTHH:MM:SS.

#### to
Datetime up to which data is fetched. Should be given on ISO 8601 format YY-MM-DDTHH:MM:SS.

#### pResultArray
List of null terminated strings that will get filled with rows (if any) from the table. The list is allocated on the heap and must be freed by the user. If no result is returned set to a NULL pointer.

    YY-MM-DDTHH:MM:SSsss, value1[,other fields]<CR><LF>
    YY-MM-DDTHH:MM:SSsss, value2[,other fields]<CR><LF>
    YY-MM-DDTHH:MM:SSsss, value3[,other fields]<CR><LF>
    ...
    YY-MM-DDTHH:MM:SS, valuen[,other fields]<CR><LF>

#### bFull
If TRUe (!=0) all fields of a table row is returned (other fields above) in a comma separated list. Note that datetime is always listed first followed by value regardless of how the columns of the table is arranged.


### Return Value
CANAL_ERROR_SUCCESS on success or an error code on failure.

### Description
Get data from a named table in a range to-from. One can fetch all columns of the table (bFull) or just datetime and value (default). 


### See Also
[vscphlp_tableGetRaw](vscphlp_tablegetraw.md)



[filename](./bottom_copyright.md ':include')