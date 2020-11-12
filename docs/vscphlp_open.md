

```clike
long vscphlp_open( long handle,
                        const char *host, 
                        const char *username, 
                        const char *password )
```

```python
long pyvscphlp_open( handle,
                     host, 
                     username, 
                     password )
```

### Parameters

#### handle
Handle for the communication channel obtained from a call to [vscphlp_newsession](vscphlp_newsession.md).

#### host

String pointing to hostname of host to connect to. This can be a name that needs to be resolved e.g. “”www.grodansparadis.com” or a dotted IP-address e.g. “192.168.1.1”. The general format for the hostname is

    [PROTO://]HOST:PORT[:CERT][:CA_CERT] 

where PROTO could be tcp:// or ssl://. If HOST is not an IP address, the system will resolve it - beware that standard blocking resolver will be used. It is a good practice to pre-resolve hosts beforehand and use only IP addresses to avoid blocking an IO thread.

For SSL connections, specify CERT if server is requiring client auth. Specify CA_CERT to authenticate server certificate. All certificates must be in PEM format.
handle

#### username
Username to use as credentials for login to the remote VSCP daemon.
pPassword

#### password
Password to use as credentials for login to the remote VSCP daemon.


### Return Value
VSCP_ERROR_SUCCESS is returned on success. VSCP_ERROR_INVALID_HANDLE will be returned if the interface is not initialized, VSCP_ERROR_MEMORY will there is problem to allocate needed structures, VSCP_ERROR_TIMEOUT is returned if connection or responses is not received in time, VSCP_ERROR_USER for problems with username, VSCP_ERROR_PASSWORD for problems with password and for all other error VSCP_ERROR_ERROR will be returned. 

### Description
Opens a session to the TCP/IP interface of a VSCP server. 

#### C example

```clike
// Open Channel 1
rv=vscphlp_open( handle1, 
                    "127.0.0.1:9598",
                    "admin",
                    "secret" ); 
if ( VSCP_ERROR_SUCCESS == rv ) {
    printf("Command success: vscphlp_open on channel 1\n");
}
else {
    printf("\aCommand error: vscphlp_open on channel 1  Error code=%d\n", rv);
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
```

### See Also
[vscphlp_openInterface](vscphlp_openinterface.md)  
[vscphlp_close](vscphlp_close.md)



[filename](./bottom_copyright.md ':include')