

```clike
int vscphlp_getDataCodingString(const unsigned char *pData,
                                   unsigned char dataLength, 
                                   char *strResult,
                                   size_t len )
```

### Parameters

#### pData
Pointer to the data coding byte of the data.

#### dataLength
Total length of the data including the data coding byte.

#### strResult
Pointer to the buffer that will receive the resulting string.

#### len
Size of the supplied buffer (strResult). Max size of the string is 7 bytes + the terminating zero so the supplied size should be 8 bytes or larger.


### Return Value
VSCP_ERROR_SUCCESS is returned on success. 

### Description
Get string coded measurement data as a string value. 

#### C example
mmmm

```clike
unsigned char stringarry[6];
stringarry[0] = VSCP_DATACODING_STRING; // Data cding byte. Default unit, sensoridx=0
stringarry[1] = 0x32;
stringarry[2] = 0x33;
stringarry[3] = 0x34;
stringarry[4] = 0x2E;
stringarry[5] = 0x35;
char stringbuf[32];
if ( VSCP_ERROR_SUCCESS == vscphlp_getDataCodingString( stringarry,
                                                           sizeof( stringarry ), 
                                                           stringbuf,
                                                           sizeof( stringbuf ) ) ) {
    printf("OK - vscphlp_getDataCodingString value = %s \n", stringbuf );
}
else {
    printf("Error - vscphlp_getDataCodingString value = %s \n", stringbuf );
}
```



[filename](./bottom_copyright.md ':include')