
```clike
int vscphlp_writeVscpDataToString( const vscpEvent *pEvent, 
                                       char *pstr, 
                                       size_t len,
                                       int bUseHtmlBreak )
```

### Parameters

#### pEvent

The event that contains the data to be written

#### bUseHtmlBreak
Set to true (non zero) to use “\<br\>” instead of “\n” as linebreak in string.


### Return Value
VSCP_ERROR_SUCCESS is returned on success. 

### Description
Write VSCP data in readable form to a possibly multi line string. 

#### C example

```clike
char dataBuf[80];
 
if ( VSCP_ERROR_SUCCESS == 
    vscphlp_writeVscpDataToString( pEvent, 
                                    dataBuf, 
                                    sizeof( dataBuf )-1,
                                    0 ) ) {
    printf( "OK vscphlp_writeVscpDataToString \n%s \n", dataBuf );
}
else {
    printf( "\aError: vscphlp_writeVscpDataToString\n");
}
```

[filename](./bottom_copyright.md ':include')