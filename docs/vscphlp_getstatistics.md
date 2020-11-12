


```clike
int vscphlp_getStatistics( long handle, 
                            canalStatistics *pStatistics )
```

```python
int vscphlp_getStatistics( handle, statistics )
```

### Parameters

#### handle
Handle for the communication channel obtained from a call to [vscphlp_newsession](vscphlp_newsession.md).

#### pStatistics (c/c++)
A pointer to a VSCP statistics structure as defined in [vscp.h](https://github.com/grodansparadis/vscp_software/blob/master/src/vscp/common/vscp.h). The format is 

```clike
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
```

#### statistics (Python)
```python
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


```

### Return Value
Return VSCP_ERROR_SUCCESS on success, VSCP_ERROR_ERROR on failure. If the connection is closed VSCP_ERROR_CONNECTION is returned. VSCP_ERROR_PARAMETER is returned if called while in a receive loop. 

### Description
Get VSCP statistics. 

#### C example

Get statistics

```clike
// Get statistics
VSCPStatistics stat;
if ( VSCP_ERROR_SUCCESS == (rv = vscphlp_getStatistics( handle2, &stat ) ) ) {
    printf( "Command success: vscphlp_getStatistics on channel 2\n" );
}
else {
    printf("\aCommand error: vscphlp_getStatistics on channel 2  Error code=%d\n", rv);
}
```

#### Python example

Get statistics

```python
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
```



[filename](./bottom_copyright.md ':include')