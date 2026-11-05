

```clike
int vscphlp_getGuidFromStringEx( vscpEventEx *pEvent,
                            const char * pGUID )
```

### Parameters

#### pEvent
VSCP event ex.

#### pGUID
Pointer to a GUID in string form.


### Return Value
`VSCP_ERROR_SUCCESS` (`0`) indicates success. Possible error codes: `VSCP_ERROR_ERROR`.

### Description
Write GUID into VSCP event ex from a string. 

> **Known limitation:** The VSCP implementation currently pinned by this
> library can stop after parsing the first GUID byte while returning success.
> Do not rely on this function until the implementation is corrected.

The C and Python APIs use the same implementation and have this limitation.

#### JavaScript availability

The official [Node.js binding](bindings.md#nodejs) does not currently expose this helper API, so there is no equivalent JavaScript example.

### See Also
[vscphlp_getGuidFromString](vscphlp_getguidfromstring.md)



[filename](./bottom_copyright.md ':include')