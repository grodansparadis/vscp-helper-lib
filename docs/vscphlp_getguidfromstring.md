

```clike
int vscphlp_getGuidFromString( vscpEvent *pEvent, 
                            const char *pGUID )
```
### Parameters

#### pEvent
VSCP event.

#### pGUID
Pointer to a GUID in string form.

### Return Value
`VSCP_ERROR_SUCCESS` (`0`) indicates success. Possible error codes: `VSCP_ERROR_ERROR`.

### Description
Write GUID into VSCP event from a string. 

#### C example

```clike
vscpEvent event = {0};
const char *guid = "FF:FF:FF:FF:FF:FF:FF:F5:00:00:00:00:00:00:00:01";
int result = vscphlp_getGuidFromString(&event, guid);
if (result != VSCP_ERROR_SUCCESS) {
    fprintf(stderr, "getGuidFromString failed (error %d)\n", result);
} else {
    printf("Last GUID byte: %02X\n", event.GUID[15]);
}
```

#### Python example

Using the official [Python helper binding](bindings.md#python):

```python
import vscp
import vscphelper

event = vscp.vscpEvent()
result = vscphelper.getGuidFromString(event, "FF:FF:FF:FF:FF:FF:FF:F5:00:00:00:00:00:00:00:01")
if result != vscp.VSCP_ERROR_SUCCESS:
    raise RuntimeError("getGuidFromString failed (error {})".format(result))
print(list(event.guid))
```

#### JavaScript availability

The official [Node.js binding](bindings.md#nodejs) does not currently expose this helper API, so there is no equivalent JavaScript example.

### See Also
[vscphlp_getGuidFromString](vscphlp_getguidfromstring.md)



[filename](./bottom_copyright.md ':include')