

```clike
int vscphlp_readFilterFromString( vscpEventFilter *pFilter, 
                            char *strFilter )
```

### Parameters

#### pFilter
Filter structure to write filter to.

#### strFilter
Filter in string form

    filter-priority, filter-class, filter-type, filter-GUID

as in this example

    1,0x0000,0x0006,ff:ff:ff:ff:ff:ff:ff:01:00:00:00:00:00:00:00:00

and all is optional but if given must be given in order. This means

    1,0x0000,0x0006

for example is OK setting GUID to all zeros.


### Return Value
VSCP_ERROR_SUCCESS on success. 

### Description
Read a filter from a string. If strFilter is an empty string all elements in filter will be set to zero. Arguments is

    priority,class,type,GUID 

and all is optional but if given must be given in order. 

#### C example

```clike
if ( VSCP_ERROR_SUCCESS != vscphlp_readFilterFromString( &filter, 
                "1,0x0000,0x0006,ff:ff:ff:ff:ff:ff:ff:01:00:00:00:00:00:00:00:00" ) ) {
    printf( "\aError: vscphlp_readFilterFromString\n");   
}
```

### See Also
[vscphlp_writeFilterToString](vscphlp_writefiltertostring.md)



[filename](./bottom_copyright.md ':include')