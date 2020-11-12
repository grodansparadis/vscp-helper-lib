

```clike
int vscphlp_readMaskFromString( vscpEventFilter *pFilter, 
                                const char * strMask )
```

### Parameters

#### pFilter

Filter structure to write mask to.

#### strMask

Mask in string form

    mask-priority, mask-class, mask-type, mask-GUID

as in this example

    1,0x00ff,0x00ff,ff:ff:ff:ff:ff:ff:ff:ff:ff:ff:ff:ff:ff:ff:ff:ff  

and all is optional but if given must be given in order.This means that

    1,0x00ff

will be interpreted as

    1,0x00ff,0x0000,00:00:00:00:00:00:00:00:00:00:00:00:00:00:00:00  



### Return Value
VSCP_ERROR_SUCCESS on success. 

### Description
Read a mask from a string. If strMask is an empty string elements in mask will be set to zero. 

#### C example

```clike
if ( VSCP_ERROR_SUCCESS != vscphlp_readMaskFromString( &filter, 
                "1,0x0000,0x0006,ff:ff:ff:ff:ff:ff:ff:01:00:00:00:00:00:00:00:00" ) ) {
    printf( "\aError: vscphlp_readMaskFromString\n");   
}
```

#### See Also
* [vscphlp_writeMaskToString](vscphlp_writemasktostring.md)



[filename](./bottom_copyright.md ':include')