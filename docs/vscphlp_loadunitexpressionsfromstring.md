

```clike
int vscphlp_loadUnitExpressionsFromString(const char *json)
```

### Parameters

#### json
JSON text in the format of `vscp-units.json` or `vscp-hashtypeevents.json`.

### Return Value
As [vscphlp_loadUnitExpressions](vscphlp_loadunitexpressions.md).

### Description
As [vscphlp_loadUnitExpressions](vscphlp_loadunitexpressions.md) for JSON text, for example fetched from a server.

#### C example

```clike
const char *json = "{\"units\":[{\"type\":6,\"unit\":0},"
                   "{\"type\":6,\"unit\":1,\"conversion0\":\"{{{val}}} + 273.15\",\"conversion\":\"{{{val}}} - 273.15\"}]}";
int rv = vscphlp_loadUnitExpressionsFromString(json);
```

#### Bindings

Not yet in the [Python and Node.js bindings](bindings.md); call it through the C API.

[filename](./bottom_copyright.md ':include')