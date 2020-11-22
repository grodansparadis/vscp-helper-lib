

```clike
int vscphlp_noop( long handle )
```

```python
int pyvscphlp_noop( handle )
```

### Parameters

#### handle
Handle for the communication channel obtained from a call to [vscphlp_newsession](vscphlp_newsession.md).

### Return Value
Return VSCP_ERROR_SUCCESS on success, VSCP_ERROR_ERROR on failure. If the connection is closed VSCP_ERROR_CONNECTION is returned. VSCP_ERROR_PARAMETER is returned if called while in a receive loop. 

### Description
This is a command that can be used for test purposes. It does not do anything else then to send a command over the interfaces and check the result. 

#### C example

```clike
// NOOP on handle1
if ( VSCP_ERROR_SUCCESS == (rv = vscphlp_noop( handle1 ) ) ) {
    printf( "Command success: vscphlp_noop on channel 1\n" );
}
else {
    printf("\aCommand error: vscphlp_noop on channel 1  Error code=%d\n", rv);
}
```

#### Python example

```python
print "command: noop"
rv = lib.vscphlp_noop( h1 )
if VSCP_ERROR_SUCCESS != rv :
    pyvscphlp_closeSession(h1)
    raise ValueError('Command error: ''noop''  Error code=%d' % rv )
```




[filename](./bottom_copyright.md ':include')