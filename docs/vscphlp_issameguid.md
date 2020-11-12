

```clike
int vscphlp_isSameGUID( const unsigned char *pGUID1, 
                        const unsigned char *pGUID2 )
```

### Parameters

#### pGUID1
GUID1 to compare.

#### pGUID2
GUID2 to compare.


### Return Value
True (non-zero) if GUIDs are the same. 

### Description
Check if two GUID's is equal to each other. 

#### C example

```clike
if ( vscphlp_isSameGUID( emptyGUID, GUID2) ) {
    printf( "\aError: vscphlp_isSameGUID\n");
}
else {
    printf( "vscphlp_isSameGUID  - Correct, GUIDs are not the same.\n" );
}
```



[filename](./bottom_copyright.md ':include')