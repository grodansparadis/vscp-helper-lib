

```clike
int vscphlp_openInterface( long handle,
                            const char *interface, 
                            unsigned long flags )
```

```python
int pyvscphlp_openInterface( handle,
                               interface, 
                               flags )
```

### Parameters

#### handle
Handle for the communication channel obtained from a call to [vscphlp_newsession](vscphlp_newsession.md).one

#### interface
Pointer to a string with the name of interface to open. The format of this string is

    host;username;password

or

    tcp://host;username;password

where in both cases host is

    host-address:port

#### flags
Flags to use for the interface. Currently not used.


### Return Value
Possible return values are the same as for [vscphlp_Open](vscphlp_open.md)

### Description
Opens a session to the TCP/IP interface of a VSCP server. 

#### C example

```clike
 // Open Channel 1
rv=vscphlp_open( handle1, "192.168.1.9:9598;admin;secret" ); 
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
rv = pyvscphlp_openInterface(h1,"127.0.0.1:9598;admin;secret")
if VSCP_ERROR_SUCCESS == rv :
    print "Command success: pyvscphlp_openInterface on channel 1"
else:
    pyvscphlp_closeSession(h1)
    raise ValueError('Command error: pyvscphlp_openInterface on channel 1  Error code=%d' % rv )
```

### See Also
[vscphlp_open](vscphlp_open.md)  
[vscphlp_close](vscphlp_close.md)



[filename](./bottom_copyright.md ':include')