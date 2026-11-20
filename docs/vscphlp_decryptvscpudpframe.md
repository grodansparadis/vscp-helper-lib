# vscphlp_decryptVscpUdpFrame

```clike
int vscphlp_decryptVscpUdpFrame( unsigned char *output, unsigned char *input, size_t len,
                                 const unsigned char *key, const unsigned char *iv,
                                 unsigned char nAlgorithm )
```

### Parameters

#### output
Buffer of at least `len` bytes for the decrypted frame.

#### input
The encrypted frame.

#### len
Length of the encrypted frame, including the appended IV.

#### key
AES key (16, 24 or 32 bytes).

#### iv
NULL to use the IV at the end of the frame, or a 16-byte IV.

#### nAlgorithm
1 AES-128, 2 AES-192, 3 AES-256.

### Return Value
`VSCP_ERROR_SUCCESS`, `VSCP_ERROR_INVALID_POINTER`, `VSCP_ERROR_PARAMETER` if `len` is 0, `VSCP_ERROR_ERROR` if decryption fails.

### Description
Decrypts a frame encrypted with [vscphlp_encryptVscpUdpFrame](vscphlp_encryptvscpudpframe.md). The frame is not authenticated: a wrong key or a changed frame can decrypt to wrong data, so check the frame CRC afterwards.

#### C example

```clike
unsigned char plain[512 + 32];
int rv = vscphlp_decryptVscpUdpFrame(plain, encrypted, encryptedLen, key, NULL, 1);
```

#### Python

The [Python binding](bindings.md#python) (pyvscphelper) has `vscphelper.decryptVscpUdpFrame`.

[filename](./bottom_copyright.md ':include')
