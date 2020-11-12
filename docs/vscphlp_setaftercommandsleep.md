

```clike
int vscphlp_setAfterCommandSleep( long handle, 
                unsigned short millisecondSleep )
```

```python
int vscphlp_setAfterCommandSleep( handle, 
                                millisecondSleep )
```

### Parameters

Handle for the communication channel obtained from a call to [vscphlp_newSession](vscphlp_newsession.md).

#### secondsTimeout
Timeout given in seconds. Can be set also before the session is open.


### Return Value
VSCP_ERROR_SUCCESS is returned on success. VSCP_ERROR_INVALID_HANDLE is returned if an invalid handle is given. 

### Description
This is the sleep time in milliseconds used to wait for the server to reply to a command. If there is not valid response received the thread will sleep for the amount of time set here + 200 milliseconds and then check the queue again for a valid response then sleep again and so on until the time set for the response timeout has elapsed, a valid response or an error response has been received. Default value is 0 milliseconds. 

#### C example


```clike

```

#### Python example


```python

```

### See Also
[vscphlp_setResponseTimeout](vscphlp_setresponsetimeout.md)



[filename](./bottom_copyright.md ':include')
