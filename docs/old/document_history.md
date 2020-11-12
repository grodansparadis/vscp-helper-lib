# Document History

*  2017-05-08 AKHE vscphlp_writeVscpDataWithSizeToString added

*  2017-05-08 AKHE vscphlp_setRemoteVariableValue - synonym for vscphlp_setRemoteVariableString vscphlp_getRemoteVariableValue - synonym for vscphlp_getRemoteVariableString added

*  2017-05-08 AKHE All methods with buffer size now have the size in unit **size_t** Methods that did not have a size have it added. 

	
	vscphlp_writeVscpDataToString*
	vscphlp_getVendorString*
	vscphlp_getDriverInfo*
	vscphlp_getRemoteVariableString* 
	vscphlp_getRemoteVariableGUIDString* Added len
	vscphlp_getRemoteVariableDateTime*
	vscphlp_getRemoteVariableDate*
	vscphlp_getRemoteVariableTime*
	vscphlp_getRemoteVariableBlob*
	vscphlp_getRemoteVariableMIME*
	vscphlp_getRemoteVariableHTML*
	vscphlp_getRemoteVariableJavaScript*
	vscphlp_getRemoteVariableLUA*
	vscphlp_getRemoteVariableLUARES*
	vscphlp_getRemoteVariableUX1*
	vscphlp_getRemoteVariableDMROW*
	vscphlp_getRemoteVariableDriver*
	vscphlp_getRemoteVariableUser*
	vscphlp_getRemoteVariableFilter*
	vscphlp_writeGuidToString* + len
	vscphlp_writeGuidToStringEx* + len
	vscphlp_writeGuidToString4Rows*
	vscphlp_writeGuidToString4RowsEx*
	vscphlp_writeGuidArrayToString*
	vscphlp_writeVscpEventToString*
	vscphlp_writeVscpEventExToString*
	vscphlp_getDataCodingString*
	vscphlp_getVSCPMeasurementAsString*
	vscphlp_getVSCPMeasurementFloat64AsString*
	vscphlp_convertEventToJSON*
	vscphlp_convertEventExToJSON*
	vscphlp_convertEventToXML*
	vscphlp_convertEventExToXML*
	vscphlp_convertEventToHTML*
	vscphlp_convertEventExToHTML*



*  2017-04-18 AKHE Added **vscphlp_getTimeString**, **vscphlp_getISOTimeString**, **vscphlp_getDateStringFromEvent**, and **vscphlp_getDateStringFromEventEx** 

*  2017-04-18 AKHE Changed names for **vscphlp_setEventDateTimeBlock** and **vscphlp_setEventDateTimeBlockEx** to **vscphlp_setEventDateTimeBlockToNow** and **vscphlp_setEventExDateTimeBlockToNow**.

*  2017-04-13 AKHE Added **vscphlp_setEventDateTimeBlock** and **vscphlp_setEventDateTimeBlockEx** to set new date/time blocks in events.

*  2017-03-10 AKHE Added missing getters/setter for variables **vscphlp_getRemoteVariableVSCPTimestamp, vscphlp_setRemoteVariableVSCPTimestamp, vscphlp_getRemoteVariableDateTime, vscphlp_setRemoteVariableDateTime, vscphlp_getRemoteVariableDate,vscphlp_setRemoteVariableDate, vscphlp_getRemoteVariableTime, vscphlp_setRemoteVariableTime,vscphlp_getRemoteVariableBlob, vscphlp_setRemoteVariableBlob, vscphlp_getRemoteVariableMIME, vscphlp_setRemoteVariableMIME, vscphlp_getRemoteVariableHTML, vscphlp_setRemoteVariableHTML, vscphlp_getRemoteVariableJavaScript, vscphlp_setRemoteVariableJavaScript, vscphlp_getRemoteVariableLUA, vscphlp_setRemoteVariableLUA, vscphlp_getRemoteVariableLUARES, vscphlp_setRemoteVariableLUARES, vscphlp_getRemoteVariableUX1, vscphlp_setRemoteVariableUX1, vscphlp_getRemoteVariableDMROW, vscphlp_setRemoteVariableDMROW
vscphlp_getRemoteVariableDriver, vscphlp_setRemoteVariableDriver, vscphlp_getRemoteVariableUser
vscphlp_setRemoteVariableUser, vscphlp_getRemoteVariableFilter, vscphlp_setRemoteVariableFilter**

*  2017-03-08 AKHE Added **vscphlp_newVSCPevent**

*  2017-03-08 AKHE Added **vscphlp_deleteVSCPevent_v2**

*  2017-03-08 AKHE From version 2 names has been changed to **vscphlp_xxxxRemoteVariable** instead of **vscphlp_xxxxVariable**

*  2017-03-07 AKHE **vscphlp_setVariableMeasurement** / **vscphlp_getVariableMeasurement** had wrong parameters.

*  2017-01-31 AKHE Added vscphlp_makeLevel2FloatMeasurementEvent and vscphlp_makeLevel2StringMeasurementEvent

*  2017-01-30 AKHE Added vscphlp_convertLevel1MeasuremenToLevel2Double and vscphlp_convertLevel1MeasuremenToLevel2String

*  2017-01-28 AKHE vscphlp_copyVSCPFilter added.

*  2017-01-23 AKHE - Added vscphlp_convertEventToJSON, vscphlp_convertEventExToJSON, vscphlp_convertEventToXML, vscphlp_convertEventExToXML, vscphlp_convertEventToHTML, vscphlp_convertEventExToHTML

*  2017-01-12 AKHE - Added vscphlp_getMeasurementSensorIndex, vscphlp_getMeasurementZone and vscphlp_getMeasurementSubZone

*  2017-01-10 AKHE - Added vscphlp_getMeasurementUnit and vscphlp_isMeasurement

*  2016-10-27 AKHE - Added info about filter string read/write methods. 

*  2015-09-24 AKHE - vscphlp_setResponseTimeout has timeout value changed to millseconds instead of seconds.

*  2015-09-19 AKHE - Added vscphlp_setAfterCommandSleep. Bumped version to 4

*  2015-09-09 AKHE - The string parameter for [vscphlp_readFilterFromString] and [[https://www.vscp.org/docs/vscphelper/doku.php?id=helper_lib_api_helpers#vscphlp_readmaskfromstring](https://www.vscp.org/docs/vscphelper/doku.php?id=helper_lib_api_helpers#vscphlp_readfilterfromstring) can now be empty or just have some of the arguments defined. 


