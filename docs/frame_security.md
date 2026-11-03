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

The Python wrapper does not yet expose these functions; use `ctypes` with an
open session as in the [TLS example](tls.md#python-example). Set
`VSCPHELPER_LIB` to the full shared-library path. Do not mix these sessions
with Python-wrapper-owned sessions.

```python
import ctypes
import os

library = ctypes.CDLL(os.environ["VSCPHELPER_LIB"])
byte_pointer = ctypes.POINTER(ctypes.c_ubyte)
library.vscphlp_setBinarySecurity.argtypes = [
    ctypes.c_long, ctypes.c_int,
    byte_pointer, ctypes.c_size_t, byte_pointer, ctypes.c_size_t,
]
library.vscphlp_setBinarySecurity.restype = ctypes.c_int
library.vscphlp_doCmdBinary.argtypes = [ctypes.c_long]
library.vscphlp_doCmdBinary.restype = ctypes.c_int


def enable_authenticated_binary(session, aes_key, hmac_key):
    if len(aes_key) != 32 or len(hmac_key) != 32:
        raise ValueError("AES-256 and HMAC keys must each be 32 bytes")
    aes = (ctypes.c_ubyte * 32).from_buffer_copy(aes_key)
    mac = (ctypes.c_ubyte * 32).from_buffer_copy(hmac_key)
    result = library.vscphlp_setBinarySecurity(session, 3, aes, 32, mac, 32)
    if result != 0:
        raise RuntimeError("Binary security configuration failed (error {})".format(result))
    result = library.vscphlp_doCmdBinary(session)
    if result != 0:
        raise RuntimeError("Binary negotiation failed (error {})".format(result))
```

Pass keys obtained securely from your application, not the public test vectors.
Use the [binary ctypes functions](binary_link.md#python-example) afterward:
they now operate on plaintext frames while the transport handles AES/HMAC.

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

These AES-256 helpers return Python-owned copies. Keep `crypto_library` loaded
while calling them. A failed authentication raises an exception instead of
returning plaintext.

```python
import ctypes
import os

crypto_library = ctypes.CDLL(os.environ["VSCPHELPER_LIB"])
crypto_byte_pointer = ctypes.POINTER(ctypes.c_ubyte)
crypto_library.vscphlp_encryptFrameV1.argtypes = [
    crypto_byte_pointer, ctypes.c_size_t, ctypes.POINTER(ctypes.c_size_t),
    crypto_byte_pointer, ctypes.c_size_t,
    crypto_byte_pointer, ctypes.c_size_t, crypto_byte_pointer, ctypes.c_size_t,
    crypto_byte_pointer, ctypes.c_size_t, ctypes.c_int,
]
crypto_library.vscphlp_encryptFrameV1.restype = ctypes.c_int
crypto_library.vscphlp_decryptFrameV1.argtypes = [
    crypto_byte_pointer, ctypes.c_size_t, ctypes.POINTER(ctypes.c_size_t),
    crypto_byte_pointer, ctypes.c_size_t,
    crypto_byte_pointer, ctypes.c_size_t, crypto_byte_pointer, ctypes.c_size_t,
]
crypto_library.vscphlp_decryptFrameV1.restype = ctypes.c_int


def frame_crypto_keys(aes_key, hmac_key):
    if len(aes_key) != 32 or len(hmac_key) != 32:
        raise ValueError("AES-256 and HMAC keys must each be 32 bytes")
    return ((ctypes.c_ubyte * 32).from_buffer_copy(aes_key),
            (ctypes.c_ubyte * 32).from_buffer_copy(hmac_key))


def encrypt_frame_v1(plain, aes_key, hmac_key):
    aes, mac = frame_crypto_keys(aes_key, hmac_key)
    source = (ctypes.c_ubyte * len(plain)).from_buffer_copy(plain)
    output = (ctypes.c_ubyte * (len(plain) + 48))()
    length = ctypes.c_size_t()
    result = crypto_library.vscphlp_encryptFrameV1(
        output, len(output), ctypes.byref(length), source, len(plain),
        aes, 32, mac, 32, None, 0, 3,
    )
    if result != 0:
        raise RuntimeError("Authenticated encryption failed (error {})".format(result))
    return bytes(output[:length.value])


def decrypt_frame_v1(encrypted, aes_key, hmac_key):
    aes, mac = frame_crypto_keys(aes_key, hmac_key)
    source = (ctypes.c_ubyte * len(encrypted)).from_buffer_copy(encrypted)
    output = (ctypes.c_ubyte * len(encrypted))()
    length = ctypes.c_size_t()
    result = crypto_library.vscphlp_decryptFrameV1(
        output, len(output), ctypes.byref(length), source, len(encrypted),
        aes, 32, mac, 32,
    )
    if result != 0:
        raise RuntimeError("Authentication/decryption failed (error {})".format(result))
    return bytes(output[:length.value])
```

`decrypt_frame_v1` retains the encryption nibble just like the C helper.

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

Functions return `VSCP_ERROR_SUCCESS` on success. Invalid pointers, key/IV
lengths, algorithms, or attempts to reconfigure a connected binary session
return `VSCP_ERROR_PARAMETER`. Other errors include `VSCP_ERROR_INVALID_HANDLE`,
`VSCP_ERROR_BUFFER_TO_SMALL`, `VSCP_ERROR_SIZE`, `VSCP_ERROR_MEMORY`, and
`VSCP_ERROR_INVALID_FRAME` for failed authentication/decryption. Standalone
encryption reports `VSCP_ERROR_ERROR` if the cryptographic operation fails.
Always check the return value before using an output length or plaintext.

The official [Node.js binding](bindings.md#nodejs) does not currently expose
these APIs.

The build applies a repository-owned transport patch to a **build-local copy**
of the pinned VSCP client. It requires Git and leaves downloaded/local
dependency sources untouched. The patch fails explicitly if it cannot be
applied; no reduced-security implementation is substituted.

[filename](./bottom_copyright.md ':include')
