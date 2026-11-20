# vscphlp_setEventToNow

```clike
int vscphlp_setEventToNow( vscpEvent *pEvent )
```

### Parameters

#### pEvent
The event.

### Return Value
`VSCP_ERROR_SUCCESS`, `VSCP_ERROR_INVALID_POINTER`, `VSCP_ERROR_ERROR`.

### Description
Sets the date/time of the event (year, month, day, hour, minute, second) to the current UTC time and sets the timestamp. See also [vscphlp_setEventDateTimeBlockToNow](vscphlp_seteventdatetimeblocktonow.md).

#### C example

```clike
vscpEvent ev = {0};
vscphlp_setEventToNow(&ev);
```

#### Python

The [Python binding](bindings.md#python) (pyvscphelper) has `vscphelper.setEventToNow`.

[filename](./bottom_copyright.md ':include')
