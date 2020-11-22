

## vscphlp_xxx

```clike
bool vscphlp_convertEventExToCanal( canalMsg *pcanalMsg, 
                                       const vscpEventEx *pvscpEvent )
```

### Parameters

#### pcanalMsg
CANAL message that will hold result.

#### pvscpEvent
VSCP ex event that will be converted.


### Return Value
VSCP_ERROR_SUCCESS on succes. 

### Description
Convert VSCP event ex to CANAL message. 

#### C example

```clike
if ( VSCP_ERROR_SUCCESS == vscphlp_convertEventExToCanal( &canalMsg, &ex5 ) ) {
    printf( "OK vscphlp_convertEventExToCanal id=%08X\n", canalMsg.id );
}
else {
    printf( "\aError: vscphlp_convertEventExToCanal\n");
}
```

### See Also
[vscphlp_convertCanalToEvent](vscphlp_convertcanaltoevent.md)   [vscphlp_convertCanalToEventEx](vscphlp_convertcanaltoeventex.md)    [vscphlp_convertEventToCanal](vscphlp_converteventtocanal.md)  



[filename](./bottom_copyright.md ':include')