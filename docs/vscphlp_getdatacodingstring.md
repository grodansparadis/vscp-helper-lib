

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
Size of the supplied buffer (strResult). The string is at most 7 bytes plus the terminating zero, so the buffer should be at least 8 bytes.


### Return Value
`VSCP_ERROR_SUCCESS` (`0`) indicates success. Possible error codes: `VSCP_ERROR_ERROR`.
`VSCP_ERROR_ERROR` is returned if `pData` or `strResult` is null.

Truncation is not reported; the output may lack a terminating null byte if the buffer is too
small. The input length is not validated; it must include the coding byte and
fit the documented maximum of eight bytes.

### Description
Get string coded measurement data as a string value. 

#### C example

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



#### Python example

Using the official [Python helper binding](bindings.md#python):

```python
import vscp
import vscphelper

data = bytearray([0x40, ord('3'), ord('.'), ord('1')])
result, value = vscphelper.getDataCodingString(data)
if result != vscp.VSCP_ERROR_SUCCESS:
    raise RuntimeError("getDataCodingString failed (error {})".format(result))
print(value)
```

#### JavaScript availability

See the [Node.js binding](bindings.md#nodejs) for C API access and native library availability.

[filename](./bottom_copyright.md ':include')