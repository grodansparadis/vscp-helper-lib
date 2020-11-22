

```clike
unsigned short 
vscphlp_getVSCPnicknameFromCANALid( unsigned long id )
```

### Parameters

#### id
Extended 29-bit CAN id to get head from.

### Return Value
VSCP 8-bit nickname. 

### Description
Get the VSCP 8-bit nickname from a a CANAL message id. 

#### C example

```clike
unsigned long canalid = 0x0c0a0601;
unsigned char canal_nickname = vscphlp_getVSCPnicknameFromCANALid( canalid );
if ( 1 == canal_nickname ) {
    printf("VSCP Type = %d\n", canal_vscptype );
}
else {
    printf("\aError: vscphlp_getVSCPnicknameFromCANALid = %d\n", canal_nickname );
}
```



[filename](./bottom_copyright.md ':include')