

```clike
int vscphlp_convertStringToEventEx( vscpEventEx *pEventEx, 
                                    const char *pstr )
```

> Added in 14.0.2

### Parameters

#### pEventEx
The VSCP event ex which will be written to.

#### pstr
Pointer to string buffer that contain an event in string form

    head,class,type,obid,datetime,timestamp,GUID,data1,data2,data3....

### Return Value
VSCP_ERROR_SUCCESS is returned on success. 

### Description
Set VSCP event from a string.

#### C example

```clike
vscpEventEx ex;
 
if ( VSCP_ERROR_SUCCESS == vscphlp_convertStringToEventEx( &ex,                
       "0,10,6,0,20170102T19:32:48,0,FF:FF:FF:FF:FF:FF:FF:00:00:00:00:7F:00:01:01:FD,0x8A,0x00,0x1E" ) ) {
    printf( "OK vscphlp_convertStringToEventEx class=%d Type=%d\n", 
                   ex.vscp_class, ex.vscp_type );
}
else {
    printf( "\aError: vscphlp_convertStringToEventEx\n");
}
 
// Free the events
vscphlp_deleteVSCPeventEx( pEventString1 );
```
### See Also
[vscphlp_convertStringToEvent](vscphlp_convertstringtoevent.md)



[filename](./bottom_copyright.md ':include')