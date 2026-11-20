# vscphlp_writeEventToUdpFrame

```clike
int vscphlp_writeEventToUdpFrame( unsigned char *frame, size_t len,
                                  unsigned char pkttype, const vscpEvent *pEvent )
```

### Parameters

#### frame
Buffer of at least [vscphlp_getUDpFrameSizeFromEvent](vscphlp_getudpframesizefromevent.md) bytes.

#### len
Size of the buffer.

#### pkttype
The low nibble is the encryption (0 none, 1-3 AES); the high nibble of the first frame byte is set to the event frame type (1).

#### pEvent
The event.

### Return Value
`VSCP_ERROR_SUCCESS`, `VSCP_ERROR_INVALID_POINTER`, `VSCP_ERROR_ERROR` if the buffer is too small or the event is invalid.

### Description
Writes an event as a VSCP (version 0) frame, as sent over UDP and multicast: type byte, head, timestamp, date/time, class, type, GUID, data size, data and CRC, numbers MSB first. Encrypt it with [vscphlp_encryptVscpUdpFrame](vscphlp_encryptvscpudpframe.md).

#### C example

```clike
size_t size = vscphlp_getUDpFrameSizeFromEvent(pEvent);
unsigned char *frame = malloc(size);
int rv = vscphlp_writeEventToUdpFrame(frame, size, 0, pEvent);
```

#### Python

The [Python binding](bindings.md#python) (pyvscphelper) has `vscphelper.writeEventToUdpFrame`.

[filename](./bottom_copyright.md ':include')
