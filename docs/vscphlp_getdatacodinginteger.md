

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
Get measurement data that is coded as a aigned integer (1-7 bytes) as a 64-bit integer. 

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



[filename](./bottom_copyright.md ':include')