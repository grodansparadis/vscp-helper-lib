

```clike
int vscphlp_convertIntegerToNormalizedEventData( unsigned char *pdata,
                                unsigned short *psize,
                                unsigned long long val64,
                                unsigned char unit,
                                unsigned char sensoridx )
```

### Parameters

#### pdata
Pointer to the data buffer that will receive the result. The buffer should be large enough to hold the normalized data, which is larger than eight bytes.

#### psize
The size of the written data will be returned here.

#### val64
Unsigned integer value to encode.

#### unit
A unit value from 0 to 3.

#### sensoridx
A sensor index from 0 to 7.


### Return Value
VSCP_ERROR_SUCCESS is returned on success.

### Description
Write an integer value as measurement event data in normalized integer form.

> **Known limitation:** The VSCP implementation currently pinned by this
> library can return success with incorrectly encoded data. For example,
> encoding 1234 with unit 2 and sensor index 1 returns zero-filled bytes in
> the tested Linux build. Do not rely on this function until the implementation
> is corrected.

#### C availability

The current implementation exports this function on Linux, but the public C
header does not declare it. A C example requires a matching declaration in
the header; availability may vary on other platforms.



#### Python availability

The official Python wrapper exposes this function, but it uses the same
implementation and therefore has the same limitation.

#### JavaScript availability

The official [Node.js binding](bindings.md#nodejs) does not currently expose this helper API, so there is no equivalent JavaScript example.

[filename](./bottom_copyright.md ':include')