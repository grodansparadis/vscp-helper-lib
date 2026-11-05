

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

See the [Node.js binding](bindings.md#nodejs) for C API access and native library availability.

### See Also
[vscphlp_getGuidFromString](vscphlp_getguidfromstring.md)



[filename](./bottom_copyright.md ':include')