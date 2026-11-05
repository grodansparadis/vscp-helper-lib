

```clike
int vscphlp_writeVscpDataWithSizeToString( const unsigned char *pData,
                                           unsigned short sizeData,
                                           char *pStr,
                                           size_t len,
                                           int bUseHtmlBreak,
                                           int bBreak )
```

### Parameters

#### pData
Pointer to VSCP data array.

#### size
Number of bytes in data array.

#### pstr
Pointer to string buffer that will receive string.

#### len
Size of string receive buffer.

#### bUseHtmlBreak
Set to true (nonzero) to use “\<br\>” instead of “\n” as the line break in the string.
bBreak

Set to true (nonzero) to add the break character.


### Return Value
`VSCP_ERROR_SUCCESS` (`0`) indicates success. Possible error codes: `VSCP_ERROR_ERROR`.

### Description
Write VSCP data in readable form to a possibly multi line string from a data array with size.

#### C availability

The current header declares the data buffer and size before the output
buffer, but the implementation expects the output buffer first. Calling the
function using the current header declaration is unsafe; do not use the C
API until the declaration and implementation agree. The Python wrapper
uses the implementation's argument order.


#### Python example

Using the official [Python helper binding](bindings.md#python):

```python
import vscp
import vscphelper

data = bytearray([11, 22, 33, 44])
result, value = vscphelper.writeVscpDataWithSizeToString(data)
if result != vscp.VSCP_ERROR_SUCCESS:
    raise RuntimeError("writeVscpDataWithSizeToString failed (error {})".format(result))
print(value)
```

#### JavaScript availability

The official [Node.js binding](bindings.md#nodejs) does not currently expose this helper API, so there is no equivalent JavaScript example.

[filename](./bottom_copyright.md ':include')