

```clike
int vscphlp_convertCanalToEvent( vscpEvent *pvscpEvent,
                                    const canalMsg *pcanalMsg,
                                    unsigned char *pGUID )
```

### Parameters

#### pvscpEvent
VSCP event that will hold the conversion result.

#### pcanalMsg
CANAL message that should be converted.

#### pGUID
GUID for event.

### Return Value
`VSCP_ERROR_SUCCESS` (`0`) indicates success. Possible error codes: `VSCP_ERROR_ERROR`.

### Description
Convert CANAL message to VSCP event. 

#### C example

With the helper-library headers and standard C headers included:

```clike
canalMsg message = {0};
message.id = 0x0C0A0601;
message.sizeData = 3;
message.data[0] = 11; message.data[1] = 22; message.data[2] = 33;
uint8_t interface_guid[16] = {0};
vscpEvent *event = NULL;
int result = vscphlp_newVSCPevent(&event);
if (result != VSCP_ERROR_SUCCESS || event == NULL) {
    fprintf(stderr, "Could not allocate event (error %d)\n", result);
} else {
    result = vscphlp_convertCanalToEvent(event, &message, interface_guid);
    if (result != VSCP_ERROR_SUCCESS) {
        fprintf(stderr, "convertCanalToEvent failed (error %d)\n", result);
    } else {
        printf("class=%u type=%u nickname=%u data=%u,%u,%u\n",
               event->vscp_class, event->vscp_type, event->GUID[15],
               event->pdata[0], event->pdata[1], event->pdata[2]);
    }
    vscphlp_deleteVSCPevent_v2(&event);
}
```

#### Python availability

The Python wrapper exposes this conversion, but the official `pyvscp` package does not currently provide the required `canalMsg` structure. A self-contained example using only the official bindings is therefore not available. See [bindings](bindings.md#python).

#### JavaScript availability

The official [Node.js binding](bindings.md#nodejs) does not currently expose this helper API, so there is no equivalent JavaScript example.

### See Also
[vscphlp_convertCanalToEventEx](vscphlp_convertcanaltoeventex.md)  [vscphlp_convertEventToCanal](vscphlp_converteventtocanal.md)  [vscphlp_convertEventExToCanal](vscphlp_converteventextocanal.md)



[filename](./bottom_copyright.md ':include')