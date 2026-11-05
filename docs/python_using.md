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

The [frame security](frame_security.md#python-example) and
[UDP/multicast](datagram_clients.md#python-example) guides show the updated
Python wrapper's AES/HMAC APIs. The separate wrapper changes must be installed
from source until they are released. For Node.js, see
[language bindings](bindings.md#nodejs).

[filename](./bottom_copyright.md ':include')