


```clike
int vscphlp_tableList( unsigned char **pLists )
```

### Parameters

#### pLists
List of null terminated strings that will get filled with table names. The list is allocated on the heap and must be freed by the user. If no result is returned set to a NULL pointer.


### Return Value
CANAL_ERROR_SUCCESS on success or an error code on failure.

### Description
Get a list of all defined tables. 




[filename](./bottom_copyright.md ':include')