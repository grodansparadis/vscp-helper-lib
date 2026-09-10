

```clike
int vscphlp_parseGuid( uint8_t* pGUID, const char* pStr )
```

```python
int pyvscphlp_parseGuid( guid, str )
```

### Parameters

#### pGUID
Pointer to GUID array.

#### pStr
Pointer to GUID in string form.

#### Return Value
VSCP_ERROR_SUCCESS on success


### Description
Parse extended GUID from string to VSCP GUID array. Supports all valid forms of GUID strings. For a list of valid formats [see](https://grodansparadis.github.io/vscp-doc-spec/#/./vscp_globally_unique_identifiers).

#### C example


```clike
if ( VSCP_ERROR_SUCCESS == vscphlp_parseGuid( pGUID, strguid ) ) {
   vscphlp_writeGuidToString( pEvent, strguid2, sizeof( strguid2 )-1 );
   printf( "GUID=%s\n", strguid2 );
}
else {
    printf( "\aError: vscphlp_parseGuid\n");
}
```

### See Also
[vscphlp_writeGuidToStringEx](vscphlp_writeguidtostringex.md)



[filename](./bottom_copyright.md ':include')