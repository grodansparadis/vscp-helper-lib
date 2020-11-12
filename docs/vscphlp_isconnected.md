

```clike
int vscphlp_isConnected( long handle )
```

```python
int vscphlp_isConnected( handle )
```

### Parameters

#### handle
Handle for the communication channel obtained from a call to [vscphlp_newsession](vscphlp_newsession.md).

### Return Value
VSCP_ERROR_SUCCESS if the session is active and VSCP_ERROR_ERROR if it is inactive. VSCP_ERROR_INVALID_HANDLE is returned if an invalid handle is given. 

### Description
Check if the session is active or not. 

#### C example

```clike
if ( VSCP_ERROR_SUCCESS == vscphlp_isConnected( handle1 ) ) {
    // Do your stuff here 
}
```

#### Python example

```python
print "\n\nConnection in progress..."
rv = pyvscphlp_open(h1,"127.0.0.1:9598","admin","secret")
if VSCP_ERROR_SUCCESS == rv :
    print "Command success: pyvscphlp_open on channel 1"
else:
    pyvscphlp_closeSession(h1)
    raise ValueError('Command error: pyvscphlp_open on channel 1  Error code=%d' % rv )
 
if ( VSCP_ERROR_SUCCESS == pyvscphlp_isConnected(h1) ):
    print "CONNECTED!"
else:
    print "DISCONNECTED!"
```




[filename](./bottom_copyright.md ':include')
