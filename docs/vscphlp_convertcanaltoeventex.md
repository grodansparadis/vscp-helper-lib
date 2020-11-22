

```clike
int vscphlp_convertCanalToEventEx( vscpEvent *pvscpEvent, 
                                const canalMsg *pcanalMsg, 
                                unsigned char *pGUID )
```

### Parameters

#### pvscpEvent
VSCP event ex that will hold the conversion result.

#### pcanalMsg
CANAL message that should be converted.

#### pGUID
GUID for event.

### Return Value
VSCP_ERROR_SUCCESS on success. 

### Description
Convert CANAL message to VSCP ex event. 

#### C example

```clike
canalMsg canalMsg;
canalMsg.id = 0x0c0a0601;
canalMsg.sizeData = 3;
canalMsg.data[0] = 138;
canalMsg.data[1] = 0;
canalMsg.data[2] = 30;
 
vscpEventEx ex5;
if ( VSCP_ERROR_SUCCESS == vscphlp_convertCanalToEventEx( &ex5,
                                                            &canalMsg,
                                                            GUID2 ) ) {
    printf( "OK vscphlp_convertCanalToEventEx VSCP class=%d Type=%d\n",
                       ex5.vscp_class, ex5.vscp_type );
}
else {
    printf( "\aError: vscphlp_convertCanalToEvent\n");
}
```

### See Also
[vscphlp_convertCanalToEvent](vscphlp_convertcanaltoevent.md)  [vscphlp_convertEventToCanal](vscphlp_converteventtocanal.md)  [vscphlp_convertEventExToCanal](vscphlp_converteventextocanal.md)



[filename](./bottom_copyright.md ':include')