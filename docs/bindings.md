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

The [binary link API](binary_link.md#python-example) is likewise available
through `ctypes`; it is not yet exposed by the Python wrapper.

The [frame security examples](frame_security.md) likewise use the exported C
API for AES/HMAC session configuration and standalone authenticated frames.

For an event allocated by `newVSCPevent`, call `deleteVSCPevent_v2` to release
both its helper-owned data and the event structure. The older
`deleteVSCPevent` releases only the data. Do not pass a Python-owned event or
data buffer to the full-event deleter.

The current Python wrapper unloads the shared library when `closeSession` is
called. Call it only after all work with the wrapper is finished; do not make
further wrapper calls or keep other sessions active afterward.

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

The [node-vscp-helper](https://github.com/grodansparadis/node-vscp-helper)
package exists, but its current native addon exports only the `hello`
function. It does not yet expose the helper-library or `VscpRemoteTcpIf`
methods, so equivalent JavaScript examples for those APIs are not currently
available.

<a id="others"></a>
## Others 

We are also interested in other bindings. Let us know about your work.




[filename](./bottom_copyright.md ':include')