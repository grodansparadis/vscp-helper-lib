

```clike
int vscphlp_convertVSCPtoEx( vscpEventEx *pEventEx, 
                              const vscpEvent *pEvent )
```

### Parameters

#### pEventEx
VSCP event ex to convert to

#### pEvent
VSCP event to convert to.

### Return Value
VSCP_ERROR_SUCCESS on success. 

### Description
Convert VSCP standard event form to ex form. 

#### C example

```clike
vscpEventEx ex4;
if ( VSCP_ERROR_SUCCESS != vscphlp_convertVSCPtoEx( &ex4, pEvent ) ) {
    printf( "\aError: vscphlp_getGuidFromStringToArray\n");
}
```


### See Also
[vscphlp_convertVSCPfromEx](vscphlp_convertvscpfromex.md)



[filename](./bottom_copyright.md ':include')