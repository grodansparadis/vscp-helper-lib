

```clike
int vscphlp_evalUnitExpression(const char *expr, double value, double *presult)
```

### Parameters

#### expr
The expression, for example `({{{val}}} + 459.67) * 5/9`.

#### value
Value used for `{{{val}}}` (or `{{val}}`).

#### presult
Receives the result.

### Return Value
`VSCP_ERROR_SUCCESS`, `VSCP_ERROR_INVALID_POINTER`, `VSCP_ERROR_INVALID_SYNTAX` if the expression is not valid, `VSCP_ERROR_INVALID_FORMAT` if the result is not a finite number (for example division by zero).

### Description
Evaluates a unit conversion expression as written in the VSCP class definitions. Expressions can hold numbers (also `1e-4` form), `+ - * /`, unary `+`/`-`, parentheses and the value. They are evaluated the same way in every locale (the decimal point is always `.`).

#### C example

```clike
double k;
vscphlp_evalUnitExpression("({{{val}}} + 459.67) * 5/9", 212, &k);   // 373.15
```

#### Bindings

Not yet in the [Python and Node.js bindings](bindings.md); call it through the C API.

[filename](./bottom_copyright.md ':include')