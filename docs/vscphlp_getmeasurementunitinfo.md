

```clike
int vscphlp_getMeasurementUnitInfo(unsigned short vscp_type,
                                   unsigned char unit,
                                   char *name, size_t len_name,
                                   char *symbol_ascii, size_t len_symbol_ascii,
                                   char *symbol_utf8, size_t len_symbol_utf8,
                                   int *pconvertible)
```

### Parameters

#### vscp_type
Measurement type (CLASS1.MEASUREMENT type).

#### unit
Unit 0-255.

#### name, len_name
Buffer for the name of the unit, or NULL.

#### symbol_ascii, len_symbol_ascii
Buffer for the ASCII symbol (`C`), or NULL.

#### symbol_utf8, len_symbol_utf8
Buffer for the UTF-8 symbol (`°C`), or NULL.

#### pconvertible
Set to 1 if the unit can be converted to the other units of the type, else 0. May be NULL.

### Return Value
`VSCP_ERROR_SUCCESS`, `VSCP_ERROR_UNKNOWN_ITEM` if the type or unit is not defined, `VSCP_ERROR_BUFFER_TO_SMALL` if a value does not fit its buffer (the buffer is then set to an empty string).

### Description
Gets the name, symbols and convertibility of a measurement unit from the compiled unit table.
All measurement classes (CLASS1.MEASUREMENT, its X1-X4 classes, MEASUREMENT32/64, MEASUREZONE, SETVALUEZONE, their Level II variants, MEASUREMENT_STR and MEASUREMENT_FLOAT) use the types and units of CLASS1.MEASUREMENT, so the type is the event type and the unit the unit in the event.


#### C example

```clike
char name[64], symbol[16];
int convertible;
if (VSCP_ERROR_SUCCESS == vscphlp_getMeasurementUnitInfo(6, 1, name, sizeof(name), NULL, 0,
                                                         symbol, sizeof(symbol), &convertible)) {
    printf("%s [%s]\n", name, symbol);   // Celsius [°C]
}
```

#### Bindings

Not yet in the [Python and Node.js bindings](bindings.md); call it through the C API.

[filename](./bottom_copyright.md ':include')