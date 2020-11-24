
> Deprecated: Use [vscphlp_convertStringToEvent](vscphlp_convertstringtoevent.md)



```clike
int vscphlp_setVscpEventFromString( vscpEvent *pEvent, 
                                    const char *pstr )
```

### Parameters

#### pEvent
The VSCP event which will be written to.

#### pstr
Pointer to string buffer that contain an event in string form

    head,class,type,obid,datetime,timestamp,GUID,data1,data2,data3....

### Return Value
VSCP_ERROR_SUCCESS is returned on success. 

### Description
Set VSCP event from a string.

#### C example

```clike
vscpEvent *pEventString1 = new vscpEvent;
pEventString1->pdata = NULL;
 
if ( VSCP_ERROR_SUCCESS == vscphlp_setVscpEventFromString( pEventString1,                
       "0,10,6,0,20170102T19:32:48,0,FF:FF:FF:FF:FF:FF:FF:00:00:00:00:7F:00:01:01:FD,0x8A,0x00,0x1E" ) ) {
    printf( "OK vscphlp_setVscpEventFromString class=%d Type=%d\n", 
                   pEventString1->vscp_class, pEventString1->vscp_type );
}
else {
    printf( "\aError: vscphlp_setVscpEventFromString\n");
}
 
// Free the events
vscphlp_deleteVSCPevent( pEventString1 );
```
### See Also
[vscphlp_setVscpEventExFromString](vscphlp_setvscpeventexfromstring.md)



[filename](./bottom_copyright.md ':include')