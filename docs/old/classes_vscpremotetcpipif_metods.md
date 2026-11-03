# Methods in the VscpRemoteTcpIf class

This is a description of the public methods of the [VscpRemoteTcpIf](https///github.com/grodansparadis/vscp/blob/master/src/vscp/common/vscpremotetcpif.h) class. 

\\ \\ 
# General methods

## setResponseTimeout

`<code=cpp>`
    void setResponseTimeout(uint32_t to);
`</code>`

Set response timeout value in milliseconds. Default is 1000 milliseconds.

##### to

Timeout value in milliseconds.


## setAfterCommandSleep

`<code=cpp>`
    void setAfterCommandSleep(uint16_t to);
`</code>`

Set the sleep time after a command, in milliseconds. The default is 0 milliseconds because a delay is normally unnecessary, but it can be useful on systems that respond slowly to commands.

##### to

Sleep value in milliseconds.

## setRegisterOperationTiming

`<code=cpp>`
    void setRegisterOperationTiming(uint8_t retries, uint32_t resendto, uint32_t errorto);
`</code>`

Set register read/write timings

##### retries

Number of allowed resend retries before giving up a register read.

##### resendto

Resend timeout in milliseconds.

##### erroto

Error timeout in milliseconds before giving up a read register operation.

## isConnected

`<code=cpp>`
    bool isConnected(void);
`</code>`

Check if connected to remote VSCP server.

##### Return value

Returns true if we are connected, false otherwise.

## checkReturnValue

`<code=cpp>`
    bool checkReturnValue(bool bClear = false);
`</code>`

Check the response from the remote VSCP server for an error or a successfully completed command.

##### bClear

If true, the input queue array is cleared before the call.

##### Return value

Returns true if a positive response (+OK) is received from the remote VSCP server. Returns false for a negative response or a timeout.

## doClrInputQueue

`<code=cpp>`
    void doClrInputQueue(void);
`</code>`

Clear the input queue

## doCommand

`<code=cpp>`
    int doCommand(wxString& cmd);
`</code>`

Send any command to the remote VSCP server.

##### cmd

A VSCP remote server command that is terminated with `<CR>``<LF>` ("\r\n").

##### Return Value

Returns VSCP_ERROR_SUCCESS if the command is sent successfully and a positive response (+OK) is received, or an error code otherwise.

## doCmdOpen

The signatures and argument formats in this archived section describe an
older API. For the current class and TLS behavior, see
[doCmdOpen](../class_doCmdOpen.md) and [TLS connections](../tls.md).

`<code=cpp>`
    int doCmdOpen(const wxString& strInterface = (_("")), uint32_t flags = 0L);
`</code>`

Open communication interface.

#####  strInterface

If used, set this to "username;password;ip-addr;port". All values, including the port, are optional. The defaults are no username or password, server "localhost", and port "9598".

##### flags

Currently not used.
           
##### Return Value

Returns VSCP_ERROR_SUCCESS if the connection to the remote VSCP server is established, or an error code otherwise.
      
## doCmdOpen

`<code=cpp>`
    int doCmdOpen(const wxString& strHostname,
                    const wxString& strUsername,
                    const wxString& strPassword);
`</code>`

Open communication interface.

##### strHostname

Host to connect to.

##### strUsername

Username for VSCP remote server account.

##### strPassword

Password for VSCP remote server account.

##### Return Value

Returns VSCP_ERROR_SUCCESS if the connection to the remote VSCP server is established, or an error code otherwise.

## doCmdClose

`<code=cpp>`
    int doCmdClose(void);
`</code>`

Close connection to remote VSCP server.

##### Return Value

Returns CANAL_ERROR_SUCCESS on success or an error code on failure.
          
## doCmdNOOP

`<code=cpp>`
    int doCmdNOOP(void);
`</code>`

Send the NOOP (no operation) command to the VSCP remote server. This command only returns a positive response and can be used to test if a connection works.

##### Return Value

Returns CANAL_ERROR_SUCCESS on success or an error code on failure.
    
## doCmdClear

`<code=cpp>`
    int doCmdClear(void);
`</code>`

Clear input queue on the remote VSCP server.

##### Return Value

Returns CANAL_ERROR_SUCCESS on success or an error code on failure.
     
## doCmdGetLevel

`<code=cpp>`
    unsigned long doCmdGetLevel(void);
`</code>`
    
Get the CANAL protocol level. Mainly used by the CANAL/VSCP combined subsystem.
    
##### Return Value

Returns the constant VSCP_LEVEL2.
       
## doCmdSend

`<code=cpp>`
    int doCmdSend(const vscpEvent *pEvent);
`</code>`

Send a VSCP Level II event to the VSCP remote server.

##### pEvent

Pointer to VSCP Level II event to send. If the event have a GUID all set to zero the GUID of the VSCP remote server interface ("-") will be used.

##### Return Value

Returns CANAL_ERROR_SUCCESS on success or an error code on failure.
         
## doCmdSendEx

`<code=cpp>`
    int doCmdSendEx(const vscpEventEx *pEventEx);
`</code>`

Send a VSCP Level II event ex to the VSCP remote server. 

*A vscpEvent structure contains a pointer to the event data, while each vscpEventEx allocates storage for the maximum amount of data and can therefore use considerably more memory.*

##### pEventEx

Pointer to VSCP Level II event ex to send. If the event have a GUID all set to zero the GUID of the VSCP remote server interface ("-") will be used.

##### Return Value

Returns CANAL_ERROR_SUCCESS on success or an error code on failure.
           
## doCmdSendLevel1

`<code=cpp>`
    int doCmdSendLevel1(const canalMsg *pMsg);
`</code>`           
       
Send a Level I event to the VSCP remote server. The GUID of the interface will be used for the resulting VSCP event.

##### pMsg

A pointer to a CANAL message.
           
##### Return Value

Returns CANAL_ERROR_SUCCESS on success or an error code on failure.

## doCmdReceive

`<code=cpp>`
    int doCmdReceive(vscpEvent *pEvent);
`</code>`

##### pEvent

Pointer to a VSCP event that will receive the event from the remote VSCP server queue on success.

##### Return Value

Returns CANAL_ERROR_SUCCESS on success or an error code on failure.

## doCmdReceiveEx

`<code=cpp>`
    int doCmdReceiveEx(vscpEventEx *pEventEx);
`</code>`

##### pEventEx

Pointer to a VSCP event ex that will receive the event from the remote VSCP server queue on success.

##### Return Value

Returns CANAL_ERROR_SUCCESS on success or an error code on failure.

## doCmdReceiveLevel1

`<code=cpp>`
    int doCmdReceiveLevel1(canalMsg *pCanalMsg);
`</code>`

Receive a VSCP Level I event from the remote VSCP server queue. The low eight bits of the CAN ID are taken from GUID[15], the least significant byte of the GUID.
        
##### pCanalMsg

Pointer to a CANAL message that will receive the event from the remote VSCP server queue on success.

##### Return Value

Returns CANAL_ERROR_SUCCESS on success or an error code on failure.
       
## doCmdEnterReceiveLoop

`<code=cpp>`
    int doCmdEnterReceiveLoop(void);
`</code>` 

This command puts an open interface into the receive loop (RCVLOOP) state and checks that it entered that state.

**Note!** The only way to terminate this receive loop is to close the session with doCmdClose (or just close the socket) or send the doQuitLoop command below.      

##### Return Value

Returns CANAL_ERROR_SUCCESS on success or an error code on failure.
        
## doCmdEnterReceiveLoop

`<code=cpp>`
    int doCmdQuitReceiveLoop(void);
`</code>` 

Quit the receive loop.

##### Return Value

Returns CANAL_ERROR_SUCCESS on success or an error code on failure.

## doCmdBlockingReceive

`<code=cpp>`
    int doCmdBlockingReceive(vscpEvent *pEvent, uint32_t timeout = 500);
`</code>`

Receive an event from the remote VSCP server. The **receiveloop** command must be issued before calling this method.

##### pEvent

Pointer to a VSCP event that will receive the received event on success.

##### timeout

Time to wait for data, in milliseconds. The default is 500 milliseconds.

##### Return Value

Returns CANAL_ERROR_SUCCESS on success or an error code on failure. CANAL_ERROR_FIFO_EMPTY indicates that no event was available, CANAL_ERROR_TIMEOUT indicates a timeout, and CANAL_ERROR_COMMUNICATION indicates a socket error.
        
## doCmdBlockingReceive

`<code=cpp>`
    int doCmdBlockingReceive(vscpEventEx *pEventEx, uint32_t timeout = 500);
`</code>`

Receive an event ex from the remote VSCP server. The **receiveloop** command must be issued before calling this method.

##### pEventEx

Pointer to a VSCP event ex that will receive the received event on success.

##### timeout

Time to wait for data, in milliseconds. The default is 500 milliseconds.

##### Return Value

Returns CANAL_ERROR_SUCCESS on success or an error code on failure. CANAL_ERROR_FIFO_EMPTY indicates that no event was available, CANAL_ERROR_TIMEOUT indicates a timeout, and CANAL_ERROR_COMMUNICATION indicates a socket error.
        
## doCmdDataAvailable

`<code=cpp>`
    int doCmdDataAvailable(void);
`</code>`
        
Get the number of events in the input queue of this interface

##### Return value

Returns the number of events available in the remote VSCP server queue, or a negative error code on failure.
        
## doCmdStatus

`<code=cpp>`
    int doCmdStatus(canalStatus *pStatus);
`</code>`                
        
Receive the CANAL status structure from the remote VSCP server.

##### pStatus

Pointer to a canalStatus structure that will receive the remote VSCP server status.

##### Return Value

Returns CANAL_ERROR_SUCCESS on success or an error code on failure.
    
## doCmdStatus

`<code=cpp>`
    int doCmdStatus(VSCPStatus *pStatus);
`</code>`                
        
Receive the VSCP status structure from the remote VSCP server.

##### pStatus

Pointer to a VSCPStatus structure that will receive the remote VSCP server status.

##### Return Value

Returns CANAL_ERROR_SUCCESS on success or an error code on failure.

## doCmdStatistics

`<code=cpp>`
    int doCmdStatistics(canalStatistics *pStatistics);
`</code>`

Get the CANAL statistics structure from the VSCP remote server.

##### pStatistics

Pointer to a canalStatistics structure that will receive the remote VSCP server statistics.

##### Return Value

Returns CANAL_ERROR_SUCCESS on success or an error code on failure.

## doCmdStatistics

`<code=cpp>`
    int doCmdStatistics(VSCPStatistics *pStatistics);
`</code>`

Get the VSCP statistics structure from the VSCP remote server.

##### pStatistics

Pointer to a VSCPStatistics structure that will receive the remote VSCP server statistics.

##### Return Value

Returns CANAL_ERROR_SUCCESS on success or an error code on failure.
        
## doCmdFilter

`<code=cpp>`
    int doCmdFilter(const vscpEventFilter *pFilter);
`</code>`

Set the receive filter on the remote VSCP server to select which events to receive. For more complex setups, you can open several channels and set a filter on each one.

##### pFilter

Pointer to VSCP filter structure to set.

##### Return Value

Returns CANAL_ERROR_SUCCESS on success or an error code on failure.
        
## doCmdFilter

`<code=cpp>`
    int doCmdFilter(const wxString& filter, const wxString& mask);
`</code>`        

Set the receive filter on the remote VSCP server to select which events to receive. For more complex setups, you can open several channels and set a filter on each one.

##### filter

Filter to set, in string form ("priority,class,type,guid").

##### mask

Mask to set, in string form ("priority,class,type,guid").

##### Return Value

Returns CANAL_ERROR_SUCCESS on success or an error code on failure.
        
## doCmdFilter

`<code=cpp>`
    int doCmdVersion(uint8_t *pMajorVer,
                     uint8_t *pMinorVer,
                     uint8_t *pSubMinorVer);
`</code>` 

Get the interface version from the remote VSCP server.

##### pMajorVer

Major version of VSCP remote server interface.

##### pMinorVer

Minor version of VSCP remote server interface.

##### pSubMinorVer

Sub version of VSCP remote server interface.

##### Return Value

Returns CANAL_ERROR_SUCCESS on success or an error code on failure.
     
## doCmdDLLVersion

`<code=cpp>`
    unsigned long doCmdDLLVersion(void);
`</code>`
     
Get DL/DLL version. This is intended for CANAL.
   
##### Return Value

DL/DLL version. A negative error code is returned on failure. 
        
## doCmdVendorString

`<code=cpp>`
    const char *doCmdVendorString(void);
`</code>`      

Get the vendor (maker of DL/DLL) string. This is intended for CANAL.  
     
##### Return Value

Returns a pointer to a null-terminated string containing vendor information, or a NULL pointer on failure.

## doCmdGetDriverInfo

`<code=cpp>`
    const char *doCmdGetDriverInfo(void);
`</code>`  

Get the driver information string from the remote VSCP server. This is intended for CANAL.

##### Return Value

Returns a pointer to a null-terminated string containing driver information in XML format, or a NULL pointer on failure.

## doCmdGetGUID

`<code=cpp>`
    int doCmdGetGUID(char *pGUID);
`</code>`  

Get GUID for the remote VSCP server interface.

##### pGUID

Pointer to a 16-byte array that will receive the GUID. The most significant byte is first.

##### Return Value

Returns CANAL_ERROR_SUCCESS on success or an error code on failure.

## doCmdGetGUID

`<code=cpp>`
    int doCmdGetGUID(cguid& ifguid);
`</code>`  

Get GUID for the remote VSCP server interface.

##### ifguid

Reference to the GUID that will receive the information.

##### Return Value

Returns CANAL_ERROR_SUCCESS on success or an error code on failure.

## doCmdSetGUID

`<code=cpp>`
    int doCmdSetGUID(const char *pGUID);
`</code>`

Set GUID for the remote VSCP server interface.

##### pGUID

Pointer to a 16-byte array containing the new GUID. The most significant byte is first.

##### Return Value

Returns CANAL_ERROR_SUCCESS on success or an error code on failure.

## doCmdSetGUID

`<code=cpp>`
    int doCmdSetGUID(cguid &ifGUID);
`</code>`

Set GUID for the remote VSCP server interface.

##### ifGUID

Reference to the GUID containing the new value.

##### Return Value

Returns CANAL_ERROR_SUCCESS on success or an error code on failure.

## doCmdGetChannelInfo

`<code=cpp>`
    int doCmdGetChannelInfo(VSCPChannelInfo *pChannelInfo);
`</code>`

Get information about the remote VSCP server interface channel.

##### Return Value

Returns CANAL_ERROR_SUCCESS on success or an error code on failure.

## doCmdGetChannelInfo

`<code=cpp>`
    int doCmdGetChannelID(uint32_t *pChannelID);
`</code>`

Get Channel ID for the remote VSCP server interface channel.

##### Return Value

Returns CANAL_ERROR_SUCCESS on success or an error code on failure.

## doCmdInterfaceList

`<code=cpp>`
    int doCmdInterfaceList(wxArrayString& arrayIf );
`</code>`

Get available interfaces on the VSCP remote server.

##### arrayIf

An array that will receive descriptions of the interfaces available on the remote VSCP server.

##### Return Value

Returns CANAL_ERROR_SUCCESS on success or an error code on failure.

## doCmdSetBaudrate

`<code=cpp>`
    int doCmdSetBaudrate(uint32_t baudrate);
`</code>`

Dummy for required CANAL method.

##### baudrate

CANAL baudrate.

##### Return Value

Always returns CANAL_ERROR_SUCCESS.

## doCmdFilter

`<code=cpp>`
    int doCmdFilter(uint32_t filter);
`</code>`

Dummy for required CANAL method.

##### filter

CANAL 32-bit filter.

##### Return Value

Always returns CANAL_ERROR_SUCCESS.

## doCmdMask

`<code=cpp>`
    int doCmdMask(uint32_t mask);
`</code>`

Dummy for required CANAL method.

##### mask

CANAL 32-bit mask.

##### Return Value

Always returns CANAL_ERROR_SUCCESS.

## doCmdShutDown

`<code=cpp>`
    int doCmdShutDown(void);
`</code>`

Shut down the remote VSCP server. This command requires elevated privileges on the server.

##### Return Value

Returns CANAL_ERROR_SUCCESS on success or an error code on failure.

# Remote variable handling methods

## getRemoteVariableList

`<code=cpp>`
    int getRemoteVariableList( wxArrayString& arrayVars, 
                                    const wxString regexp = _(""),
                                    const int type = 0 );
`</code>`

Get a list of defined variables on remote VSCP server.

##### arrayVars

Reference to a string array that will be filled with the names of VSCP remote variables.

#####  regexp

Regular expression used to select variables. Leave blank to return all variables.

#####  type

Variable type that should be listed or 0 for all variable types.

##### Return Value

Returns CANAL_ERROR_SUCCESS on success or an error code on failure.

## saveRemoteVariablesToDisk

`<code=cpp>`
    int saveRemoteVariablesToDisk( const wxString& path, 
                                        const int select=0, 
                                        const wxString& regExp=_("") );
`</code>`

Save (selected) variables to external disk space in XML format.

##### path

Path, including file name, to save variables to.

##### select

Select whether to write persistent variables, non-persistent variables, or both to the file.

 * **1** for only writing persistent variables.
 * **2** only write non-persistent variables.
 * **3** or **0**  for writing both types.

##### regExp

Optional regular expression that selects which variables to write. By default, all variables are selected.

##### Return Value

Returns CANAL_ERROR_SUCCESS on success or an error code on failure.

## loadRemoteVariablesFromDisk

`<code=cpp>`
    int loadRemoteVariablesFromDisk( const wxString& path );
`</code>`

##### path

Path to load the remote variable XML file from.

##### Return Value

Returns CANAL_ERROR_SUCCESS on success or an error code on failure.

## createRemoteVariable

`<code=cpp>`
    int createRemoteVariable( const wxString& name, 
                                const wxString& strType,
                                const bool bPersistent,
                                const wxString& strUser,
                                const uint32_t rights,
                                const wxString& strValue,
                                const wxString& strNote = _("") );
`</code>`

Create a new remote variable
     
#####  name

Name of the remote variable to create. A user variable name cannot start with "vscp.".

##### strType

Type of the variable, in string or numeric form.

##### bPersistet

True if the variable should be persistent (default: false).

##### strUser

Owner of the variable. If left empty, the logged-in user becomes the owner.

##### rights

Access rights for the variable.

##### strValue

Value for the remote variable.

##### strNote

Optional note for the remote variable.

##### Return Value

Returns CANAL_ERROR_SUCCESS on success or an error code on failure.

## deleteRemoteVariable

`<code=cpp>`
    int deleteRemoteVariable( const wxString& name );
`</code>`

##### name

Name of the remote variable to delete.

##### Return Value

Returns CANAL_ERROR_SUCCESS on success or an error code on failure.

## getRemoteVariable

`<code=cpp>`
    int getRemoteVariable( const wxString& name, wxString& strVariable );
`</code>`

Get remote variable (full info).

Format is: 
    "variable name";"type";"persistence";"user";"rights";"value";"note"

#####  name

Name of the remote variable whose information will be retrieved.

#####  strVariable

String that will receive variable information.

##### Return Value

Returns CANAL_ERROR_SUCCESS on success or an error code on failure.

## getRemoteVariableLastChange

`<code=cpp>`
    int getRemoteVariableLastChange( const wxString& name, wxDateTime& lastChange );
`</code>`

Get last change date/time for a remote variable.

#####  name

Name of the remote variable whose information will be retrieved.

#####  lastChange

Date and time when the variable was last changed.

##### Return Value

Returns CANAL_ERROR_SUCCESS on success or an error code on failure.


## getRemoteVariableType

`<code=cpp>`
    int getRemoteVariableType( const wxString& name, wxString& strType );
`</code>`

Get the type of a remote variable in string form.

#####  name

Name of the remote variable whose information will be retrieved.

#####  strType

Receives the type of the remote variable.

##### Return Value

Returns CANAL_ERROR_SUCCESS on success or an error code on failure.

## getRemoteVariableType

`<code=cpp>`
    int getRemoteVariableType( const wxString& name, uint8_t *pType );
`</code>`

Get the type of a remote variable in numeric form.

#####  name

Name of the remote variable whose information will be retrieved.

#####  pType

Pointer to a uint8_t that will receive the variable type for the remote variable.

##### Return Value

Returns CANAL_ERROR_SUCCESS on success or an error code on failure.

## getRemoteVariablePersistence

`<code=cpp>`
    int getRemoteVariablePersistence( const wxString& name, bool *pPersistent );
`</code>`

Get persistence for a remote variable.

#####  name

Name of the remote variable whose information will be retrieved.

#####  pPersistent

Pointer to a bool that will receive the persistence for the remote variable.

##### Return Value

Returns CANAL_ERROR_SUCCESS on success or an error code on failure.

## getRemoteVariableOwner

`<code=cpp>`
    int getRemoteVariableOwner( const wxString& name, uint32_t *pOwner );
`</code>`

Get owner for a remote variable.

#####  name

Name of the remote variable whose information will be retrieved.

#####  strOwner

Reference to a string that will receive the owner of the remote variable.

##### Return Value

Returns CANAL_ERROR_SUCCESS on success or an error code on failure.

## getRemoteVariableAccessRights

`<code=cpp>`
    int getRemoteVariableAccessRights( const wxString& name, uint16_t *pRights );
`</code>`

Get access rights for a remote variable.

#####  name

Name of the remote variable whose information will be retrieved.

#####  pRights

Pointer to a uint16_t that will receive the rights for the remote variable.

##### Return Value

Returns CANAL_ERROR_SUCCESS on success or an error code on failure.

## getRemoteVariableValue

`<code=cpp>`
    int getRemoteVariableValue( const wxString& name, wxString& strValue );
`</code>`

Get the value of a remote variable in string form.

#####  name

Name of the remote variable whose information will be retrieved.

#####  strValue

Reference to a string that will receive the remote variable's value in string form.

##### Return Value

Returns CANAL_ERROR_SUCCESS on success or an error code on failure.

## setRemoteVariableValue

`<code=cpp>`
    int setRemoteVariableValue( const wxString& name, wxString& strValue );
`</code>`

Set the value for a remote variable from a string.

#####  name

Name of the remote variable whose information will be retrieved.

#####  strValue

Reference to a string containing the value to assign to the remote variable.

##### Return Value

Returns CANAL_ERROR_SUCCESS on success or an error code on failure.

## getRemoteVariableNote

`<code=cpp>`
    int getRemoteVariableNote( const wxString& name, wxString& strNote );
`</code>`

Get note for remote variable.

#####  name

Name of the remote variable whose information will be retrieved.

#####  strNote

Reference to a string that will receive the note for the remote variable.

##### Return Value

Returns CANAL_ERROR_SUCCESS on success or an error code on failure.

## getRemoteVariableAsString

`<code=cpp>`
    int getRemoteVariableAsString( const wxString& name, wxString& strVariable );
`</code>`

Get a remote variable's value in string form.

#####  name

Name of the remote variable whose information will be retrieved.

#####  strVariable

Reference to a string that will receive the remote variable's value in string form.

##### Return Value

Returns CANAL_ERROR_SUCCESS on success or an error code on failure.

## setRemoteVariableFromString

`<code=cpp>`
    int setRemoteVariableFromString( const wxString& name, 
                                        const wxString& strValue,
                                        const bool bPersistent = false,
                                        const uint32_t rights = 0x744 );
`</code>`

Set a remote variable value from its string form.

#####  name

Name of the remote variable whose information will be retrieved.

#####  strValue

Reference to a string containing the value to assign to the remote variable.

#####  bPersistent

True if the variable should be persistent.

#####  rights

Access rights for the variable.

##### Return Value

Returns CANAL_ERROR_SUCCESS on success or an error code on failure.


## getRemoteVariableBool

`<code=cpp>`
    int getRemoteVariableBool( const wxString& name, bool *bValue);
`</code>`

Get the value of the boolean variable.

#####  name

Name of the remote variable whose value will be retrieved.

#####  bValue

Pointer to boolean value that will be set to the remote variable's value.

##### Return Value

Returns CANAL_ERROR_SUCCESS on success or an error code on failure.

## setRemoteVariableBool

`<code=cpp>`
    int setRemoteVariableBool( const wxString& name, const bool bValue);
`</code>`

Set variable value for boolean remote variable.

#####  name

Name of the remote variable.

#####  bValue

Boolean value that the remote variables will be set to.

##### Return Value

Returns CANAL_ERROR_SUCCESS on success or an error code on failure.

## getRemoteVariableInt

`<code=cpp>`
    int getRemoteVariableInt( const wxString& name, int *value);
`</code>`

Get the value of the integer variable.

#####  name

Name of the remote variable whose value will be retrieved.

#####  value

Pointer to integer value that will be set to the remote variable's value.

##### Return Value

Returns CANAL_ERROR_SUCCESS on success or an error code on failure.

## setRemoteVariableInt

`<code=cpp>`
    int setRemoteVariableInt( const wxString& name, int value);
`</code>`

Set variable value for integer remote variable.

#####  name

Name of the remote variable.

#####  value

Integer value that the remote variables will be set to.

##### Return Value

Returns CANAL_ERROR_SUCCESS on success or an error code on failure.

## getRemoteVariableLong

`<code=cpp>`
    int getRemoteVariableLong( const wxString& name, long *value);
`</code>`

Get the value of the long variable.

#####  name

Name of the remote variable whose value will be retrieved.

#####  value

Pointer to long value that will be set to the remote variable's value.

##### Return Value

Returns CANAL_ERROR_SUCCESS on success or an error code on failure.

## setRemoteVariableLong

`<code=cpp>`
    int setRemoteVariableLong( const wxString& name, long value);
`</code>`

Set variable value for long remote variable.

#####  name

Name of the remote variable.

#####  value

Long value that the remote variables will be set to.

##### Return Value

Returns CANAL_ERROR_SUCCESS on success or an error code on failure.

## getRemoteVariableDouble

`<code=cpp>`
    int getRemoteVariableDouble( const wxString& name, double *value);
`</code>`

Get the value of the double variable.

#####  name

Name of the remote variable whose value will be retrieved.

#####  value

Pointer to double value that will be set to the remote variable's value.

##### Return Value

Returns CANAL_ERROR_SUCCESS on success or an error code on failure.

## setRemoteVariableDouble

`<code=cpp>`
    int setRemoteVariableDouble( const wxString& name, double value);
`</code>`

Set variable value for double remote variable.

#####  name

Name of the remote variable.

#####  value

Double value that the remote variables will be set to.

##### Return Value

Returns CANAL_ERROR_SUCCESS on success or an error code on failure.

## getRemoteVariableMeasurement

`<code=cpp>`
    int getRemoteVariableMeasurement( const wxString& name, 
                                        double *pvalue,
                                        uint8_t *punit,
                                        uint8_t *psensoridx,
                                        uint8_t *pzone,
                                        uint8_t *psubzone );
`</code>`

Get the value of the measurement variable.

#####  name

Name of the remote variable.

#####  pvalue

Pointer to a double that will receive the value of the measurement.

#####  punit

Pointer to a uint8_t that will receive the unit of the measurement.

##### psensoridx

Pointer to a uint8_t that will receive the sensor index of the measurement.

##### pzone

Pointer to a uint8_t that will receive the zone of the measurement.

#####  psubzone

Pointer to a uint8_t that will receive the subzone of the measurement.

##### Return Value

Returns CANAL_ERROR_SUCCESS on success or an error code on failure.

## setRemoteVariableMeasurement

`<code=cpp>`
    int setRemoteVariableMeasurement( const wxString& name, 
                                        double value,
                                        uint8_t unit = 0,
                                        uint8_t sensoridx = 0,
                                        uint8_t zone = 255,
                                        uint8_t subzone = 255 );
`</code>`

Set remote measurement variable value.

#####  name

Name of the remote variable.

#####  value

Double containing the value for the measurement.

#####  unit

The unit for the measurement.

#####  sensoridx

The sensor index for the measurement.

##### zone

The zone for the measurement.

#####  subzone

The subzone for the measurement.

##### Return Value

Returns CANAL_ERROR_SUCCESS on success or an error code on failure.

## getRemoteVariableEvent

`<code=cpp>`
    int getRemoteVariableEvent( const wxString& name, vscpEvent *pEvent);
`</code>`

Set variable value for VSCP event remote variable.

#####  name

Name of the remote variable.

#####  value

Pointer to VSCP event value that the remote variables will be set to.

##### Return Value

Returns CANAL_ERROR_SUCCESS on success or an error code on failure.

## setRemoteVariableEvent

`<code=cpp>`
    int setRemoteVariableEvent( const wxString& name, vscpEvent *pEvent);
`</code>`

Set remote variable value for VSCP event variable.

#####  name

Name of the remote variable.

#####  value

Pointer to VSCP event value that will be set to the remote variable's value.

##### Return Value

Returns CANAL_ERROR_SUCCESS on success or an error code on failure.

## getRemoteVariableEventEx

`<code=cpp>`
    int getRemoteVariableEventEx( const wxString& name, vscpEventEx *pEventEx);
`</code>`

Set variable value for VSCP event ex remote variable.

#####  name

Name of the remote variable.

#####  pEventEx

Pointer to VSCP event ex value that the remote variables will be set to.

##### Return Value

Returns CANAL_ERROR_SUCCESS on success or an error code on failure.

## setRemoteVariableEventEx

`<code=cpp>`
    int setRemoteVariableEventEx( const wxString& name, vscpEventEx *pEventEx);
`</code>`

Set remote variable value for VSCP event ex variable.

#####  name

Name of the remote variable.

#####  pEventEx

Pointer to VSCP event ex value that will be set to the remote variable's value.

##### Return Value

Returns CANAL_ERROR_SUCCESS on success or an error code on failure.

## getRemoteVariableEventEx

`<code=cpp>`
    int getRemoteVariableGUID( const wxString& name, cguid& guid );
`</code>`

Get the value of the GUID variable.

#####  name

Name of the remote variable.

#####  guid

Reference to GUID value that the remote variables will be set to.

##### Return Value

Returns CANAL_ERROR_SUCCESS on success or an error code on failure.

## setRemoteVariableGUID

`<code=cpp>`
    int setRemoteVariableGUID( const wxString& name, cguid& guid);
`</code>`

Set remote variable value for VSCP guid variable.

#####  name

Name of the remote variable.

#####  guid

Reference to guid value that will be set to the remote variable's value.

##### Return Value

Returns CANAL_ERROR_SUCCESS on success or an error code on failure.


## getRemoteVariableVSCPdata

`<code=cpp>`
    int getRemoteVariableVSCPdata( const wxString& name, 
                                        uint8_t *psizeData, 
                                        uint16_t *pData);
`</code>`

Get the value of the VSCP data variable.

#####  name

Name of the remote variable.

##### psizeData

Pointer to an unsigned char that will receive the size of the data array.

#####  pData

Pointer to a VSCP data array variable (unsigned char [487]) that will receive the value of the remote variable.

##### Return Value

Returns CANAL_ERROR_SUCCESS on success or an error code on failure.

## setRemoteVariableVSCPdata

`<code=cpp>`
    int setRemoteVariableVSCPdata( const wxString& name, uint8_t *pData, uint16_t size);
`</code>`

set remote variable value for VSCP data.

#####  name

Name of the remote variable.

#####  sizeData

Size of VSCP data.

#####  pData

Pointer to VSCP data array to set data from.

##### Return Value

Returns CANAL_ERROR_SUCCESS on success or an error code on failure.

## getRemoteVariableVSCPclass

`<code=cpp>`
    int getRemoteVariableVSCPclass( const wxString& name, uint16_t *vscp_class);
`</code>`

Get the value of the VSCP class variable.

#####  name

Name of the remote variable.

##### vscp_class

Pointer to a uint16_t that will receive the value of the VSCP class variable.

##### Return Value

Returns CANAL_ERROR_SUCCESS on success or an error code on failure.

## setRemoteVariableVSCPclass

`<code=cpp>`
    int setRemoteVariableVSCPclass( const wxString& name, uint16_t vscp_class);
`</code>`

Set remote variable value from VSCP class.

#####  name

Name of the remote variable.

#####  vscp_class

VSCP class to write to remote variable.

##### Return Value

Returns CANAL_ERROR_SUCCESS on success or an error code on failure.



## getRemoteVariableVSCPtype

`<code=cpp>`
    int getRemoteVariableVSCPtype( const wxString& name, uint16_t *vscp_type);
`</code>`

Get the value of the VSCP type variable.

#####  name

Name of the remote variable.

##### vscp_type

Pointer to a uint16_t that will receive the value of the VSCP type variable.

##### Return Value

Returns CANAL_ERROR_SUCCESS on success or an error code on failure.

## setRemoteVariableVSCPtype

`<code=cpp>`
    int setRemoteVariableVSCPtype( const wxString& name, uint16_t vscp_type);
`</code>`

Set remote variable value from VSCP type.

#####  name

Name of the remote variable.

#####  vscp_type

VSCP type to write to remote variable.

##### Return Value

Returns CANAL_ERROR_SUCCESS on success or an error code on failure.

## getRemoteVariableVSCPTimestamp

`<code=cpp>`
    int getRemoteVariableVSCPTimestamp( const wxString& name, uint32_t *vscp_timestamp);
`</code>`

Get the value of the VSCP timestamp variable.

#####  name

Name of the remote variable.

##### vscp_timestamp

Pointer to a uint32_t that will receive the value of the VSCP timestamp variable.

##### Return Value

Returns CANAL_ERROR_SUCCESS on success or an error code on failure.

## setRemoteVariableVSCPTimestamp

`<code=cpp>`
    int setRemoteVariableVSCPTimestamp( const wxString& name, uint32_t vscp_timestamp);
`</code>`

Set remote variable value from VSCP timestamp.

#####  name

Name of the remote variable.

#####  vscp_timestamp

VSCP timestamp to write to remote variable.

##### Return Value

Returns CANAL_ERROR_SUCCESS on success or an error code on failure.

## getRemoteVariableDateTime

`<code=cpp>`
    int getRemoteVariableDateTime( const wxString& name, wxDateTime& datetime );
`</code>`

Get the value of the VSCP datetime variable.

#####  name

Name of the remote variable.

##### datetime

Pointer to a wxDateTime object that will receive the value of the VSCP datetime variable.

##### Return Value

Returns CANAL_ERROR_SUCCESS on success or an error code on failure.

## setRemoteVariableDateTime

`<code=cpp>`
    int setRemoteVariableDateTime( const wxString& name, wxDateTime& datetime );
`</code>`

Set remote variable value from VSCP datetime.

#####  name

Name of the remote variable.

#####  datetime

VSCP datetime to write to remote variable.

##### Return Value

Returns CANAL_ERROR_SUCCESS on success or an error code on failure.

## getRemoteVariableDate

`<code=cpp>`
    int getRemoteVariableDate( const wxString& name, wxDateTime& date );
`</code>`

Get the value of the VSCP date variable.

#####  name

Name of the remote variable.

##### date

Pointer to a wxDateTime object that will receive the value of the VSCP date variable.

##### Return Value

Returns CANAL_ERROR_SUCCESS on success or an error code on failure.

## setRemoteVariableDate

`<code=cpp>`
    int setRemoteVariableDate( const wxString& name, wxDateTime& date );
`</code>`

Set remote variable value from VSCP date.

#####  name

Name of the remote variable.

#####  date

VSCP date to write to remote variable.

##### Return Value

Returns CANAL_ERROR_SUCCESS on success or an error code on failure.

## getRemoteVariableTime

`<code=cpp>`
    int getRemoteVariableTime( const wxString& name, wxDateTime& time );
`</code>`

Get the value of the VSCP time variable.

#####  name

Name of the remote variable.

##### time

Pointer to a wxDateTime object that will receive the value of the VSCP time variable.

##### Return Value

Returns CANAL_ERROR_SUCCESS on success or an error code on failure.

## setRemoteVariableTime

`<code=cpp>`
    int setRemoteVariableTime( const wxString& name, wxDateTime& time );
`</code>`

Set remote variable value from VSCP time.

#####  name

Name of the remote variable.

#####  time

VSCP time to write to remote variable.

##### Return Value

Returns CANAL_ERROR_SUCCESS on success or an error code on failure.

## getRemoteVariableBlob

`<code=cpp>`
    int getRemoteVariableBlob( const wxString& name, wxString& blob );
`</code>`

Get the value of a Base64-encoded blob variable.

#####  name

Name of the remote variable.

##### blob

Reference to blob that will receive the value of the Base64-encoded blob variable.

##### Return Value

Returns CANAL_ERROR_SUCCESS on success or an error code on failure.

## setRemoteVariableBlob

`<code=cpp>`
    int setRemoteVariableBlob( const wxString& name, wxString& blob );
`</code>`

Set remote variable from Base64-encoded blob.

#####  name

Name of the remote variable.

#####  blob

Reference to Base64-encoded blob to write to variable.

##### Return Value

Returns CANAL_ERROR_SUCCESS on success or an error code on failure.



## getRemoteVariableMIME

`<code=cpp>`
    int getRemoteVariableMIME( const wxString& name, wxString& mime );
`</code>`

Get the value of a Base64-encoded MIME variable.

#####  name

Name of the remote variable.

##### mime

Reference to MIME data that will receive the value of the Base64-encoded MIME variable.

##### Return Value

Returns CANAL_ERROR_SUCCESS on success or an error code on failure.

## setRemoteVariableMIME

`<code=cpp>`
    int setRemoteVariableMIME( const wxString& name, wxString& mime );
`</code>`

Set remote variable value from Base64-encoded MIME data.

#####  name

Name of the remote variable.

#####  mime

Reference to Base64-encoded MIME data to write to variable.

##### Return Value

Returns CANAL_ERROR_SUCCESS on success or an error code on failure.

## getRemoteVariableHTML

`<code=cpp>`
    int getRemoteVariableHTML( const wxString& name, wxString& html );
`</code>`

Get the value of a Base64-encoded HTML variable.

#####  name

Name of the remote variable.

##### html

Reference to HTML data that will receive the value of the Base64-encoded HTML variable.

##### Return Value

Returns CANAL_ERROR_SUCCESS on success or an error code on failure.

## setRemoteVariableHTML

`<code=cpp>`
    int setRemoteVariableHTML( const wxString& name, wxString& html );
`</code>`

Set remote variable value from Base64-encoded HTML data.

#####  name

Name of the remote variable.

#####  html

Reference to Base64-encoded HTML data to write to variable.

##### Return Value

Returns CANAL_ERROR_SUCCESS on success or an error code on failure.


## getRemoteVariableJavaScript

`<code=cpp>`
    int getRemoteVariableJavaScript( const wxString& name, wxString& js );
`</code>`

Get the value of a Base64-encoded JavaScript variable.

#####  name

Name of the remote variable.

##### js

Reference to JavaScript data that will receive the value of the Base64-encoded JavaScript variable.

##### Return Value

Returns CANAL_ERROR_SUCCESS on success or an error code on failure.

## setRemoteVariableJavaScript

`<code=cpp>`
    int setRemoteVariableJavaScript( const wxString& name, wxString& js ); 
`</code>`

Set remote variable value from Base64-encoded JavaScript data.

#####  name

Name of the remote variable.

#####  js

Reference to Base64-encoded JavaScript data to write to variable.

##### Return Value

Returns CANAL_ERROR_SUCCESS on success or an error code on failure.

## getRemoteVariableLUA

`<code=cpp>`
    int getRemoteVariableLUA( const wxString& name, wxString& lua );
`</code>`

Get the value of a Base64-encoded LUA variable.

#####  name

Name of the remote variable.

##### lua

Reference to LUA data that will receive the value of the Base64-encoded LUA variable.

##### Return Value

Returns CANAL_ERROR_SUCCESS on success or an error code on failure.

## setRemoteVariableLUA

`<code=cpp>`
    int setRemoteVariableLUA( const wxString& name, wxString& lua ); 
`</code>`

Set remote variable value from Base64-encoded LUA data.

#####  name

Name of the remote variable.

#####  lua

Reference to Base64-encoded LUA data to write to variable.

##### Return Value

Returns CANAL_ERROR_SUCCESS on success or an error code on failure.


## getRemoteVariableLUARES

`<code=cpp>`
    int getRemoteVariableLUARES( const wxString& name, wxString& luares );
`</code>`

Get the value of a Base64-encoded LUARES variable.

#####  name

Name of the remote variable.

##### luares

Reference to LUARES data that will receive the value of the Base64-encoded LUARES variable.

##### Return Value

Returns CANAL_ERROR_SUCCESS on success or an error code on failure.

## setRemoteVariableLUARES

`<code=cpp>`
    int setRemoteVariableLUARES( const wxString& name, wxString& luares ); 
`</code>`

Set remote variable value from Base64-encoded LUARES data.

#####  name

Name of the remote variable.

#####  luares

Reference to Base64-encoded LUARES data to write to variable.

##### Return Value

Returns CANAL_ERROR_SUCCESS on success or an error code on failure.

## getRemoteVariableUX1

`<code=cpp>`
    int getRemoteVariableUX1( const wxString& name, wxString& ux1 );
`</code>`

Get the value of a Base64-encoded UX1 variable.

#####  name

Name of the remote variable.

##### ux1

Reference to UX1 data that will receive the value of the Base64-encoded UX1 variable.

##### Return Value

Returns CANAL_ERROR_SUCCESS on success or an error code on failure.

## setRemoteVariableUX1

`<code=cpp>`
    int setRemoteVariableUX1( const wxString& name, wxString& ux1 ); 
`</code>`

Set remote variable value from Base64-encoded UX1 data.

#####  name

Name of the remote variable.

#####  ux1

Reference to Base64-encoded UX1 data to write to variable.

##### Return Value

Returns CANAL_ERROR_SUCCESS on success or an error code on failure.


## getRemoteVariableDMROW

`<code=cpp>`
    int getRemoteVariableDMROQ( const wxString& name, wxString& dmrow );
`</code>`

Get the value of a Base64-encoded DM row variable.

#####  name

Name of the remote variable.

##### dmrow

Reference to DM row data that will receive the value of the Base64-encoded DM row variable.

##### Return Value

Returns CANAL_ERROR_SUCCESS on success or an error code on failure.

## setRemoteVariableDMROW

`<code=cpp>`
    int setRemoteVariableDMROW( const wxString& name, wxString& dmrow ); 
`</code>`

Set remote variable value from Base64-encoded DM row data.

#####  name

Name of the remote variable.

#####  dmrow

Reference to Base64-encoded DM row data to write to variable.

##### Return Value

Returns CANAL_ERROR_SUCCESS on success or an error code on failure.


## getRemoteVariableDriver

`<code=cpp>`
    int getRemoteVariableDriver( const wxString& name, wxString& drv );
`</code>`

Get the value of a Base64-encoded driver variable.

#####  name

Name of the remote variable.

##### drv

Reference to driver data that will receive the value of the Base64-encoded driver variable.

##### Return Value

Returns CANAL_ERROR_SUCCESS on success or an error code on failure.

## setRemoteVariableDriver

`<code=cpp>`
    int setRemoteVariableDriver( const wxString& name, wxString& drv ); 
`</code>`

Set remote variable value from Base64-encoded driver data.

#####  name

Name of the remote variable.

#####  drv

Reference to Base64-encoded driver data to write to variable.

##### Return Value

Returns CANAL_ERROR_SUCCESS on success or an error code on failure.


## getRemoteVariableUser

`<code=cpp>`
    int getRemoteVariableUser( const wxString& name, wxString& user );
`</code>`

Get the value of a Base64-encoded user variable.

#####  name

Name of the remote variable.

##### user

Reference to user data that will receive the value of the Base64-encoded user variable.

##### Return Value

Returns CANAL_ERROR_SUCCESS on success or an error code on failure.

## setRemoteVariableUser

`<code=cpp>`
    int setRemoteVariableUser( const wxString& name, wxString& user ); 
`</code>`

Set remote variable value from Base64-encoded user data.

#####  name

Name of the remote variable.

#####  user

Reference to Base64-encoded user data to write to variable.

##### Return Value

Returns CANAL_ERROR_SUCCESS on success or an error code on failure.

## getRemoteVariableFilter

`<code=cpp>`
    int getRemoteVariableFilter( const wxString& name, wxString& filter );
`</code>`

Get the value of a Base64-encoded filter variable.

#####  name

Name of the remote variable.

##### filter

Reference to filter data that will receive the value of the Base64-encoded filter variable.

##### Return Value

Returns CANAL_ERROR_SUCCESS on success or an error code on failure.

## setRemoteVariableFilter

`<code=cpp>`
    int setRemoteVariableFilter( const wxString& name, wxString& filter ); 
`</code>`

Set remote variable value from Base64-encoded filter data.

#####  name

Name of the remote variable.

#####  filter

Reference to Base64-encoded filter data to write to variable.

##### Return Value

Returns CANAL_ERROR_SUCCESS on success or an error code on failure.


# Table handling methods

## tableCreate

`<code=cpp>`
    int tableCreate( const wxString& defTable ); 
`</code>`

Create table from XML data.

#####  defTable

XML definition of table.

##### Return Value

Returns CANAL_ERROR_SUCCESS on success or an error code on failure.

## tableDelete

`<code=cpp>`
    int tableDelete( const wxString &tblName, bool bDeleteFile=false ); 
`</code>`

Delete named table.

#####  tblName

Name of an existing table.

#####  bDeleteFile

If true, delete the database **file** as well. Otherwise, it is reused if a table with the same name is created later.

##### Return Value

Returns CANAL_ERROR_SUCCESS on success or an error code on failure.

## tableList

`<code=cpp>`
    int tableList( wxArrayString &tablesArray );
`</code>`

Get a list of all defined tables.

#####  tablesArray

List that will be filled with table names.

##### Return Value

Returns CANAL_ERROR_SUCCESS on success or an error code on failure.

## tableListInfo

`<code=cpp>`
    int tableListInfo( const wxString &tblName, wxString &tableInfo, bool bXML = true ); 
`</code>`

Delete named table.

#####  tblName

Name of an existing table.

#####  tableInfo

Parameter that will receive information about the table.

##### bXML

If true, information is returned as Base64-encoded XML data.

##### Return Value

Returns CANAL_ERROR_SUCCESS on success or an error code on failure.

## tableGet

`<code=cpp>`
    int tableGet( const wxString& tblName, 
                                const wxDateTime& from, 
                                const wxDateTime& to,
                                wxArrayString& resultArray,
                                bool bFull = false  ); 
`</code>`

Get data from a named table for a date/time range. You can fetch all columns (bFull) or just the datetime and value (the default).

#####  tblName

Name of an existing table.

#####  from

Start datetime for the data to fetch, in ISO 8601 format YY-MM-DDTHH:MM:SS.

#####  to

End datetime for the data to fetch, in ISO 8601 format YY-MM-DDTHH:MM:SS.

##### resultArray

String array that is filled with resulting rows (if any) from the table. The format is

    'count' rows`<CR>``<LF>`
    YY-MM-DDTHH:MM:SSsss, value1[,other fields]`<CR>``<LF>`
    YY-MM-DDTHH:MM:SSsss, value2[,other fields]`<CR>``<LF>`
    YY-MM-DDTHH:MM:SSsss, value3[,other fields]`<CR>``<LF>`
    ...
    YY-MM-DDTHH:MM:SS, valuen[,other fields]`<CR>``<LF>`
    +OK - Success.`<CR>``<LF>`

##### bFull

If true, all fields of a table row are returned (//other fields// above) in a comma-separated list. Datetime is always listed first, followed by value, regardless of the table's column order.

##### Return Value

Returns CANAL_ERROR_SUCCESS on success or an error code on failure.

## tableGetRaw

`<code=cpp>`
    int tableGetRaw( const wxString& tblName, 
                                const wxDateTime& from, 
                                const wxDateTime& to,
                                wxArrayString& resultArray ); 
`</code>`

Get data from a named table for a date/time range. All columns of the table are always returned.

#####  tblName

Name of an existing table.

#####  from

Start datetime for the data to fetch, in ISO 8601 format YY-MM-DDTHH:MM:SS.

#####  to

End datetime for the data to fetch, in ISO 8601 format YY-MM-DDTHH:MM:SS.

##### resultArray

String array that is filled with resulting rows (if any) from the table. The format is

    'count' rows`<CR>``<LF>`
    comma separated row of database columns`<CR>``<LF>`
    comma separated row of database columns`<CR>``<LF>`
    comma separated row of database columns`<CR>``<LF>`
    ...
    comma separated row of database columns`<CR>``<LF>`
    +OK - Success.`<CR>``<LF>`

##### Return Value

Returns CANAL_ERROR_SUCCESS on success or an error code on failure.


## tableLog

`<code=cpp>`
    int tableLog( const wxString& tblName, 
                        double value, 
                        wxDateTime *pdt = NULL ); 
`</code>`

Log a value, date/time pair to a table.

#####  tblName

Name of an existing table.

#####  value

Value to log. 

#####  pdt

Pointer to a date/time value. If NULL, the current date and time are used.

##### Return Value

Returns CANAL_ERROR_SUCCESS on success or an error code on failure.

## tableLogSQL

`<code=cpp>`
    int tableLogSQL( const wxString& tblName, 
                        const wxString& sql ); 
`</code>`

Log data using an SQL expression.

#####  tblName

Name of an existing table.

#####  sql

SQL expression used to log data. 

##### Return Value

Returns CANAL_ERROR_SUCCESS on success or an error code on failure.

## tableGetNumRecords

`<code=cpp>`
    int tableGetNumRecords( const wxString& tblName, 
                                const wxDateTime& from, 
                                const wxDateTime& to,
                                size_t *pRecords ); 
`</code>`

Get the number of records for an interval in a named table.

#####  tblName

Name of an existing table.

#####  from

Start date and time for the data to fetch. Set to "0000-01-01T00:00:00" for the *beginning of time*.

##### to

End date and time for the data to fetch. Set to "9999-12-31T23:59:59" for the *end of time*.

#####  pRecords

A size_t that will receive the number of records in the interval on success.

##### Return Value

Returns CANAL_ERROR_SUCCESS on success or an error code on failure.

## tableGetFirstDate

`<code=cpp>`
    int tableGetFirstDate( const wxString& tblName, 
                                const wxDateTime& from, 
                                const wxDateTime& to,
                                wxDateTime& first ); 
`</code>`

Get the first date/time for an interval in a named table.

#####  tblName

Name of an existing table.

#####  from

Start date and time for the data to fetch. Set to "0000-01-01T00:00:00" for the *beginning of time*.

##### to

End date and time for the data to fetch. Set to "9999-12-31T23:59:59" for the *end of time*.

#####  first

Receives the first date/time in the interval on success.

##### Return Value

Returns CANAL_ERROR_SUCCESS on success or an error code on failure.

## tableGetLastDate

`<code=cpp>`
    int tableGetLastDate( const wxString& tblName, 
                                const wxDateTime& from, 
                                const wxDateTime& to,
                                wxDateTime& last ); 
`</code>`

Get the last date/time for an interval in a named table.

#####  tblName

Name of an existing table.

#####  from

Start date and time for the data to fetch. Set to "0000-01-01T00:00:00" for the *beginning of time*.

##### to

End date and time for the data to fetch. Set to "9999-12-31T23:59:59" for the *end of time*.

#####  last

Receives the last date/time in the interval on success.

##### Return Value

Returns CANAL_ERROR_SUCCESS on success or an error code on failure.

## tableGetSum

`<code=cpp>`
    int tableGetSum( const wxString& tblName, 
                        const wxDateTime& from, 
                        const wxDateTime& to,
                        double *pSum ); 
`</code>`

Get the sum of all values for an interval in a named table.

#####  tblName

Name of an existing table.

#####  from

Start date and time for the data to fetch. Set to "0000-01-01T00:00:00" for the *beginning of time*.

##### to

End date and time for the data to fetch. Set to "9999-12-31T23:59:59" for the *end of time*.

#####  pSum

Pointer to a double that will receive the sum of all values in the interval on success.

##### Return Value

Returns CANAL_ERROR_SUCCESS on success or an error code on failure.

## tableGetMin

`<code=cpp>`
    int tableGetMin( const wxString& tblName, 
                        const wxDateTime& from, 
                        const wxDateTime& to,
                        double *pMin ); 
`</code>`

Get the minimum of all values for an interval in a named table.

#####  tblName

Name of an existing table.

#####  from

Start date and time for the data to fetch. Set to "0000-01-01T00:00:00" for the *beginning of time*.

##### to

End date and time for the data to fetch. Set to "9999-12-31T23:59:59" for the *end of time*.

#####  pMin

Pointer to a double that will receive the minimum of all values in the interval on success.

##### Return Value

Returns CANAL_ERROR_SUCCESS on success or an error code on failure.

## tableGetMax

`<code=cpp>`
    int tableGetMax( const wxString& tblName, 
                        const wxDateTime& from, 
                        const wxDateTime& to,
                        double *pMax ); 
`</code>`

Get the maximum of all values for an interval in a named table.

#####  tblName

Name of an existing table.

#####  from

Start date and time for the data to fetch. Set to "0000-01-01T00:00:00" for the *beginning of time*.

##### to

End date and time for the data to fetch. Set to "9999-12-31T23:59:59" for the *end of time*.

#####  pMax

Pointer to a double that will receive the maximum of all values in the interval on success.

##### Return Value

Returns CANAL_ERROR_SUCCESS on success or an error code on failure.


## tableGetAverage

`<code=cpp>`
    int tableGetAverage( const wxString& tblName, 
                            const wxDateTime& from, 
                            const wxDateTime& to,
                            double *pAverage ); 
`</code>`

Get the average of all values for an interval in a named table.

#####  tblName

Name of an existing table.

#####  from

Start date and time for the data to fetch. Set to "0000-01-01T00:00:00" for the *beginning of time*.

##### to

End date and time for the data to fetch. Set to "9999-12-31T23:59:59" for the *end of time*.

#####  pAverage

Pointer to a double that will receive the average of all values in the interval on success.

##### Return Value

Returns CANAL_ERROR_SUCCESS on success or an error code on failure.

## tableGetMedian

`<code=cpp>`
    int tableGetMedian( const wxString& tblName, 
                            const wxDateTime& from, 
                            const wxDateTime& to,
                            double *pMedian ); 
`</code>`

Get the median (middle/second quartile) of all values for an interval in a named table.

#####  tblName

Name of an existing table.

#####  from

Start date and time for the data to fetch. Set to "0000-01-01T00:00:00" for the *beginning of time*.

##### to

End date and time for the data to fetch. Set to "9999-12-31T23:59:59" for the *end of time*.

#####  pMedian

Pointer to a double that will receive the median of all values in the interval on success.

##### Return Value

Returns CANAL_ERROR_SUCCESS on success or an error code on failure.

## tableGetStdDev

`<code=cpp>`
    int tableGetStdDev( const wxString& tblName, 
                            const wxDateTime& from, 
                            const wxDateTime& to,
                            double *pStdDev ); 
`</code>`

Get the standard deviation of all values for an interval in a named table.

#####  tblName

Name of an existing table.

#####  from

Start date and time for the data to fetch. Set to "0000-01-01T00:00:00" for the *beginning of time*.

##### to

End date and time for the data to fetch. Set to "9999-12-31T23:59:59" for the *end of time*.

#####  pStdDev

Pointer to a double that will receive the standard deviation of all values in the interval on success.

##### Return Value

Returns CANAL_ERROR_SUCCESS on success or an error code on failure.

## tableGetVariance

`<code=cpp>`
    int tableGetVariance( const wxString& tblName, 
                            const wxDateTime& from, 
                            const wxDateTime& to,
                            double *pVariance ); 
`</code>`

Get the variance of all values for an interval in a named table.

#####  tblName

Name of an existing table.

#####  from

Start date and time for the data to fetch. Set to "0000-01-01T00:00:00" for the *beginning of time*.

##### to

End date and time for the data to fetch. Set to "9999-12-31T23:59:59" for the *end of time*.

#####  pVariance

Pointer to a double that will receive the variance of all values in the interval on success.

##### Return Value

Returns CANAL_ERROR_SUCCESS on success or an error code on failure.

## tableGetMode

`<code=cpp>`
    int tableGetMode( const wxString& tblName, 
                            const wxDateTime& from, 
                            const wxDateTime& to,
                            double *pMode ); 
`</code>`

Get the mode of all values for an interval in a named table.

#####  tblName

Name of an existing table.

#####  from

Start date and time for the data to fetch. Set to "0000-01-01T00:00:00" for the *beginning of time*.

##### to

End date and time for the data to fetch. Set to "9999-12-31T23:59:59" for the *end of time*.

#####  pMode

Pointer to a double that will receive the mode of all values in the interval on success.

##### Return Value

Returns CANAL_ERROR_SUCCESS on success or an error code on failure.

## tableGetLowerQ

`<code=cpp>`
    int tableGetLowerQ( const wxString& tblName, 
                            const wxDateTime& from, 
                            const wxDateTime& to,
                            double *pLowerQ ); 
`</code>`

Get the lower/first quartile of all values for an interval in a named table.

#####  tblName

Name of an existing table.

#####  from

Start date and time for the data to fetch. Set to "0000-01-01T00:00:00" for the *beginning of time*.

##### to

End date and time for the data to fetch. Set to "9999-12-31T23:59:59" for the *end of time*.

#####  pLowerQ

Pointer to a double that will receive the lower quartile of all values in the interval on success.

##### Return Value

Returns CANAL_ERROR_SUCCESS on success or an error code on failure.

## tableGetUpperQ

`<code=cpp>`
    int tableGetUpperQ( const wxString& tblName, 
                            const wxDateTime& from, 
                            const wxDateTime& to,
                            double *pUpperQ ); 
`</code>`

Get the upper/third quartile of all values for an interval in a named table.

#####  tblName

Name of an existing table.

#####  from

Start date and time for the data to fetch. Set to "0000-01-01T00:00:00" for the *beginning of time*.

##### to

End date and time for the data to fetch. Set to "9999-12-31T23:59:59" for the *end of time*.

#####  pUpperQ

Pointer to a double that will receive the upper quartile of all values in the interval on success.

##### Return Value

Returns CANAL_ERROR_SUCCESS on success or an error code on failure.

## tableClear

`<code=cpp>`
    int tableClear( const wxString& tblName, 
                            const wxDateTime& from, 
                            const wxDateTime& to ); 
`</code>`

Remove all records in an interval in a named table.

#####  tblName

Name of an existing table.

#####  from

Start date and time for the data to fetch. Set to "0000-01-01T00:00:00" for the *beginning of time*.

##### to

End date and time for the data to fetch. Set to "9999-12-31T23:59:59" for the *end of time*.

##### Return Value

Returns CANAL_ERROR_SUCCESS on success or an error code on failure.


# Register handling methods


## readLevel2Register

`<code=cpp>`
    int readLevel2Register( uint32_t reg,
                                uint16_t page,
                                uint8_t *pval,
                                cguid& ifGUID,
                                cguid *pdestGUID = NULL,
                                bool bLevel2 = false); 
`</code>`

Read a level II register.

#####  reg

Register to read (32-bit value for true Level II).

#####  page

Page to read the register from.

##### pval

Pointer to an eight-bit value that will receive the value read from the register.

##### ifGUID

GUID of the interface on which these events should be sent. This is used to read registers of Level I devices.
                
##### pdestGUID

GUID of the remote node.

##### bLevel2

If true, this is a true Level II read operation.

##### Return Value

Returns CANAL_ERROR_SUCCESS on success or an error code on failure.


## readLevel2Registers

`<code=cpp>`
    int readLevel2Registers( uint32_t reg,
                                uint16_t page,
                                uint8_t count,
                                uint8_t *pval,
                                cguid& ifGUID,
                                cguid *pdestGUID = NULL,
                                bool bLevel2 = false ); 
`</code>`

Read one or more level II registers.

#####  reg

First register to read (32-bit value for true Level II).

#####  page

Page to read the register(s) from.

#####  count

Number of registers to read.

##### pval

Pointer to an array that will receive the values read from the registers.

##### ifGUID

GUID of the interface on which these events should be sent. This is used to read registers of Level I devices.
                
##### pdestGUID

GUID of the remote node.

##### bLevel2

If true, this is a true Level II read operation.

##### Return Value

Returns CANAL_ERROR_SUCCESS on success or an error code on failure.


## writeLevel2Register

`<code=cpp>`
    int writeLevel2Register(uint32_t reg,
                                uint16_t page,
                                uint8_t *pval,
                                cguid& ifGUID,
                                cguid *pdestGUID = NULL,
                                bool bLevel2 = false ); 
`</code>`

Write a level 2 register.

#####  reg

Register to write to (32-bit value for true Level II).

#####  page

Page at which the register is located.

##### pval

Pointer to the byte to write to the register. On return, it contains the written value returned by the node.

##### ifGUID

GUID of the interface on which these events should be sent. This is used to read registers of Level I devices.
                
##### pdestGUID

GUID of the remote node.

##### bLevel2

If true, this is a true Level II read operation.

##### Return Value

Returns CANAL_ERROR_SUCCESS on success or an error code on failure.


## getMDFUrlFromLevel2Device

`<code=cpp>`
    bool getMDFUrlFromLevel2Device( cguid& ifGUID,
                                        cguid& destGUID,
                                        wxString &strurl,
                                        bool bLevel2 = false );
`</code>`

Get the MDF file from the device registers.

##### ifGUID

GUID of the interface on which these events should be sent. This is used to read registers of Level I devices.
                
##### pdestGUID

GUID of the remote node.

##### strURL

Reference to a string that will receive the device's MDF URL on success.

##### bLevel2

If true, this is a true Level II read operation.

##### Return Value

Returns CANAL_ERROR_SUCCESS on success or an error code on failure.

## fetchIterfaceGUID

`<code=cpp>`
    int fetchIterfaceGUID( const wxString& ifName, cguid& guid );
`</code>`

Fetch the GUID of a TCP/IP interface by name.

##### ifName

Real text name of the VSCP server interface.
                
##### guid

GUID of the interface, if the named interface exists.

##### Return Value

Returns CANAL_ERROR_SUCCESS on success or an error code on failure.
