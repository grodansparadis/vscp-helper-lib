


```clike
int vscphlp_convertEventToString( const vscpEvent *pEvent, 
                                    char *pstr, 
                                    size_t len )
```

> Added in 14.0.2

### Parameters

#### pEvent
The VSCP event which will be written to the string buffer.

#### pstr
Pointer to string buffer that will receive result.

#### len
Size of buffer.

### Return Value
VSCP_ERROR_SUCCESS is returned on success. 

### Description
Write VSCP event content to a string. 

#### C example

```clike
char eventBuf[128];
if ( VSCP_ERROR_SUCCESS == vscphlp_convertEventToString( pEvent, eventBuf, sizeof( eventBuf )-1 ) ) {
    printf( "OK vscphlp_convertEventToString Event = %s\n", eventBuf );    
}
else {
    printf( "\aError: vscphlp_convertEventToString\n");
}
```

### See Also

[vscphlp_writeVscpEventExToString](vscphlp_writevscpeventextostring.md)



[filename](./bottom_copyright.md ':include')
