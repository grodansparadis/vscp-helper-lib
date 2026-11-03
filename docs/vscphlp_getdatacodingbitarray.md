

```clike
unsigned long long 
vscphlp_getDataCodingBitArray( const unsigned char *pNorm,
                                int size)
```

### Parameters

#### pNorm
Pointer to the data coding byte of event measurement data.

#### size
Number of bytes in the measurement data, including the initial data coding byte.


### Return Value
A 64-bit unsigned integer is returned. The bits in the measurement data array are in MSB - LSB order and this is preserved in the unsigned 64-bit integer. 

### Description
Get measurement data encoded as bits as an unsigned 64-bit value.

#### C example

```clike
unsigned char bitarry[3];
bitarry[0] = VSCP_DATACODING_BIT; // Data cding byte. Default unit, sensoridx=0
bitarry[1] = 0x55;
bitarry[2] = 0xAA;
unsigned long long bitarray64 = vscphlp_getDataCodingBitArray( bitarry, sizeof( bitarry ) )
```



#### Python example

Using the official [Python helper binding](bindings.md#python):

```python
import vscp
import vscphelper

data = bytearray([0x00, 0x55])
print(vscphelper.getDataCodingBitArray(data))
```

#### JavaScript availability

The official [Node.js binding](bindings.md#nodejs) does not currently expose this helper API, so there is no equivalent JavaScript example.

[filename](./bottom_copyright.md ':include')