# TLS connections

The VSCP helper library can connect to a TLS-enabled VSCP daemon. Configure the
daemon to accept TLS connections and ensure the client trusts the CA that
issued its certificate.

## Select the transport

For the C API declared in `vscphelperlib.h`, use one of these endpoint formats:

| API | TLS endpoint |
| --- | --- |
| `vscphlp_open` | `stcp://host:port`, with the username and password passed separately |
| `vscphlp_openInterface` | `stcp://host:port;username;password`, with flags set to `0` |

Use the port on which the daemon actually accepts TLS. An endpoint beginning
with `tcp://`, or with no prefix, uses **unencrypted TCP**; the library does not
automatically upgrade it to TLS. Credentials sent over plain TCP are not
protected by TLS.

The legacy `ssl://` prefix and `:CERT:CA_CERT` endpoint suffixes are not
supported. For the semicolon-separated form, keep the interface string out of
logs. It does not support escaping semicolons in credentials; use
`vscphlp_open` if a username or password contains one.

Connection and login are synchronous. If an application must keep its I/O or
UI thread responsive, make the call on an appropriate worker thread.

## Trust and server identity

By default, TLS verifies both the server's certificate chain and its hostname.
Use the DNS name in the server certificate; replacing it with an IP address
may cause verification to fail. The server must present a certificate trusted
by the client.

The library uses OpenSSL's default CA file and directories, which may differ
from the operating system's native certificate store. To use a private CA,
configure those trust locations or set these process environment variables
before starting the application:

* `SSL_CERT_FILE`: a PEM file containing trusted CA certificates.
* `SSL_CERT_DIR`: a directory containing PEM CA certificates.

For example, on Linux or macOS:

```sh
export SSL_CERT_FILE=/path/to/vscp-ca-bundle.pem
```

In Windows PowerShell:

```powershell
$env:SSL_CERT_FILE = 'C:\certs\vscp-ca-bundle.pem'
```

These are trust certificates, not the client private key. Configure trust
appropriately for the application; do not disable certificate verification to
work around an untrusted or mismatched server.

## C example

This program opens a TLS connection, sends `NOOP`, and releases the session.
It reads credentials from `VSCP_USER` and `VSCP_PASSWORD` for illustration;
choose an appropriate secrets-management mechanism for production, since
environment variables may be visible to other processes.

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <vscphelperlib.h>

int main(int argc, char **argv)
{
    const char *username = getenv("VSCP_USER");
    const char *password = getenv("VSCP_PASSWORD");

    if (argc != 2 || strncmp(argv[1], "stcp://", 7) != 0 ||
        username == NULL || password == NULL) {
        fprintf(stderr, "Usage: %s stcp://host:port\n"
                        "Set VSCP_USER and VSCP_PASSWORD in the environment.\n",
                argv[0]);
        return EXIT_FAILURE;
    }

    long session = vscphlp_newSession();
    if (session == 0) {
        fprintf(stderr, "Could not create a VSCP session\n");
        return EXIT_FAILURE;
    }

    int result = vscphlp_open(session, argv[1], username, password);
    if (result != VSCP_ERROR_SUCCESS) {
        fprintf(stderr, "VSCP connection failed (error %d)\n", result);
        vscphlp_closeSession(session);
        return EXIT_FAILURE;
    }

    result = vscphlp_noop(session);
    if (result != VSCP_ERROR_SUCCESS) {
        fprintf(stderr, "VSCP NOOP failed (error %d)\n", result);
        vscphlp_closeSession(session);
        return EXIT_FAILURE;
    }

    puts("TLS connection and VSCP NOOP succeeded");
    vscphlp_closeSession(session);
    return EXIT_SUCCESS;
}
```

For example, save it as `tls-client.c` and, on Linux with version 15's
development files in the compiler's default paths, build it with:

```sh
cc -std=c11 -Wall -Wextra tls-client.c -o tls-client -lvscphelper15
```

Replace `15` with the installed library's major version. Add include or
library search paths if the development files are installed elsewhere.

After supplying the credentials and any required CA trust, run for example:

```sh
./tls-client stcp://server.example.com:9598
```

Replace the hostname and port with those of your TLS-enabled daemon. Port 9598
is only an example and is not necessarily configured for TLS on your server.
`vscphlp_closeSession` also closes the connection.

## Python example

Install the official `pyvscphelper` package and the VSCP helper library as
described in [language bindings](bindings.md#python). The Python wrapper uses
the same TLS endpoint and CA trust configuration as the C API.

```python
import os
import sys

import vscp
import vscphelper

if len(sys.argv) != 2 or not sys.argv[1].startswith("stcp://"):
    raise SystemExit("Usage: python tls_client.py stcp://host:port")

username = os.environ.get("VSCP_USER")
password = os.environ.get("VSCP_PASSWORD")
if username is None or password is None:
    raise SystemExit("Set VSCP_USER and VSCP_PASSWORD in the environment")

session = vscphelper.newSession()
if not session:
    raise RuntimeError("Could not create a VSCP session")

try:
    result = vscphelper.open(session, sys.argv[1], username, password)
    if result != vscp.VSCP_ERROR_SUCCESS:
        raise RuntimeError("VSCP connection failed (error {})".format(result))
    result = vscphelper.noop(session)
    if result != vscp.VSCP_ERROR_SUCCESS:
        raise RuntimeError("VSCP NOOP failed (error {})".format(result))
    print("TLS connection and VSCP NOOP succeeded")
finally:
    vscphelper.closeSession(session)
```

Save this as `tls_client.py` and run it with the TLS endpoint as its argument.
As in the C example, the environment variables are illustrative; use an
appropriate secrets-management mechanism in production.

## JavaScript

The official [Node.js helper binding](bindings.md#nodejs) does not currently
expose the connection functions, so it cannot provide an equivalent TLS
example yet.

## Client certificates

The public `vscphlp_*` C API does not provide a way to configure a client
certificate or private key. A server requiring mutual TLS cannot be used through
these C functions as currently exposed.

Applications using the VSCP project's C++ `VscpRemoteTcpIf` class directly can
configure a client certificate and key with `setTLSOptions`:

```cpp
#include <string>
#include <vscpremotetcpif.h>

int openMutualTls(VscpRemoteTcpIf& client,
                  const std::string& endpoint,
                  const std::string& username,
                  const std::string& password,
                  const std::string& caFile,
                  const std::string& clientCert,
                  const std::string& clientKey)
{
    client.setTLSOptions(true, caFile, "", clientCert, clientKey);
    return client.doCmdOpen(endpoint, username, password);
}
```

Pass a TLS endpoint such as `stcp://server.example.com:9598`, a PEM CA bundle,
and paths to the client certificate and private key. Check the return value
against `VSCP_ERROR_SUCCESS` and call `client.doCmdClose()` when finished.
The `true` argument enables certificate and hostname verification.
`setTLSOptions` forces TLS; a nonempty CA file or directory replaces the
default trust locations for that client. Leave both CA arguments empty to
use the defaults. An optional final argument supplies an encrypted key's
password.

This C++ class is separate from the C helper API; see the
[first C++ project](classes_first_project.md) for how to use it.

## Troubleshooting

* `VSCP_ERROR_PARAMETER`: check the endpoint format and port. Use brackets
  around an IPv6 literal, such as `[::1]:9598`.
* `VSCP_ERROR_CONNECTION`: check that the daemon accepts TLS on the selected
  port, that the CA is trusted, and that the hostname matches the certificate.
  The transport may print additional diagnostics beginning with `VSCP TCP:`
  to standard error.
* `VSCP_ERROR_TIMEOUT`: check name resolution, network reachability, and the
  server's TLS endpoint.
* `VSCP_ERROR_USER` or `VSCP_ERROR_PASSWORD`: check the VSCP login credentials.

On systems with the `openssl` command, you can inspect a server's handshake
and certificate verification independently of the helper library:

```sh
openssl s_client -connect server.example.com:9598 \
  -servername server.example.com -verify_hostname server.example.com \
  -CAfile /path/to/vscp-ca-bundle.pem -verify_return_error </dev/null
```

Replace the host, TLS port, and CA file with the values for your server.

[filename](./bottom_copyright.md ':include')
