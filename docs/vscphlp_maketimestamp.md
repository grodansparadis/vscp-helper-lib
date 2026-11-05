

```clike
unsigned long vscphlp_makeTimeStamp( void )
```

### Parameters

#### handle
Handle for the communication channel obtained from a call to [vscphlp_newsession](vscphlp_newsession.md).

### Return Value
Returns a timestamp value, not an error code.

### Description
Get new VSCP timestamp. 

#### C example

```clike
printf( "vscphlp_makeTimeStamp  %04lX\n", vscphlp_makeTimeStamp() );
```



#### Python example

Using the official [Python helper binding](bindings.md#python):

```python
import vscp
import vscphelper

timestamp = vscphelper.makeTimeStamp()
print(timestamp)
```

#### JavaScript availability

The official [Node.js binding](bindings.md#nodejs) does not currently expose this helper API, so there is no equivalent JavaScript example.

[filename](./bottom_copyright.md ':include')