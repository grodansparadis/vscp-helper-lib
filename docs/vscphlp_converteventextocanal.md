

## vscphlp_xxx

```clike
int vscphlp_convertEventExToCanal( canalMsg *pcanalMsg,
                                       const vscpEventEx *pvscpEvent )
```

### Parameters

#### pcanalMsg
CANAL message that will hold result.

#### pvscpEvent
VSCP ex event that will be converted.


### Return Value
`VSCP_ERROR_SUCCESS` (`0`) indicates success. Possible error codes: `VSCP_ERROR_ERROR`.

### Description
Convert VSCP event ex to CANAL message. 

#### C example

With the helper-library headers and standard C headers included:

```clike
vscpEventEx event = {0};
event.vscp_class = 10; event.vscp_type = 6; event.GUID[15] = 1;
event.sizeData = 3;
event.data[0] = 11; event.data[1] = 22; event.data[2] = 33;
vscphlp_setVscpPriorityEx(&event, 3);
canalMsg message = {0};
int result = vscphlp_convertEventExToCanal(&message, &event);
if (result != VSCP_ERROR_SUCCESS) {
    fprintf(stderr, "convertEventExToCanal failed (error %d)\n", result);
} else {
    printf("id=0x%08lX data=%u,%u,%u\n", (unsigned long)message.id,
           message.data[0], message.data[1], message.data[2]);
}
```

#### Python availability

The Python wrapper exposes this conversion, but the official `pyvscp` package does not currently provide the required `canalMsg` structure. A self-contained example using only the official bindings is therefore not available. See [bindings](bindings.md#python).

#### JavaScript availability

The official [Node.js binding](bindings.md#nodejs) does not currently expose this helper API, so there is no equivalent JavaScript example.

### See Also
[vscphlp_convertCanalToEvent](vscphlp_convertcanaltoevent.md)   [vscphlp_convertCanalToEventEx](vscphlp_convertcanaltoeventex.md)    [vscphlp_convertEventToCanal](vscphlp_converteventtocanal.md)  



[filename](./bottom_copyright.md ':include')