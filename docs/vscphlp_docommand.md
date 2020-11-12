

```clike
int vscphlp_doCommand( long handle, 
                        const char *cmd )
```

```python
int vscphlp_doCommand( handle, command )
```

### Parameters

#### handle
Handle for the communication channel obtained from a call to [vscphlp_newsession](vscphlp_newsession.md).

#### cmd
This is the command that should be sent to the server. It should be terminated with “\r\n”.


### Return Value
VSCP_ERROR_SUCCESS if the VSCP daemon respond with +OK after it has received the command and VSCP_ERROR_ERROR if not (-OK) or no response before the timeout expires. VSCP_ERROR_CONNECTION is returned if the communication channel is not open. VSCP_ERROR_INVALID_HANDLE is returned if an invalid handle is given. 

### Description
Send a command over the communication link. The command should have “\r\n” to it's end. The response from the server will be checked for +OK. 

#### C example

```clike
if ( VSCP_ERROR_SUCCESS == vscphlp_doCommand( handle1, "NOOP\r\n" ) ) {
    printf("Command sent successfully!\n");   
}
```

#### Python example

```python
print "command: doCommand"
command = "NOOP\r\n"
rv = pyvscphlp_doCommand( h1, command )
if VSCP_ERROR_SUCCESS != rv :
    pyvscphlp_closeSession(h1)
    raise ValueError('Command error: ''doCommand''  Error code=%d' % rv ) 
```

### See Also
[vscphlp_checkReply](vscphlp_checkreply.md)  
[vscphlp_clearLocalInputQueue](vscphlp_clearlocalinputqueue.md)



[filename](./bottom_copyright.md ':include')