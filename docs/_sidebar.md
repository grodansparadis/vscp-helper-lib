* Overview
 * [The VSCP helper library](README.md)
 * [Language Bindings](bindings.md)

* Using the library
 * [Using the library](using.md)
 * [Return values and erro handling](error_handling.md)
 * [Using with c](c_using.md)
 * [Using with Python](python_using.md)

* Methods in library

  * Initialization and configuration

   * [vscphlp_newSession](vscphlp_newsession.md)
   * [vscphlp_closeSession](vscphlp_closesession.md)
   * [vscphlp_setResponseTimeout](vscphlp_setresponsetimeout.md)
   * [vscphlp_setAfterCommandSleep](vscphlp_setaftercommandsleep.md)

  * Communication link methods

   * [vscphlp_isConnected](vscphlp_isconnected.md)
   * [vscphlp_doCommand](vscphlp_docommand.md)
   * [vscphlp_checkReply](vscphlp_checkreply.md)
   * [vscphlp_clearLocalInputQueue](vscphlp_clearlocalinputqueue.md)
   * [vscphlp_open](vscphlp_open.md)
   * [vscphlp_openInterface](vscphlp_openinterface.md)
   * [vscphlp_close](vscphlp_close.md)
   * [vscphlp_noop](vscphlp_noop.md)
   * [vscphlp_clearDaemonEventQueue](vscphlp_cleardaemoneventqueue.md)
   * [vscphlp_sendEvent](vscphlp_sendevent.md)
   * [vscphlp_sendEventEx](vscphlp_sendeventex.md)
   * [vscphlp_isDataAvailable](vscphlp_isdataavailable.md)
   * [vscphlp_enterReceiveLoop](vscphlp_enterreceiveloop.md)
   * [vscphlp_quitReceiveLoop](vscphlp_quitreceiveloop.md)
   * [vscphlp_blockingReceiveEvent](vscphlp_blockingreceiveevent.md)
   * [vscphlp_blockingReceiveEventEx](vscphlp_blockingreceiveeventex.md)
   * [vscphlp_setFilter](vscphlp_setfilter.md)
   * [vscphlp_getStatistics](vscphlp_getstatistics.md)
   * [vscphlp_getStatus](vscphlp_getstatus.md)
   * [vscphlp_getVersion](vscphlp_getversion.md)
   * [vscphlp_getDLLVersion](vscphlp_getdllversion.md)
   * [vscphlp_getVendorString](vscphlp_getvendorstring.md)
   * [vscphlp_getDriverInfo](vscphlp_getdriverinfo.md)
   * [vscphlp_doCmdShutDown](vscphlp_docmdshutdown.md)

  * GUID handling

   * [vscphlp_getGuidFromString](vscphlp_getguidfromstring.md)
   * [vscphlp_getGuidFromStringEx](vscphlp_getguidfromstringex.md)
   * [vscphlp_getGuidFromStringToArray](vscphlp_getguidfromstringtoarray.md)
   * [vscphlp_writeGuidToString](vscphlp_writeguidtostring.md)
   * [vscphlp_writeGuidToStringEx](vscphlp_writeguidtostringex.md)
   * [vscphlp_writeGuidToString4Rows](vscphlp_writeguidtostring4rows.md)
   * [vscphlp_writeGuidToString4RowsEx](vscphlp_writeguidtostring4rowsex.md)
   * [vscphlp_writeGuidArrayToString](vscphlp_writeguidarraytostring.md)
   * [vscphlp_isGUIDEmpty](vscphlp_isguidempty.md)
   * [vscphlp_isSameGUID](vscphlp_issameguid.md)
   * [vscphlp_reverseGUID](vscphlp_reverseguid.md)
   * [vscphlp_calcCRC4GUIDArray](vscphlp_calccrc4guidarray.md)
   * [vscphlp_calcCRC4GUIDString](vscphlp_calccrc4guidstring.md)

  * Filter handling

   * [vscphlp_clearVSCPFilter](vscphlp_clearvscpfilter.md)
   * [vscphlp_copyVSCPFilter](vscphlp_copyvscpFilter.md)
   * [vscphlp_readFilterFromString](vscphlp_readfilterfromstring.md)
   * [vscphlp_writeFilterToString](vscphlp_writefiltertostring.md)
   * [vscphlp_readMaskFromString](vscphlp_readmaskfromstring.md)
   * [vscphlp_writeMaskToString](vscphlp_writemasktostring.md)
   * [vscphlp_doLevel2Filter](vscphlp_doLevel2filter.md)

  * Event helpers and conversions

   * [vscphlp_copyVSCPEvent](vscphlp_copyvscpevent.md)
   * [vscphlp_getVscpPriority](vscphlp_getvscppriority.md)
   * [vscphlp_getVscpPriorityEx](vscphlp_getvscppriorityex.md)
   * [vscphlp_setVscpPriority](vscphlp_setvscppriority.md)
   * [vscphlp_setVscpPriorityEx](vscphlp_setvscppriorityex.md)
   * [vscphlp_convertVSCPtoEx](vscphlp_convertvscptoex.md)
   * [vscphlp_convertVSCPfromEx](vscphlp_convertvscpfromex.md)
   * [vscphlp_newVSCPevent](vscphlp_newvscpevent.md)
   * [vscphlp_deleteVSCPevent](vscphlp_deletevscpevent.md)
   * [vscphlp_deleteVSCPevent_v2](vscphlp_deletescpevent_v2.md)
   * <small>**VSCP data**</small>
    * [vscphlp_writeVscpDataToString](vscphlp_writevscpdatatostring.md)
    * [vscphlp_writeVscpDataWithSizeToString](vscphlp_writevscpdatawithsizetostring.md)
    * [vscphlp_setVscpDataFromString](vscphlp_setvscpdatafromstring)
   * <small>**CANAL conversions**</small>
     * [vscphlp_convertCanalToEvent](vscphlp_convertcanaltoevent.md)
     * [vscphlp_convertCanalToEventEx](vscphlp_convertcanaltoeventex.md)
     * [vscphlp_convertEventToCanal](vscphlp_converteventtocanal.md)
     * [vscphlp_convertEventExToCanal](vscphlp_converteventextocanal.md)
   * <small>**Date/Time**</small> 
     * [vscphlp_setEventDateTimeBlockToNow](vscphlp_seteventdatetimeblocktonow.md)
     * [vscphlp_setEventExDateTimeBlockToNow](vscphlp_seteventexdatetimeblocktonow.md)
   * <small>**String**</small>
     * [vscphlp_writeVscpEventToString](vscphlp_writevscpeventtostring.md)
     * [vscphlp_writeVscpEventExToString](vscphlp_writevscpeventextostring.md)
     * [vscphlp_setVscpEventFromString](vscphlp_setvscpeventfromstring.md)
     * [vscphlp_setVscpEventExFromString](vscphlp_setvscpeventexfromstring.md)
     * [vscphlp_getDateStringFromEvent](vscphlp_getdatestringfromevent.md)
     * [vscphlp_getDateStringFromEventEx](vscphlp_getdatestringfromeventex.md) 
     * [vscphlp_convertStringToEvent](vscphlp_convertStringToEvent.md)
     * [vscphlp_convertStringToEventEx](vscphlp_convertStringToEventEx.md)
   * <small>**JSON**</small> 
     * [vscphlp_convertEventToJSON](vscphlp_converteventtojson.md)
     * [vscphlp_convertEventExToJSON](vscphlp_converteventextojson.md)
   * <small>**XML**</small>
     * [vscphlp_convertEventToXML](vscphlp_converteventtoxml.md)
     * [vscphlp_convertEventExToXML](vscphlp_converteventextoxml.md)
   * <small>**HTML**</small>
     * [vscphlp_convertEventToHTML](vscphlp_converteventtohtml.md)
     * [vscphlp_convertEventExToHTML](vscphlp_converteventextohtml.md)

  * CANAL helpers and conversions

   * [vscphlp_getVSCPheadFromCANALid](vscphlp_getvscpheadfromcanalid.md)
   * [vscphlp_getVSCPclassFromCANALid](vscphlp_getvscpclassfromcanalid.md)
   * [vscphlp_getVSCPtypeFromCANALid](vscphlp_getvscptypefromcanalid.md)
   * [vscphlp_getVSCPnicknameFromCANALid](vscphlp_getvscpnicknamefromcanalid.md)
   * [vscphlp_getCANALidFromVSCPdata](vscphlp_getcanalidfromvscpdata.md)
   * [vscphlp_getCANALidFromVSCPevent](vscphlp_getcanalidfromvscpevent.md)
   * [vscphlp_getCANALidFromVSCPeventEx](vscphlp_getcanalidfromvscpeventex.md)
   * [vscphlp_calc_crc_Event](vscphlp_calc_crc_event.md)
   * [vscphlp_calc_crc_EventEx](vscphlp_calc_crc_eventex.md)
   * <small>**Event conversions**</small>
     * [vscphlp_convertCanalToEvent](vscphlp_convertcanaltoevent.md)
     * [vscphlp_convertCanalToEventEx](vscphlp_convertcanaltoeventex.md)
     * [vscphlp_convertEventToCanal](vscphlp_converteventtocanal.md)
     * [vscphlp_convertEventExToCanal](vscphlp_converteventextocanal.md)

  * Measurements

   * [vscphlp_getMeasurementDataCoding](vscphlp_getmeasurementdatacoding.md)
   * [vscphlp_getDataCodingBitArray](vscphlp_getdatacodingbitarray.md)
   * [vscphlp_getDataCodingInteger](vscphlp_getdatacodinginteger.md)
   * [vscphlp_getDataCodingNormalizedInteger](vscphlp_getdatacodingnormalizedinteger.md)
   * [vscphlp_getDataCodingString](vscphlp_getdatacodingstring.md)
   * [vscphlp_getVSCPMeasurementAsString](vscphlp_getvscpmeasurementasstring.md)
   * [vscphlp_getVSCPMeasurementAsDouble](vscphlp_getvscpmeasurementasdouble.md)
   * [vscphlp_getVSCPMeasurementFloat64AsString](vscphlp_getvscpmeasurementfloat64asstring.md)
   * [vscphlp_convertFloatToNormalizedEventData](vscphlp_convertfloattonormalizedeventdata.md)
   * [vscphlp_convertFloatToFloatEventData](vscphlp_convertfloattofloateventdata.md)
   * [vscphlp_convertIntegerToNormalizedEventData](vscphlp_convertintegertonormalizedeventdata.md)
   * [vscphlp_makeFloatMeasurementEvent](vscphlp_makefloatmeasurementevent.md)
   * [vscphlp_getMeasurementAsFloat](vscphlp_getmeasurementasfloat.md)
   * [vscphlp_getMeasurementUnit](vscphlp_getmeasurementunit.md)
   * [vscphlp_getMeasurementSensorIndex](vscphlp_getmeasurementsensorindex.md)
   * [vscphlp_getMeasurementZone](vscphlp_getmeasurementzone.md)
   * [vscphlp_getMeasurementSubZone](vscphlp_getmeasurementSubzone.md)
   * [vscphlp_isMeasurement](vscphlp_ismeasurement.md)
   * [vscphlp_convertLevel1MeasuremenToLevel2Double](vscphlp_convertlevel1measurementolevel2double.md)
   * [vscphlp_convertLevel1MeasuremenToLevel2String](vscphlp_convertlevel1measurementolevel2string.md)
   * [vscphlp_makeLevel2FloatMeasurementEvent](vscphlp_makelevel2floatmeasurementevent.md)
   * [vscphlp_makeLevel2StringMeasurementEvent](vscphlp_makelevel2stringmeasurementevent.md)

  * General helpers

   * [vscphlp_readStringValue](vscphlp_readstringvalue.md)
   * [vscphlp_replaceBackslash](vscphlp_replacebackslash.md)
   * [vscphlp_getTimeString](vscphlp_gettimestring.md)
   * [vscphlp_getISOTimeString](vscphlp_getisotimestring.md)
   * [vscphlp_convertCanalToEvent](vscphlp_convertcanaltoevent.md)
   * [vscphlp_convertCanalToEventEx](vscphlp_convertcanaltoeventex.md)
   * [vscphlp_convertEventToCanal](vscphlp_converteventtocanal.md)
   * [vscphlp_convertEventExToCanal](vscphlp_converteventextocanal.md)
   * [vscphlp_makeTimeStamp](vscphlp_maketimestamp.md)

  * Encryption and Password handling
  
   * [vscphlp_getEncryptionTokenFromCode](vscphlp_getEncryptionTokenFromCode.md)
   * [vscphlp_getEncryptionFrameSizeFromEvent](vscphlp_getEncryptionFrameSizeFromEvent.md)
   * [vscphlp_getEncryptionFrameSizeFromEventEx](vscphlp_getEncryptionFrameSizeFromEventEx.md)
   * [vscphlp_writeEventToEncryptionFrame](vscphlp_writeEventToEncryptionFrame.md)
   * [vscphlp_writeEventExToEncryptionFrame](vscphlp_writeEventExToEncryptionFrame.md)
   * [vscphlp_getEventFromEncryptionFrame](vscphlp_getEventFromEncryptionFrame.md)
   * [vscphlp_getEventExFromEncryptionFrame](vscphlp_getEventExFromEncryptionFrame.md)
   * [vscphlp_encryptFrame](vscphlp_encryptFrame.md)
   * [vscphlp_decryptFrame](vscphlp_decryptFrame.md)
   * [vscphlp_md5](vscphlphlp_md5.md)
   * [vscphlp_byteArray2HexStr](vscphlp_byteArray2HexStr.md)
   * [vscphlp_hexStr2ByteArray](vscphlp_hexStr2ByteArray.md)
   * [vscphlp_getHashPasswordComponents](vscphlp_getHashPasswordComponents.md)
   * [vscphlp_makePasswordHash](vscphlp_makePasswordHash.md)
   * [vscphlp_isPasswordValid](vscphlp_isPasswordValid.md)
   * [vscphlp_getSalt](vscphlp_getSalt.md)
   * [vscphlp_getSaltHex](vscphlp_getSaltHex.md)



---

* Using C++ classes directly
 * [Introduction to direct use of VSCP classes](classes_intro.md)
 * [First project](classes_first_project.md)
 * [Methods in the VscpRemoteTcpIf class](classes_methods.md)

 * Available methods

   * General Methods

     * [setResponseTimeout](class_setResponseTimeout.md)
     * [setAfterCommandSleep](class_setAfterCommandSleep.md)
     * [setRegisterOperationTiming](class_setRegisterOperationTiming.md)
     * [isConnected](class_isConnected.md)
     * [checkReturnValue](class_checkReturnValue.md)
     * [doClrInputQueue](class_doClrInputQueue.md)
     * [doCommand](class_doCommand.md)
     * [doCmdOpen](class_doCmdOpen.md)
     * [doCmdOpen](class_doCmdOpen2.md)
     * [doCmdClose](class_doCmdClose.md)
     * [doCmdNOOP](class_doCmdNOOP.md)
     * [doCmdClear](class_doCmdClear.md)
     * [doCmdGetLevel](class_doCmdGetLevel.md)
     * [doCmdSend](class_doCmdSend.md)
     * [doCmdSendEx](class_doCmdSendEx.md)
     * [doCmdSendLevel1](class_doCmdSendLevel1.md)
     * [doCmdReceive](class_doCmdReceive.md)
     * [doCmdReceiveEx](class_doCmdReceiveEx.md)
     * [doCmdReceiveLevel1](class_doCmdReceiveLevel1.md)
     * [doCmdEnterReceiveLoop](class_doCmdEnterReceiveLoop.md)
     * [doCmdQuitReceiveLoop](class_doCmdQuitReceiveLoop.md)
     * [doCmdBlockingReceive](class_doCmdBlockingReceive,.md)
     * [doCmdBlockingReceive](class_doCmdBlockingReceive2.md)
     * [doCmdDataAvailable](class_doCmdDataAvailable.md)
     * [doCmdStatus](class_doCmdStatus.md)
     * [doCmdStatus](class_doCmdStatus2.md)
     * [doCmdStatistics](class_doCmdStatistics.md)
     * [doCmdStatistics](class_doCmdStatistics2.md)
     * [doCmdFilter](class_doCmdFilter.md)
     * [doCmdFilter](class_doCmdFilter2.md)
     * [doCmdVersion](class_doCmdVersion.md)
     * [doCmdDLLVersion](class_doCmdDLLVersion.md)
     * [doCmdVendorString](class_doCmdVendorString.md)
     * [doCmdGetDriverInfo](class_doCmdGetDriverInfo.md)
     * [doCmdGetGUID](class_doCmdGetGUID.md)
     * [doCmdGetGUID](class_doCmdGetGUID2.md)
     * [doCmdSetGUID](class_doCmdSetGUID.md)
     * [doCmdSetGUID](class_doCmdSetGUID2.md)
     * [doCmdGetChannelInfo](class_doCmdGetChannelInfo.md)
     * [doCmdGetChannelID](class_doCmdGetChannelID.md)
     * [doCmdInterfaceList](class.doCmdInterfaceList.md)
     * [doCmdSetBaudrate](class_doCmdSetBaudrate.md)
     * [doCmdFilter](class_doCmdFilter_canal.md)
     * [doCmdMask](class_doCmdMask_canal.md)
     * [doCmdShutDown](class_doCmdShutDown.md)

   * Register handling
     * [readLevel2Register](class_readLevel2Register.md)
     * [readLevel2Registers](class_readLevel2Registers.md)
     * [writeLevel2Register](class_writeLevel2Register.md)
     * [getMDFUrlFromLevel2Device](class_getMDFUrlFromLevel2Device.md)
     * [fetchIterfaceGUID](class_fetchIterfaceGUID.md)

* The CANAL library
    * [libcanal](canal_libcanal.md)
    * [Using the library](canal_using.md)

* Other documentation
  * [VSCP documentation portal](https://docs.vscp.org)





