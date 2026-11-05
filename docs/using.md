# Using the library

Here are some guidelines on how to use the library.

An [example](https://github.com/grodansparadis/vscp-helper-lib) uses most of the methods available in the library.

## Using with JavaScript

The helper library exposes a native C API; it cannot be loaded directly in a
browser. The official [Node.js addon](https://github.com/grodansparadis/node-vscp-helper)
currently exports only `hello`, not the helper functions. In Node.js, one way
to call the C API is through the third-party [Koffi](https://koffi.dev/) FFI
package.

Install the shared library from the
[releases](https://github.com/grodansparadis/vscp-helper-lib/releases), or
build it yourself. The library and Node.js must use the same platform and
CPU architecture. In your Node.js project, install Koffi:

```sh
npm install koffi
```

Save the following as `example.cjs`. It loads the library, prints its version,
and converts a hexadecimal string; no VSCP daemon is required.

```javascript
const koffi = require('koffi');

const libraryPath = process.env.VSCPHELPER_LIB;
if (!libraryPath) {
    throw new Error('Set VSCPHELPER_LIB to the full shared-library path');
}

const library = koffi.load(libraryPath);
const getVersion = library.func('const char *vscphlp_getVersionString(void)');
const readValue = library.func('unsigned long vscphlp_readStringValue(const char *text)');

console.log('Helper library version:', getVersion());
console.log('0x22 =', readValue('0x22')); // 34
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

For other functions, declare the exact signatures from the C API. In
particular, a session handle must be positive, status codes must be checked
against zero, and sessions must be closed when finished. Calls such as opening
a connection are synchronous, so use a worker when they must not block the
Node.js event loop. See [return values and error handling](error_handling.md)
and [TLS connections](tls.md) for session, error, and connection details.


[filename](./bottom_copyright.md ':include')