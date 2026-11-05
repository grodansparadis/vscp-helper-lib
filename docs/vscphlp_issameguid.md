

```clike
int vscphlp_isSameGUID( const unsigned char *pGUID1, 
                        const unsigned char *pGUID2 )
```

### Parameters

#### pGUID1
GUID1 to compare.

#### pGUID2
GUID2 to compare.


### Return Value
Returns `1` if the GUIDs are equal and `0` otherwise. A null pointer also returns `0`; these
are boolean values, not VSCP error codes.

### Description
Check whether two GUIDs are equal.

#### C example

```clike
if ( vscphlp_isSameGUID( emptyGUID, GUID2) ) {
    printf( "\aError: vscphlp_isSameGUID\n");
}
else {
    printf( "vscphlp_isSameGUID  - Correct, GUIDs are not the same.\n" );
}
```



#### Python example

Using the official [Python helper binding](bindings.md#python):

```python
from ctypes import c_ubyte

import vscp
import vscphelper

first = (c_ubyte * 16)(*range(16))
second = (c_ubyte * 16)(*range(16))
print(bool(vscphelper.isSameGuid(first, second)))
```

#### JavaScript availability

See the [Node.js binding](bindings.md#nodejs) for C API access and native library availability.

[filename](./bottom_copyright.md ':include')