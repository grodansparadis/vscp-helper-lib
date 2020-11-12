

```clike
int vscphlp_writeGuidToStringEc( const vscpEventEx *pEvent, 
                                    char *pStr, 
                                    size_t len )
```

### Parameters

#### pEvent
VSCP event.

#### pStr
Pointer to GUID in string form.

#### len
Size of string buffer.

### Return Value
VSCP_ERROR_SUCCESS on success

### Description
Write GUID from VSCP event to string. 

#### C example
mmmm

```clike
if ( VSCP_ERROR_SUCCESS == vscphlp_getGuidFromStringEx( &ex3, strguid ) ) {
    vscphlp_writeGuidToStringEx( &ex3, strguid2, sizeof( strguid2 )-1 );
    printf( "GUID=%s\n", strguid2 );
}
else {
    printf( "\aError: vscphlp_writeGuidArrayToString\n");
}

```


### See Also
[vscphlp_writeGuidToString](vscphlp_writeguidtostring.md)



[filename](./bottom_copyright.md ':include')