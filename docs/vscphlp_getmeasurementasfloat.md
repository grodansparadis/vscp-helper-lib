

```clike
int vscphlp_getMeasurementAsFloat(const unsigned char *pData, 
                                     unsigned char length,
                                     float *pResult )
```

### Parameters

#### pdata
Pointer to VSCP event data for measurement event.

### Return Value
`VSCP_ERROR_SUCCESS` (`0`) indicates success. Possible error codes: `VSCP_ERROR_ERROR`.

### Description
Get a coded measurement as a float. 

#### C example

```clike
const unsigned char data[] = {0xB1, 0x40, 0x48, 0xF5, 0xC3};
float value = 0.0f;
int result = vscphlp_getMeasurementAsFloat(data, sizeof(data), &value);
if (result != VSCP_ERROR_SUCCESS) {
    fprintf(stderr, "getMeasurementAsFloat failed (error %d)\n", result);
} else {
    printf("%.2f\n", value);
}
```

#### Python example

```python
import vscp
import vscphelper

data = bytearray([0xB1, 0x40, 0x48, 0xF5, 0xC3])
result, value = vscphelper.getMeasurementAsFloat(data)
if result != vscp.VSCP_ERROR_SUCCESS:
    raise RuntimeError("getMeasurementAsFloat failed (error {})".format(result))
print("{:.2f}".format(value))
```

The four float bytes in this example are in big-endian order.


#### JavaScript availability

The official [Node.js binding](bindings.md#nodejs) does not currently expose this helper API, so there is no equivalent JavaScript example.

[filename](./bottom_copyright.md ':include')
