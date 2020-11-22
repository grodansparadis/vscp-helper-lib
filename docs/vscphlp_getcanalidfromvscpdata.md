

```clike
unsigned long 
vscphlp_getCANALidFromVSCPdata( unsigned char priority, 
                                unsigned short vscp_class, 
                                unsigned short vscp_type )
```

### Parameters

#### priority
VSCP event priority (0-7).

#### vscp_class
VSCP Class.

#### vscp_type
VSCP type.

### Return Value
CANAL (CAN) id. 

### Description
Construct a CANAL id (CAN id ) from a VSCP event. 

#### C example

```clike
unsigned long constr_canal_id2 = vscphlp_getCANALidFromVSCPdata( 3, 10, 6 ); 
if ( 0x0c0a0600 == constr_canal_id2 ) {
    printf("Nickname = %08X\n", constr_canal_id2 );
}
else {
   printf("\aError: vscphlp_getVSCPnicknameFromCANALid = %08X\n", constr_canal_id2 );
} 
```



[filename](./bottom_copyright.md ':include')