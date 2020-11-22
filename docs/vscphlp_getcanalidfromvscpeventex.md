

```clike
unsigned long 
vscphlp_getCANALidFromVSCPeventEx( const vscpEventEx *pEvent )
```
### Parameters

#### pEvent
VSCP event.

### Return Value
CANAL (CAN) id.

### Description
Get CANAL id (CAN id) from VSCP event. 

#### C example

```clike
constr_canal_id2 = vscphlp_getCANALidFromVSCPeventEx( &ex ); 
if ( 0x0c0a0600 == constr_canal_id2 ) {
    printf("Nickname = %08X\n", constr_canal_id2 );
}
else {
    printf("\aError: vscphlp_getCANALidFromVSCPeventEx = %08X\n", constr_canal_id2 );
} 
```

### See Also
[vscphlp_getCANALidFromVSCPevent](vscphlp_getcanalidfromvscpevent.md)



[filename](./bottom_copyright.md ':include')