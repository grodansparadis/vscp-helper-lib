# vscphlp_getEncryptionTokenFromCode

```clike
int vscphlp_getEncryptionTokenFromCode( int nEncryptionCode, char *pEncryptionToken, size_t len )
```

### Parameters

#### nEncryptionCode
0 none, 1 AES-128, 2 AES-192, 3 AES-256.

#### pEncryptionToken
Buffer for the token (`""`, `AES128`, `AES192` or `AES256`).

#### len
Size of the buffer.

### Return Value
`VSCP_ERROR_SUCCESS`, `VSCP_ERROR_INVALID_POINTER`, `VSCP_ERROR_PARAMETER` for a code that is not 0-3, `VSCP_ERROR_BUFFER_TO_SMALL`.

### Description
Gets the encryption token for an encryption code; the opposite of [vscphlp_getEncryptionCodeFromToken](vscphlp_getencryptioncodefromtoken.md).

#### C example

```clike
char token[16];
vscphlp_getEncryptionTokenFromCode(1, token, sizeof(token));   // "AES128"
```

#### Python

The [Python binding](bindings.md#python) (pyvscphelper) has `vscphelper.getEncryptionTokenFromCode`.

[filename](./bottom_copyright.md ':include')
