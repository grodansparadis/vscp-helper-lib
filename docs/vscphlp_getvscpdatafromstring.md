# vscphlp_getVscpDataFromString

```clike
int vscphlp_getVscpDataFromString( vscpEvent *pEvent, const char *pstr )
```

### Parameters

#### pEvent
Event that gets the data. Its `pdata` is replaced (allocated by the library; free the event with [vscphlp_deleteVSCPevent](vscphlp_deletevscpevent.md)).

#### pstr
Comma separated data bytes, decimal or hexadecimal, for example `1,2,0x10,255`.

### Return Value
`VSCP_ERROR_SUCCESS`, `VSCP_ERROR_INVALID_POINTER`, `VSCP_ERROR_ERROR` if the string is not valid.

### Description
Sets the data of an event from a string. The same as [vscphlp_setVscpDataFromString](vscphlp_setvscpdatafromstring.md).

#### C example

```clike
vscpEvent *pEvent = /* event allocated with new */;
int rv = vscphlp_getVscpDataFromString(pEvent, "1,2,0x10,255");
```

#### Python

The [Python binding](bindings.md#python) (pyvscphelper) has `vscphelper.getVscpDataFromString`.

[filename](./bottom_copyright.md ':include')
