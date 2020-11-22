

```clike
int vscphlp_setEventExDateTimeBlockToNow( vscpEventEx *pEventEx )
```

### Parameters

#### pEventEx
Pointer to event that willhave its daettime block set to the current time.

### Return Value
VSCP_ERROR_SUCCESS is returned on success. 

### Description
Get date/time block for an ex event. 

#### C example

```clike
vscpEventEx *pEventEx;
vscphlp_setEventExDateTimeBlockToNow( pEventEx );
```

### See Also
[vscphlp_setEventDateTimeBlockToNow](vscphlp_seteventdatetimeblocktonow.md)



[filename](./bottom_copyright.md ':include')