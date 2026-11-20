# vscphlp_getEncryptionCodeFromToken

```clike
int vscphlp_getEncryptionCodeFromToken( const char *pToken, int *pEncryptionCode )
```

### Parameters

#### pToken
`AES128`, `AES192` or `AES256` (any letter case, surrounding spaces ignored), or an empty string for no encryption.

#### pEncryptionCode
Set to the encryption code: 0 none, 1 AES-128, 2 AES-192, 3 AES-256.

### Return Value
`VSCP_ERROR_SUCCESS`, `VSCP_ERROR_INVALID_POINTER`, `VSCP_ERROR_PARAMETER` for an unknown token.

### Description
Gets the encryption code for an encryption token, as used in configuration files.

#### C example

```clike
int code;
vscphlp_getEncryptionCodeFromToken("AES256", &code);   // 3
```

#### Python

The [Python binding](bindings.md#python) (pyvscphelper) has `vscphelper.getEncryptionCodeFromToken`.

[filename](./bottom_copyright.md ':include')
