# Per-session TLS configuration

These functions in `vscphelperlib.h` mirror the TLS methods of
`VscpRemoteTcpIf`. Configure a session before calling
[vscphlp_open](vscphlp_open.md) or
[vscphlp_openInterface](vscphlp_openinterface.md). No TLS environment
variables are required when you supply an explicit CA file or directory.

Settings belong to one session, survive `vscphlp_close`, and are released by
`vscphlp_closeSession`. Changes affect the **next connection**, not an
existing connection: they do not renegotiate TLS or upgrade/downgrade a live
socket. Close and reopen to apply them. Serialize calls using the same session.

All five functions return `VSCP_ERROR_SUCCESS` on success or
`VSCP_ERROR_INVALID_HANDLE` for an invalid session. The mode setter and getter
also return `VSCP_ERROR_PARAMETER` as described below. An invalid argument
does not change the configuration or the getter's output.

## vscphlp_setTLSOptions

```c
int vscphlp_setTLSOptions(long handle,
                         int verifyPeer,
                         const char *caFile,
                         const char *caPath,
                         const char *certFile,
                         const char *keyFile,
                         const char *keyPassword);
```

Copies all options and **forces TLS**, regardless of the endpoint prefix.
Each call replaces all previous TLS options, including the verification flag.
The caller can release its strings after the call returns.

| Parameter | Meaning |
| --- | --- |
| `handle` | Session returned by `vscphlp_newSession`. |
| `verifyPeer` | Nonzero verifies the server's certificate chain and hostname. This is the default for new sessions. `0` disables both checks and is unsafe for production. |
| `caFile` | PEM file containing trusted CA certificates. |
| `caPath` | Directory containing PEM CA certificates. |
| `certFile` | Optional client certificate chain in PEM format, or a single DER certificate, for mutual TLS. |
| `keyFile` | Optional PEM private key matching the client certificate. If empty, the key is read from `certFile`, allowing a combined PEM file. |
| `keyPassword` | Optional passphrase for an encrypted private key. The library stores a copy for subsequent connections; do not log it. |

Any string may be `NULL` or `""`; both mean empty, not "keep the old value".
If either CA argument is nonempty, only the explicitly supplied CA file and/or
directory are used for that session. Otherwise, OpenSSL's default trust
locations, including `SSL_CERT_FILE` and `SSL_CERT_DIR`, are used. CA
configuration is used only when `verifyPeer` is nonzero.

The setter does not access files or contact the server. Missing/invalid
certificates, unreadable keys, an incorrect key passphrase, trust/hostname
failures, or a rejected handshake are reported by the subsequent open call,
normally as `VSCP_ERROR_CONNECTION`; no insecure fallback occurs.

To clear client credentials and restore default trust and verification, call:

```c
int result = vscphlp_setTLSOptions(handle, 1, NULL, NULL, NULL, NULL, NULL);
```

Check `result` against `VSCP_ERROR_SUCCESS`. This still forces TLS; use
`vscphlp_setTLSAutoSelect` afterward if endpoint-based selection is wanted.

## vscphlp_enableTLS

```c
int vscphlp_enableTLS(long handle, int enable);
```

Nonzero forces TLS; `0` forces plain TCP, **even for an `stcp://` endpoint**.
This changes only the transport mode and retains the verification, CA, and
client-certificate options. Disabling TLS is not the same as restoring
automatic selection.

## vscphlp_setTLSAutoSelect

```c
int vscphlp_setTLSAutoSelect(long handle);
```

Restores the default transport mode: `stcp://` selects TLS; `tcp://` or no
prefix selects plain TCP. It retains all TLS options. There is no automatic
retry using plain TCP if TLS fails.

## vscphlp_setTLSMode

```c
int vscphlp_setTLSMode(long handle, int mode);
```

Sets one of the constants declared in `vscphelperlib.h`:

| Constant | Value | Behavior |
| --- | --- | --- |
| `VSCPHELPER_TLS_MODE_AUTO_SELECT` | `0` | Select by endpoint prefix; default for new sessions. |
| `VSCPHELPER_TLS_MODE_FORCE_TLS` | `1` | Always use TLS. |
| `VSCPHELPER_TLS_MODE_FORCE_PLAIN` | `2` | Always use unencrypted TCP. |

Other values return `VSCP_ERROR_PARAMETER`. Like `vscphlp_enableTLS`, this
preserves the other TLS options.

## vscphlp_getTLSMode

```c
int vscphlp_getTLSMode(long handle, int *pMode);
```

Writes the configured mode to `*pMode`. Passing `NULL` returns
`VSCP_ERROR_PARAMETER`. This reports the selection policy, **not whether the
current socket is encrypted**; an auto-selected TLS connection still reports
`VSCPHELPER_TLS_MODE_AUTO_SELECT`.

## C and C++ examples

The [TLS guide](tls.md#c-example) has a complete C program that supplies a CA
file through `vscphlp_setTLSOptions`.

This C++ helper configures mutual TLS through the same C API:

```cpp
#include <string>
#include <vscphelperlib.h>

int openMutualTls(long session,
                  const std::string& endpoint,
                  const std::string& username,
                  const std::string& password,
                  const std::string& caFile,
                  const std::string& clientCert,
                  const std::string& clientKey,
                  const std::string& keyPassword)
{
    int result = vscphlp_setTLSOptions(session, 1, caFile.c_str(), nullptr,
                                      clientCert.c_str(), clientKey.c_str(),
                                      keyPassword.c_str());
    if (result != VSCP_ERROR_SUCCESS) {
        return result;
    }
    return vscphlp_open(session, endpoint.c_str(), username.c_str(), password.c_str());
}
```

The caller creates the session, checks the returned error code, and calls
`vscphlp_closeSession` when finished. Pass an empty `keyPassword` for an
unencrypted key. Supply credentials and passphrases through the application's
secrets-management mechanism.

## Python example

The Python wrapper does not yet expose these new setters directly. The
[ctypes example](tls.md#python-example) calls the exported C functions with
explicit argument types and supports both server verification and mutual TLS.

## JavaScript availability

The official [Node.js binding](bindings.md#nodejs) does not currently expose
these functions. Do not assume methods with the C++ names exist in that addon.

[filename](./bottom_copyright.md ':include')
