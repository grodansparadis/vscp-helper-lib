

```clike
int vscphlp_parseGuid( uint8_t* pGUID, const char* pStr )
```


### Parameters

#### pGUID
Pointer to GUID array.

#### pStr
Pointer to a GUID in string form.

### Return Value
`VSCP_ERROR_SUCCESS` (`0`) indicates success. Possible error codes:
`VSCP_ERROR_INVALID_POINTER`, `VSCP_ERROR_INVALID_SYNTAX`.

The parser may accept abbreviated forms; success does not imply strict validation of every
character.

### Description
Parse extended GUID from string to VSCP GUID array. Supports all valid forms of GUID strings. For a list of valid formats [see](https://grodansparadis.github.io/vscp-doc-spec/#/./vscp_globally_unique_identifiers).

#### C example

```clike
uint8_t guid[16] = {0};
int result = vscphlp_parseGuid(
    guid, "FF:FF:FF:FF:FF:FF:FF:F5:00:00:00:00:00:00:00:01");
if (result != VSCP_ERROR_SUCCESS) {
    fprintf(stderr, "parseGuid failed (error %d)\n", result);
} else {
    for (size_t i = 0; i < sizeof(guid); ++i) {
        printf("%02X%s", guid[i], i + 1 == sizeof(guid) ? "\n" : ":");
    }
}
```

#### Python example

The wrapper returns the status and the parsed GUID:

```python
import vscp
import vscphelper

result, guid = vscphelper.parseGuid("FF:FF:FF:FF:FF:FF:FF:F5:00:00:00:00:00:00:00:01")
if result != vscp.VSCP_ERROR_SUCCESS:
    raise RuntimeError("parseGuid failed (error {})".format(result))
print(list(guid))
```

#### JavaScript availability

See the [Node.js binding](bindings.md#nodejs) for C API access and native library availability.

### See Also
[vscphlp_writeGuidToStringEx](vscphlp_writeguidtostringex.md)



[filename](./bottom_copyright.md ':include')