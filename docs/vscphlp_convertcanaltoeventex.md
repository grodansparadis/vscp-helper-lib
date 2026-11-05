

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
`VSCP_ERROR_SUCCESS` (`0`) indicates success. Possible error codes: `VSCP_ERROR_ERROR`.

### Description
Convert CANAL message to VSCP ex event. 

> **Known limitation:** The VSCP implementation currently pinned by this library allocates an internal event but releases only its data, leaking the event structure on each call.

#### C example

With the helper-library headers and standard C headers included:

```clike
canalMsg message = {0};
message.id = 0x0C0A0601;
message.sizeData = 3;
message.data[0] = 11; message.data[1] = 22; message.data[2] = 33;
uint8_t interface_guid[16] = {0};
vscpEventEx event = {0};
int result = vscphlp_convertCanalToEventEx(&event, &message, interface_guid);
if (result != VSCP_ERROR_SUCCESS) {
    fprintf(stderr, "convertCanalToEventEx failed (error %d)\n", result);
} else {
    printf("class=%u type=%u nickname=%u data=%u,%u,%u\n",
           event.vscp_class, event.vscp_type, event.GUID[15],
           event.data[0], event.data[1], event.data[2]);
}
```

#### Python availability

The Python wrapper exposes this conversion, but the official `pyvscp` package does not currently provide the required `canalMsg` structure. A self-contained example using only the official bindings is therefore not available. See [bindings](bindings.md#python).

#### JavaScript availability

The official [Node.js binding](bindings.md#nodejs) does not currently expose this helper API, so there is no equivalent JavaScript example.

### See Also
[vscphlp_convertCanalToEvent](vscphlp_convertcanaltoevent.md)  [vscphlp_convertEventToCanal](vscphlp_converteventtocanal.md)  [vscphlp_convertEventExToCanal](vscphlp_converteventextocanal.md)



[filename](./bottom_copyright.md ':include')