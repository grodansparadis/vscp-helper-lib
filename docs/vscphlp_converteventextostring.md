


```clike
int vscphlp_convertEventExToString( const vscpEventEx *pEvent, 
                                    char *pstr, 
                                    size_t len )
```

> Added in 14.0.2

### Parameters

#### pEventEx
The VSCP event ex which will be written to the string buffer.

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
if ( VSCP_ERROR_SUCCESS == vscphlp_convertEventExToString( pEventEx, eventBuf, sizeof( eventBuf )-1 ) ) {
    printf( "OK vscphlp_convertEventExToString Event = %s\n", eventBuf );    
}
else {
    printf( "\aError: vscphlp_convertEventExToString\n");
}
```

### See Also

[vscphlp_convertEventToString](vscphlp_converteventtostring.md)



[filename](./bottom_copyright.md ':include')
