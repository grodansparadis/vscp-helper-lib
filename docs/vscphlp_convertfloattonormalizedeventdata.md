

```clike
int vscphlp_convertFloatToNormalizedEventData( 
                            unsigned char *pdata,        unsigned short *psize,    
                            double value, 
                            unsigned char unit,
                            unsigned char sensoridx )
```

### Parameters

#### pdata
Pointer to a data buffer of at least eight bytes that will receive the result.

#### psize
The size of the written data will be returned here.

#### value
Floating point value to write as a 64-bit double.

#### unit
A unit value from 0 to 3.

#### sensoridx
A sensor index from 0 to 7.

### Return Value
VSCP_ERROR_SUCCESS is returned on success.

### Description
Write a 64-bit floating point value as event measurement data. 

#### C example

```clike
unsigned char data[8] = {0};
unsigned short size = 0;
int result = vscphlp_convertFloatToNormalizedEventData(data, &size, 3.14, 2, 1);
if (result != VSCP_ERROR_SUCCESS) {
    fprintf(stderr, "convertFloatToNormalizedEventData failed (error %d)\n", result);
} else {
    for (unsigned short i = 0; i < size; ++i) {
        printf("%02X%s", data[i], i + 1 == size ? "\n" : " ");
    }
}
```

#### Python example

Using the official [Python helper binding](bindings.md#python):

```python
import vscp
import vscphelper

result, data = vscphelper.convertFloatToNormalizedEventData(3.14, 2, 1)
if result != vscp.VSCP_ERROR_SUCCESS:
    raise RuntimeError("convertFloatToNormalizedEventData failed (error {})".format(result))
if not data:
    raise RuntimeError("No measurement data returned")
print(list(data))
```

#### JavaScript availability

The official [Node.js binding](bindings.md#nodejs) does not currently expose this helper API, so there is no equivalent JavaScript example.

[filename](./bottom_copyright.md ':include')