

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
True (non-zero) if GUIDs are the same. 

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

The official [Node.js binding](bindings.md#nodejs) does not currently expose this helper API, so there is no equivalent JavaScript example.

[filename](./bottom_copyright.md ':include')