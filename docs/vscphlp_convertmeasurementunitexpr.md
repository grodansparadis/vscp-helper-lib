

```clike
int vscphlp_convertMeasurementUnitExpr(unsigned short vscp_type,
                                       unsigned char from_unit,
                                       unsigned char to_unit,
                                       double value,
                                       double *presult)
```

### Parameters

#### vscp_type
Measurement type (CLASS1.MEASUREMENT type).

#### from_unit
Unit of `value`.

#### to_unit
Unit to convert to.

#### value
Value to convert.

#### presult
Receives the converted value.

### Return Value
`VSCP_ERROR_SUCCESS`, `VSCP_ERROR_INIT_MISSING` if no units are loaded, `VSCP_ERROR_INVALID_POINTER`, `VSCP_ERROR_UNKNOWN_ITEM` if the type or a unit is not loaded, `VSCP_ERROR_NOT_SUPPORTED` if a unit can not be converted, or an error from [vscphlp_evalUnitExpression](vscphlp_evalunitexpression.md).

### Description
Converts a measurement value from one unit to another with the conversion expressions loaded with [vscphlp_loadUnitExpressions](vscphlp_loadunitexpressions.md): the value is converted to unit 0 with the `conversion0` expression of `from_unit` and from unit 0 with the `conversion` expression of `to_unit`.

This is the runtime alternative to [vscphlp_convertMeasurementUnit](vscphlp_convertmeasurementunit.md): new or changed units work by loading a new file, without a new library. The compiled table is faster and needs no file; for the units published with the library both give the same results.

#### C example

```clike
double f;
vscphlp_loadUnitExpressions("vscp-units.json");
vscphlp_convertMeasurementUnitExpr(6, 1, 2, 100.0, &f);   // 100 C = 212 F
```

#### Bindings

Not yet in the [Python and Node.js bindings](bindings.md); call it through the C API.

[filename](./bottom_copyright.md ':include')