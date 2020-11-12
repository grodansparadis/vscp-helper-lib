

```clike
unsigned short 
vscphlp_getVSCPtypeFromCANANALid( const unsigned long id )
```

### Parameters

#### id
Extended 29-bit CANAL id to get head from.

### Return Value
VSCP type. 

### Description
Get the VSCP type from a a CANAL message id (CAN id). 

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



[filename](./bottom_copyright.md ':include')