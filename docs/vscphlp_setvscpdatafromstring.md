

```clike
int vscphlp_setVscpDataFromString( vscpEvent *pEvent, 
                                   const char *pstr )
```

```python
xxxx
```

### Parameters

#### pEvent
VSCP Event which will have its data set.

#### pstr
Pointer to null terminated string that contains data on comma separated form.

### Return Value
VSCP_ERROR_SUCCESS is returned on success. 

### Description
Set data in VSCP event from a string. 

#### C example

```clike
vscpEvent e;
 
if ( VSCP_ERROR_SUCCESS == 
    setVscpDataFromString( e,
                           "1,2,3,4,5,6,0x07,0x55,3,4,0xaa,0xff,0xff" ) ) {
        printf( "OK vscphlp_setVscpDataFromString size=%d Data = \n", e.sizeData );
        for ( int i=0; i<e.sizeData; i++ ) {
            printf("%d ", e.data[i] );
        }
        printf("\n");
}
else {
   printf( "\aError: vscphlp_setVscpDataFromString\n");
}
```



[filename](./bottom_copyright.md ':include')