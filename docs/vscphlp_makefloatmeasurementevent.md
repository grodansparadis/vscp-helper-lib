

```clike
int vscphlp_makeFloatMeasurementEvent( vscpEvent *pEvent, 
                                        float value,
                                        unsigned char unit,
                                        unsigned char sensoridx )
```

### Parameters

#### pEvent
Pointer to a VSCP event that will receive the result as its data.

#### value
Floating point value to write as a 32-bit float.

#### unit
A unit value from 0 to 3.

#### sensoridx
A sensor index from 0 to 7.

### Return Value
`VSCP_ERROR_SUCCESS` (`0`) indicates success. Possible error codes: `VSCP_ERROR_ERROR`.

### Description
Make a floating point (32-bit) coded level I event from floating point data.

> **Known limitation:** On the tested little-endian build, encoding 3.14 and
> decoding the resulting data returned approximately -490.564. The encoder
> writes host-order bytes while the decoder expects big-endian bytes. Do not
> rely on this function until the implementation is corrected; the C and
> Python APIs share the same implementation.



#### JavaScript availability

See the [Node.js binding](bindings.md#nodejs) for C API access and native library availability.

[filename](./bottom_copyright.md ':include')