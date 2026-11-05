

```clike
int vscphlp_setFilter( long handle, 
                        const vscpEventFilter *pFilter )
```


### Parameters

#### handle
Handle for the communication channel obtained from a call to [vscphlp_newsession](vscphlp_newsession.md).

#### pFilter (c/c++)
Pointer to a VSCP filter structure that should be applied to the sending stream on the server. The VSCP filter structure is defined in [vscp.h](https://github.com/grodansparadis/vscp_software/blob/master/src/vscp/common/vscp.h) and has the following format 

```clike
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
```

#### filter (Python)

Use the `vscp.vscpEventFilter` structure supplied by `pyvscp`.

### Return Value
`VSCP_ERROR_SUCCESS` (`0`) indicates success. Possible error codes:
`VSCP_ERROR_INVALID_HANDLE`, `VSCP_ERROR_CONNECTION`, `VSCP_ERROR_PARAMETER`,
`VSCP_ERROR_ERROR`.

### Description
Set VSCP filter/mask.

#### C example
Set filter.

```clike
// Set VSCP filter
vscpEventFilter filter = {0};
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
```

#### C example
Clear filter

```clike
// Clear the filter
memset( &filter, 0, sizeof( vscpEventFilter ) );
if ( VSCP_ERROR_SUCCESS == (rv = vscphlp_setFilter( handle2, &filter ) ) ) {
    printf( "Command success: vscphlp_setFilter on channel 2\n" );
}
else {
    printf("\aCommand error: vscphlp_setFilter on channel 2  Error code=%d\n", rv);
}
```

#### Python example

With an open session handle named `handle` (see the [TLS guide](tls.md#python-example)),
this filter accepts class 10 events of any type or GUID:

```python
import vscp
import vscphelper

event_filter = vscp.vscpEventFilter()
event_filter.filter_class = 10
event_filter.mask_class = 0xFFFF

result = vscphelper.setFilter(handle, event_filter)
if result != vscp.VSCP_ERROR_SUCCESS:
    raise RuntimeError("setFilter failed (error {})".format(result))
```

#### JavaScript availability

See the [Node.js binding](bindings.md#nodejs) for C API access and native library availability.

[filename](./bottom_copyright.md ':include')