


```clike
bool vscp_writeFilterToString( vscpEventFilter *pFilter, 
                                char *strFilter);
```

### Parameters

#### pFilter
Filter structure to write filter to.

#### strFilter
Will get the filter in string form priority,class,type,GUID. Must be at least 65 bytes.

    filter-priority, filter-class, filter-type, filter-GUID

### Return Value
VSCP_ERROR_SUCCESS on success.

### Description
Write a filter on comma separated form to a string (priority,class,type,GUID). 

#### C example

```clike
if ( VSCP_ERROR_SUCCESS != vscphlp_writeFilterToString( &filter, str ) ) {
    printf( "\aError: vscphlp_writeFilterToString\n");   
}
```

### See Also
[vscphlp_readFilterFromString](vscphlp_readfilterfromstring.md)



[filename](./bottom_copyright.md ':include')