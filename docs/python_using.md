# Using the library from Python {#c_python}

The official `pyvscphelper` package wraps the C helper library. Install it
alongside the shared library as described in [language bindings](bindings.md#python).

Import `vscphelper` for helper functions and `vscp` for event types and
constants. For example:

```python
import vscphelper

value = vscphelper.readStringValue("0x22")
print(value)
```

For a complete connection and session example, see the
[Python TLS example](tls.md#python-example).

The [TLS guide](tls.md#c-example) also includes a C example and a C++ client
certificate example. The official Node.js binding does not yet expose these
helper functions; see [language bindings](bindings.md#nodejs).

[filename](./bottom_copyright.md ':include')