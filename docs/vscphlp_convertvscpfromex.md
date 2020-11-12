

```clike
int vscphlp_convertVSCPfromEx( vscpEvent *pEvent, 
                    const vscpEventEx *pEventEx )
```

### Parameters

#### pEvent
VSCP event to convert to.

#### pEventEx
VSCP event ex to convert from.

### Return Value
VSCP_ERROR_SUCCESS on success. 

### Description
Convert VSCP ex. event form to standard form.

#### C example

```clike
if ( VSCP_ERROR_SUCCESS != vscphlp_convertVSCPfromEx( pEvent, &ex4 ) ) {
    printf( "\aError: vscphlp_convertVSCPfromEx\n");
}
```

### See Also
[vscphlp_convertVSCPtoEx](vscphlp_convertvscptoex.md)



[filename](./bottom_copyright.md ':include')