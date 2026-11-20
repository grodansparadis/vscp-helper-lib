

```clike
int vscphlp_convertMeasurement(const vscpEvent *pEvent, unsigned char to_unit, double *presult)
```

### Parameters

#### pEvent
A measurement event.

#### to_unit
Unit to convert to.

#### presult
Receives the converted value.

### Return Value
`VSCP_ERROR_SUCCESS`, `VSCP_ERROR_INVALID_POINTER`, `VSCP_ERROR_PARAMETER` if the event is not a measurement event (CLASS1.DATA has units of its own and is not handled), `VSCP_ERROR_INVALID_FORMAT` if the value or unit can not be read, or an error from [vscphlp_convertMeasurementUnit](vscphlp_convertmeasurementunit.md).

### Description
Reads the value and unit of a measurement event and converts the value to `to_unit`. MEASUREMENT32 and MEASUREMENT64 values are always in unit 0.
All measurement classes (CLASS1.MEASUREMENT, its X1-X4 classes, MEASUREMENT32/64, MEASUREZONE, SETVALUEZONE, their Level II variants, MEASUREMENT_STR and MEASUREMENT_FLOAT) use the types and units of CLASS1.MEASUREMENT, so the type is the event type and the unit the unit in the event.


#### C example

```clike
double celsius;
if (VSCP_ERROR_SUCCESS == vscphlp_convertMeasurement(pEvent, 1, &celsius)) {
    printf("%.1f C\n", celsius);
}
```

#### Bindings

Not yet in the [Python and Node.js bindings](bindings.md); call it through the C API.

[filename](./bottom_copyright.md ':include')