

```clike
int vscphlp_isGUIDEmpty( unsigned char *pGUID )
```

### Parameters

#### pGUID
GUID array to check for all zeros.

### Return Value
True (non-zero) if GUID are empty. 

### Description
Check if GUID is empty (all nulls). 

#### C example

```clike
unsigned char emptyGUID[16];
memset( emptyGUID,0, 16 );
if ( vscphlp_isGUIDEmpty( emptyGUID ) ) {
    printf( "vscphlp_isGUIDEmpty  - GUID is detected as empty as it should be\n" );    
}
else {
    printf( "\aError: vscphlp_isGUIDEmpty\n");
}
 
if ( vscphlp_isGUIDEmpty( GUID2 ) ) {
    printf( "\aError: vscphlp_isGUIDEmpty\n");    
}
else {
    printf( "vscphlp_isGUIDEmpty  - GUID is detected as NOT empty as it should be\n" );
}
```



[filename](./bottom_copyright.md ':include')