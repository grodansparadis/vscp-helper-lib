

```clike
double 
vscphlp_getDataCodingNormalizedInteger(const unsigned char *pCode, 
                                        int size )
```

### Parameters

#### pCode
A pointer to the data coding byte of the measurement data.

#### size
The size of the measurement data including the data coding byte.

### Return Value
Returns the decoded `double`, not an error code. A null input or rejected length returns
`0.0`, which is also a valid decoded value.

### Description
Get measurement data that is coded as a normalized integer as a floating point value.

#### C example

```clike
unsigned char data[] = {0x89, 0x82, 0x01, 0x36};
double value = vscphlp_getDataCodingNormalizedInteger(data, sizeof(data));
printf("Decoded value: %.2f\n", value); // 3.10
```



#### Python example

Using the official [Python helper binding](bindings.md#python):

```python
import vscp
import vscphelper

data = bytearray([0x80, 0x02, 0x1B, 0x22])
print(vscphelper.getDataCodingNormalizedInteger(data))
```

#### JavaScript availability

The official [Node.js binding](bindings.md#nodejs) does not currently expose this helper API, so there is no equivalent JavaScript example.

[filename](./bottom_copyright.md ':include')
