

```clike
unsigned char vscphlp_calcCRC4GUIDString( unsigned char *strguid)
```

### Parameters

#### strguid
String containing a GUID in standard string form.


### Return Value
Returns the 8-bit GUID CRC, not an error code. The string pointer must be non-null; the
parser's result is not returned separately.

### Description
Calculate the 8-bit CRC for a GUID string.

#### C example

```clike
// Calculate GUID for GUID string
char strguid[64];
strcpy( strguid, "FF:FF:FF:FF:FF:FF:FF:00:00:00:00:7F:00:01:01:FD" );
crc8 = vscphlp_calcCRC4GUIDString( strguid);
printf("CRC = %02X\n", crc8 )
```



#### Python example

Using the official [Python helper binding](bindings.md#python):

```python
import vscp
import vscphelper

print(vscphelper.calcCRC4GUIDString("FF:FF:FF:FF:FF:FF:FF:F5:00:00:00:00:00:00:00:01"))
```

#### JavaScript availability

See the [Node.js binding](bindings.md#nodejs) for C API access and native library availability.

[filename](./bottom_copyright.md ':include')