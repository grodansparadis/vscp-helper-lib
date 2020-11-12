
```clike
int vscphlp_checkReply( long handle, int bclear )
```

```python
int pyvscphlp_checkReply( handle, bclear )
```

### Parameters

#### handle
Handle for the communication channel obtained from a call to [vscphlp_newsession](vscphlp_newsession.md).

#### bclear
If TRUE (not zero) the input buffer will be cleared before starting to wait for a +OK/-OK in the incoming data.


### Return Value
VSCP_ERROR_SUCCESS if the VSCP daemon respond with “+OK” after it has received the command and VSCP_ERROR_ERROR if not or no response before the timeout expires. 

### Description
Check reply data for “+OK”/“-OK” on server. 

#### C example

```clike
if ( VSCP_ERROR_SUCCESS == vscphlp_checkReply( handle1, TRUE ) ) {
    printf("+OK was received from VSCP daemon.\n");   
}


```

#### Python example

```python
print "command: vscphlp_checkReply"
rv = lib.vscphlp_checkReply( h1, command, 1)
if VSCP_ERROR_SUCCESS != rv :
    pyvscphlp_closeSession(h1)
    raise ValueError('Command error: ''vscphlp_checkReply''  Error code=%d' % rv ) 
```

### See Also
[vscphlp_doCommand](vscphlp_docommand.md)



[filename](./bottom_copyright.md ':include')