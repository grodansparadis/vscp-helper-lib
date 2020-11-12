

```clike
int vscphlp_close( long handle )
```

```python
int pyvscphlp_close( handle )
```

### Parameters

#### handle
Handle for the communication channel obtained from a call to [vscphlp_newsession](vscphlp_newsession.md).

### Return Value
VSCP_ERROR_SUCCESS is returned on sucess. VSCP_ERROR_INVALID_HANDLE will be returned if the interface is not initialized. 

### Description
Close the interface. 

#### C example

```clike
if ( VSCP_ERROR_SUCCESS == vscphlp_close( handle1 ) ) {
    prinf("Closed successfully.\n");
 }
```

#### Python example

```python
print "command: close"
rv = pyvscphlp_close(h1)
if VSCP_ERROR_SUCCESS != rv :
    pyvscphlp_closeSession(h1)
    raise ValueError('Command error: close  Error code=%d' % rv )
```

### See Also
[vscphlp_open](vscphlp_open.md)  
[vscphlp_openInterface](vscphlp_openinterface.md)  



[filename](./bottom_copyright.md ':include')