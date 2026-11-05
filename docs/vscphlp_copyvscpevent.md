

```clike
int vscphlp_copyVSCPEvent( vscpEvent *pEventTo, 
                              const vscpEvent *pEventFrom )
```

### Parameters

#### pEventTo
VSCP event that will receive the result.

#### pEventFrom
VSCP event that should be copied


### Return Value
`VSCP_ERROR_SUCCESS` (`0`) indicates success. Possible error codes: `VSCP_ERROR_ERROR`.

### Description
Copy a VSCP event to another event.

#### C example

```clike
vscpEvent source = {0};
uint8_t data[] = {0xAA, 0x55};
source.vscp_class = 10;
source.vscp_type = 6;
source.sizeData = sizeof(data);
source.pdata = data;

vscpEvent *destination = NULL;
int result = vscphlp_newVSCPevent(&destination);
if (result != VSCP_ERROR_SUCCESS || destination == NULL) {
    fprintf(stderr, "Could not allocate event (error %d)\n", result);
} else {
    result = vscphlp_copyVSCPEvent(destination, &source);
    if (result != VSCP_ERROR_SUCCESS) {
        fprintf(stderr, "copyVSCPEvent failed (error %d)\n", result);
    } else {
        printf("Copied data: %02X %02X\n",
               destination->pdata[0], destination->pdata[1]);
    }
    vscphlp_deleteVSCPevent_v2(&destination);
}
```

#### Python example

Using the official [Python helper binding](bindings.md#python):

```python
import vscp
import vscphelper

source = vscp.vscpEvent()
source.vscpclass = 20
source.vscptype = 9
destination = vscp.vscpEvent()
result = vscphelper.copyVSCPEvent(destination, source)
if result != vscp.VSCP_ERROR_SUCCESS:
    raise RuntimeError("copyVSCPEvent failed (error {})".format(result))
print(destination.vscpclass, destination.vscptype)
```

#### JavaScript availability

The official [Node.js binding](bindings.md#nodejs) does not currently expose this helper API, so there is no equivalent JavaScript example.

[filename](./bottom_copyright.md ':include')