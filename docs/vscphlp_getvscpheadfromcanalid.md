

```clike
unsigned unsigned char 
vscphlp_getVSCPheadFromCANALid( const unsigned long id ))
```

### Parameters

#### id
Extended 29-bit CANBUS id to get head from.

### Return Value
VSCP head byte.

### Description
Get the VSCP head from a CANAL message id. The VSCP head is defined as shown in the [vscp.h](https://github.com/grodansparadis/vscp_software/blob/master/src/vscp/common/vscp.h) header file. 

#### C example

```clike
unsigned char vscphead;
unsigned long canalid = 0x0c0a0601;
vscphead = vscphlp_getVSCPheadFromCANALid( canalid );
if ( 96 == vscphead ) {  // Priority == 3 Not hard coded
    printf("VSCP head = %d\n", vscphead );
}
else {
   printf("\aError: vscphlp_getVSCPheadFromCANALid = %d\n", vscphead );
}
```



[filename](./bottom_copyright.md ':include')
