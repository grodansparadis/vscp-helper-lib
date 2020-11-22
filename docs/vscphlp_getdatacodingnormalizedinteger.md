

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
A double precision floating point value that is the decimal representation of the measurement data. 

### Description
Get measurement data that is coded as a normalized integer as a floating point value.

#### C example

```clike
unsigned char normarry[4];
normarry[0] = 0x89; // Data coding byte: Normalized integer, unit=1, sensoridx=1
normarry[1] = 0x02;
normarry[2] = 0x01;
normarry[3] = 0x36;
double value =  vscphlp_getDataCodingNormalizedInteger (normarry, sizeof( normarry ) );
if ( 3.1 == value ) {
    printf("OK - vscphlp_getDataCodingNormalizedInteger value = %f \n", value );
}
else {
    printf("Error - vscphlp_getDataCodingNormalizedInteger value = %f \n", value );
}
```



[filename](./bottom_copyright.md ':include')
