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

Set after command sleep time (milliseconds). Default is 0 milliseconds as it is normally not needed but can be on a system that is very slow to respond to commands.

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

Check the response from the remote VSCP server and look for an error or a correctly carried out command.

##### bClear

If set to true the input queue array will be cleared before the call.

##### Return value

True is returned if a positive response (+OK) s received from the remote VSCP server, false otherwise which can be the result of a negative reply or a timeout.

## doClrInputQueue

`<code=cpp>`
    void doClrInputQueue(void);
`</code>`

Clear the input queue

## doCommand

`<code=cpp>`
    int doCommand(wxString& cmd);
`</code>`

Send a command to the remote VSCP server. Allows to send any command.

##### cmd

A VSCP remote server command that is terminated with `<CR>``<LF>` ("\r\n").

##### Return Value

Returns VSCP_ERROR_SUCCESS if the command could be sent successfully and a positive response (+OK) is received. If not an error code will be returned.

## doCmdOpen

`<code=cpp>`
    int doCmdOpen(const wxString& strInterface = (_("")), uint32_t flags = 0L);
`</code>`

Open communication interface.

#####  strInterface

Should be set to "username;password;ip-addr;port" if used. All values including port is optional and defaults to no username/password, server as "localhost" and port as "9598"

##### flags

Currently not used.
           
##### Return Value

VSCP_ERROR_SUCCESS is returned if the connection to the remote VSCP server could be established. If not an error code will be returned.
      
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

VSCP_ERROR_SUCCESS is returned if the connection to the remote VSCP server could be established. If not an error code will be returned.

## doCmdClose

`<code=cpp>`
    int doCmdClose(void);
`</code>`

Close connection to remote VSCP server.

##### Return Value

CANAL_ERROR_SUCCESS on success or an error code on failure.
          
## doCmdNOOP

`<code=cpp>`
    int doCmdNOOP(void);
`</code>`

Send the NOOP (no operation) command to the VSCP remote server. This command only returns a positive response and can be used to test if a connection works.

##### Return Value

CANAL_ERROR_SUCCESS on success or an error code on failure.
    
## doCmdClear

`<code=cpp>`
    int doCmdClear(void);
`</code>`

Clear input queue on the remote VSCP server.

##### Return Value

CANAL_ERROR_SUCCESS on success or an error code on failure.      
     
## doCmdGetLevel

`<code=cpp>`
    unsigned long doCmdGetLevel(void);
`</code>`
    
Get the CANAL protocol level. Mainly used by the CANAL/VSCP combined subsystem.
    
##### Return Value

Return the constant VSCP_LEVEL2.
       
## doCmdSend

`<code=cpp>`
    int doCmdSend(const vscpEvent *pEvent);
`</code>`

Send a VSCP Level II event to the VSCP remote server.

##### pEvent

Pointer to VSCP Level II event to send. If the event have a GUID all set to zero the GUID of the VSCP remote server interface ("-") will be used.

##### Return Value

CANAL_ERROR_SUCCESS on success or an error code on failure.
         
## doCmdSendEx

`<code=cpp>`
    int doCmdSendEx(const vscpEventEx *pEventEx);
`</code>`

Send a VSCP Level II event ex to the VSCP remote server. 

*A vscpEvent structure contains a pointer to the data part of the event, while the vscpEventEx have the max data storage allocated in every event and therefore waste a lot of memory that can be used in a better way.*

##### pEventEx

Pointer to VSCP Level II event ex to send. If the event have a GUID all set to zero the GUID of the VSCP remote server interface ("-") will be used.

##### Return Value

CANAL_ERROR_SUCCESS on success or an error code on failure.
           
## doCmdSendLevel1

`<code=cpp>`
    int doCmdSendLevel1(const canalMsg *pMsg);
`</code>`           
       
Send a Level I event to the VSCP remote server. The GUID of the interface will be used for the resulting VSCP event.

##### pMsg

A pointer to a CANAL message.
           
##### Return Value

CANAL_ERROR_SUCCESS on success or an error code on failure.

## doCmdReceive

`<code=cpp>`
    int doCmdReceive(vscpEvent *pEvent);
`</code>`

##### pEvent

Pointer to VSCP event that will receive the event from the remote VSCP server queue if the call is successful.

##### Return Value

CANAL_ERROR_SUCCESS on success or an error code on failure.

## doCmdReceiveEx

`<code=cpp>`
    int doCmdReceiveEx(vscpEventEx *pEventEx);
`</code>`

##### pEventEx

Pointer to VSCP event ex that will receive the event ex from the remote VSCP server queue if the call is successful.

##### Return Value

CANAL_ERROR_SUCCESS on success or an error code on failure.

## doCmdReceiveLevel1

`<code=cpp>`
    int doCmdReceiveLevel1(canalMsg *pCanalMsg);
`</code>`

Receive an VSCP Level I event from the VSCP remote server queue. The low eight bits of the CAN id is fetched from GUID[15], that is from the LSB of the GUID.
        
##### pCanalMsg

Pointer to a CANAL message that will receive the vent from the remote VSCP server queue if the call is successful. 

##### Return Value

CANAL_ERROR_SUCCESS on success or an error code on failure.       
       
## doCmdEnterReceiveLoop

`<code=cpp>`
    int doCmdEnterReceiveLoop(void);
`</code>` 

This command sets an open interface in the receive loop (RCVLOOP) state. It does nothing other then putting the interface in the loop mode and  checking that it went there.

**Note!** The only way to terminate this receive loop is to close the session with doCmdClose (or just close the socket) or send the doQuitLoop command below.      

##### Return Value

CANAL_ERROR_SUCCESS on success or an error code on failure. 
        
## doCmdEnterReceiveLoop

`<code=cpp>`
    int doCmdQuitReceiveLoop(void);
`</code>` 

Quit the receive loop.

##### Return Value

CANAL_ERROR_SUCCESS on success or an error code on failure. 

## doCmdBlockingReceive

`<code=cpp>`
    int doCmdBlockingReceive(vscpEvent *pEvent, uint32_t timeout = 500);
`</code>`

Receive an event from the remote VSCP server. The **receiveloop** command must have been issued for this method to work as.

##### pEvent

Pointer to a VSCP event that will receive the received event on success.

##### timeout

Timeout in milliseconds to wait for data. Default is 500 milliseconds.

##### Return Value

CANAL_ERROR_SUCCESS on success or an error code on failure. CANAL_ERROR_FIFO_EMPTY is returned if no event was available. CANAL_ERROR_TIMEOUT on timeout. CANAL_ERROR_COMMUNICATION is returned if a socket error is detected.
        
## doCmdBlockingReceive

`<code=cpp>`
    int doCmdBlockingReceive(vscpEventEx *pEventEx, uint32_t timeout = 500);
`</code>`

Receive an event ex from the remote VSCP server. The **receiveloop** command must have been issued for this method to work as.

##### pEventEx

Pointer to a VSCP event ex that will receive the received event on success.

##### timeout

Timeout in milliseconds to wait for data. Default is 500 milliseconds.

##### Return Value

CANAL_ERROR_SUCCESS on success or an error code on failure. CANAL_ERROR_FIFO_EMPTY is returned if no event was available. CANAL_ERROR_TIMEOUT on timeout. CANAL_ERROR_COMMUNICATION is returned if a socket error is detected.        
        
## doCmdDataAvailable

`<code=cpp>`
    int doCmdDataAvailable(void);
`</code>`
        
Get the number of events in the input queue of this interface

##### Return value

Return the number of events available in the queue at the remote VSCP server or if a failure occur a negative error code is returned.
        
## doCmdStatus

`<code=cpp>`
    int doCmdStatus(canalStatus *pStatus);
`</code>`                
        
Receive the CANAL status structure from the remote VSCP server.

##### pStatus

Pointer to canalStatus structure that will get the VSCP remote server status.

##### Return Value

CANAL_ERROR_SUCCESS on success or an error code on failure.
    
## doCmdStatus

`<code=cpp>`
    int doCmdStatus(VSCPStatus *pStatus);
`</code>`                
        
Receive the VSCP status structure from the remote VSCP server.

##### pStatus

Pointer to VSCPStatus structure that will get the VSCP remote server status.

##### Return Value

CANAL_ERROR_SUCCESS on success or an error code on failure.

## doCmdStatistics

`<code=cpp>`
    int doCmdStatistics(canalStatistics *pStatistics);
`</code>`

Get the CANAL statistics structure from the VSCP remote server.

##### pStatistics

Pointer to canalStatistics structure that will get the VSCP remote server statistics.

##### Return Value

CANAL_ERROR_SUCCESS on success or an error code on failure.

## doCmdStatistics

`<code=cpp>`
    int doCmdStatistics(VSCPStatistics *pStatistics);
`</code>`

Get the VSCP statistics structure from the VSCP remote server.

##### pStatistics

Pointer to VSCPStatistics structure that will get the VSCP remote server statistics.

##### Return Value

CANAL_ERROR_SUCCESS on success or an error code on failure.
        
## doCmdFilter

`<code=cpp>`
    int doCmdFilter(const vscpEventFilter *pFilter);
`</code>`

Set the receive filter on the remote VSCP server. By setting the filter on can select which events one want to receive. It is possible to open several channels ans have a filter on each for complex setups.

##### pFilter

Pointer to VSCP filter structure to set.

##### Return Value

CANAL_ERROR_SUCCESS on success or an error code on failure.        
        
## doCmdFilter

`<code=cpp>`
    int doCmdFilter(const wxString& filter, const wxString& mask);
`</code>`        

Set the receive filter on the remote VSCP server. By setting the filter on can select which events one want to receive. It is possible to open several channels ans have a filter on each for complex setups.

##### filter

Filter to set on string form ("priority,class,type,guid").

##### mask

Mask to set on string form ("priority,class,type,guid").

##### Return Value

CANAL_ERROR_SUCCESS on success or an error code on failure. 
        
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

CANAL_ERROR_SUCCESS on success or an error code on failure.         
     
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

A pointer to a null terminated string containing vendor information is returned. On failure a NULL pointer is returned.      

## doCmdGetDriverInfo

`<code=cpp>`
    const char *doCmdGetDriverInfo(void);
`</code>`  

Get the driver information string from the remote VSCP server. This is intended for CANAL.

##### Return Value

A pointer to a null terminated string containing driver information on XML format is returned. On failure a NULL pointer is returned.

## doCmdGetGUID

`<code=cpp>`
    int doCmdGetGUID(char *pGUID);
`</code>`  

Get GUID for the remote VSCP server interface.

##### pGUID

Pointer to a 16-byte array that will get the GUID. MSB is in the first byte.

##### Return Value

CANAL_ERROR_SUCCESS on success or an error code on failure.

## doCmdGetGUID

`<code=cpp>`
    int doCmdGetGUID(cguid& ifguid);
`</code>`  

Get GUID for the remote VSCP server interface.

##### ifguid

Reference to the GUID that will get the information.

##### Return Value

CANAL_ERROR_SUCCESS on success or an error code on failure.

## doCmdSetGUID

`<code=cpp>`
    int doCmdSetGUID(const char *pGUID);
`</code>`

Set GUID for the remote VSCP server interface.

##### pGUID

Pointer to a 16-byte array that contain the new GUID. MSB is in the first byte.

##### Return Value

CANAL_ERROR_SUCCESS on success or an error code on failure.

## doCmdSetGUID

`<code=cpp>`
    int doCmdSetGUID(cguid &ifGUID);
`</code>`

Set GUID for the remote VSCP server interface.

##### ifGUID

Reference to GUID that contain the new GUID. 

##### Return Value

CANAL_ERROR_SUCCESS on success or an error code on failure.

## doCmdGetChannelInfo

`<code=cpp>`
    int doCmdGetChannelInfo(VSCPChannelInfo *pChannelInfo);
`</code>`

Get information about the remote VSCP server interface channel.

##### Return Value

CANAL_ERROR_SUCCESS on success or an error code on failure.

## doCmdGetChannelInfo

`<code=cpp>`
    int doCmdGetChannelID(uint32_t *pChannelID);
`</code>`

Get Channel ID for the remote VSCP server interface channel.

##### Return Value

CANAL_ERROR_SUCCESS on success or an error code on failure.

## doCmdInterfaceList

`<code=cpp>`
    int doCmdInterfaceList(wxArrayString& arrayIf );
`</code>`

Get available interfaces on the VSCP remote server.

##### arrayIf

An array that will be filled with interface descriptions of interfaces available on the remote VSCP server.

##### Return Value

CANAL_ERROR_SUCCESS on success or an error code on failure.

## doCmdSetBaudrate

`<code=cpp>`
    int doCmdSetBaudrate(uint32_t baudrate);
`</code>`

Dummy for required CANAL method.

##### baudrate

CANAL baudrate.

##### Return Value

Always return CANAL_ERROR_SUCCESS.

## doCmdFilter

`<code=cpp>`
    int doCmdFilter(uint32_t filter);
`</code>`

Dummy for required CANAL method.

##### filter

CANAL 32-bit filter.

##### Return Value

Always return CANAL_ERROR_SUCCESS.

## doCmdMask

`<code=cpp>`
    int doCmdMask(uint32_t mask);
`</code>`

Dummy for required CANAL method.

##### mask

CANAL 32-bit mask.

##### Return Value

Always return CANAL_ERROR_SUCCESS.

## doCmdShutDown

`<code=cpp>`
    int doCmdShutDown(void);
`</code>`

Shutdown the remote VSCP server. Needless to say you need high privileges on the server to perform this command.

##### Return Value

CANAL_ERROR_SUCCESS on success or an error code on failure.

# Remote variable handling methods

## getRemoteVariableList

`<code=cpp>`
    int getRemoteVariableList( wxArrayString& arrayVars, 
                                    const wxString regexp = _(""),
                                    const int type = 0 );
`</code>`

Get a list of defined variables on remote VSCP server.

##### arrayVars

A reference to a string array that Will be filed with names of VSCP remote variables.

#####  regexp

Regular expression used to select variables. Leave blank to return all variables.

#####  type

Variable type that should be listed or 0 for all variable types.

##### Return Value

CANAL_ERROR_SUCCESS on success or an error code on failure.

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

Select if persistent, non-persistent or both types of variables should be written out to the file.

 * **1** for only writing persistent variables.
 * **2** only write non-persistent variables.
 * **3** or **0**  for writing both types.

##### regExp

Optional regular expression that selects which variables to write. Default is all.

##### Return Value

CANAL_ERROR_SUCCESS on success or an error code on failure.

## loadRemoteVariablesFromDisk

`<code=cpp>`
    int loadRemoteVariablesFromDisk( const wxString& path );
`</code>`

##### path

Path to load the remote variable XML file from.

##### Return Value

CANAL_ERROR_SUCCESS on success or an error code on failure.

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

Name of remote variable to create. A user variable can not have a name that start with "vscp.".

##### strType

Type of variable either in string or numeric form.

##### bPersistet

True if the variable should be persistent (default=false)

##### strUser

Owner of variable. Can be left empty in which case the logged in user will be set as owner.

##### rights

Access rights for variable.

##### strValue

Value for the remote variable.

##### strNote

Optional note for the remote variable.

##### Return Value

CANAL_ERROR_SUCCESS on success or an error code on failure.

## deleteRemoteVariable

`<code=cpp>`
    int deleteRemoteVariable( const wxString& name );
`</code>`

##### name

Name of remote variable to delete.

##### Return Value

CANAL_ERROR_SUCCESS on success or an error code on failure.

## getRemoteVariable

`<code=cpp>`
    int getRemoteVariable( const wxString& name, wxString& strVariable );
`</code>`

Get remote variable (full info).

Format is: 
    "variable name";"type";"persistence";"user";"rights";"value";"note"

#####  name

Name of remote variable to get information for.

#####  strVariable

String that will get variable information.

##### Return Value

CANAL_ERROR_SUCCESS on success or an error code on failure.

## getRemoteVariableLastChange

`<code=cpp>`
    int getRemoteVariableLastChange( const wxString& name, wxDateTime& lastChange );
`</code>`

Get last change date/time for a remote variable.

#####  name

Name of remote variable to get information for.

#####  lastChange

Date/time when variable last was changed.

##### Return Value

CANAL_ERROR_SUCCESS on success or an error code on failure.


## getRemoteVariableType

`<code=cpp>`
    int getRemoteVariableType( const wxString& name, wxString& strType );
`</code>`

Get type on string form for a remote variable.

#####  name

Name of remote variable to get information for.

#####  strType

Will get the variable type for the remote variable.

##### Return Value

CANAL_ERROR_SUCCESS on success or an error code on failure.

## getRemoteVariableType

`<code=cpp>`
    int getRemoteVariableType( const wxString& name, uint8_t *pType );
`</code>`

Get type on numeric form for a remote variable.

#####  name

Name of remote variable to get information for.

#####  pType

Pointer to uint8_t that will get the variable type for the remote variable.

##### Return Value

CANAL_ERROR_SUCCESS on success or an error code on failure.

## getRemoteVariablePersistence

`<code=cpp>`
    int getRemoteVariablePersistence( const wxString& name, bool *pPersistent );
`</code>`

Get persistence for a remote variable.

#####  name

Name of remote variable to get information for.

#####  pPersistent

Pointer to bool that will get the persistence for the remote variable.

##### Return Value

CANAL_ERROR_SUCCESS on success or an error code on failure.

## getRemoteVariableOwner

`<code=cpp>`
    int getRemoteVariableOwner( const wxString& name, uint32_t *pOwner );
`</code>`

Get owner for a remote variable.

#####  name

Name of remote variable to get information for.

#####  strOwner

Reference to string that will get the owner for the remote variable.

##### Return Value

CANAL_ERROR_SUCCESS on success or an error code on failure.

## getRemoteVariableAccessRights

`<code=cpp>`
    int getRemoteVariableAccessRights( const wxString& name, uint16_t *pRights );
`</code>`

Get access rights for a remote variable.

#####  name

Name of remote variable to get information for.

#####  pRights

Pointer to an uint16_t that will get the rights for the remote variable.

##### Return Value

CANAL_ERROR_SUCCESS on success or an error code on failure.

## getRemoteVariableValue

`<code=cpp>`
    int getRemoteVariableValue( const wxString& name, wxString& strValue );
`</code>`

Get value on string form for a remote variable.

#####  name

Name of remote variable to get information for.

#####  strValue

Reference to string that will get the value on string form for the remote variable.

##### Return Value

CANAL_ERROR_SUCCESS on success or an error code on failure.

## setRemoteVariableValue

`<code=cpp>`
    int setRemoteVariableValue( const wxString& name, wxString& strValue );
`</code>`

Set the value for a remote variable from a string.

#####  name

Name of remote variable to get information for.

#####  strValue

Reference to string that hold the value on string form that the remote variable will be set to.

##### Return Value

CANAL_ERROR_SUCCESS on success or an error code on failure.

## getRemoteVariableNote

`<code=cpp>`
    int getRemoteVariableNote( const wxString& name, wxString& strNote );
`</code>`

Get note for remote variable.

#####  name

Name of remote variable to get information for.

#####  strNote

Reference to string that will get the note for the remote variable.

##### Return Value

CANAL_ERROR_SUCCESS on success or an error code on failure.

## getRemoteVariableAsString

`<code=cpp>`
    int getRemoteVariableAsString( const wxString& name, wxString& strVariable );
`</code>`

Get a remote variables value on string form.

#####  name

Name of remote variable to get information for.

#####  strVariable

Reference to string that will get the value for the remote variable on string form.

##### Return Value

CANAL_ERROR_SUCCESS on success or an error code on failure.

## setRemoteVariableFromString

`<code=cpp>`
    int setRemoteVariableFromString( const wxString& name, 
                                        const wxString& strValue,
                                        const bool bPersistent = false,
                                        const uint32_t rights = 0x744 );
`</code>`

Set a remote variable value from its string form.

#####  name

Name of remote variable to get information for.

#####  strValue

Reference to string  with value to set the remote variable to on string form.

#####  bPersistent

True if the variable should be persistent.

#####  rights

Access rights for the variable.

##### Return Value

CANAL_ERROR_SUCCESS on success or an error code on failure.


## getRemoteVariableBool

`<code=cpp>`
    int getRemoteVariableBool( const wxString& name, bool *bValue);
`</code>`

Get remote variable value for boolean variable.

#####  name

Name of remote variable to get value for.

#####  bValue

Pointer to boolean value that will be set to the remote variables value.

##### Return Value

CANAL_ERROR_SUCCESS on success or an error code on failure.

## setRemoteVariableBool

`<code=cpp>`
    int setRemoteVariableBool( const wxString& name, const bool bValue);
`</code>`

Set variable value for boolean remote variable.

#####  name

Name of remote variable to set value for.

#####  bValue

Boolean value that the remote variables will be set to.

##### Return Value

CANAL_ERROR_SUCCESS on success or an error code on failure.

## getRemoteVariableInt

`<code=cpp>`
    int getRemoteVariableInt( const wxString& name, int *value);
`</code>`

Get remote variable value for integer variable.

#####  name

Name of remote variable to get value for.

#####  value

Pointer to integer value that will be set to the remote variables value.

##### Return Value

CANAL_ERROR_SUCCESS on success or an error code on failure.

## setRemoteVariableInt

`<code=cpp>`
    int setRemoteVariableInt( const wxString& name, int value);
`</code>`

Set variable value for integer remote variable.

#####  name

Name of remote variable to set value for.

#####  value

Integer value that the remote variables will be set to.

##### Return Value

CANAL_ERROR_SUCCESS on success or an error code on failure.

## getRemoteVariableLong

`<code=cpp>`
    int getRemoteVariableLong( const wxString& name, long *value);
`</code>`

Get remote variable value for long variable.

#####  name

Name of remote variable to get value for.

#####  value

Pointer to long value that will be set to the remote variables value.

##### Return Value

CANAL_ERROR_SUCCESS on success or an error code on failure.

## setRemoteVariableLong

`<code=cpp>`
    int setRemoteVariableLong( const wxString& name, long value);
`</code>`

Set variable value for long remote variable.

#####  name

Name of remote variable to set value for.

#####  value

Long value that the remote variables will be set to.

##### Return Value

CANAL_ERROR_SUCCESS on success or an error code on failure.

## getRemoteVariableDouble

`<code=cpp>`
    int getRemoteVariableDouble( const wxString& name, double *value);
`</code>`

Get remote variable value for double variable.

#####  name

Name of remote variable to get value for.

#####  value

Pointer to double value that will be set to the remote variables value.

##### Return Value

CANAL_ERROR_SUCCESS on success or an error code on failure.

## setRemoteVariableDouble

`<code=cpp>`
    int setRemoteVariableDouble( const wxString& name, double value);
`</code>`

Set variable value for double remote variable.

#####  name

Name of remote variable to set value for.

#####  value

Double value that the remote variables will be set to.

##### Return Value

CANAL_ERROR_SUCCESS on success or an error code on failure.

## getRemoteVariableMeasurement

`<code=cpp>`
    int getRemoteVariableMeasurement( const wxString& name, 
                                        double *pvalue,
                                        uint8_t *punit,
                                        uint8_t *psensoridx,
                                        uint8_t *pzone,
                                        uint8_t *psubzone );
`</code>`

Get remote variable value for measurement variable.

#####  name

Name of remote variable to set value for.

#####  pvalue

Pointer to a double that will get the value of the measurement.

#####  punit

Pointer to uint8_t that will get the unit of the measurement.

##### psensoridx

Pointer to uint8_t that will get the sensor index of the measurement.

##### pzone

Pointer to a uint8_t that will get the zone of the measurement.

#####  psubzone

Pointer to a unit8_t that will get the sub zone of the measurement.

##### Return Value

CANAL_ERROR_SUCCESS on success or an error code on failure.

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

Name of remote variable to set value for.

#####  value

Double containing the value for the measurement.

#####  unit

The unit for the measurement.

#####  sensoridx

The sensor index for the measurement.

##### zone

The zone for the measurement.

#####  subzone

The sub zone for the measurement.

##### Return Value

CANAL_ERROR_SUCCESS on success or an error code on failure.

## getRemoteVariableEvent

`<code=cpp>`
    int getRemoteVariableEvent( const wxString& name, vscpEvent *pEvent);
`</code>`

Set variable value for VSCP event remote variable.

#####  name

Name of remote variable to set value for.

#####  value

Pointer to VSCP event value that the remote variables will be set to.

##### Return Value

CANAL_ERROR_SUCCESS on success or an error code on failure.

## setRemoteVariableEvent

`<code=cpp>`
    int setRemoteVariableEvent( const wxString& name, vscpEvent *pEvent);
`</code>`

Set remote variable value for VSCP event variable.

#####  name

Name of remote variable to set value for.

#####  value

Pointer to VSCP event value that will be set to the remote variables value.

##### Return Value

CANAL_ERROR_SUCCESS on success or an error code on failure.

## getRemoteVariableEventEx

`<code=cpp>`
    int getRemoteVariableEventEx( const wxString& name, vscpEventEx *pEventEx);
`</code>`

Set variable value for VSCP event ex remote variable.

#####  name

Name of remote variable to set value for.

#####  pEventEx

Pointer to VSCP event ex value that the remote variables will be set to.

##### Return Value

CANAL_ERROR_SUCCESS on success or an error code on failure.

## setRemoteVariableEventEx

`<code=cpp>`
    int setRemoteVariableEventEx( const wxString& name, vscpEventEx *pEventEx);
`</code>`

Set remote variable value for VSCP event ex variable.

#####  name

Name of remote variable to set value for.

#####  pEventEx

Pointer to VSCP event ex value that will be set to the remote variables value.

##### Return Value

CANAL_ERROR_SUCCESS on success or an error code on failure.

## getRemoteVariableEventEx

`<code=cpp>`
    int getRemoteVariableGUID( const wxString& name, cguid& guid );
`</code>`

Get remote variable value for GUID variable.

#####  name

Name of remote variable to set value for.

#####  guid

Reference to GUID value that the remote variables will be set to.

##### Return Value

CANAL_ERROR_SUCCESS on success or an error code on failure.

## setRemoteVariableGUID

`<code=cpp>`
    int setRemoteVariableGUID( const wxString& name, cguid& guid);
`</code>`

Set remote variable value for VSCP guid variable.

#####  name

Name of remote variable to set value for.

#####  guid

Reference to guid value that will be set to the remote variables value.

##### Return Value

CANAL_ERROR_SUCCESS on success or an error code on failure.


## getRemoteVariableVSCPdata

`<code=cpp>`
    int getRemoteVariableVSCPdata( const wxString& name, 
                                        uint8_t *psizeData, 
                                        uint16_t *pData);
`</code>`

Get remote variable value from VSCP data variable.

#####  name

Name of remote variable to set value for.

##### psizeData

Pointer to unsigned char that will get the size of the data array.

#####  pData

Pointer to VSCP data array variable (unsigned char [487] ) that get the value of the remote variable.

##### Return Value

CANAL_ERROR_SUCCESS on success or an error code on failure.

## setRemoteVariableVSCPdata

`<code=cpp>`
    int setRemoteVariableVSCPdata( const wxString& name, uint8_t *pData, uint16_t size);
`</code>`

set remote variable value for VSCP data.

#####  name

Name of remote variable to set value for.

#####  sizeData

Size of VSCP data.

#####  pData

Pointer to VSCP data array to set data from.

##### Return Value

CANAL_ERROR_SUCCESS on success or an error code on failure.

## getRemoteVariableVSCPclass

`<code=cpp>`
    int getRemoteVariableVSCPclass( const wxString& name, uint16_t *vscp_class);
`</code>`

Get remote variable value from VSCP class variable.

#####  name

Name of remote variable to set value for.

##### vscp_class

Pointer to uint16_t that get the value of the VSCP class variable.

##### Return Value

CANAL_ERROR_SUCCESS on success or an error code on failure.

## setRemoteVariableVSCPclass

`<code=cpp>`
    int setRemoteVariableVSCPclass( const wxString& name, uint16_t vscp_class);
`</code>`

Set remote variable value from VSCP class.

#####  name

Name of remote variable to set value for.

#####  vscp_class

VSCP class to write to remote variable.

##### Return Value

CANAL_ERROR_SUCCESS on success or an error code on failure.



## getRemoteVariableVSCPtype

`<code=cpp>`
    int getRemoteVariableVSCPtype( const wxString& name, uint16_t *vscp_type);
`</code>`

Get remote variable value from VSCP type variable.

#####  name

Name of remote variable to set value for.

##### vscp_type

Pointer to uint16_t that get the value of the VSCP type variable.

##### Return Value

CANAL_ERROR_SUCCESS on success or an error code on failure.

## setRemoteVariableVSCPtype

`<code=cpp>`
    int setRemoteVariableVSCPtype( const wxString& name, uint16_t vscp_type);
`</code>`

Set remote variable value from VSCP type.

#####  name

Name of remote variable to set value for.

#####  vscp_type

VSCP type to write to remote variable.

##### Return Value

CANAL_ERROR_SUCCESS on success or an error code on failure.

## getRemoteVariableVSCPTimestamp

`<code=cpp>`
    int getRemoteVariableVSCPTimestamp( const wxString& name, uint32_t *vscp_timestamp);
`</code>`

Get remote variable value from VSCP timestamp variable.

#####  name

Name of remote variable to set value for.

##### vscp_timestamp

Pointer to uint32_t that get the value of the VSCP timestamp variable.

##### Return Value

CANAL_ERROR_SUCCESS on success or an error code on failure.

## setRemoteVariableVSCPTimestamp

`<code=cpp>`
    int setRemoteVariableVSCPTimestamp( const wxString& name, uint32_t vscp_timestamp);
`</code>`

Set remote variable value from VSCP timestamp.

#####  name

Name of remote variable to set value for.

#####  vscp_timestamp

VSCP timestamp to write to remote variable.

##### Return Value

CANAL_ERROR_SUCCESS on success or an error code on failure.

## getRemoteVariableDateTime

`<code=cpp>`
    int getRemoteVariableDateTime( const wxString& name, wxDateTime& datetime );
`</code>`

Get remote variable value from VSCP datetime variable.

#####  name

Name of remote variable to set value for.

##### datetime

Pointer to date wxDateTime class that get the value of the VSCP datetime variable.

##### Return Value

CANAL_ERROR_SUCCESS on success or an error code on failure.

## setRemoteVariableDateTime

`<code=cpp>`
    int setRemoteVariableDateTime( const wxString& name, wxDateTime& datetime );
`</code>`

Set remote variable value from VSCP datetime.

#####  name

Name of remote variable to set value for.

#####  datetime

VSCP datetime to write to remote variable.

##### Return Value

CANAL_ERROR_SUCCESS on success or an error code on failure.

## getRemoteVariableDate

`<code=cpp>`
    int getRemoteVariableDate( const wxString& name, wxDateTime& date );
`</code>`

Get remote variable value from VSCP date variable.

#####  name

Name of remote variable to set value for.

##### date

Pointer to date wxDateTime class that get the value of the VSCP date variable.

##### Return Value

CANAL_ERROR_SUCCESS on success or an error code on failure.

## setRemoteVariableDate

`<code=cpp>`
    int setRemoteVariableDate( const wxString& name, wxDateTime& date );
`</code>`

Set remote variable value from VSCP date.

#####  name

Name of remote variable to set value for.

#####  date

VSCP date to write to remote variable.

##### Return Value

CANAL_ERROR_SUCCESS on success or an error code on failure.

## getRemoteVariableTime

`<code=cpp>`
    int getRemoteVariableTime( const wxString& name, wxDateTime& time );
`</code>`

Get remote variable value from VSCP time variable.

#####  name

Name of remote variable to set value for.

##### time

Pointer to date wxDateTime class that get the value of the VSCP time variable.

##### Return Value

CANAL_ERROR_SUCCESS on success or an error code on failure.

## setRemoteVariableTime

`<code=cpp>`
    int setRemoteVariableTime( const wxString& name, wxDateTime& time );
`</code>`

Set remote variable value from VSCP time.

#####  name

Name of remote variable to set value for.

#####  time

VSCP time to write to remote variable.

##### Return Value

CANAL_ERROR_SUCCESS on success or an error code on failure.

## getRemoteVariableBlob

`<code=cpp>`
    int getRemoteVariableBlob( const wxString& name, wxString& blob );
`</code>`

Get remote variable value from a base64 ENCODED blob variable.

#####  name

Name of remote variable to set value for.

##### blob

Reference to blob that get the value of the BASE64 encoded blob variable.

##### Return Value

CANAL_ERROR_SUCCESS on success or an error code on failure.

## setRemoteVariableBlob

`<code=cpp>`
    int setRemoteVariableBlob( const wxString& name, wxString& blob );
`</code>`

Set remote variable from BASE64 encoded blob.

#####  name

Name of remote variable to set value for.

#####  blob

Reference to BASE64 encoded blob to write to variable.

##### Return Value

CANAL_ERROR_SUCCESS on success or an error code on failure.



## getRemoteVariableMIME

`<code=cpp>`
    int getRemoteVariableMIME( const wxString& name, wxString& mime );
`</code>`

Get remote variable value from a base64 ENCODED MIME variable.

#####  name

Name of remote variable to set value for.

##### mime

Reference MIME data that get the value of the BASE64 encoded MIME variable.

##### Return Value

CANAL_ERROR_SUCCESS on success or an error code on failure.

## setRemoteVariableMIME

`<code=cpp>`
    int setRemoteVariableMIME( const wxString& name, wxString& mime );
`</code>`

Set remote variable value from BASE64 encoded MIME data.

#####  name

Name of remote variable to set value for.

#####  mime

Reference to BASE64 encoded MIME data to write to variable.

##### Return Value

CANAL_ERROR_SUCCESS on success or an error code on failure.

## getRemoteVariableHTML

`<code=cpp>`
    int getRemoteVariableHTML( const wxString& name, wxString& html );
`</code>`

Get remote variable value from a base64 ENCODED HTML variable.

#####  name

Name of remote variable to set value for.

##### html

Reference to HTML data that get the value of the BASE64 encoded HTML variable.

##### Return Value

CANAL_ERROR_SUCCESS on success or an error code on failure.

## setRemoteVariableHTML

`<code=cpp>`
    int setRemoteVariableHTML( const wxString& name, wxString& html );
`</code>`

Set remote variable value from BASE64 encoded HTML data.

#####  name

Name of remote variable to set value for.

#####  html

Reference to BASE64 encoded HTML data to write to variable.

##### Return Value

CANAL_ERROR_SUCCESS on success or an error code on failure.


## getRemoteVariableJavaScript

`<code=cpp>`
    int getRemoteVariableJavaScript( const wxString& name, wxString& js );
`</code>`

Get remote variable value from a base64 ENCODED JavaScript variable.

#####  name

Name of remote variable to set value for.

##### js

Reference to JavaScript data that get the value of the BASE64 encoded JavaScript variable.

##### Return Value

CANAL_ERROR_SUCCESS on success or an error code on failure.

## setRemoteVariableJavaScript

`<code=cpp>`
    int setRemoteVariableJavaScript( const wxString& name, wxString& js ); 
`</code>`

Set remote variable value from BASE64 encoded JavaScript data.

#####  name

Name of remote variable to set value for.

#####  js

Reference to BASE64 encoded JavaScript data to write to variable.

##### Return Value

CANAL_ERROR_SUCCESS on success or an error code on failure.

## getRemoteVariableLUA

`<code=cpp>`
    int getRemoteVariableLUA( const wxString& name, wxString& lua );
`</code>`

Get remote variable value from a base64 ENCODED LUA variable.

#####  name

Name of remote variable to set value for.

##### lua

Reference to LUA data that get the value of the BASE64 encoded LUA variable.

##### Return Value

CANAL_ERROR_SUCCESS on success or an error code on failure.

## setRemoteVariableLUA

`<code=cpp>`
    int setRemoteVariableLUA( const wxString& name, wxString& lua ); 
`</code>`

Set remote variable value from BASE64 encoded LUA data.

#####  name

Name of remote variable to set value for.

#####  lua

Reference to BASE64 encoded LUA data to write to variable.

##### Return Value

CANAL_ERROR_SUCCESS on success or an error code on failure.


## getRemoteVariableLUARES

`<code=cpp>`
    int getRemoteVariableLUARES( const wxString& name, wxString& luares );
`</code>`

Get remote variable value from a base64 ENCODED LUARES variable.

#####  name

Name of remote variable to set value for.

##### luares

Reference to LUARES data that get the value of the BASE64 encoded LUARES variable.

##### Return Value

CANAL_ERROR_SUCCESS on success or an error code on failure.

## setRemoteVariableLUARES

`<code=cpp>`
    int setRemoteVariableLUARES( const wxString& name, wxString& luares ); 
`</code>`

Set remote variable value from BASE64 encoded LUARES data.

#####  name

Name of remote variable to set value for.

#####  luares

Reference to BASE64 encoded LUARES data to write to variable.

##### Return Value

CANAL_ERROR_SUCCESS on success or an error code on failure.

## getRemoteVariableUX1

`<code=cpp>`
    int getRemoteVariableUX1( const wxString& name, wxString& ux1 );
`</code>`

Get remote variable value from a base64 ENCODED UX1 variable.

#####  name

Name of remote variable to set value for.

##### ux1

Reference to UX1 data that get the value of the BASE64 encoded UX1 variable.

##### Return Value

CANAL_ERROR_SUCCESS on success or an error code on failure.

## setRemoteVariableUX1

`<code=cpp>`
    int setRemoteVariableUX1( const wxString& name, wxString& ux1 ); 
`</code>`

Set remote variable value from BASE64 encoded UX1 data.

#####  name

Name of remote variable to set value for.

#####  ux1

Reference to BASE64 encoded UX1 data to write to variable.

##### Return Value

CANAL_ERROR_SUCCESS on success or an error code on failure.


## getRemoteVariableDMROW

`<code=cpp>`
    int getRemoteVariableDMROQ( const wxString& name, wxString& dmrow );
`</code>`

Get remote variable value from a base64 ENCODED DM row variable.

#####  name

Name of remote variable to set value for.

##### dmrow

Reference to DM row data that get the value of the BASE64 encoded DM row variable.

##### Return Value

CANAL_ERROR_SUCCESS on success or an error code on failure.

## setRemoteVariableDMROW

`<code=cpp>`
    int setRemoteVariableDMROW( const wxString& name, wxString& dmrow ); 
`</code>`

Set remote variable value from BASE64 encoded DM row data.

#####  name

Name of remote variable to set value for.

#####  dmrow

Reference to BASE64 encoded DM row data to write to variable.

##### Return Value

CANAL_ERROR_SUCCESS on success or an error code on failure.


## getRemoteVariableDriver

`<code=cpp>`
    int getRemoteVariableDriver( const wxString& name, wxString& drv );
`</code>`

Get remote variable value from a base64 ENCODED driver variable.

#####  name

Name of remote variable to set value for.

##### drv

Reference to driver data that get the value of the BASE64 encoded driver variable.

##### Return Value

CANAL_ERROR_SUCCESS on success or an error code on failure.

## setRemoteVariableDriver

`<code=cpp>`
    int setRemoteVariableDriver( const wxString& name, wxString& drv ); 
`</code>`

Set remote variable value from BASE64 encoded driver data.

#####  name

Name of remote variable to set value for.

#####  drv

Reference to BASE64 encoded driver data to write to variable.

##### Return Value

CANAL_ERROR_SUCCESS on success or an error code on failure.


## getRemoteVariableUser

`<code=cpp>`
    int getRemoteVariableUser( const wxString& name, wxString& user );
`</code>`

Get remote variable value from a base64 ENCODED user variable.

#####  name

Name of remote variable to set value for.

##### user

Reference to user data that get the value of the BASE64 encoded user variable.

##### Return Value

CANAL_ERROR_SUCCESS on success or an error code on failure.

## setRemoteVariableUser

`<code=cpp>`
    int setRemoteVariableUser( const wxString& name, wxString& user ); 
`</code>`

Set remote variable value from BASE64 encoded user data.

#####  name

Name of remote variable to set value for.

#####  user

Reference to BASE64 encoded user data to write to variable.

##### Return Value

CANAL_ERROR_SUCCESS on success or an error code on failure.

## getRemoteVariableFilter

`<code=cpp>`
    int getRemoteVariableFilter( const wxString& name, wxString& filter );
`</code>`

Get remote variable value from a base64 ENCODED filter variable.

#####  name

Name of remote variable to set value for.

##### filter

Reference to filter data that get the value of the BASE64 encoded filter variable.

##### Return Value

CANAL_ERROR_SUCCESS on success or an error code on failure.

## setRemoteVariableFilter

`<code=cpp>`
    int setRemoteVariableFilter( const wxString& name, wxString& filter ); 
`</code>`

Set remote variable value from BASE64 encoded filter data.

#####  name

Name of remote variable to set value for.

#####  filter

Reference to BASE64 encoded filter data to write to variable.

##### Return Value

CANAL_ERROR_SUCCESS on success or an error code on failure.


# Table handling methods

## tableCreate

`<code=cpp>`
    int tableCreate( const wxString& defTable ); 
`</code>`

Create table from XML data.

#####  defTable

XML definition of table.

##### Return Value

CANAL_ERROR_SUCCESS on success or an error code on failure.

## tableDelete

`<code=cpp>`
    int tableDelete( const wxString &tblName, bool bDeleteFile=false ); 
`</code>`

Delete named table.

#####  tblName

Name of an existing table.

#####  bDeleteFile

If true the database **file** also should be deleted. If not it will be reused if a table with the same name is created later.

##### Return Value

CANAL_ERROR_SUCCESS on success or an error code on failure.

## tableList

`<code=cpp>`
    int tableList( wxArrayString &tablesArray );
`</code>`

Get a list of all defined tables.

#####  tablesArray

List that will get filled with table names.

##### Return Value

CANAL_ERROR_SUCCESS on success or an error code on failure.

## tableListInfo

`<code=cpp>`
    int tableListInfo( const wxString &tblName, wxString &tableInfo, bool bXML = true ); 
`</code>`

Delete named table.

#####  tblName

Name of an existing table.

#####  tableInfo

Parameter that will get the information about the table.

##### bXML

If true info will be returnd as BASE64 encoded XML data.

##### Return Value

CANAL_ERROR_SUCCESS on success or an error code on failure.

## tableGet

`<code=cpp>`
    int tableGet( const wxString& tblName, 
                                const wxDateTime& from, 
                                const wxDateTime& to,
                                wxArrayString& resultArray,
                                bool bFull = false  ); 
`</code>`

Get data from a named table in a range to-from. One can fetch all columns of the table (bFull) or just datetime and value (default).

#####  tblName

Name of an existing table.

#####  from

Datetime from which data should be fetched. Should be given on ISO 8601 format YY-MM-DDTHH:MM:SS. 

#####  to

Datetime up to which data is fetched. Should be given on ISO 8601 format YY-MM-DDTHH:MM:SS. 

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

If true all fields of a table row is returned (//other fields// above) in a comma separated list. Note that datetime is always listed first followed by value regardless of how the columns of the table is arranged.

##### Return Value

CANAL_ERROR_SUCCESS on success or an error code on failure.

## tableGetRaw

`<code=cpp>`
    int tableGetRaw( const wxString& tblName, 
                                const wxDateTime& from, 
                                const wxDateTime& to,
                                wxArrayString& resultArray ); 
`</code>`

Get data from a named table in a range to-from. All columns of the table is always returned.

#####  tblName

Name of an existing table.

#####  from

Datetime from which data should be fetched. Should be given on ISO 8601 format YY-MM-DDTHH:MM:SS. 

#####  to

Datetime up to which data is fetched. Should be given on ISO 8601 format YY-MM-DDTHH:MM:SS. 

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

CANAL_ERROR_SUCCESS on success or an error code on failure.


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

Pointer to date/time value. Can be NULL and in which case the current date/time is used. 

##### Return Value

CANAL_ERROR_SUCCESS on success or an error code on failure.

## tableLogSQL

`<code=cpp>`
    int tableLogSQL( const wxString& tblName, 
                        const wxString& sql ); 
`</code>`

Log data to with a SQL expression. 

#####  tblName

Name of an existing table.

#####  sql

SQL expression used to log data. 

##### Return Value

CANAL_ERROR_SUCCESS on success or an error code on failure.

## tableGetNumRecords

`<code=cpp>`
    int tableGetNumRecords( const wxString& tblName, 
                                const wxDateTime& from, 
                                const wxDateTime& to,
                                size_t *pRecords ); 
`</code>`

Get number of records for an interval in a named table.

#####  tblName

Name of an existing table.

#####  from

Date/time from which resulting data should be fetched. Set to "0000-01-01T00:00:00" for *beginning of time*.

##### to

Date/time to which resulting data should be fetched. Set to "9999-12-31T23:59:59" for *end of time*.

#####  pRecords

size_t that will get number of records in the interval on success. 

##### Return Value

CANAL_ERROR_SUCCESS on success or an error code on failure.

## tableGetFirstDate

`<code=cpp>`
    int tableGetFirstDate( const wxString& tblName, 
                                const wxDateTime& from, 
                                const wxDateTime& to,
                                wxDateTime& first ); 
`</code>`

Get the first data/time for an interval in a named table.

#####  tblName

Name of an existing table.

#####  from

Date/time from which resulting data should be fetched. Set to "0000-01-01T00:00:00" for *beginning of time*.

##### to

Date/time to which resulting data should be fetched. Set to "9999-12-31T23:59:59" for *end of time*.

#####  first

Will get the first date/time in the interval on success. 

##### Return Value

CANAL_ERROR_SUCCESS on success or an error code on failure.

## tableGetLastDate

`<code=cpp>`
    int tableGetLastDate( const wxString& tblName, 
                                const wxDateTime& from, 
                                const wxDateTime& to,
                                wxDateTime& last ); 
`</code>`

Get the last data/time for an interval in a named table.

#####  tblName

Name of an existing table.

#####  from

Date/time from which resulting data should be fetched. Set to "0000-01-01T00:00:00" for *beginning of time*.

##### to

Date/time to which resulting data should be fetched. Set to "9999-12-31T23:59:59" for *end of time*.

#####  last

Will get the last date/time in the interval on success. 

##### Return Value

CANAL_ERROR_SUCCESS on success or an error code on failure.

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

Date/time from which resulting data should be fetched. Set to "0000-01-01T00:00:00" for *beginning of time*.

##### to

Date/time to which resulting data should be fetched. Set to "9999-12-31T23:59:59" for *end of time*.

#####  pSum

Pointer to a double that will get the sum of all values in the interval on success. 

##### Return Value

CANAL_ERROR_SUCCESS on success or an error code on failure.

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

Date/time from which resulting data should be fetched. Set to "0000-01-01T00:00:00" for *beginning of time*.

##### to

Date/time to which resulting data should be fetched. Set to "9999-12-31T23:59:59" for *end of time*.

#####  pMin

Pointer to a double that will get the minimum of all values in the interval on success. 

##### Return Value

CANAL_ERROR_SUCCESS on success or an error code on failure.

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

Date/time from which resulting data should be fetched. Set to "0000-01-01T00:00:00" for *beginning of time*.

##### to

Date/time to which resulting data should be fetched. Set to "9999-12-31T23:59:59" for *end of time*.

#####  pMax

Pointer to a double that will get the maximum of all values in the interval on success. 

##### Return Value

CANAL_ERROR_SUCCESS on success or an error code on failure.


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

Date/time from which resulting data should be fetched. Set to "0000-01-01T00:00:00" for *beginning of time*.

##### to

Date/time to which resulting data should be fetched. Set to "9999-12-31T23:59:59" for *end of time*.

#####  pAverage

Pointer to a double that will get the average of all values in the interval on success. 

##### Return Value

CANAL_ERROR_SUCCESS on success or an error code on failure.

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

Date/time from which resulting data should be fetched. Set to "0000-01-01T00:00:00" for *beginning of time*.

##### to

Date/time to which resulting data should be fetched. Set to "9999-12-31T23:59:59" for *end of time*.

#####  pMedian

Pointer to a double that will get the median of all values in the interval on success. 

##### Return Value

CANAL_ERROR_SUCCESS on success or an error code on failure.

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

Date/time from which resulting data should be fetched. Set to "0000-01-01T00:00:00" for *beginning of time*.

##### to

Date/time to which resulting data should be fetched. Set to "9999-12-31T23:59:59" for *end of time*.

#####  pStdDev

Pointer to a double that will get the standard deviation of all values in the interval on success. 

##### Return Value

CANAL_ERROR_SUCCESS on success or an error code on failure.

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

Date/time from which resulting data should be fetched. Set to "0000-01-01T00:00:00" for *beginning of time*.

##### to

Date/time to which resulting data should be fetched. Set to "9999-12-31T23:59:59" for *end of time*.

#####  pVariance

Pointer to a double that will get the variance of all values in the interval on success. 

##### Return Value

CANAL_ERROR_SUCCESS on success or an error code on failure.

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

Date/time from which resulting data should be fetched. Set to "0000-01-01T00:00:00" for *beginning of time*.

##### to

Date/time to which resulting data should be fetched. Set to "9999-12-31T23:59:59" for *end of time*.

#####  pMode

Pointer to a double that will get the mode of all values in the interval on success. 

##### Return Value

CANAL_ERROR_SUCCESS on success or an error code on failure.

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

Date/time from which resulting data should be fetched. Set to "0000-01-01T00:00:00" for *beginning of time*.

##### to

Date/time to which resulting data should be fetched. Set to "9999-12-31T23:59:59" for *end of time*.

#####  pLowerQ

Pointer to a double that will get the lower quartile of all values in the interval on success. 

##### Return Value

CANAL_ERROR_SUCCESS on success or an error code on failure.

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

Date/time from which resulting data should be fetched. Set to "0000-01-01T00:00:00" for *beginning of time*.

##### to

Date/time to which resulting data should be fetched. Set to "9999-12-31T23:59:59" for *end of time*.

#####  pUpperQ

Pointer to a double that will get the upper quartile of all values in the interval on success. 

##### Return Value

CANAL_ERROR_SUCCESS on success or an error code on failure.

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

Date/time from which resulting data should be fetched. Set to "0000-01-01T00:00:00" for *beginning of time*.

##### to

Date/time to which resulting data should be fetched. Set to "9999-12-31T23:59:59" for *end of time*.

##### Return Value

CANAL_ERROR_SUCCESS on success or an error code on failure.


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

Pointer to eight bit value that will get read value from register.

##### ifGUID

GUID for interface this events should be sent on. This is used to read registers of Level I devices.
                
##### pdestGUID

GUID for remote node.

##### bLevel2

If true this is a true Level II read operation.

##### Return Value

CANAL_ERROR_SUCCESS on success or an error code on failure.


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

Pointer to array that will get read value(s) from register(s).

##### ifGUID

GUID for interface this events should be sent on. This is used to read registers of Level I devices.
                
##### pdestGUID

GUID for remote node.

##### bLevel2

If true this is a true Level II read operation.

##### Return Value

CANAL_ERROR_SUCCESS on success or an error code on failure.


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

Pointer to byte that should be written into the register. At exit this byte contains the written value returned from the node where it got written.

##### ifGUID

GUID for interface this events should be sent on. This is used to read registers of Level I devices.
                
##### pdestGUID

GUID for remote node.

##### bLevel2

If true this is a true Level II read operation.

##### Return Value

CANAL_ERROR_SUCCESS on success or an error code on failure.


## getMDFUrlFromLevel2Device

`<code=cpp>`
    bool getMDFUrlFromLevel2Device( cguid& ifGUID,
                                        cguid& destGUID,
                                        wxString &strurl,
                                        bool bLevel2 = false );
`</code>`

Get MDf file from device registers.

##### ifGUID

GUID for interface this events should be sent on. This is used to read registers of Level I devices.
                
##### pdestGUID

GUID for remote node.

##### strURL

Reference to string that will get the MDF url of the device if call is successful..

##### bLevel2

If true this is a true Level II read operation.

##### Return Value

CANAL_ERROR_SUCCESS on success or an error code on failure.

## fetchIterfaceGUID

`<code=cpp>`
    int fetchIterfaceGUID( const wxString& ifName, cguid& guid );
`</code>`

Fetch guid for a tcp/ip interface from it's name.

##### ifName

Real text name of the VSCP server interface.
                
##### guid

GUID for the interface if the named interface exist.

##### Return Value

CANAL_ERROR_SUCCESS on success or an error code on failure.


