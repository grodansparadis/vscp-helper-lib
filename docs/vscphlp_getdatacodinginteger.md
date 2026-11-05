

```clike
unsigned long long 
vscphlp_getDataCodingInteger(const unsigned char *pCode, 
                            int size )
```

### Parameters

#### pCode
A pointer to the data coding byte of the measurement data.

#### size
The size of the measurement data including the data coding byte.

### Return Value
Returns the decoded integer as `unsigned long long`, not an error code. Negative decoded
values are converted to unsigned. A null input or an 8-bit length below two returns `0`,
which is also a valid decoded value. The supplied size is converted to an 8-bit length.

### Description
Get measurement data encoded as a signed integer (1-7 bytes) as a 64-bit integer.

#### C example

```clike
unsigned char data[] = {0x60, 0x01, 0x02};
unsigned long long value = vscphlp_getDataCodingInteger(data, sizeof(data));
printf("Decoded value: %llu\n", value); // 258
```



#### Python example

Using the official [Python helper binding](bindings.md#python):

```python
import vscp
import vscphelper

data = bytearray([0x60, 0x01, 0x02])
print(vscphelper.getDataCodingInteger(data))
```

#### JavaScript availability

The official [Node.js binding](bindings.md#nodejs) does not currently expose this helper API, so there is no equivalent JavaScript example.

[filename](./bottom_copyright.md ':include')