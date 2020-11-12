

```clike
unsigned long long 
vscphlp_getDataCodingBitArray( const unsigned char *pNorm,
                                int size)
```

### Parameters

#### pNorm
Pointer to the data coding byte of event measurement data.

#### size
Number of bytes the measurement data consist of including the initial data coding byte.


### Return Value
A 64-bit unsigned integer is returned. The bits in the measurement data array are in MSB - LSB order and this is preserved in the unsigned 64-bit integer. 

### Description
Get measurement data that is coed as bits as a unsigned 64-bit value. 

#### C example

```clike
unsigned char bitarry[3];
bitarry[0] = VSCP_DATACODING_BIT; // Data cding byte. Default unit, sensoridx=0
bitarry[1] = 0x55;
bitarry[2] = 0xAA;
unsigned long long bitarray64 = vscphlp_getDataCodingBitArray( bitarry, sizeof( bitarry ) )
```



[filename](./bottom_copyright.md ':include')