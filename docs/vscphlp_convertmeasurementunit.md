

```clike
int vscphlp_convertMeasurementUnit(unsigned short vscp_type,
                                   unsigned char from_unit,
                                   unsigned char to_unit,
                                   double value,
                                   double *presult)
```

### Parameters

#### vscp_type
Measurement type (CLASS1.MEASUREMENT type), for example 6 for temperature.

#### from_unit
Unit of `value`.

#### to_unit
Unit to convert to.

#### value
Value to convert.

#### presult
Receives the converted value.

### Return Value
`VSCP_ERROR_SUCCESS`, `VSCP_ERROR_INVALID_POINTER` if `presult` is NULL, `VSCP_ERROR_UNKNOWN_ITEM` if the type or a unit is not defined, `VSCP_ERROR_NOT_SUPPORTED` if a unit can not be converted (latitude/longitude, ppm/percent of a molar concentration, date/time formats, ...).

### Description
Converts a measurement value from one unit to another, through the default unit (unit 0). The units come from a table compiled into the library (`vscp-units.h`, generated from the [VSCP class definitions](https://github.com/grodansparadis/vscp-classes)): each unit is stored as `value_in_unit_0 = value * scale + offset`, so the conversion is exact and needs no files. Converting a defined unit to itself always succeeds.

See [vscphlp_convertMeasurementUnitExpr](vscphlp_convertmeasurementunitexpr.md) for the alternative that reads the conversions from a file at runtime.
All measurement classes (CLASS1.MEASUREMENT, its X1-X4 classes, MEASUREMENT32/64, MEASUREZONE, SETVALUEZONE, their Level II variants, MEASUREMENT_STR and MEASUREMENT_FLOAT) use the types and units of CLASS1.MEASUREMENT, so the type is the event type and the unit the unit in the event.


#### C example

```clike
double kelvin = 0;
// 25 degrees Celsius (unit 1) to Kelvin (unit 0)
int rv = vscphlp_convertMeasurementUnit(6, 1, 0, 25.0, &kelvin);
if (VSCP_ERROR_SUCCESS == rv) {
    printf("%.2f K\n", kelvin);   // 298.15 K
}
```

#### Bindings

Not yet in the [Python and Node.js bindings](bindings.md); call it through the C API.

[filename](./bottom_copyright.md ':include')