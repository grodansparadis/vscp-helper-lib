

```clike
int vscphlp_isGUIDEmpty( unsigned char *pGUID )
```

### Parameters

#### pGUID
GUID array to check for all zeros.

### Return Value
Returns `1` if the GUID is empty and `0` otherwise. A null pointer also returns `0`; these
are boolean values, not VSCP error codes.

### Description
Check if GUID is empty (all nulls). 

#### C example

```clike
unsigned char emptyGUID[16];
memset( emptyGUID,0, 16 );
if ( vscphlp_isGUIDEmpty( emptyGUID ) ) {
    printf( "vscphlp_isGUIDEmpty  - GUID is detected as empty as it should be\n" );    
}
else {
    printf( "\aError: vscphlp_isGUIDEmpty\n");
}
 
if ( vscphlp_isGUIDEmpty( GUID2 ) ) {
    printf( "\aError: vscphlp_isGUIDEmpty\n");    
}
else {
    printf( "vscphlp_isGUIDEmpty  - GUID is detected as NOT empty as it should be\n" );
}
```



#### Python example

Using the official [Python helper binding](bindings.md#python):

```python
from ctypes import c_ubyte

import vscp
import vscphelper

guid = (c_ubyte * 16)()
print(bool(vscphelper.isGuidEmpty(guid)))
```

#### JavaScript availability

See the [Node.js binding](bindings.md#nodejs) for C API access and native library availability.

[filename](./bottom_copyright.md ':include')