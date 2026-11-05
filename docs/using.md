# Using the library

Here are some guidelines on how to use the library.

An [example](https://github.com/grodansparadis/vscp-helper-lib) uses most of the methods available in the library.

## Using with JavaScript

The helper library exposes a native C API; it cannot be loaded directly in a
browser. The development version of the
[Node.js wrapper](https://github.com/grodansparadis/node-vscp-helper) uses
[Koffi](https://koffi.dev/) to call it.

Install the shared library from the
[releases](https://github.com/grodansparadis/vscp-helper-lib/releases), or
build it yourself. The library and Node.js must use the same platform and
CPU architecture. Install a version of the wrapper containing these changes:

```sh
npm install node-vscp-helper
```

Until the wrapper is published, install it from its source checkout instead.
Save the following as `example.cjs`; no VSCP daemon is required:

```javascript
const { loadHelper } = require('node-vscp-helper');
const api = loadHelper();

console.log('Helper library version:', api.raw.vscphlp_getVersionString());
console.log('0x22 =', api.raw.vscphlp_readStringValue('0x22')); // 34
```

Run it with `VSCPHELPER_LIB` set to the absolute path of the shared library.
For example, on Linux or macOS:

```sh
VSCPHELPER_LIB=/absolute/path/to/the/shared-library node example.cjs
```

On Windows PowerShell:

```powershell
$env:VSCPHELPER_LIB = 'C:\path\to\the\shared-library.dll'
node .\example.cjs
```

Convenience methods and `api.raw` are described in
[language bindings](bindings.md#nodejs). Raw calls retain the C API's buffer
and ownership requirements, and a declaration may be absent from an older
or incomplete native build. Check status codes against zero and release
sessions and datagram clients when finished. Calls are synchronous; use a
worker when they must not block the event loop. See
[frame security](frame_security.md) and [UDP/multicast](datagram_clients.md)
for authenticated examples.


[filename](./bottom_copyright.md ':include')