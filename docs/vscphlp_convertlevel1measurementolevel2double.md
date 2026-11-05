

```clike
int vscphlp_convertLevel1MeasuremenToLevel2Double( vscpEvent *pEvent )
```

### Parameters

#### pEvent
Pointer to a VSCP event.

### Return Value
`VSCP_ERROR_SUCCESS` (`0`) indicates success. Possible error codes: `VSCP_ERROR_ERROR`.

### Description
Convert Level I measurement to a Level II float measurement event [CLASS2.MEASUREMENT_FLOAT](https://grodansparadis.gitbooks.io/the-vscp-specification/class2.measurement_float.html). 

> **Known limitations:** The public header declares the name with
> `Measuremen`, but the library exports it with `Measurement`. In addition,
> on the tested build, converting 3.14 produced a value of approximately
> 2.16e17 when decoded. The Python wrapper resolves the exported name but
> uses the same faulty conversion. Do not rely on it until corrected.


#### JavaScript availability

The official [Node.js binding](bindings.md#nodejs) does not currently expose this helper API, so there is no equivalent JavaScript example.

### See Also
[vscphlp_convertLevel1MeasuremenToLevel2DoubleEx](vscphlp_convertlevel1measurementolevel2doubleex.md)
[vscphlp_convertLevel1MeasuremenToLevel2String](vscphlp_convertlevel1measurementolevel2string.md)
[vscphlp_convertLevel1MeasuremenToLevel2StringEx](vscphlp_convertlevel1measurementolevel2stringex.md)



[filename](./bottom_copyright.md ':include')
