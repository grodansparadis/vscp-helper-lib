

```clike
int vscphlp_getVSCPMeasurementFloat64AsString(const vscpEvent *pEvent, 
                                    char *pStrResult, 
                                    size_t len )
```

### Parameters

#### pEvent
The event containing the measurement data.

#### pStrResult
Buffer that will receive the result as a null-terminated string.

#### len
The size of the buffer.

### Return Value
VSCP_ERROR_SUCCESS is returned on success.

> **Known limitation:** The implementation interprets the data as an aligned `double` in host byte order. Do not pass an arbitrary wire-format buffer without accounting for alignment and byte order.

### Description
This method displays data stored in 64-bit floating-point form ([IEEE 754](https://en.wikipedia.org/wiki/IEEE_floating_point)) as a string.

#### C example

With the helper-library headers and standard C headers included:

```clike
double encoded_value = 3.14;
vscpEvent event = {0};
event.vscp_class = 60;
event.sizeData = sizeof(encoded_value);
event.pdata = (uint8_t *)&encoded_value;
char text[64] = {0};
int result = vscphlp_getVSCPMeasurementFloat64AsString(&event, text, sizeof(text) - 1);
if (result != VSCP_ERROR_SUCCESS) {
    fprintf(stderr, "getVSCPMeasurementFloat64AsString failed (error %d)\n", result);
} else {
    printf("%s\n", text);
}
```

#### Python availability

The current official Python helper wrapper does not expose this specific function.

#### JavaScript availability

The official [Node.js binding](bindings.md#nodejs) does not currently expose this helper API, so there is no equivalent JavaScript example.

[filename](./bottom_copyright.md ':include')