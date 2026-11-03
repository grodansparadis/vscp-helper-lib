

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
A double precision floating point value that is the decimal representation of the measurement data. 

### Description
Get measurement data encoded as a signed integer (1-7 bytes) as a 64-bit integer.

#### C example

```clike
unsigned char normarry[4];
normarry[0] = 0x60; // Data coding byte:integer, unit=0, sensoridx=0
normarry[1] = 0xFF;
normarry[2] = 0xFF;
normarry[3] = 0xFF;
double value =  vscphlp_getDataCodingInteger (normarry, sizeof( normarry ) );
if ( 3.1 == value ) {
    printf("OK - vscphlp_getDataCodingInteger value = %f \n", value );
}
else {
    printf("Error - vscphlp_getDataCodingNormalizedInteger value = %f \n", value );
}
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