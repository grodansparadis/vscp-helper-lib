# VSCP Helper library API - Communication 

This part describes the main functionality and communication methods available in the library.

----

## vscphlp_setResponseTimeout

**c/c++**
`<code="c">`
int vscphlp_setResponseTimeout( long handle, unsigned long timeout )
`</code>`

**Python**
`<code="python">`
int pyvscphlp_setResponseTimeout( handle, timeout )
`</code>`

This is the timeout in seconds used when checking for replies after commands are sent to the server. It can be changed at any time during a communication session. The default is 3000 milliseconds.

#####  handle

Handle for the communication channel obtained from a call to [vscphlp_newSession](./vscphlp_newsession.md).

##### timeout

Timeout in milliseconds. It can also be set before the session is opened.

##### Return value

VSCP_ERROR_SUCCESS is returned on success. VSCP_ERROR_INVALID_HANDLE is returned if an invalid handle is given.

----

## vscphlp_setAfterCommandSleep

**c/c++**
`<code="c">`
int vscphlp_setAfterCommandSleep( long handle, unsigned short millisecondSleep )
`</code>`

**Python**
`<code="python">`
int vscphlp_setAfterCommandSleep( handle, millisecondSleep )
`</code>`

This is the sleep time in milliseconds while waiting for the server to reply to a command. If no valid response is received, the thread sleeps for this value plus 200 milliseconds, then checks the queue again. This repeats until the response timeout expires or a valid response or error response is received. The default is 0 milliseconds.

#####  handle

Handle for the communication channel obtained from a call to [vscphlp_newSession](./vscphlp_newsession.md).

##### secondsTimeout

Timeout in seconds. It can also be set before the session is opened.

##### Return value

VSCP_ERROR_SUCCESS is returned on success. VSCP_ERROR_INVALID_HANDLE is returned if an invalid handle is given.

----

## vscphlp_isConnected

**c/c++**
`<code="c">`
int vscphlp_isConnected( long handle )
`</code>`

**Python**
`<code="python">`
int vscphlp_isConnected( handle )
`</code>`

Check if the session is active or not.

#####  handle

Handle for the communication channel obtained from a call to [vscphlp_newSession](./vscphlp_newsession.md).

##### Return value

VSCP_ERROR_SUCCESS if the session is active and VSCP_ERROR_ERROR if it is inactive. VSCP_ERROR_INVALID_HANDLE is returned if an invalid handle is given.

##### Example (c/c++)

`<code="c">`
    if ( VSCP_ERROR_SUCCESS == vscphlp_isConnected( handle1 ) ) {
        // Do your stuff here 
    }
`</code>`

##### Example (c/c++)

`<code="python">`
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
`</code>`

----

## vscphlp_doCommand

**c/c++**
`<code="c">`
int vscphlp_doCommand( long handle, const char * cmd )
`</code>`

**Python**
`<code="python">`
int vscphlp_doCommand( handle, command )
`</code>`

Send a command over the communication link. The command should end with "\r\n". The server's response is checked for **+OK**.

#####  handle

Handle for the communication channel obtained from a call to [vscphlp_newSession](./vscphlp_newsession.md).

##### cmd

This is the command that should be sent to the server. It should be terminated with "\r\n".

##### Return value

Returns VSCP_ERROR_SUCCESS if the VSCP daemon responds with **+OK** after receiving the command, or VSCP_ERROR_ERROR if it responds with **-OK** or no response arrives before the timeout expires. Returns VSCP_ERROR_CONNECTION if the communication channel is not open and VSCP_ERROR_INVALID_HANDLE if the handle is invalid.

##### Example (c/c++)

`<code="c">`
    if ( VSCP_ERROR_SUCCESS == vscphlp_doCommand( handle1, "NOOP\r\n" ) ) {
        printf("Command sent successfully!\n");   
    ]
`</code>`

##### Example (Python)

`<code="python">`
print "command: doCommand"
command = "NOOP\r\n"
rv = pyvscphlp_doCommand( h1, command )
if VSCP_ERROR_SUCCESS != rv :
    pyvscphlp_closeSession(h1)
    raise ValueError('Command error: ''doCommand''  Error code=%d' % rv ) 
`</code>`

----

## vscphlp_checkReply

**c/c++**
`<code="c">`
int vscphlp_checkReply( long handle, int bClear )
`</code>`

**Python**
`<code="python">`
int pyvscphlp_checkReply( handle, bclear )
`</code>`

Check reply data for "+OK"/"-OK" on server.

#####  handle

Handle for the communication channel obtained from a call to [vscphlp_newSession](./vscphlp_newsession.md).

##### bClear

If TRUE (nonzero), clear the input buffer before waiting for +OK or -OK in the incoming data.

##### Return value

Returns VSCP_ERROR_SUCCESS if the VSCP daemon responds with "+OK" after receiving the command, or VSCP_ERROR_ERROR if it does not or no response arrives before the timeout expires.

##### Example /c/c++)

`<code="c">`
    if ( VSCP_ERROR_SUCCESS == vscphlp_checkReply( handle1, TRUE ) ) {
        printf("+OK was received from VSCP daemon.\n");   
    }
`</code>`

##### Example (Python)

`<code="python">`
print "command: vscphlp_checkReply"
rv = lib.vscphlp_checkReply( h1, command, 1 )
if VSCP_ERROR_SUCCESS != rv :
    pyvscphlp_closeSession(h1)
    raise ValueError('Command error: ''vscphlp_checkReply''  Error code=%d' % rv ) 
`</code>`

----

## vscphlp_clearLocalInputQueue

**c/c++**
`<code="c">`
int vscphlp_clearLocalInputQueue( long handle )
`</code>`

**Python**
`<code="python">`
int pyvscphlp_clearLocalInputQueue( handle )
`</code>`

Clear the local communication input queue. This is the same operation performed when **bClear** is set for [vscphlp_checkReply](#vscphlp_checkReply).

#####  handle

Handle for the communication channel obtained from a call to [vscphlp_newSession](./vscphlp_newsession.md).

##### Return value

VSCP_ERROR_SUCCESS if the VSCP daemon cleared the queue and VSCP_ERROR_ERROR if not or no response is received before the timeout expires.  VSCP_ERROR_INVALID_HANDLE is returned if an invalid handle is given.

##### Example (c/c++)

`<code="c">`
    if ( VSCP_ERROR_SUCCESS == vscphlp_clearLocalInputQueue( handle1 ) ) {
        printf("Our local input queue cleared.\n");   
    }
`</code>`

##### Example (Python)

`<code="c">`
print "command: pyvscphlp_clearLocalInputQueue"
command = "NOOP\r\n"
rv = lib.pyvscphlp_clearLocalInputQueue( h1 )
if VSCP_ERROR_SUCCESS != rv :
    pyvscphlp_closeSession(h1)
    raise ValueError('Command error: ''pyvscphlp_clearLocalInputQueue''  Error code=%d' % rv ) 
`</code>`
----

## vscphlp_open

This is an archived reference. For current connection and TLS behavior, see
[vscphlp_open](../vscphlp_open.md) and [TLS connections](../tls.md).

**c/c++**
`<code="c">`
int vscphlp_open( long handle,
                        const char *Host, 
                        const char *pUsername, 
                        const char *pPassword )
`</code>`

**Python**
`<code="python">`
long pyvscphlp_open( handle,
                     host, 
                     username, 
                     password )
`</code>`

Opens a session to the TCP/IP interface of a VSCP server.

#####  handle

Handle for the communication channel obtained from a call to [vscphlp_newSession](./vscphlp_newsession.md).

#####  pHost

The endpoint is `stcp://host:port` for TLS, or `tcp://host:port` or
`host:port` for unencrypted TCP.

The legacy `ssl://` prefix and certificate path suffixes are not supported by
the current API. See the [TLS guide](../tls.md) for trust configuration and
client-certificate limitations.

#####  handle

Handle for the communication channel obtained from a call to [vscphlp_newSession](./vscphlp_newsession.md).

#####  pUserName

Username to use as credentials for login to the remote VSCP daemon. 

#####  pPassword

Password to use as credentials for login to the remote VSCP daemon.

##### Return value

See the current [vscphlp_open reference](../vscphlp_open.md) for return values.

##### Example (c/c++)

`<code="c">`
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
`</code>`

##### Example (Python)

`<code="python">`
print "\n\nConnection in progress..."
rv = pyvscphlp_open(h1,"127.0.0.1:9598","admin","secret")
if VSCP_ERROR_SUCCESS == rv :
    print "Command success: pyvscphlp_open on channel 1"
else:
    pyvscphlp_closeSession(h1)
    raise ValueError('Command error: pyvscphlp_open on channel 1  Error code=%d' % rv )
`</code>`

----

## vscphlp_openInterface

This is an archived reference. See the current
[vscphlp_openInterface reference](../vscphlp_openinterface.md) for TLS and
credential handling.

**c/c++**
`<code="c">`
int vscphlp_openInterface( long handle,
                                   const char *pInterface, 
                                   unsigned long flags )
`</code>`

**Python**
`<code="python">`
int pyvscphlp_openInterface( handle,
                               interface, 
                               flags )
`</code>`

#####  handle

Handle for the communication channel obtained from a call to [vscphlp_newSession](./vscphlp_newsession.md).

#####  pInterface

Pointer to a string containing the name of the interface to open. The string format is:

    host;username;password

or

    tcp://host;username;password

or

    stcp://host;username;password

where in each case **host** is

    host-address:port


#####  flags

Flags to use for the interface. Currently not used.

#####  Return value

Possible return values are the same as for [vscphlp_open](../vscphlp_open.md).

##### Example (c/c++)

`<code="c">`
    // Open Channel 1
    rv=vscphlp_openInterface( handle1, "192.168.1.9:9598;admin;secret", 0 );
    if ( VSCP_ERROR_SUCCESS == rv ) {
        printf("Command success: vscphlp_openInterface on channel 1\n");
    }
    else {
        printf("\aCommand error: vscphlp_openInterface on channel 1  Error code=%d\n", rv);
    }
`</code>`

##### Example (Python)

`<code="python">`
print "\n\nConnection in progress..."
rv = pyvscphlp_openInterface(h1,"127.0.0.1:9598;admin;secret")
if VSCP_ERROR_SUCCESS == rv :
    print "Command success: pyvscphlp_openInterface on channel 1"
else:
    pyvscphlp_closeSession(h1)
    raise ValueError('Command error: pyvscphlp_openInterface on channel 1  Error code=%d' % rv )
`</code>`

----

## vscphlp_close

**c/c++**
`<code="c">`
int vscphlp_close( long handle )
`</code>`

**Python**
`<code="python">`
int pyvscphlp_close( handle )
`</code>`

Close the interface.

#####  handle

Handle for the communication channel obtained from a call to [vscphlp_newSession](./vscphlp_newsession.md).

##### return==  

Returns VSCP_ERROR_SUCCESS on success or VSCP_ERROR_INVALID_HANDLE if the interface is not initialized.

##### Example (c/c++)

`<code="c">`
    if ( VSCP_ERROR_SUCCESS == vscphlp_close( handle1 ) ) {
        // prinf("Closed successfully.\n");
    }
`</code>`

##### Example (Python)

`<code="python">`
print "command: close"
rv = pyvscphlp_close(h1)
if VSCP_ERROR_SUCCESS != rv :
    pyvscphlp_closeSession(h1)
    raise ValueError('Command error: close  Error code=%d' % rv )
`</code>`

----

## vscphlp_noop

**c/c++**
`<code="c">`
int vscphlp_noop( long handle )
`</code>`

**Python**
`<code="python">`
int pyvscphlp_noop( handle )
`</code>`

Use this command to test the connection. It sends a command over the interface and checks the result.

#####  handle

Handle for the communication channel obtained from a call to [vscphlp_newSession](./vscphlp_newsession.md).

#####  Return value

Returns VSCP_ERROR_SUCCESS on success or VSCP_ERROR_ERROR on failure. Returns VSCP_ERROR_CONNECTION if the connection is closed and VSCP_ERROR_PARAMETER if called while in a receive loop.

##### Example (c/c++)

`<code="c">`
    // NOOP on handle1
    if ( VSCP_ERROR_SUCCESS == (rv = vscphlp_noop( handle1 ) ) ) {
        printf( "Command success: vscphlp_noop on channel 1\n" );
    }
    else {
        printf("\aCommand error: vscphlp_noop on channel 1  Error code=%d\n", rv);
    }
`</code>`

##### Example (Python)

`<code="python">`
print "command: noop"
rv = lib.vscphlp_noop( h1 )
if VSCP_ERROR_SUCCESS != rv :
    pyvscphlp_closeSession(h1)
    raise ValueError('Command error: ''noop''  Error code=%d' % rv )
`</code>`

----

## vscphlp_clearDaemonEventQueue

**c/c++**
`<code="c">`
int vscphlp_clearDaemonEventQueue( long handle )
`</code>`

**Python**
`<code="python">`
int pyvscphlp_clearDaemonEventQueue( handle )
`</code>`

Clear the receiving-side event queue on the VSCP daemon.

#####  handle

Handle for the communication channel obtained from a call to [vscphlp_newSession](./vscphlp_newsession.md).

##### Return value

Returns VSCP_ERROR_SUCCESS if the VSCP daemon clears the queue, or VSCP_ERROR_ERROR if it does not or no response arrives before the timeout expires. Returns VSCP_ERROR_CONNECTION if the communication channel is not open and VSCP_ERROR_INVALID_HANDLE if the handle is invalid.

##### Example (c/c++)

`<code="c">`
    // Clear event queue on VSCP daemon on handle1
    if ( VSCP_ERROR_SUCCESS == (rv = vscphlp_clearDaemonEventQueue( handle1 ) ) ) {
        printf( "Command success: vscphlp_clearDaemonEventQueueon channel 1\n" );
    }
    else {
        printf("\aCommand error: vscphlp_clearDaemonEventQueueon channel 1  Error code=%d\n", rv);
    }
`</code>`

##### Example (Python)

`<code="python">`
print "Empty VSCP server queue"
rv = pyvscphlp_clearDaemonEventQueue(h1)
if VSCP_ERROR_SUCCESS == rv:
    print "Server queue now is empty"
else:
    print "Failed to clear server queue", rv 
`</code>`

----

## vscphlp_sendEvent

**c/c++**
`<code="c">`
int vscphlp_sendEvent( long handle, const vscpEvent *pEvent )
`</code>`

**Python**
`<code="python">`
int pyvscphlp_sendEvent( handle, event )
`</code>`

Send a VSCP event. Whether or not the event is sent successfully, the calling program is responsible for deallocating it. Remember to free the data part of an event created on the stack.

Note that there is no need to calculate a crc for the data it is only used as placeholder for more insecure transfer mechanisms. Also **head**, **obid**, the UTC timeblock and **timestamp** can be set to zero in most cases. The timeblock and timestamp will be set by the server interface when the event is received.

**pyvscphlp_sendEventEx** may be a better choice for Python because it does not use dynamically allocated event data. However, it uses more memory.

#####  handle

Handle for the communication channel obtained from a call to [vscphlp_newSession](./vscphlp_newsession.md).

#####  pEvent

The level I or level II event to send. The structure **vscpEvent** is defined in [vscp.h](https///github.com/grodansparadis/vscp_software/blob/master/src/vscp/common/vscp.h) as
`<code=c>`
    typedef struct  {	
    uint16_t crc;           // crc checksum - currently only used for UDP and RF
    uint8_t  *pdata;        // Pointer to data. Max 487 (512- 25) bytes
    // Following two are for daemon internal use
    uint32_t obid;          // Used by driver for channel info etc.
    // Time block - Always UTC time
    uint16_t year; 
    uint8_t month;          // 1-12
    uint8_t day;	          // 1-31
    uint8_t hour;           // 0-23
    uint8_t minute;         // 0-59
    uint8_t second;         // 0-59
    uint32_t timestamp;     // Relative time stamp for package in microseconds
    // CRC should be calculated from
    // here to end + datablock
    uint16_t head;          // Bit 16   GUID is IP v.6 address.
                          // bit 765  priority, Priority 0-7 where 0 is highest.
                          // bit 4 = hard coded, true for a hard coded device.
                          // bit 3 = Don't calculate CRC, false for CRC usage.
                          // bit 2 = Reserved.
                          // bit 1 = Reserved.
                          // bit 0 = Reserved.
    uint16_t vscp_class;    // VSCP class
    uint16_t vscp_type;     // VSCP type
    uint8_t  GUID[ 16 ];    // Node globally unique id LSB(0) -> MSB(15
    uint16_t sizeData;      // Number of valid data bytes		
} vscpEvent;
`</code>`

#####  Return value

Returns VSCP_ERROR_SUCCESS on success or VSCP_ERROR_ERROR on failure. Returns VSCP_ERROR_CONNECTION if the connection is closed and VSCP_ERROR_PARAMETER if called while in a receive loop.

##### Example (c/c++)

`<code="c">`
    // Send event on channel 1
    vscpEvent e;
    e.timestamp = 0                    // Let interface set timestamp
    e.year = e.month = e.day = 0;      // Let interface set date
    e.hour = e.minute = e.second = 0;  // Let interface set time
    e.vscp_class = 10;  // CLASS1.MEASUREMENT
    e.vscp_type = 6;    // Temperature
    e.head = 0;
    e.sizeData = 3;
    e.pdata = new unsigned char[3];
    e.pdata[0] = 138;  // Six degrees Celsius from sensor 2
    e.pdata[1] = 0;
    e.pdata[2] = 6;
    memset(e.GUID, 0, sizeof(e.GUID) ); // Setting GUID to all zero tell interface to use it's own GUID

    if ( VSCP_ERROR_SUCCESS == (rv = vscphlp_sendEvent( handle1, &e ) ) ) {
        printf( "Command success: vscphlp_sendEvent on channel 1\n" );
    }
    else {
        printf("\aCommand error: vscphlp_sendEvent on channel 1  Error code=%d\n", rv);
    }
    
    // The event must be deallocated
    //delete pEvent->pdata;
    //delete pEvent;
    vscphlp_deleteVSCPevent( pEvent );  // This helper is the same as the above two commented lines
    
`</code>`

##### Example (Python)

`<code="python">`
e = vscpEvent()
e.timestamp = 0
e.vscpclass = 20
e.vscptype = 9
e.sizedata = 3
p = (c_ubyte*3)()
p[0] = 11
p[1] = 22
p[2] = 33
e.pdata = cast(p, POINTER(c_ubyte))

print "------------------------------------------------------------------------"
print "command: sendEvent"
rv = pyvscphlp_sendEvent(h1,e)
if VSCP_ERROR_SUCCESS != rv :
    pyvscphlp_closeSession(h1)
    raise ValueError('Command error: sendEvent  Error code=%d' % rv )
e.pdata = None  
`</code>`

----

## vscphlp_sendEventEx

**c/c++**
`<code="c">`
int vscphlp_sendEventEx( long handle, const vscpEventEx *pEvent )
`</code>`

**Python**
`<code="python">`
int pyvscphlp_sendEventEx( handle, eventex )
`</code>`

Send a VSCP event. If the event is not sent successfully, the calling program is responsible for deallocating it.

Note that there is no need to calculate a crc for the data it is only used as placeholder for more insecure transfer mechanisms. Also **head**, **obid**, the UTC timeblock and **timestamp** can be set to zero in most cases. The timeblock and timestamp will be set by the server interface when the event is received.

#####  handle

Handle for the communication channel obtained from a call to [vscphlp_newSession](./vscphlp_newsession.md).

#####  pEvent

The level I or level II event to send. The structure **vscpEventEx** is defined in [vscp.h](https///github.com/grodansparadis/vscp_software/blob/master/src/vscp/common/vscp.h) as

`<code=c>`
    typedef struct {	
    uint16_t crc;                   // crc checksum
	
    // Following two are for daemon internal use
    uint32_t obid;                  // Used by driver for channel info etc.
    
    // Time block - Always UTC time
    uint16_t year; 
    uint8_t month;                  // 1-12
    uint8_t day;	                  // 1-31
    uint8_t hour;                   // 0-23
    uint8_t minute;                 // 0-59
    uint8_t second;                 // 0-59  
    
    uint32_t timestamp;             // Relative time stamp for package in microseconds.
    
    // CRC should be calculated from
    // here to end + datablock
    uint8_t head;                   // bit 7,6,5 prioriy => Priority 0-7 where 0 is highest.
                                  // bit 4 = hardcoded, true for a hardcoded device.
                                  // bit 3 = Dont calculate CRC, Set to zero to use CRC.
                                  // bit 2 = Set means this is CAN message.
                                  // bit 1 = If bit 2 is set; Extended CAN message if set
                                  // bit 0 = If bit 2 is set: Remote frame if set
    uint16_t vscp_class;            // VSCP class
    uint16_t vscp_type;             // VSCP type
    uint8_t  GUID[ 16 ];            // Node globally unique id MSB(15) -> LSB(0)
    uint16_t sizeData;              // Number of valid data bytes		

    uint8_t  data[VSCP_MAX_DATA];   // Pointer to data. Max 487 (512- 25) bytes

} vscpEventEx;
`</code>`

#####  Return value

Returns VSCP_ERROR_SUCCESS on success or VSCP_ERROR_ERROR on failure. Returns VSCP_ERROR_CONNECTION if the connection is closed and VSCP_ERROR_PARAMETER if called while in a receive loop.


##### Example (c/c++)

`<code="c">`
    vscpEventEx ex;
    e.timestamp = 0                    // Let interface set timestamp
    e.year = e.month = e.day = 0;      // Let interface set date
    e.hour = e.minute = e.second = 0;  // Let interface set time    
    ex.vscp_class = 10; // CLASS1.MEASUREMENT
    ex.vscp_type = 6;   // Temperature
    ex.head = 0;
    ex.sizeData = 3;
    ex.data[0] = 138;   // 6 degrees Celsius from sensor 2
    ex.data[1] = 0;
    ex.data[2] = 6;
    memset(ex.GUID, 0, sizeof(e.GUID) ); // Setting GUID to all zero tell interface to use it's own GUID

    // Send event again
    if ( VSCP_ERROR_SUCCESS == (rv = vscphlp_sendEventEx( handle1, &ex ) ) ) {
        printf( "Command success: vscphlp_sendEventEx on channel 1\n" );
    }
    else {
        printf("\aCommand error: vscphlp_sendEventEx on channel 1  Error code=%d\n", rv);
    }
`</code>`

##### Example (Python)

`<code="python">`
ex = vscpEventEx()
ex.timestamp = 0
ex.vscpclass = 10
ex.vscptype = 99
ex.sizedata = 3
ex.data[0] = 1
ex.data[1] = 2
ex.data[2] = 3
print "command: sendEventEx"
rv = pyvscphlp_sendEventEx(h1,ex)
if VSCP_ERROR_SUCCESS != rv :
    pyvscphlp_closeSession(h1)
    raise ValueError('Command error: sendEventEx  Error code=%d' % rv )
`</code>`

----

## vscphlp_receiveEvent

**c/c++**
`<code="c">`
int vscphlp_receiveEvent( long handle, vscpEvent *pEvent )
`</code>`

**Python**
`<code="python">`
int pyvscphlp_receiveEvent( handle, event )
`</code>`

Receive one VSCP event from the remote VSCP server if there is one available in the server queue. Data for the event is dynamically allocated and must be deleted by the application.

For Python, **pyvscphlp_receiveEvent** may be simpler to use because there is no dynamically allocated data to manage.

#####  handle

Handle for the communication channel obtained from a call to [vscphlp_newSession](./vscphlp_newsession.md).

#####  pEvent

Pointer to a **vscpEvent** structure that will receive the event on success. The **vscpEvent** structure is defined in [vscp.h](https///github.com/grodansparadis/vscp_software/blob/master/src/vscp/common/vscp.h) as follows:

`<code=c>`
    typedef struct  {	
    uint16_t crc;           // crc checksum - currently only used for UDP and RF
    uint8_t  *pdata;        // Pointer to data. Max 487 (512- 25) bytes
    // Following two are for daemon internal use
    uint32_t obid;          // Used by driver for channel info etc.
    
    // Time block - Always UTC time
    uint16_t year; 
    uint8_t month;                  // 1-12
    uint8_t day;	                  // 1-31
    uint8_t hour;                   // 0-23
    uint8_t minute;                 // 0-59
    uint8_t second;                 // 0-59 
    
    uint32_t timestamp;     // Relative time stamp for package in microseconds
    // CRC should be calculated from
    // here to end + datablock
    uint16_t head;          // Bit 16   GUID is IP v.6 address.
                          // bit 765  priority, Priority 0-7 where 0 is highest.
                          // bit 4 = hard coded, true for a hard coded device.
                          // bit 3 = Don't calculate CRC, false for CRC usage.
                          // bit 2 = Reserved.
                          // bit 1 = Reserved.
                          // bit 0 = Reserved.
    uint16_t vscp_class;    // VSCP class
    uint16_t vscp_type;     // VSCP type
    uint8_t  GUID[ 16 ];    // Node globally unique id LSB(0) -> MSB(15
    uint16_t sizeData;      // Number of valid data bytes		
} vscpEvent;
`</code>`

#####  Return value

Returns VSCP_ERROR_SUCCESS on success or VSCP_ERROR_ERROR on failure. Returns VSCP_ERROR_CONNECTION if the connection is closed and VSCP_ERROR_PARAMETER if called while in a receive loop.

##### Example (c/c++)

`<code="c">`
    // Read event
    vscpEvent *pEvent = new vscpEvent;
    pEvent->pdata = NULL;   // A must for a successful delete
    if ( VSCP_ERROR_SUCCESS == (rv = vscphlp_receiveEvent( handle2, pEvent ) ) ) {
        printf( "Command success: vscphlp_receiveEvent on handle2\n" );
        printf( "VSCP class=%d VSCP type=%d sizeData=%d\n", 
                    pEvent->vscp_class,
                    pEvent->vscp_type,
                    pEvent->sizeData );
        printf("Data = ");
        for ( int i=0; i`<pEvent->`sizeData; i++ ) {
            printf("%d ", pEvent->pdata[i] );
        }
        printf("\n");
    }
    else {
        printf("\aCommand error: vscphlp_receiveEvent on channel 2  Error code=%d\n", rv);
    }

    // Do something with the received event

    //delete pEvent->pdata;
    //delete pEvent;
    vscphlp_deleteVSCPevent( pEvent );  // This helper is the same as the above two commented lines
`</code>`

----

## vscphlp_receiveEventEx

**c/c++**
`<code="c">`
int vscphlp_receiveEventEx( long handle, vscpEventEx *pEventEx )
`</code>`

**Python**
`<code="python">`
int pyvscphlp_receiveEventEx( handle, eventex )
`</code>`

Receive a VSCP event. Unlike vscphlp_receiveEvent, the vscphlp_vscpEventEx structure stores the data in the structure itself; vscpEvent contains a pointer to the data.

#####  handle

Handle for the communication channel obtained from a call to [vscphlp_newSession](./vscphlp_newsession.md).

#####  pEvent

Pointer to VSCP data structure that will receive the event.

#####  Return value 

Returns VSCP_ERROR_SUCCESS on success or VSCP_ERROR_ERROR on failure. Returns VSCP_ERROR_CONNECTION if the connection is closed and VSCP_ERROR_PARAMETER if called while in a receive loop.

##### Example (c/c++)

`<code="c">`
    // Read event  -  Use vscpEventEx
    vscpEventEx ex2;
    if ( VSCP_ERROR_SUCCESS == (rv = vscphlp_receiveEventEx( handle2, &ex2 ) ) ) {
        printf( "Command success: vscphlp_receiveEventEx on handle2\n" );
        printf( "VSCP class=%d VSCP type=%d sizeData=%d\n", 
                    ex2.vscp_class,
                    ex2.vscp_type,
                    ex2.sizeData );
        printf("Data = ");
        for ( int i=0; i<ex2.sizeData; i++ ) {
            printf("%d ", ex2.data[i] );
        }
        printf("\n");
    }
    else {
        printf("\aCommand error: vscphlp_receiveEventEx on channel 2  Error code=%d\n", rv);
    }
`</code>`

##### Example (Python)

`<code="python">`
print "Waiting for incoming data..."

cntAvailable = ctypes.c_uint(0)
while cntAvailable.value==0:
    print 'Still waiting...'
    time.sleep(1)
    pyvscphlp_isDataAvailable(h1,cntAvailable)

print '%d event(s) is available' % cntAvailable.value

for i in range(0,cntAvailable.value):
    ex = vscpEventEx()
    if VSCP_ERROR_SUCCESS == pyvscphlp_receiveEventEx(h1,ex):
        ex.dump()
`</code>`

----

## vscphlp_isDataAvailable

**c/c++**
`<code="c">`
int vscphlp_isDataAvailable( long handle, unsigned int *pCount )
`</code>`

**Python**
`<code="python">`
int pyvscphlp_isDataAvailable( handle, count )
`</code>`

Check the number of events (if any) that are available in the remote input queue.

#####  handle

Handle for the communication channel obtained from a call to [vscphlp_newSession](./vscphlp_newsession.md).

#####  pCount (c/c++)

Pointer to variable that gets the number of events waiting in the queue on a successful call.

#####  count (Python)

Variable that gets the number of events waiting in the queue on a successful call.

#####  Return value 

Returns VSCP_ERROR_SUCCESS on success or VSCP_ERROR_ERROR on failure. Returns VSCP_ERROR_CONNECTION if the connection is closed and VSCP_ERROR_PARAMETER if called while in a receive loop.

##### Example (c/c++)

`<code="c">`
    // Check queue for events
    if ( VSCP_ERROR_SUCCESS == (rv = vscphlp_isDataAvailable( handle2, &count ) ) ) {
        printf( "Command success: vscphlp_isDataAvailable on handle2\n" );
        printf( "count = %d\n", count );
        if ( 3 == count ) printf("Which is correct.\n");
    }
    else {
        printf("\aCommand error: vscphlp_isDataAvailable on channel 2  Error code=%d\n", rv);
    }
`</code>`

##### Example (Python)

`<code="python">`
print "Waiting for incoming data..."

cntAvailable = ctypes.c_uint(0)
while cntAvailable.value==0:
    print 'Still waiting...'
    time.sleep(1)
    pyvscphlp_isDataAvailable(h1,cntAvailable)

print '%d event(s) is available' % cntAvailable.value

for i in range(0,cntAvailable.value):
    ex = vscpEventEx()
    if VSCP_ERROR_SUCCESS == pyvscphlp_receiveEventEx(h1,ex):
        ex.dump()
`</code>`

----

## vscphlp_enterReceiveLoop

** c/c++ ** 
`<code="c">`
int vscphlp_enterReceiveLoop( long handle )
`</code>`

** Python ** 
`<code="python">`
int pyvscphlp_enterReceiveLoop( handle )
`</code>`

Enter the receive loop. After this command only [vscphlp_quitReceiveLoop](#vscphlp_quitReceiveLoop) and [vscphlp_Close](#vscphlp_Close) and the blocking receive methods [vscphlp_blockingReceiveEvent](#vscphlp_blockingreceiveevent) / [vscphlp_blockingReceiveEventEx](#vscphlp_blockingreceiveeventex) is available. The intent of the command is for threaded communication where one thread is sending events and one is receiving events and can use blocking calls to do so.

#####  handle

Handle for the communication channel obtained from a call to [vscphlp_newSession](./vscphlp_newsession.md).


#####  Return value

Returns VSCP_ERROR_SUCCESS on success or VSCP_ERROR_ERROR on failure. Returns VSCP_ERROR_CONNECTION if the connection is closed and VSCP_ERROR_PARAMETER if called while in a receive loop.


##### Example (c/c++)

`<code="c">`
    // Enter receiveloop
    if ( VSCP_ERROR_SUCCESS == (rv = vscphlp_enterReceiveLoop( handle2 ) ) ) {
        printf( "Command success: vscphlp_enterReceiveLoop on channel 2\n" );
    }
    else {
        printf("\aCommand error: vscphlp_enterReceiveLoop on channel 2  Error code=%d\n", rv);
    }
`</code>`

##### Example (Python)

`<code="python">`
print "Enter receive loop. Will lock channel on just receiving events"
if VSCP_ERROR_SUCCESS == pyvscphlp_enterReceiveLoop(h1):
    print "Now blocking receive - will take forever if no events is received"
    
    rv = -1
    while VSCP_ERROR_SUCCESS != rv:
        ex = vscpEventEx()
        rv = pyvscphlp_blockingReceiveEventEx(h1,ex, 1000 )
        
        if VSCP_ERROR_SUCCESS == rv: 
            ex.dump()
        else:
            if VSCP_ERROR_TIMEOUT != rv:
                print "Blocking receive failed with error code = %d" % rv 
                break;
            print "Waiting for event in blocking mode rv=%d" % rv

    if VSCP_ERROR_SUCCESS == pyvscphlp_quitReceiveLoop(h1):
        print "Successfully left receive loop"
    else:
        print "failed to leave receive loop"    

else:    
    print "Failed to enter receive loop!"
`</code>`

----

## vscphlp_quitReceiveLoop

**c/c++**
`<code="c">`
int vscphlp_quitReceiveLoop( long handle )
`</code>`

**Python**
`<code="python">`
int vscphlp_quitReceiveLoop( handle )
`</code>`

Quit the receive loop. 

#####  handle

Handle for the communication channel obtained from a call to [vscphlp_newSession](./vscphlp_newsession.md).


#####  Return value

Returns VSCP_ERROR_SUCCESS on success or VSCP_ERROR_ERROR on failure. Returns VSCP_ERROR_CONNECTION if the connection is closed and VSCP_ERROR_PARAMETER if called while in a receive loop.


##### Example (c/c++)

`<code="c">`
    // Quit receiveloop
    if ( VSCP_ERROR_SUCCESS == (rv = vscphlp_quitReceiveLoop( handle2 ) ) ) {
        printf( "Command success: vscphlp_quitReceiveLoop on channel 2\n" );
    }
    else {
        printf("Command error: vscphlp_quitReceiveLoop on channel 2  Error code=%d\n", rv);
    }
`</code>`

##### Example (Python)

`<code="python">`
if VSCP_ERROR_SUCCESS == pyvscphlp_quitReceiveLoop(h1):
        print "Successfully left receive loop"
    else:
        print "failed to leave receive loop"
`</code>`

----

## vscphlp_blockingReceiveEvent

**c/c++**
`<code="c">`
int vscphlp_blockingReceiveEvent( long handle, vscpEvent *Event, unsigned long timeout )
`</code>`

**Python**
`<code="python">`
int vscphlp_blockingReceiveEvent( handle, event, timeout )
`</code>`

Blocking receive one VSCP event from the remote VSCP server if there is one available in the server queue. Data for the event is dynamically allocated and must be deleted by the application.

For Python, **pyvscphlp_receiveEvent** may be simpler to use because there is no dynamically allocated data to manage.

#####  handle

Handle for the communication channel obtained from a call to [vscphlp_newSession](./vscphlp_newsession.md).

##### pEvent

Pointer to an event that will receive the event data on success. See [vscphlp_receiveEvent](#vscphlp_receiveEvent) for a description.

##### timeout

Maximum time to block. Zero means wait indefinitely.

#####  Return value

Returns VSCP_ERROR_SUCCESS on success or VSCP_ERROR_ERROR on failure. Returns VSCP_ERROR_CONNECTION if the connection is closed and VSCP_ERROR_PARAMETER if called outside a receive loop (see [#vscphlp_enterReceiveLoop](#vscphlp_enterReceiveLoop)).


##### Example (c/c++)

`<code="C">`
    // Enter receiveloop

    pEvent = new vscpEvent;
    pEvent->pdata = NULL;   // A must for a successful delete
    if ( VSCP_ERROR_SUCCESS == vscphlp_blockingReceiveEvent( handle2, pEvent ) ) {
        printf( "Command success: vscphlp_blockingReceiveEvent on channel 2\n" );
        printf(" Event: class=%d Type=%d sizeData=%d\n", 
                        pEvent->vscp_class,
                        pEvent->vscp_type,
                        pEvent->sizeData );
        if ( pEvent->sizeData && ( NULL != pEvent->pdata ) ) {
            printf("Data = ");
            for ( int i=0; i<ex2.sizeData; i++ ) {
                 printf("%d ", ex2.data[i] );
            }
            printf("\n");
        }
    }
    vscphlp_deleteVSCPevent( pEvent );
`</code>`

##### Example (Python)

`<code="C">`
print "Enter receive loop. Will lock channel on just receiving events"
if VSCP_ERROR_SUCCESS == pyvscphlp_enterReceiveLoop(h1):
    print "Now blocking receive - will take forever if no events is received"
    
    rv = -1
    while VSCP_ERROR_SUCCESS != rv:
        e = vscpEvent()
        rv = pyvscphlp_blockingReceiveEvent(h1,e, 1000 )
        
        if VSCP_ERROR_SUCCESS == rv: 
            e.dump()
        else:
            if VSCP_ERROR_TIMEOUT != rv:
                print "Blocking receive failed with error code = %d" % rv 
                break;
            print "Waiting for event in blocking mode rv=%d" % rv

    if VSCP_ERROR_SUCCESS == pyvscphlp_quitReceiveLoop(h1):
        print "Successfully left receive loop"
    else:
        print "failed to leave receive loop"    

else:    
    print "Failed to enter receive loop!"
`</code>`

----

## vscphlp_blockingReceiveEventEx

**c/c++**
`<code="c">`
int vscphlp_blockingReceiveEventEx( long handle, vscpEventEx *Eventex, unsigned long timeout )
`</code>`

**Python**
`<code="python">`
int pyvscphlp_blockingReceiveEventEx( handle, eventex, timeout )
`</code>`

Blocking receive one VSCP event from the remote VSCP server if there is one available in the server queue.


#####  handle

Handle for the communication channel obtained from a call to [vscphlp_newSession](./vscphlp_newsession.md).

##### pEvent (c/c++)

Pointer to an event that will receive the event data on success. See [vscphlp_receiveEvent](#vscphlp_receiveEvent) for a description.

##### pEvent (Python)

Event that will receive the event data on success. See [vscphlp_receiveEvent](#vscphlp_receiveEvent) for a description.

##### timeout

Maximum time to block. Zero means wait indefinitely.

#####  Return value

Returns VSCP_ERROR_SUCCESS on success or VSCP_ERROR_ERROR on failure. Returns VSCP_ERROR_CONNECTION if the connection is closed and VSCP_ERROR_PARAMETER if called while in a receive loop.


##### Example (c/c++)

`<code="C">`
    vscpEventEx ex;

    if ( VSCP_ERROR_SUCCESS == vscphlp_blockingReceiveEventEx( handle2, &ex ) ) {
        printf( "Command success: vscphlp_blockingReceiveEventEx on channel 2\n" );
        printf(" Event: class=%d Type=%d sizeData=%d\n", 
                        ex.vscp_class,
                        ex.vscp_type,
                        ex.sizeData );
        if ( ex.sizeData ) {
            printf("Data = ");
            for ( int i=0; i<ex.sizeData; i++ ) {
                 printf("%d ", ex.data[i] );
            }
            printf("\n");
        }
    }
    vscphlp_deleteVSCPevent( pEvent );
`</code>`

##### Example (c/c++)

`<code="C">`
print "Enter receive loop. Will lock channel on just receiving events"
if VSCP_ERROR_SUCCESS == pyvscphlp_enterReceiveLoop(h1):
    print "Now blocking receive - will take forever if no events is received"
    
    rv = -1
    while VSCP_ERROR_SUCCESS != rv:
        ex = vscpEventEx()
        rv = pyvscphlp_blockingReceiveEventEx(h1,ex, 1000 )
        
        if VSCP_ERROR_SUCCESS == rv: 
            ex.dump()
        else:
            if VSCP_ERROR_TIMEOUT != rv:
                print "Blocking receive failed with error code = %d" % rv 
                break;
            print "Waiting for event in blocking mode rv=%d" % rv

    if VSCP_ERROR_SUCCESS == pyvscphlp_quitReceiveLoop(h1):
        print "Successfully left receive loop"
    else:
        print "failed to leave receive loop"    

else:    
    print "Failed to enter receive loop!"
`</code>`

----

## vscphlp_setFilter

**c/c++**
`<code="c">`
int vscphlp_setFilter( long handle, const vscpEventFilter *pFilter )
`</code>`

**Python**
`<code="c">`
int pyvscphlp_setFilter( handle, filter )
`</code>`

Set VSCP filter/mask.

#####  handle

Handle for the communication channel obtained from a call to [vscphlp_newSession](./vscphlp_newsession.md).

#####   pFilter (c/c++)

Pointer to a VSCP filter structure that should be applied to the sending stream on the server. The VSCP filter structure is defined in [vscp.h](https///github.com/grodansparadis/vscp_software/blob/master/src/vscp/common/vscp.h) and has the following format

`<code=c>`
typedef struct  {
    uint8_t filter_priority;        // Priority 
    uint8_t mask_priority;
									
    uint16_t filter_class;          // VSCP class
    uint16_t mask_class;

    uint16_t filter_type;           // VSCP type
    uint16_t mask_type;

    uint8_t filter_GUID[ 16 ];      // Node address MSB -> LSB, LSB is node nickname id
    uint8_t mask_GUID[ 16 ];        //		when interfacing the VSCP daemon.
	
} vscpEventFilter;
`</code>`

#####   filter (Python)

VSCP filter structure that should be applied to the sending stream on the server. 

`<code="python">`
# Receiving event filter

class vscpEventFilter(Structure):
    _fields_ = [("filter_priority", c_ubyte),
                ("mask_priority", c_ubyte),
                ("filter_class", c_ubyte),
                ("mask_class", c_ubyte),
                ("filter_type", c_ubyte),
                ("mask_type", c_ubyte),
                ("filter_guid", c_ubyte * 16),
                ("mask_guid", c_ubyte * 16) ]

    def __init__(self):
        self.filter_priority = 0
        self.mask_priority = 0
        self.filter_class = 0
        self.mask_class = 0
        self.filter_type = 0
        self.mask_type = 0
        for i in (0,15):
            self.filter_guid[i] = 0
        for i in (0,15):
            self.mask_guid[i] = 0
`</code>`

#####  Return value

Returns VSCP_ERROR_SUCCESS on success or VSCP_ERROR_ERROR on failure. Returns VSCP_ERROR_CONNECTION if the connection is closed and VSCP_ERROR_PARAMETER if called while in a receive loop.


##### Example - Set filter (c/c++)

`<code="c">`
    // Set VSCP filter
    vscpEventFilter filter;
    filter.filter_class = 22;   // We are interested in events with VSCP class=22 only
    filter.mask_class = 0xffff;
    filter.mask_type = 0;               // Any type
    filter.mask_priority = 0;           // Any priority
    memset( filter.mask_GUID, 0, 16 );  // Any GUID
    if ( VSCP_ERROR_SUCCESS == (rv = vscphlp_setFilter( handle2, &filter ) ) ) {
        printf( "Command success: vscphlp_setFilter on channel 2\n" );
    }
    else {
        printf("\aCommand error: vscphlp_setFilter on channel 2  Error code=%d\n", rv);
    }
`</code>`

##### Example - Clear filter (c/c++)

`<code="c">`
    // Clear the filter
    memset( &filter, 0, sizeof( vscpEventFilter ) );
    if ( VSCP_ERROR_SUCCESS == (rv = vscphlp_setFilter( handle2, &filter ) ) ) {
        printf( "Command success: vscphlp_setFilter on channel 2\n" );
    }
    else {
        printf("\aCommand error: vscphlp_setFilter on channel 2  Error code=%d\n", rv);
    }
`</code>` 

##### Example - Set Filter (Python)

`<code="Python">`
# Set filter

filter = vscpEventFilter()
filter.mask_class = 0xFFFF                      # All bits should be checked
filter.filter_class = VSCP_CLASS1_MEASUREMENT   # Only CLASS1.MEASUREMENT received
rv = pyvscphlp_setFilter( h1, filter )
if VSCP_ERROR_SUCCESS != rv :
    pyvscphlp_closeSession(h1)
    raise ValueError('Command error: pyvscphlp_setFilter  Error code=%d' % rv )

print "Enter receive loop. Will lock channel for 60 seconds or unit CLASS1.MEASUREMENT event received"
if VSCP_ERROR_SUCCESS == pyvscphlp_enterReceiveLoop(h1):
       
    cnt = 0   
    rv = -1
    while VSCP_ERROR_SUCCESS != rv:
        ex = vscpEventEx()
        rv = pyvscphlp_blockingReceiveEventEx(h1,ex, 1000 )
        
        if VSCP_ERROR_SUCCESS == rv: 
            ex.dump()
        else: 
            print "Waiting for CLASS1.MEASUREMENT event in blocking mode rv=%d" % rv

        cnt += 1
        if ( cnt > 60 ):
            print "Not received within 60 seconds. We quit!"
            break

    if VSCP_ERROR_SUCCESS == pyvscphlp_quitReceiveLoop(h1):
        print "Successfully left receive loop"
    else:
        print "failed to leave receive loop"    

else:    
    print "Failed to enter receive loop!"
`</code>`

##### Example - Clear Filter (Python)

`<code="Python">`
# Clear filter

print "Clear filter"
filter = vscpEventFilter()
filter.clear()
rv = pyvscphlp_setFilter( h1, filter )
if VSCP_ERROR_SUCCESS != rv :
    pyvscphlp_closeSession(h1)
    raise ValueError('Command error: pyvscphlp_setFilter  Error code=%d' % rv )
`</code>`

----

## vscphlp_getStatistics

**c/c++**
`<code="c">`
int vscphlp_getStatistics( long handle, canalStatistics *pStatistics )
`</code>`

**Python**
`<code="python">`
int vscphlp_getStatistics( handle, statistics )
`</code>`

Get VSCP statistics. 

#####  handle

Handle for the communication channel obtained from a call to [vscphlp_newSession](./vscphlp_newsession.md).

#####  pStatistics (c/c++)

A pointer to a VSCP statistics structure as defined in [vscp.h](https///github.com/grodansparadis/vscp_software/blob/master/src/vscp/common/vscp.h). The format is 

`<code=c>`
typedef struct structVSCPStatistics {
    unsigned long cntReceiveFrames;             // # of receive frames
    unsigned long cntTransmitFrames;            // # of transmitted frames
    unsigned long cntReceiveData;               // # of received data bytes
    unsigned long cntTransmitData;              // # of transmitted data bytes	
    unsigned long cntOverruns;                  // # of overruns
    unsigned long x;                            // Currently undefined value 
    unsigned long y;                            // Currently undefined value 
    unsigned long z;                            // Currently undefined value 
} VSCPStatistics;
`</code>`

#####  statistics (Python)

`<code="Python">`
# Transmission statistics structure

class VSCPStatistics(Structure):
    _fields_ = [("cntReceiveFrames", c_uint32),
                ("cntTransmitFrames", c_uint32),
                ("cntReceiveData", c_uint32),
                ("cntTransmitData", c_uint32),
                ("cntOverruns", c_uint32),
                ("x", c_uint32),    # Placeholder
                ("y", c_uint32),    # Placeholder
                ("z", c_uint32) ]   # Placeholder

    def __init__(self):
        self.cntReceiveFrames = 0
        self.cntTransmitFrames = 0
        self.cntReceiveData = 0
        self.cntTransmitData = 0
        self.cntOverruns = 0
        self.x = 0
        self.y = 0
        self.z = 0
`</code>`

#####  Return value

Returns VSCP_ERROR_SUCCESS on success or VSCP_ERROR_ERROR on failure. Returns VSCP_ERROR_CONNECTION if the connection is closed and VSCP_ERROR_PARAMETER if called while in a receive loop.

##### Example

**Example c/c++**
`<code="c">`
    // Get statistics
    VSCPStatistics stat;
    if ( VSCP_ERROR_SUCCESS == (rv = vscphlp_getStatistics( handle2, &stat ) ) ) {
        printf( "Command success: vscphlp_getStatistics on channel 2\n" );
    }
    else {
        printf("\aCommand error: vscphlp_getStatistics on channel 2  Error code=%d\n", rv);
    }
`</code>`

**Example Python**
`<code="python">`
print "Get statistics"
statistics = VSCPStatistics()
rv = pyvscphlp_getStatistics( h1, statistics )
if VSCP_ERROR_SUCCESS != rv :
    pyvscphlp_closeSession(h1)
    raise ValueError('Command error: pyvscphlp_setStatistics  Error code=%d' % rv )      
print "Received frames = %d" % statistics.cntReceiveFrames
print "Transmitted frames = %d" % statistics.cntTransmitFrames
print "Receive data = %d" % statistics.cntReceiveData
print "Transmitted data = %d" % statistics.cntTransmitData
print "Overruns = %d" % statistics.cntOverruns
`</code>`

----

## vscphlp_getStatus

**c/c++**
`<code="c">`
const char * vscphlp_getStatus( long handle, VSCPStatus *pstatus )
`</code>`

**Python**
`<code="python">`
const char * pyvscphlp_getStatus( handle, char status)
`</code>`

Fetch the status structure from the VSCP server.

#####  handle

Handle for the communication channel obtained from a call to [vscphlp_newSession](./vscphlp_newsession.md).

#####  pstatus (c/c++)

Pointer to **VSCPStatus** structure that will be filled with data after a successful call.

##### status (Python)

**VSCPStatus** structure that will receive status information.

#####  Return value

Returns VSCP_ERROR_SUCCESS on success or VSCP_ERROR_ERROR on failure. Returns VSCP_ERROR_CONNECTION if the connection is closed and VSCP_ERROR_PARAMETER if called while in a receive loop.


##### Example (c/c++)

`<code="c">`
VSCPStatus status;
    if ( VSCP_ERROR_SUCCESS == (rv = vscphlp_getStatus( handle2, &status ) ) ) {
        printf( "Command success: vscphlp_getStatus on channel 2\n" );
    }
    else {
        printf("\aCommand error: vscphlp_getStatus on channel 2  Error code=%d\n", rv);
    }
`</code>`

##### Example (Python)

`<code="python">`
print "Get status"
status = VSCPStatus()
rv = pyvscphlp_getStatus( h1, status )
if VSCP_ERROR_SUCCESS != rv :
    pyvscphlp_closeSession(h1)
    raise ValueError('Command error: pyvscphlp_setFilter  Error code=%d' % rv )
print "Channel status = %d" % status.channel_status 
print "Channel status = %d" % status.lasterrorcode 
print "Channel status = %d" % status.lasterrorsubcode 
`</code>`

----
   
## vscphlp_getVersion

**c/c++**
`<code="c">`
unsigned long vscphlp_getVersion( long handle, 
                                    unsigned char *pMajorVer,
                                    unsigned char *pMinorVer,
                                    unsigned char *pSubMinorVer )
`</code>`

**Python**
`<code="python">`
unsigned long pyvscphlp_getVersion( handle, 
                                      MajorVer,
                                      MinorVer,
                                      SubMinorVer )
`</code>`

Get the version of the remote VSCP server.

#####  handle

Handle for the communication channel obtained from a call to [vscphlp_newSession](./vscphlp_newsession.md).

##### MajorVer

VSCP server major version.

##### MinorVer

VSCP server minor version.

##### SubMinorVer

VSCP server sub minor version.

#####  Return value

Returns VSCP_ERROR_SUCCESS on success or VSCP_ERROR_ERROR on failure. Returns VSCP_ERROR_CONNECTION if the connection is closed and VSCP_ERROR_PARAMETER if called while in a receive loop.


##### Example (c/c++)

`<code="c">`
    // Get server version
    unsigned char v1,v2,v3;
    if ( VSCP_ERROR_SUCCESS == (rv = vscphlp_getVersion( handle2, &v1, &v2, &v3 ) ) ) {
        printf( "Command success: vscphlp_getVersion on channel 2\n" );
        printf( "Version for VSCP daemon on channel 2 is %d.%d.%d\n", v1,v2,v3 );
    }
    else {
        printf("\aCommand error: vscphlp_getVersion on channel 2  Error code=%d\n", rv);
    }
`</code>`

##### Example (Python)

`<code="python">`
print "command: Get sever version"
(rv,v1,v2,v3) = pyvscphlp_getVersion(h1)
if VSCP_ERROR_SUCCESS != rv :
    pyvscphlp_closeSession(h1)
    raise ValueError('Command error: ''pyvscphlp_getVersion''  Error code=%d' % rv )
print "Server version = %d.%d.%d" % (v1.value,v2.value,v3.value) 
`</code>`

----

## vscphlp_getDLLVersion

**c/c++**
`<code="c">`
const char * vscphlp_getDLLVersion( long handle, unsigned long *pdllversion )
`</code>`

**Python**
`<code="python">`
(rv,dllversion) = pyvscphlp_getDLLVersion( handle )
`</code>`

Fetch the DLL version from the VSCP server. This is the interface version.

#####  handle

Handle for the communication channel obtained from a call to [vscphlp_newSession](./vscphlp_newsession.md).

#####  pdllversion (c/c++)

Pointer to an unsigned long that will receive the driver version.

#####  Return value (c/c++)

Returns VSCP_ERROR_SUCCESS on success or VSCP_ERROR_ERROR on failure. Returns VSCP_ERROR_CONNECTION if the connection is closed and VSCP_ERROR_PARAMETER if called while in a receive loop.

#####  Return value (Python)

Returns a tuple containing the return value and dllversion. See the C/C++ return values above for rv.

#####  Example (c/c++)

`<code="c">`
    // Get DLL version
    unsigned long dllversion;
    if ( VSCP_ERROR_SUCCESS == (rv = vscphlp_getDLLVersion( handle2, &dllversion ) ) ) {
        printf( "Command success: vscphlp_getDLLVersion on channel 2\n" );
        printf( "DL(L) version is %08X\n", dllversion );
    }
    else {
        printf("\aCommand error: vscphlp_getDLLVersion on channel 2  Error code=%d\n", rv);
    }
`</code>`

#####  Example (Python)

`<code="python">`
print "Get DLL version"
(rv,dllversion) = pyvscphlp_getDLLVersion( h1 )
if VSCP_ERROR_SUCCESS != rv :
    pyvscphlp_closeSession(h1)
    raise ValueError('Command error: pyvscphlp_getStatus  Error code=%d' % rv )
print "DLL version = %d" % dllversion
`</code>`

----

## vscphlp_getVendorString

**c/c++**
`<code="c">`
iny vscphlp_getVendorString( long handle, char *pVendor, size_t len )
`</code>`

**Python**
`<code="python">`
(rv,strversion) pyvscphlp_getVendorString( handle )
`</code>`

Fetch the vendor string from the driver.

#####  handle

Handle for the communication channel obtained from a call to [vscphlp_newSession](./vscphlp_newsession.md).

#####  pVendor (c/c++)

Pointer to a string that will receive vendor information.

#####  len (c/c++)

Size of the supplied buffer.

#####  Return value (c/c++)

Returns VSCP_ERROR_SUCCESS on success or VSCP_ERROR_ERROR on failure. Returns VSCP_ERROR_CONNECTION if the connection is closed and VSCP_ERROR_PARAMETER if called while in a receive loop.

##### Return value (Python)

Returns a tuple containing the return value (see the C/C++ version) and the vendor string.

##### Example (c/c++)

`<code="c">`
    // Get vendor string
    char buf[120];
    if ( VSCP_ERROR_SUCCESS == (rv = vscphlp_getVendorString( handle2, buf, sizeof(buf) ) ) ) {
        printf( "Command success: vscphlp_getVendorString on channel 2\n" );
        printf( "Vendorstring = \"%s\"\n", buf );
    }
    else {
        printf("\aCommand error: vscphlp_getVendorString on channel 2  Error code=%d\n", rv);
    }
`</code>`

##### Example (Python)

`<code="python">`
print "Get vendor string"
(rv,strvendor) = pyvscphlp_getVendorString( h1 )
if VSCP_ERROR_SUCCESS != rv :
    pyvscphlp_closeSession(h1)
    raise ValueError('Command error: pyvscphlp_getVendorString  Error code=%d' % rv )
print "Vendor string = %s" % strvendor
`</code>`

----

## vscphlp_getDriverInfo

**c/c++**
`<code="c">`
const char * vscphlp_getDriverInfo( long handle, char *pInfo, size_t len )
`</code>`

**Python**
`<code="python">`
(rv,strdriverinfo) = vscphlp_getDriverInfo( handle )
`</code>`

Get driver information. Supply a buffer large enough to hold the XML data. For Python, 32000 bytes are used.

#####  handle

Handle for the communication channel obtained from a call to [vscphlp_newSession](./vscphlp_newsession.md).

##### pInfo

Pointer to a string containing XML-formatted information about the driver in use. If available, this information can help users configure the driver.

#####  len

Size of the supplied buffer.

#####  Return value (c/c++)

Returns VSCP_ERROR_SUCCESS on success or VSCP_ERROR_ERROR on failure. Returns VSCP_ERROR_CONNECTION if the connection is closed and VSCP_ERROR_PARAMETER if called while in a receive loop.

#####  Return value (Python)

Returns a tuple containing the return value and the driver information string. See the C/C++ return values for the return codes.

##### Example (c/c++)

`<code="c">`
    // Get driver info
    if ( VSCP_ERROR_SUCCESS == (rv = vscphlp_getDriverInfo( handle2, buf, sizeof(buf) ) ) ) {
     printf( "Command success: vscphlp_getDriverInfo on channel 2\n" );
     printf( "Driver info = \"%s\"\n", buf );
    }
    else {
     printf("\aCommand error: vscphlp_getDriverInfo on channel 2  Error code=%d\n", rv);
    }
`</code>`

##### Example (Python)

`<code="c">`
print "Get driver info string"
(rv,strdriverinfo) = pyvscphlp_getDriverInfo( h1 )
if VSCP_ERROR_SUCCESS != rv :
    pyvscphlp_closeSession(h1)
    raise ValueError('Command error: pyvscphlp_getDriverInfo  Error code=%d' % rv )
print "Driver info string = %s" % strdriverinfo
`</code>`

----

## vscphlp_doCmdShutDown

**c/c++**
`<code="c">`
int vscphlp_doCmdShutDown( long handle )
`</code>`

**Python**
`<code="python">`
int vscphlp_doCmdShutDown( handle )
`</code>`

Shut down the daemon. Needless to say this is a privileged command on the server side.

#####  handle

Handle for the communication channel obtained from a call to [vscphlp_newSession](./vscphlp_newsession.md).

#####  Return value 

Returns VSCP_ERROR_SUCCESS on success or VSCP_ERROR_ERROR on failure. Returns VSCP_ERROR_CONNECTION if the connection is closed and VSCP_ERROR_PARAMETER if called while in a receive loop.


##### Example (c/c++)

`<code="c">`
// Shut down the server
if ( VSCP_ERROR_SUCCESS == (rv = vscphlp_doCmdShutDown( handle2 ) ) ) {
    printf( "Command success: vscphlp_doCmdShutDownon channel 2\n" );
}
else {
    printf("\aCommand error: vscphlp_doCmdShutDownon channel 2  Error code=%d\n", rv);
}
`</code>`


##### Example (Python)

`<code="python">`
print "Shut down server"
rv = pyvscphlp_serverShutDown( h1 )
if VSCP_ERROR_SUCCESS != rv :
    pyvscphlp_closeSession(h1)
    raise ValueError('Command error: pyvscphlp_serverShutDown  Error code=%d' % rv )
`</code>`

\\ 
----
Copyright (c) 2000-2019 [Åke Hedman](mailto/akhe@grodansparadis.com), [Paradise of the Frog / the VSCP Project](https://www.grodansparadis.com)
