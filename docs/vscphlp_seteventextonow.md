# vscphlp_setEventExToNow

```clike
int vscphlp_setEventExToNow( vscpEventEx *pEventEx )
```

### Parameters

#### pEventEx
The event.

### Return Value
`VSCP_ERROR_SUCCESS`, `VSCP_ERROR_INVALID_POINTER`, `VSCP_ERROR_ERROR`.

### Description
As [vscphlp_setEventToNow](vscphlp_seteventtonow.md) for a `vscpEventEx`.

#### C example

```clike
vscpEventEx ex = {0};
vscphlp_setEventExToNow(&ex);
```

#### Python

The [Python binding](bindings.md#python) (pyvscphelper) has `vscphelper.setEventExToNow`.

[filename](./bottom_copyright.md ':include')
