

```clike
int vscphlp_reverseGUID(unsigned char *pGUID)
```


### Parameters

#### pGUID1
GUID array to be reversed.


### Return Value
Return VSCP_ERROR_SUCCESS on success. 

### Description
Reverse a GUID array. 

#### C example

```clike
vscphlp_writeGuidArrayToString( GUID2, strguid2, sizeof( strguid2 )-1 );
printf( "GUID before reverse = %s\n", strguid2 );
if ( VSCP_ERROR_SUCCESS == vscphlp_reverseGUID( GUID2 ) ) {
    vscphlp_writeGuidArrayToString( GUID2, strguid2, sizeof( strguid2 )-1 );
    printf( "GUID  after reverse = %s\n", strguid2 );
}
else {
    printf( "\aError: vscphlp_reverseGUID\n");
}
```



#### Python example

Using the official [Python helper binding](bindings.md#python):

```python
from ctypes import c_ubyte

import vscp
import vscphelper

guid = (c_ubyte * 16)(*range(16))
result = vscphelper.reverseGUID(guid)
if result != vscp.VSCP_ERROR_SUCCESS:
    raise RuntimeError("reverseGUID failed (error {})".format(result))
print(list(guid))
```

#### JavaScript availability

The official [Node.js binding](bindings.md#nodejs) does not currently expose this helper API, so there is no equivalent JavaScript example.

[filename](./bottom_copyright.md ':include')