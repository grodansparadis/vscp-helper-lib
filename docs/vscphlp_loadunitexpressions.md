

```clike
int vscphlp_loadUnitExpressions(const char *path)
```

### Parameters

#### path
Path to `vscp-units.json` or `vscp-hashtypeevents.json`.

### Return Value
`VSCP_ERROR_SUCCESS`, `VSCP_ERROR_INVALID_POINTER`, `VSCP_ERROR_INVALID_PATH` if the file can not be read, `VSCP_ERROR_INVALID_FORMAT` or `VSCP_ERROR_INVALID_SYNTAX` if the content or an expression is not valid.

### Description
Loads the measurement units and their conversion expressions for [vscphlp_convertMeasurementUnitExpr](vscphlp_convertmeasurementunitexpr.md). `vscp-units.json` is generated from the [VSCP class definitions](https://github.com/grodansparadis/vscp-classes) (`script/make_vscphelper_units.py json`) and published with them; the units of CLASS1.MEASUREMENT in `vscp-hashtypeevents.json` can be used as well.

The library holds one set of units. A successful load replaces it; a failed load keeps the units loaded before. Loading is safe while other threads convert.

#### C example

```clike
if (VSCP_ERROR_SUCCESS != vscphlp_loadUnitExpressions("vscp-units.json")) {
    fprintf(stderr, "Could not load the unit definitions\n");
}
```

#### Bindings

Not yet in the [Python and Node.js bindings](bindings.md); call it through the C API.

[filename](./bottom_copyright.md ':include')