

```clike
unsigned char
vscphlp_getVSCPnicknameFromCANALid( const unsigned long id )
```

### Parameters

#### id
Extended 29-bit CAN id to get the nickname from.

### Return Value
Returns the extracted node nickname, not an error code.

### Description
Get the VSCP 8-bit nickname from a CANAL message ID.

#### C example

```clike
unsigned long canalid = 0x0c0a0601;
unsigned char canal_nickname = vscphlp_getVSCPnicknameFromCANALid( canalid );
printf("VSCP nickname = %u\n", (unsigned int)canal_nickname);
```



#### Python example

Using the official [Python helper binding](bindings.md#python):

```python
import vscp
import vscphelper

canal_id = vscphelper.getCANALidFromData(7, 10, 6)
print(vscphelper.getVSCPnicknameFromCANALid(canal_id))
```

#### JavaScript availability

The official [Node.js binding](bindings.md#nodejs) does not currently expose this helper API, so there is no equivalent JavaScript example.

[filename](./bottom_copyright.md ':include')