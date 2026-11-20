# vscphlp_encryptVscpUdpFrame

```clike
int vscphlp_encryptVscpUdpFrame( unsigned char *output, unsigned char *input, size_t len,
                                 const unsigned char *key, const unsigned char *iv,
                                 unsigned char nAlgorithm )
```

### Parameters

#### output
Buffer of at least `len + 32` bytes for the encrypted frame.

#### input
The frame (from [vscphlp_writeEventToUdpFrame](vscphlp_writeeventtoudpframe.md)).

#### len
Length of the frame, including its first (type) byte.

#### key
AES key: 16, 24 or 32 bytes for algorithm 1, 2 or 3.

#### iv
16-byte initialization vector, or NULL for a random one.

#### nAlgorithm
1 AES-128, 2 AES-192, 3 AES-256.

### Return Value
`VSCP_ERROR_SUCCESS`, `VSCP_ERROR_INVALID_POINTER`, `VSCP_ERROR_PARAMETER` if `len` is 0, `VSCP_ERROR_ERROR` if encryption fails.

### Description
Encrypts a legacy (version 0) frame: the first byte is kept with the algorithm in its low nibble, the rest is AES-CBC encrypted with PKCS#7 padding, and the IV is appended. The encrypted frame is `1 + 16 * ((len - 1) / 16 + 1) + 16` bytes. This frame has no authentication; for new designs use the authenticated [vscphlp_encryptFrameV1](frame_security.md#standalone-authenticated-frame-helpers).

#### C example

```clike
unsigned char out[512 + 32];
int rv = vscphlp_encryptVscpUdpFrame(out, frame, size, key, NULL, 1);
size_t outLen = 1 + 16 * ((size - 1) / 16 + 1) + 16;
```

#### Python

The [Python binding](bindings.md#python) (pyvscphelper) has `vscphelper.encryptVscpUdpFrame`.

[filename](./bottom_copyright.md ':include')
