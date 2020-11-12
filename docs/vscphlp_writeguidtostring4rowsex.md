

```clike
int vscphlp_writeGuidToString4RowsEx( const vscpEventEx *pEvent, 
                                        char *strGUID,
                                        size_t len )
```

### Parameters

#### pEvent
VSCP event.

#### strGUID
String that get formatted GUID.

#### len
Size of string buffer.

### Return Value
VSCP_ERROR_SUCCESS on success. 

### Description
Write GUID from VSCP event to string with four bytes on each row separated by “\r\n”. 

#### C example

```clike
if ( VSCP_ERROR_SUCCESS == vscphlp_writeGuidToString4RowsEx( &ex3, strguid2, sizeof( strguid2 )-1 ) ) {
    printf( "GUID\n%s\n", strguid2 );
}
else {
    printf( "Error: vscphlp_writeGuidArrayToString\n");
}
```


### See Also
[vscphlp_writeGuidToString4Rows](vscphlp_writeguidtostring4rows.md)



[filename](./bottom_copyright.md ':include')