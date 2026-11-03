


```clike
int vscphlp_getStatistics( long handle, 
                            VSCPStatistics *pStatistics )
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
Use the `vscp.VSCPStatistics` structure supplied by `pyvscp`.

### Return Value
Returns VSCP_ERROR_SUCCESS on success or VSCP_ERROR_ERROR on failure. Returns VSCP_ERROR_CONNECTION if the connection is closed and VSCP_ERROR_PARAMETER if called while in a receive loop.

### Description
Get VSCP statistics.

> **Known limitation:** In the VSCP implementation currently pinned by this
> library, the `STAT` response parser can copy the first response value into
> multiple counters. A successful call does not guarantee that the reported
> counters match the server response; verify the behavior of the VSCP version
> in use before relying on them.

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

With an open session handle named `handle` (see the [TLS guide](tls.md#python-example)):

```python
import vscp
import vscphelper

statistics = vscp.VSCPStatistics()

result = vscphelper.getStatistics(handle, statistics)
if result != vscp.VSCP_ERROR_SUCCESS:
    raise RuntimeError("getStatistics failed (error {})".format(result))
print("Received frames: {}".format(statistics.cntReceiveFrames))
print("Transmitted frames: {}".format(statistics.cntTransmitFrames))
```

#### JavaScript availability

The official [Node.js binding](bindings.md#nodejs) does not currently expose this helper API, so there is no equivalent JavaScript example.

[filename](./bottom_copyright.md ':include')