

```clike
int doCommand(wxString& cmd)
```

### Parameters

#### cmd
A VSCP remote server command that is terminated with \<CR\>\<LF\> (“\r\n”).


### Return Value
Returns VSCP_ERROR_SUCCESS if the command could be sent successfully and a positive response (+OK) is received. If not an error code will be returned. 

### Description
Send a command to the remote VSCP server. Allows to send any command. 



[filename](./bottom_copyright.md ':include')