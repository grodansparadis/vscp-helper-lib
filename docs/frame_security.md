# HMAC and binary frame encryption

The helper library supports both automatic per-session security and standalone
authenticated frame helpers. They use VSCP version-1 records: **AES-CBC with
PKCS#7 padding and encrypt-then-MAC using HMAC-SHA-256**, truncated to its
leftmost 128 bits. The AES choices are 128, 192, and 256 bits.

The receiver compares the HMAC in constant time **before decryption**, then
checks padding and CRC. Authentication, padding, or CRC failure releases no
plaintext. There is no unauthenticated fallback or automatic downgrade.

TLS and frame security are independent. Frame encryption does not replace TLS
server identity verification or prevent replay. Use TLS where possible and
provide application-level replay protection when needed.

Frame security starts only after binary negotiation. Initial text-mode login
credentials remain unencrypted on a plain TCP connection; TLS protects that
login too. There is no key exchange: provision matching algorithms and keys
on both peers through a separate secure mechanism.

## Transport coverage and limits

AES with HMAC-SHA-256 is available on these paths, but it is opt-in and does
not cover every kind of communication:

| Communication path | AES + HMAC | Notes |
| --- | --- | --- |
| TCP or TLS in binary mode | Yes | Configure with `vscphlp_setBinarySecurity` before binary negotiation. TLS remains separately responsible for protecting the connection and verifying server identity. |
| TCP or TLS in text mode | No | Frame security is not applied to text commands, events, or login. Use TLS to protect the connection; plain TCP does not protect credentials. |
| UDP and multicast clients | Yes | Configure `encryption`, `key`, and `hmac-key` in the client JSON. Without `hmac-key`, the existing datagram formats remain unauthenticated. See [UDP and multicast security](datagram_clients.md#authenticated-udp-and-multicast-hmac). |
| Application-managed frames | Yes | `vscphlp_encryptFrameV1` and `vscphlp_decryptFrameV1` provide standalone helpers; the application is responsible for transporting and validating the records. |
| Legacy UDP frame helpers | No | The header declares legacy AES-only helpers, but the current library does not export them. |

Security is not enabled by default, and keys are not exchanged by these APIs.
Peers must be provisioned with matching AES and HMAC keys through a separate
secure mechanism. HMAC detects modification and authenticates possession of
the shared key, but it does not prevent replay of a previously valid frame or
datagram. Add application-level sequence numbers or timestamps where replay
protection is required.

The updated Python and Node.js wrappers expose session security, standalone
frame helpers, and UDP/multicast configuration. They are maintained in
separate repositories and must be released or installed from source before
these APIs are available.

UDP and multicast clients use the same version-1 records, with the 3-byte
prefix sent in every datagram, when configured with an `hmac-key`. See
[authenticated UDP and multicast](datagram_clients.md#authenticated-udp-and-multicast-hmac).

## Automatic per-session security

```c
int vscphlp_setBinarySecurity(long handle,
                             int algorithm,
                             const unsigned char *key,
                             size_t keyLength,
                             const unsigned char *hmacKey,
                             size_t hmacKeyLength);

int vscphlp_getBinarySecurity(long handle, int *pAlgorithm);
```

Configure security before [binary negotiation](binary_link.md); this is allowed
on a disconnected session or an authenticated connection still in text mode.
It cannot be changed while a connected session is in binary mode. Close the
connection before rotating keys or changing policy.

| Algorithm | AES key length | HMAC key length |
| --- | --- | --- |
| `VSCP_ENCRYPTION_AES128` | 16 bytes | 32 bytes |
| `VSCP_ENCRYPTION_AES192` | 24 bytes | 32 bytes |
| `VSCP_ENCRYPTION_AES256` | 32 bytes | 32 bytes |
| `VSCP_ENCRYPTION_NONE` | 0 | 0 |

Use independent, securely provisioned binary keys, **not** password strings.
The library rejects missing/incorrect key lengths and an HMAC key whose prefix
reuses the AES key. This check is not a substitute for independent generation.
Never reuse the AES key as the HMAC key.

Keys are copied into the session, retained across reconnects, and erased when
replaced or the session is destroyed. No getter exposes key material. The
getter reports the configured algorithm, including on a disconnected session;
it does not report whether a socket is connected or already in binary mode.

The default is `VSCP_ENCRYPTION_NONE`, preserving legacy binary framing.
Pass `NONE`, `NULL`, `0`, `NULL`, `0` to explicitly restore that policy.
Invalid arguments leave existing settings unchanged.

With AES selected, the existing binary send/receive APIs accept and return
**plaintext inner frames**. Supply a valid CRC and a type byte with encryption
bits cleared; do not pre-encrypt the frame. The transport generates a fresh
random IV, encrypts and authenticates each record, and authenticates/decrypts
received records. Returned plaintext has its encryption nibble cleared.
The existing event APIs and their confirmations use the same security policy.

The peer must implement the version-1 wire format described below. An
authenticated connection rejects legacy records, version 0, unencrypted
frames, a different AES algorithm, invalid tags, padding, or CRCs, and closes
the connection. Receive returns `VSCP_ERROR_INVALID_FRAME`, with no frame
allocation returned. Timeouts still retain partial input for a later receive.

Automatic mode permits plaintext frames of **5 through 4,048 bytes**.
The complete encrypted inner frame is limited to 4,096 bytes. Legacy raw
mode's 65,535-byte transport limit is unchanged.

### C example

With a session already opened and authenticated, and two independent 32-byte
keys supplied by the application's secrets-management mechanism:

```c
#include <vscphelperlib.h>

int enableAuthenticatedBinary(long session,
                               const unsigned char aesKey[32],
                               const unsigned char hmacKey[32])
{
    int result = vscphlp_setBinarySecurity(session, VSCP_ENCRYPTION_AES256,
                                           aesKey, 32, hmacKey, 32);
    if (result != VSCP_ERROR_SUCCESS) {
        return result;
    }
    return vscphlp_doCmdBinary(session);
}
```

Check the result, then use the [binary frame APIs](binary_link.md) or
`vscphlp_sendEventEx` / `vscphlp_blockingReceiveEventEx`. Encryption and HMAC
are automatic; do not call the standalone encryptor on these outgoing frames.
After reconnecting, negotiate binary mode again; the keys remain configured.

### C++ example

```cpp
#include <array>
#include <vscphelperlib.h>

int enableAuthenticatedBinaryCpp(long session,
                                  const std::array<unsigned char, 32>& aesKey,
                                  const std::array<unsigned char, 32>& hmacKey)
{
    int result = vscphlp_setBinarySecurity(session, VSCP_ENCRYPTION_AES256,
                                           aesKey.data(), aesKey.size(),
                                           hmacKey.data(), hmacKey.size());
    if (result != VSCP_ERROR_SUCCESS) {
        return result;
    }
    return vscphlp_doCmdBinary(session);
}
```

The caller owns the session and checks all subsequent send/receive errors.

### Python example

With a session already opened and authenticated, use independent keys from
your application's secrets store:

```python
import vscphelper


def enable_authenticated_binary(session, aes_key, hmac_key):
    result = vscphelper.setBinarySecurity(session, 3, aes_key, hmac_key)
    if result != 0:
        raise RuntimeError("Binary security configuration failed (error {})".format(result))
    result = vscphelper.doCmdBinary(session)
    if result != 0:
        raise RuntimeError("Binary negotiation failed (error {})".format(result))
```

Use the [binary frame functions](binary_link.md#python-example) or event APIs
afterward: they operate on plaintext while the transport handles AES/HMAC.
The wrapper returns native status codes and copies received buffers before
freeing native memory.

### JavaScript example

The Node.js calls are synchronous. Configure an open session with independent
32-byte `Buffer` keys, then negotiate binary mode:

```javascript
const { loadHelper, ENCRYPTION } = require('node-vscp-helper');
const api = loadHelper();

function enableAuthenticatedBinary(session, aesKey, hmacKey) {
    let status = api.setBinarySecurity(session, ENCRYPTION.AES256, aesKey, hmacKey);
    if (status !== 0) throw new Error(`Security configuration failed: ${status}`);
    status = api.doCmdBinary(session);
    if (status !== 0) throw new Error(`Binary negotiation failed: ${status}`);
}
```

`api.sendBinaryFrame` and `api.receiveBinaryFrame` then operate on plaintext
inner frames. Receive returns `[status, Buffer | null]` and frees its native
allocation after copying. `api.sendEventEx` and `api.blockingReceiveEventEx`
also use the session's configured policy. Use a worker thread for blocking
calls when the event loop must remain responsive.

## Standalone authenticated frame helpers

These are session-independent functions for applications managing their own
version-1 records. Their output buffers are **caller-owned**, unlike the
library-owned buffers returned by `vscphlp_receiveBinaryFrame`.

```c
int vscphlp_encryptFrameV1(unsigned char *output,
                          size_t capacity,
                          size_t *outputLength,
                          const unsigned char *input,
                          size_t inputLength,
                          const unsigned char *key,
                          size_t keyLength,
                          const unsigned char *hmacKey,
                          size_t hmacKeyLength,
                          const unsigned char *iv,
                          size_t ivLength,
                          int algorithm);

int vscphlp_decryptFrameV1(unsigned char *output,
                          size_t capacity,
                          size_t *outputLength,
                          const unsigned char *input,
                          size_t inputLength,
                          const unsigned char *key,
                          size_t keyLength,
                          const unsigned char *hmacKey,
                          size_t hmacKeyLength);
```

Encryption takes a plaintext inner frame including type byte and CRC, and
returns an encrypted inner frame including IV and tag. Allocate at least
`inputLength + 48` bytes. Pass `NULL, 0` for the IV to generate a fresh random
16-byte IV. An explicit IV must have length 16 and must never be reused with
the same AES key; fixed IVs are suitable only for interoperability tests.
`VSCP_ENCRYPTION_FROM_TYPE_BYTE` selects the algorithm from the input's low
nibble; otherwise select AES128/192/256 explicitly. `NONE` is rejected.

Decryption authenticates before decrypting and validates padding and CRC.
Allocate up to the encrypted input length for the plaintext. Success reports
the unpadded plaintext length. Unlike automatic transport decoding, this
low-level helper **retains the authenticated encryption nibble** in the type
byte. Input and output may alias. Failed calls leave output bytes unchanged
and set `*outputLength` to zero when that pointer is valid.

The inner length must fit 13 bits, including padding, IV, and tag. This helper
limit is separate from the automatic transport's stricter 4,096-byte limit.
With CBC padding, the largest supported plaintext is 8,144 bytes, producing
an 8,177-byte encrypted inner frame.

For example, with application-supplied keys and a valid `plain` frame
(include `<stdio.h>` and `<vscphelperlib.h>`):

```c
unsigned char encrypted[1024];
size_t encryptedSize = 0;
int result = vscphlp_encryptFrameV1(
    encrypted, sizeof(encrypted), &encryptedSize,
    plain, plainSize, aesKey, 32, hmacKey, 32,
    NULL, 0, VSCP_ENCRYPTION_AES256);
if (result != VSCP_ERROR_SUCCESS) {
    fprintf(stderr, "Frame encryption failed (error %d)\n", result);
}
```

Supply a capacity large enough for your frame; this example's 1,024-byte
buffer is not a universal maximum. On success, use exactly `encryptedSize`
bytes and add the version-1 prefix if your application owns the stream.
Do **not** pass this result to automatic encrypted send (which expects
plaintext), or use legacy two-byte framing for it.

### Standalone C++ example

With `plain` as a `std::vector<unsigned char>` containing a valid inner frame,
and two independent 32-byte `std::array` keys:

```cpp
std::vector<unsigned char> encrypted(plain.size() + 48);
size_t encryptedSize = 0;
int result = vscphlp_encryptFrameV1(
    encrypted.data(), encrypted.size(), &encryptedSize,
    plain.data(), plain.size(), aesKey.data(), aesKey.size(),
    hmacKey.data(), hmacKey.size(), nullptr, 0, VSCP_ENCRYPTION_AES256);
if (result != VSCP_ERROR_SUCCESS) {
    throw std::runtime_error("Authenticated frame encryption failed");
}
encrypted.resize(encryptedSize);
```

Include `<array>`, `<vector>`, `<stdexcept>`, and `<vscphelperlib.h>`.
For decryption, allocate a vector up to the encrypted length, call
`vscphlp_decryptFrameV1`, check its result, and resize to its output length.

### Standalone Python example

The Python wrapper returns `(status, bytes)` and returns `None` instead of
plaintext on failure. Given a valid `plain` inner frame and independent
32-byte keys:

```python
import vscphelper

status, encrypted = vscphelper.encryptFrameV1(plain, aes_key, hmac_key, 3)
if status != 0:
    raise RuntimeError("Encryption failed (error {})".format(status))
status, decrypted = vscphelper.decryptFrameV1(encrypted, aes_key, hmac_key)
if status != 0:
    raise RuntimeError("Authentication/decryption failed (error {})".format(status))
```

`decryptFrameV1` retains the encryption nibble just like the C helper.
Omit the optional IV to generate a fresh random IV.

### Standalone JavaScript example

Given a valid `plain` `Buffer` and independent AES-256 and HMAC keys:

```javascript
const { loadHelper, ENCRYPTION } = require('node-vscp-helper');
const api = loadHelper();
const [encryptStatus, encrypted] = api.encryptFrameV1(
    plain, aesKey, hmacKey, ENCRYPTION.AES256);
if (encryptStatus !== 0) throw new Error(`Encryption failed: ${encryptStatus}`);
const [decryptStatus, decrypted] = api.decryptFrameV1(encrypted, aesKey, hmacKey);
if (decryptStatus !== 0) throw new Error(`Authentication failed: ${decryptStatus}`);
```

The values are Node-owned buffers; failures return `null` for the output.

## Wire format and interoperability

The authenticated record is:

```text
[0x55][version:3 | innerLength:13, big-endian]
[type/encryption:1][PKCS#7 AES-CBC ciphertext][IV:16][HMAC tag:16]
```

Version is `1`. `innerLength` includes type, ciphertext, IV, and tag, not the
three-byte prefix. HMAC-SHA-256 authenticates
`prefix || type/encryption || ciphertext || IV`. The first 16 digest bytes
form the tag. Encryption covers the body and CRC, not the type byte.

Standalone helpers reconstruct the canonical prefix for HMAC, but do not
read/write it. A caller implementing its own transport must validate the
received marker, version, length, and expected algorithm before decrypting.
Automatic transport performs these checks and never silently falls back.

## Errors and availability

Each function returns `VSCP_ERROR_SUCCESS` on success. Possible errors are:

| Function | Error codes |
| --- | --- |
| `vscphlp_setBinarySecurity` | `VSCP_ERROR_INVALID_HANDLE`, `VSCP_ERROR_PARAMETER` |
| `vscphlp_getBinarySecurity` | `VSCP_ERROR_INVALID_HANDLE`, `VSCP_ERROR_PARAMETER` |
| `vscphlp_encryptFrameV1` | `VSCP_ERROR_PARAMETER`, `VSCP_ERROR_SIZE`, `VSCP_ERROR_BUFFER_TO_SMALL`, `VSCP_ERROR_ERROR`, `VSCP_ERROR_MEMORY` |
| `vscphlp_decryptFrameV1` | `VSCP_ERROR_PARAMETER`, `VSCP_ERROR_INVALID_FRAME`, `VSCP_ERROR_BUFFER_TO_SMALL`, `VSCP_ERROR_MEMORY` |

`VSCP_ERROR_PARAMETER` covers invalid pointers, key/IV lengths or algorithms,
and attempts to reconfigure a connected binary session. Decryption reports
`VSCP_ERROR_INVALID_FRAME` for failed authentication, padding, or CRC checks.
Always check the return value before using an output length or plaintext. See
[error handling](error_handling.md) for code values.

The updated wrappers return these native status codes. Invalid wrapper argument
types and out-of-range timeouts additionally raise language exceptions.

The build applies a repository-owned transport patch to a **build-local copy**
of the pinned VSCP client. It requires Git and leaves downloaded/local
dependency sources untouched. The patch fails explicitly if it cannot be
applied; no reduced-security implementation is substituted.

[filename](./bottom_copyright.md ':include')
