

```clike
int vscphlp_convertFloatToFloatEventData( unsigned char *pdata,
                                unsigned short *psize, 
                                float value,
                                unsigned char unit,
                                unsigned char sensoridx )
```

### Parameters

#### pdata
Pointer to a data buffer of at least eight bytes that will receive the result.

#### psize
The size of the written data will be returned here.

#### value
Floating point value to write as a 32-bit float.

#### unit
A unit value from 0 to 3.

#### sensoridx
A sensor index from 0 to 7.

### Return Value
VSCP_ERROR_SUCCESS is returned on success.

### Description
Write a 32-bit floating point value as measurement event data.

> **Known limitation:** The VSCP implementation currently pinned by this
> library writes the float in host byte order, while its measurement decoder
> expects big-endian bytes. On a little-endian machine, the encoded value may
> not round-trip correctly. Do not rely on this function until the byte order
> is corrected.

The C and Python APIs use the same implementation and have the same
limitation. See [vscphlp_getMeasurementAsFloat](vscphlp_getmeasurementasfloat.md)
for an example that decodes correctly ordered bytes.

#### JavaScript availability

The official [Node.js binding](bindings.md#nodejs) does not currently expose this helper API, so there is no equivalent JavaScript example.

[filename](./bottom_copyright.md ':include')