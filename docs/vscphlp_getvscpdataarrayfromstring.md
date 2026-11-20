# vscphlp_getVscpDataArrayFromString

```clike
int vscphlp_getVscpDataArrayFromString( unsigned char *pData,
                                        unsigned short *psizeData,
                                        const char *pstr )
```

### Parameters

#### pData
Buffer of at least 512 bytes that gets the data.

#### psizeData
Set to the number of data bytes.

#### pstr
Comma separated data bytes, for example `1,2,0x10,255`.

### Return Value
`VSCP_ERROR_SUCCESS`, `VSCP_ERROR_INVALID_POINTER`, `VSCP_ERROR_ERROR` if the string is not valid.

### Description
Reads data bytes from a string into a buffer. The same as `vscphlp_setVscpDataArrayFromString`.

#### C example

```clike
unsigned char data[512];
unsigned short size;
if (VSCP_ERROR_SUCCESS == vscphlp_getVscpDataArrayFromString(data, &size, "1,2,0x10")) {
    printf("%d bytes\n", size);   // 3 bytes
}
```

#### Python

The [Python binding](bindings.md#python) (pyvscphelper) has `vscphelper.getVscpDataArrayFromString`.

[filename](./bottom_copyright.md ':include')
