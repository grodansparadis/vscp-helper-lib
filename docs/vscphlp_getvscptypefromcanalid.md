

```clike
unsigned short 
vscphlp_getVSCPtypeFromCANALid( const unsigned long id )
```

### Parameters

#### id
Extended 29-bit CANAL id to get head from.

### Return Value
Returns the extracted VSCP type, not an error code.

### Description
Get the VSCP type from a CANAL message ID (CAN ID).

#### C example

```clike
unsigned long cananalid = 0x0c0a0601;
 
unsigned short canal_vscptype = vscphlp_getVSCPtypeFromCANALid( canalid );
if ( 6 == canal_vscptype ) {
    printf("VSCP Type = %d\n", canal_vscptype );
}
else {
    printf("\aError: vscphlp_getVSCPtypeFromCANALid = %d\n", canal_vscptype );
}
```



#### Python example

Using the official [Python helper binding](bindings.md#python):

```python
import vscp
import vscphelper

canal_id = vscphelper.getCANALidFromData(7, 10, 6)
print(vscphelper.getVSCPtypeFromCANALid(canal_id))
```

#### JavaScript availability

The official [Node.js binding](bindings.md#nodejs) does not currently expose this helper API, so there is no equivalent JavaScript example.

[filename](./bottom_copyright.md ':include')