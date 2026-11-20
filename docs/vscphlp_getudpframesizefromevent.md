# vscphlp_getUDpFrameSizeFromEvent

```clike
size_t vscphlp_getUDpFrameSizeFromEvent( vscpEvent *pEvent )
```

### Parameters

#### pEvent
The event.

### Return Value
The size in bytes of the (unencrypted) frame for the event: 38 + the data size. 0 for NULL or an invalid event.

### Description
Gets the buffer size needed by [vscphlp_writeEventToUdpFrame](vscphlp_writeeventtoudpframe.md).

#### C example

```clike
size_t size = vscphlp_getUDpFrameSizeFromEvent(pEvent);
```

#### Python

The [Python binding](bindings.md#python) (pyvscphelper) has `vscphelper.getUdpFrameSizeFromEvent`.

[filename](./bottom_copyright.md ':include')
