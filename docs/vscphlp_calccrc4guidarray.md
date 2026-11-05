

```clike
unsigned char vscphlp_calcCRC4GUIDArray( unsigned char *pguid )
```

### Parameters

#### pguid
Array of sixteen bytes containing the GUID in most-significant-byte-first order.


### Return Value
Returns the 8-bit GUID CRC, not an error code. The array pointer must be valid.

### Description
Calculate the 8-bit CRC for a GUID array.

#### C example

```clike
// Calculate CRC for GID array
unsigned char GUID2[16];
memset( GUID2, 0, 16 );
for ( int i=0;i<16; i++ ) {
    GUID2[i] = i;
}
unsigned char crc8 = vscphlp_calcCRC4GUIDArray( GUID2 );
printf("CRC = %02X\n", crc8 );
```



#### Python example

Using the official [Python helper binding](bindings.md#python):

```python
from ctypes import c_ubyte

import vscp
import vscphelper

guid = (c_ubyte * 16)(*range(16))
print(vscphelper.calcCRC4GUIDArray(guid))
```

#### JavaScript availability

See the [Node.js binding](bindings.md#nodejs) for C API access and native library availability.

[filename](./bottom_copyright.md ':include')