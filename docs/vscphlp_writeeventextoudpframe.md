# vscphlp_writeEventExToUdpFrame

```clike
int vscphlp_writeEventExToUdpFrame( unsigned char *frame, size_t len,
                                    unsigned char pkttype, const vscpEventEx *pEventEx )
```

### Parameters

#### frame
Buffer of at least [vscphlp_getUDpFrameSizeFromEventEx](vscphlp_getudpframesizefromeventex.md) bytes.

#### len
Size of the buffer.

#### pkttype
As for [vscphlp_writeEventToUdpFrame](vscphlp_writeeventtoudpframe.md).

#### pEventEx
The event.

### Return Value
As [vscphlp_writeEventToUdpFrame](vscphlp_writeeventtoudpframe.md).

### Description
As [vscphlp_writeEventToUdpFrame](vscphlp_writeeventtoudpframe.md) for a `vscpEventEx`.

#### C example

```clike
int rv = vscphlp_writeEventExToUdpFrame(frame, size, 0, &ex);
```

#### Python

The [Python binding](bindings.md#python) (pyvscphelper) has `vscphelper.writeEventExToUdpFrame`.

[filename](./bottom_copyright.md ':include')
