

```clike
int vscphlp_convertEventToCanal( canalMsg *pcanalMsg,
                        const vscpEvent *pvscpEvent )
```


### Parameters

#### pcanalMsg
CANAL message that will hold result.

#### pvscpEvent
VSCP event that will be converted.

### Return Value
`VSCP_ERROR_SUCCESS` (`0`) indicates success. Possible error codes: `VSCP_ERROR_ERROR`.

### Description
Convert VSCP event to CANAL message. 

#### C example

With the helper-library headers and standard C headers included:

```clike
uint8_t data[] = {11, 22, 33};
vscpEvent event = {0};
event.vscp_class = 10; event.vscp_type = 6; event.GUID[15] = 1;
event.sizeData = sizeof(data); event.pdata = data;
vscphlp_setVscpPriority(&event, 3);
canalMsg message = {0};
int result = vscphlp_convertEventToCanal(&message, &event);
if (result != VSCP_ERROR_SUCCESS) {
    fprintf(stderr, "convertEventToCanal failed (error %d)\n", result);
} else {
    printf("id=0x%08lX data=%u,%u,%u\n", (unsigned long)message.id,
           message.data[0], message.data[1], message.data[2]);
}
```

#### Python availability

The Python wrapper exposes this conversion, but the official `pyvscp` package does not currently provide the required `canalMsg` structure. A self-contained example using only the official bindings is therefore not available. See [bindings](bindings.md#python).

#### JavaScript availability

See the [Node.js binding](bindings.md#nodejs) for C API access and native library availability.

### See Also
[vscphlp_convertCanalToEvent](vscphlp_convertcanaltoevent.md)  
[vscphlp_convertCanalToEventEx](vscphlp_convertcanaltoeventex.md)



[filename](./bottom_copyright.md ':include')