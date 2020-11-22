

```clike
bool vscphlp_convertEventToCanal( canalMsg *pcanalMsg, 
                        const vscpEvent *pvscpEvent )
```

```python
xxxx
```

### Parameters

#### pcanalMsg
CANAL message that will hold result.

#### pvscpEvent
VSCP event that will be converted.

### Return Value
VSCP_ERROR_SUCCESS on succes. 

### Description
Convert VSCP event to CANAL message. 

#### C example

```clike
if ( VSCP_ERROR_SUCCESS == vscphlp_convertEventToCanal( &canalMsg, pEvent ) ) {
    printf( "OK vscphlp_convertEventToCanal id=%08X\n", canalMsg.id );
}
else {
    printf( "\aError: vscphlp_convertEventToCanal\n");
}
```

### See Also
[vscphlp_convertCanalToEvent](vscphlp_convertcanaltoevent.md)  
[vscphlp_convertCanalToEventEx](vscphlp_convertcanaltoeventex.md)



[filename](./bottom_copyright.md ':include')