# vscphlp_getUDpFrameSizeFromEventEx

```clike
size_t vscphlp_getUDpFrameSizeFromEventEx( vscpEventEx *pEventEx )
```

### Parameters

#### pEventEx
The event.

### Return Value
As [vscphlp_getUDpFrameSizeFromEvent](vscphlp_getudpframesizefromevent.md).

### Description
As [vscphlp_getUDpFrameSizeFromEvent](vscphlp_getudpframesizefromevent.md) for a `vscpEventEx`. (The header declared the argument as `vscpEvent *` before; it is a `vscpEventEx *`.)

#### C example

```clike
size_t size = vscphlp_getUDpFrameSizeFromEventEx(&ex);
```

#### Python

The [Python binding](bindings.md#python) (pyvscphelper) has `vscphelper.getUdpFrameSizeFromEventEx`.

[filename](./bottom_copyright.md ':include')
