

```clike
int vscphlp_clearLocalInputQueue( long handle )
```

```python
int pyvscphlp_clearLocalInputQueue( handle )
```

### Parameters

#### handle
Handle for the communication channel obtained from a call to [vscphlp_newsession](vscphlp_newsession.md).

### Return Value
rVSCP_ERROR_SUCCESS if the VSCP daemon cleared the queue and VSCP_ERROR_ERROR if not or no response is received before the timeout expires. VSCP_ERROR_INVALID_HANDLE is returned if an invalid handle is given. rrr

### Description
Clear the local communication input queue. This is the same things that is done when setting **bClear** for [vscphlp_checkReply](vscphlp_checkreply)

#### C example

```clike
if ( VSCP_ERROR_SUCCESS == vscphlp_clearLocalInputQueue( handle1 ) ) {
    printf("Our local input queue cleared.\n");   
}
```

#### Python example

```python
print "command: pyvscphlp_clearLocalInputQueue"
command = "NOOP\r\n"
rv = lib.pyvscphlp_clearLocalInputQueue( h1 )
if VSCP_ERROR_SUCCESS != rv :
    pyvscphlp_closeSession(h1)
    raise ValueError('Command error: ''pyvscphlp_clearLocalInputQueue''  Error code=%d' % rv )
```

### See Also
[vscphlp_checkReply](vscphlp_checkreply)  
[vscphlp_doCommand](vscphlp_docommand.md)



[filename](./bottom_copyright.md ':include')