

```clike
int vscphlp_convertMeasurementEx(const vscpEventEx *pEventEx, unsigned char to_unit, double *presult)
```

### Parameters

#### pEventEx
A measurement event.

#### to_unit
Unit to convert to.

#### presult
Receives the converted value.

### Return Value
As [vscphlp_convertMeasurement](vscphlp_convertmeasurement.md).

### Description
As [vscphlp_convertMeasurement](vscphlp_convertmeasurement.md) for a `vscpEventEx`.

#### C example

```clike
double fahrenheit;
int rv = vscphlp_convertMeasurementEx(&ex, 2, &fahrenheit);
```

#### Bindings

Not yet in the [Python and Node.js bindings](bindings.md); call it through the C API.

[filename](./bottom_copyright.md ':include')