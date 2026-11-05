# VSCP Helper Library Bindings {#vscp_helper_library_bindings}

<a id="c_c"></a>
## C/C++ 

Available for Windows, Linux, and macOS.

The **libvscphelper library** is available as a binary deb package for 64-bit Linux and 32- or 64-bit Raspberry Pi, as well as for 64-bit macOS and as a standard 64-bit Windows installer.

Downloadable binaries are available [here](https://www.vscp.org/downloads/vscphelper).

<a id="python"></a>
## Python 

**pyvscp** provides VSCP data types and utilities. The separate
**pyvscphelper** package wraps the C helper library.

To use the helper functions, install the VSCP helper library and then run:

```bash
python -m pip install pyvscphelper
```

Import the modules with:

```python
import vscp
import vscphelper
```

The wrapper loads the installed shared library. If it cannot find the library,
set `VSCPHELPER_LIB` to its full path before starting Python. Its functions
use names such as `vscphelper.newSession()` and `vscphelper.open()`; older
examples using `pyvscphlp_*` names do not describe this wrapper's API.

The new per-session TLS setters are exported by the C library but are not
yet wrapped by this Python package. See the [TLS ctypes example](tls.md#python-example)
for programmatic CA and client-certificate configuration without changing
the Python wrapper.

The development version of `pyvscphelper` exposes
[binary link frames](binary_link.md#python-example),
[AES/HMAC security](frame_security.md#python-example), and
[UDP/multicast clients](datagram_clients.md#python-example) directly.
These changes require a corresponding wrapper release and a shared library
that exports the new functions. TCP event-ex and datagram event-ex operations
convert both the older `pyvscp` 0.3.14 layout and the current layout. Other
event helpers still pass the `pyvscp` structures directly and require a
version compatible with the native library; the published 0.3.14 layout
predates the current ABI. A newer `pyvscp` source or release is needed for
those other helpers.

For an event allocated by `newVSCPevent`, call `deleteVSCPevent_v2` to release
both its helper-owned data and the event structure. The older
`deleteVSCPevent` releases only the data. Do not pass a Python-owned event or
data buffer to the full-event deleter.

The updated `closeSession` releases only that session; other sessions remain
usable and the module keeps the shared library loaded.

The source is available in [pyvscp](https://github.com/grodansparadis/pyvscp)
and [pyvscphelper](https://github.com/grodansparadis/pyvscphelper).

Code written by Salvo Musumeci is also available at (https://github.com/nos86/VSCP-Helper-for-Python). Development appears to have stalled, but it may continue in the future, either by the author or by someone who forks the project.

<a id="c_net"></a>
## C\#/net

 We need someone to take this on. Some work has already been done.

 Contact [akhe@grodansparadis.com](mailto:akhe@grodansparadis.com) if you work (or want to work) on this so we can put a link to your work here.

<a id="java"></a>
## Java 

 We need someone to take this on.

 Contact [akhe@grodansparadis.com](mailto:akhe@grodansparadis.com) if you work \(or want to work\) on this so we can put a link to your work here.

<a id="php"></a>
## PHP 

 We need someone to take this on.

 Contact [akhe@grodansparadis.com](mailto:akhe@grodansparadis.com) if you work \(or want to work\) on this so we can put a link to your work here.

<a id="perl"></a>
## Perl

 We need someone to take this on.

 Contact [akhe@grodansparadis.com](mailto:akhe@grodansparadis.com) if you work \(or want to work\) on this so we can put a link to your work here.

<a id="nodejs"></a>
## Node.js

The development version of
[node-vscp-helper](https://github.com/grodansparadis/node-vscp-helper)
provides a Node.js wrapper around the C helper library. It retains the
existing `hello()` addon function and adds synchronous session, event,
binary-frame, AES/HMAC, UDP, and multicast helpers. It does not expose the
`VscpRemoteTcpIf` C++ class directly.

`loadHelper()` loads the native library, using `VSCPHELPER_LIB` or an explicit
path when needed. `api.raw` provides lazily bound declarations from the C
header and `api.bind()` accepts explicit Koffi declarations. A declared
function is callable only if the installed library actually exports it: the
current build is missing some legacy declared functions, including
`vscphlp_encryptVscpUdpFrame` and `vscphlp_decryptVscpUdpFrame`. Missing
symbols raise a lookup error. The raw API requires the caller to supply
correct native buffers, struct layouts, and ownership handling.

Native calls are synchronous and can block the Node.js event loop; use a
worker thread for blocking network operations. See
[Using with JavaScript](using.md#using-with-javascript) and the security and
datagram examples. The wrapper changes require a separate package release;
an existing published package may not contain them yet.

<a id="others"></a>
## Others 

We are also interested in other bindings. Let us know about your work.




[filename](./bottom_copyright.md ':include')