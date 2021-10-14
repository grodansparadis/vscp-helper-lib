///////////////////////////////////////////////////////////////////////////////
// vscphelperlib.h
//
// This file is part of the VSCP (http://www.vscp.org)
//
// The MIT License (MIT)
//
// Copyright © 2000-2021 Ake Hedman, The VSCP Project, 
// <akhe@vscp.org>
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#ifndef WIN32
#define __LINUX__
#define HELPERLIB_API
#else
#ifdef HELPERLIB_EXPORTS
#define HELPERLIB_API __declspec(dllexport)
#else
#define HELPERLIB_API __declspec(dllimport)
#endif
#endif

#include <time.h>
#include <vscp.h>

#ifdef __cplusplus
extern "C" {
#endif


HELPERLIB_API long 
vscphlp_newSession(void);
HELPERLIB_API void 
vscphlp_closeSession(long handle);
HELPERLIB_API int 
vscphlp_setResponseTimeout(long handle, unsigned long timeout );
HELPERLIB_API int 
vscphlp_setAfterCommandSleep(long handle, unsigned short sleeptime );
HELPERLIB_API int 
vscphlp_isConnected(const long handle);
HELPERLIB_API int 
vscphlp_doCommand( long handle, const char * cmd );
HELPERLIB_API int 
vscphlp_checkReply( long handle, int bClear );
HELPERLIB_API int 
vscphlp_clearLocalInputQueue( long handle );
HELPERLIB_API int 
vscphlp_openInterface( long handle, const char *pInterface, unsigned long flags );
HELPERLIB_API int 
vscphlp_open( long handle, const char *pHostname, const char *pUsername, const char *pPassword );
HELPERLIB_API int 
vscphlp_close( long handle );
HELPERLIB_API int 
vscphlp_noop( long handle );
HELPERLIB_API int 
vscphlp_clearDaemonEventQueue( long handle );
HELPERLIB_API int 
vscphlp_sendEvent( long handle,  const vscpEvent *pEvent );
HELPERLIB_API int 
vscphlp_sendEventEx( long handle, const vscpEventEx *pEvent );
HELPERLIB_API int 
vscphlp_receiveEvent( long handle, vscpEvent *pEvent );
HELPERLIB_API int 
vscphlp_receiveEventEx( long handle, vscpEventEx *pEvent );
HELPERLIB_API int 
vscphlp_blockingReceiveEvent( long handle, vscpEvent *pEvent, unsigned long timout );
HELPERLIB_API int 
vscphlp_blockingReceiveEventEx( long handle, vscpEventEx *pEventEx, unsigned long timout );
HELPERLIB_API int 
vscphlp_enterReceiveLoop(const long handle);
HELPERLIB_API int 
vscphlp_quitReceiveLoop(const long handle);
HELPERLIB_API int 
vscphlp_isDataAvailable( long handle, unsigned int *pCount );
HELPERLIB_API int 
vscphlp_getStatus( long handle, VSCPStatus *pStatus );
HELPERLIB_API int 
vscphlp_getStatistics( long handle, VSCPStatistics *pStatistics );
HELPERLIB_API int 
vscphlp_setFilter( long handle, const vscpEventFilter *pFilter );
HELPERLIB_API int 
vscphlp_getVersion( long handle,
                      unsigned char *pMajorVer,
                      unsigned char *pMinorVer,
                      unsigned char *pSubMinorVer );
HELPERLIB_API int 
vscphlp_getDLLVersion( long handle, unsigned long *pVersion );
HELPERLIB_API int 
vscphlp_getVendorString( long handle, char *pVendorStr, size_t len  );
HELPERLIB_API int 
vscphlp_getDriverInfo( long handle, char *pDriverInfoStr, size_t len  );
HELPERLIB_API int 
vscphlp_getGUID( long handle, unsigned char *pGUID );
HELPERLIB_API int 
vscphlp_setGUID( long handle, const unsigned char *pGUID );
HELPERLIB_API int 
vscphlp_serverShutDown( long handle );


//-------------------------------------------------------------------------
//                                Helpers
//-------------------------------------------------------------------------


HELPERLIB_API unsigned long 
vscphlp_readStringValue( const char * pStrValue );
HELPERLIB_API unsigned char 
vscphlp_getVscpPriority( const vscpEvent *pEvent );
HELPERLIB_API void 
vscphlp_setVscpPriority( vscpEvent *pEvent, unsigned char priority );
HELPERLIB_API unsigned char 
vscphlp_getVSCPheadFromCANALid( const unsigned long id );
HELPERLIB_API unsigned short 
vscphlp_getVSCPclassFromCANALid( const unsigned long id );
HELPERLIB_API unsigned short 
vscphlp_getVSCPtypeFromCANALid( const unsigned long id );
HELPERLIB_API unsigned char 
vscphlp_getVSCPnicknameFromCANALid( const unsigned long id );
HELPERLIB_API unsigned long 
vscphlp_getCANALidFromData( const unsigned char priority,
                              const unsigned short vscp_class,
                              const unsigned short vscp_type );
HELPERLIB_API unsigned long 
vscphlp_getCANALidFromEvent( const vscpEvent *pEvent );
HELPERLIB_API unsigned long 
vscphlp_getCANALidFromEventEx( const vscpEventEx *pEvent );
HELPERLIB_API unsigned short 
vscphlp_calc_crc_Event( vscpEvent *pEvent, short bSet );
HELPERLIB_API unsigned short 
vscphlp_calc_crc_EventEx( vscpEvent *pEvent, short bSet );
HELPERLIB_API unsigned char 
vscphlp_calcCRC4GUIDArray( unsigned char *pguid );
HELPERLIB_API unsigned char 
vscphlp_calcCRC4GUIDString(const char *strguid);
HELPERLIB_API int 
vscphlp_getGuidFromString( vscpEvent *pEvent, const char * pGUID );
HELPERLIB_API int 
vscphlp_getGuidFromStringEx( vscpEventEx *pEvent, const char * pGUID );
HELPERLIB_API int 
vscphlp_getGuidFromStringToArray( uint8_t *pGUID, const char * pStr );
HELPERLIB_API int 
vscphlp_writeGuidToString( const vscpEvent *pEvent, char *pStr, size_t len );
HELPERLIB_API int 
vscphlp_writeGuidToStringEx( const vscpEventEx *pEvent, char *pStr, size_t len );
HELPERLIB_API int 
vscphlp_writeGuidToString4Rows( const vscpEvent *pEvent,
                                char *strGUID,
                                int size );
HELPERLIB_API int 
vscphlp_writeGuidToString4RowsEx( const vscpEventEx *pEvent,
                                  char *strGUID,
                                  size_t len );
HELPERLIB_API int 
vscphlp_writeGuidArrayToString( const unsigned char *pGUID,
                                char *strGUID,
                                size_t len );
HELPERLIB_API int 
vscphlp_isGUIDEmpty( unsigned char *pGUID );
HELPERLIB_API int 
vscphlp_isSameGUID( const unsigned char *pGUID1,
                    const unsigned char *pGUID2 );
HELPERLIB_API int 
vscphlp_reverseGUID(unsigned char *pGUID);
HELPERLIB_API int 
vscphlp_convertVSCPtoEx( vscpEventEx *pEventEx,
                          const vscpEvent *pEvent );
HELPERLIB_API int 
vscphlp_convertVSCPfromEx( vscpEvent *pEvent,
                            const vscpEventEx *pEventEx );
HELPERLIB_API int 
vscphlp_newVSCPevent( vscpEvent **ppEvent );
HELPERLIB_API void 
vscphlp_deleteVSCPevent( vscpEvent *pEvent );
HELPERLIB_API void 
vscphlp_deleteVSCPevent_v2( vscpEvent **ppEvent );
HELPERLIB_API void 
vscphlp_deleteVSCPeventEx( vscpEventEx *pEventEx );
HELPERLIB_API void 
vscphlp_clearVSCPFilter( vscpEventFilter *pFilter );
HELPERLIB_API void 
vscphlp_copyVSCPFilter( vscpEventFilter *pToFilter, const vscpEventFilter *pFromFilter );
HELPERLIB_API int 
vscphlp_readFilterFromString( vscpEventFilter *pFilter, const char *strFilter );
HELPERLIB_API int 
vscphlp_readMaskFromString( vscpEventFilter *pFilter, const char *strMask );
HELPERLIB_API int 
vscphlp_writeFilterToString( vscpEventFilter *pFilter, char *strFilter );
HELPERLIB_API int 
vscphlp_writeMaskToString( vscpEventFilter *pFilter, char *strMask );
HELPERLIB_API int 
vscphlp_doLevel2Filter( const vscpEvent *pEvent,
                               const vscpEventFilter *pFilter );
HELPERLIB_API int 
vscphlp_convertCanalToEvent( vscpEvent *pvscpEvent,
                              const canalMsg *pcanalMsg,
                              unsigned char *pGUID );
HELPERLIB_API int 
vscphlp_convertCanalToEventEx( vscpEventEx *pvscpEvent,
                                const canalMsg *pcanalMsg,
                                 unsigned char *pGUID );
HELPERLIB_API int 
vscphlp_convertEventToCanal( canalMsg *pcanalMsg,
                              const vscpEvent *pvscpEvent );
HELPERLIB_API int 
vscphlp_convertEventExToCanal( canalMsg *pcanalMsg,
                                const vscpEventEx *pvscpEventEx );
HELPERLIB_API unsigned long 
vscphlp_makeTimeStamp( void );
HELPERLIB_API int 
vscphlp_setEventDateTimeBlockToNow( vscpEvent *pEvent );
HELPERLIB_API int 
vscphlp_setEventExDateTimeBlockToNow( vscpEventEx *pEventEx );
HELPERLIB_API int 
vscphlp_copyVSCPEvent( vscpEvent *pEventTo,
                        const vscpEvent *pEventFrom );
HELPERLIB_API int 
vscphlp_writeVscpDataToString( const vscpEvent *pEvent,
                                char *pstr,
                                size_t len,
                                int bUseHtmlBreak );
HELPERLIB_API int
vscphlp_writeVscpDataWithSizeToString( const unsigned char *pData,
                                          const unsigned short sizeData,
                                          char *pStr,
                                          size_t len,
                                          int bUseHtmlBreak,
                                          int bBreak );
HELPERLIB_API int 
vscphlp_getVscpDataFromString( vscpEvent *pEvent,
                                      const char *pstr );
HELPERLIB_API int 
vscphlp_getVscpDataArrayFromString( unsigned char *pData,
                                      unsigned short *psizeData,
                                      const char *pstr );
HELPERLIB_API int 
vscphlp_writeVscpEventToString( const vscpEvent *pEvent, char *p, size_t len );
HELPERLIB_API int 
vscphlp_writeVscpEventExToString( const vscpEventEx *pEvent, char *p, size_t len );
HELPERLIB_API int 
vscphlp_setVscpEventFromString( vscpEvent *pEvent, const char *p );
HELPERLIB_API int 
vscphlp_setVscpEventExFromString( vscpEventEx *pEvent, const char *p );
HELPERLIB_API int 
vscphlp_setVscpDataFromString( vscpEvent *pEvent, const char *pstr );
HELPERLIB_API int 
vscphlp_getVSCPMeasurementAsString( const vscpEvent *pEvent,
                                           char *pResult,
                                           size_t len );
HELPERLIB_API int 
vscphlp_setVscpDataArrayFromString( unsigned char *pData,
                                      unsigned short *psizeData,
                                      const char *pstr );

HELPERLIB_API unsigned char 
vscphlp_getMeasurementDataCoding( const vscpEvent *pEvent );
HELPERLIB_API unsigned long long 
vscphlp_getDataCodingBitArray(const unsigned char *pCode, int size );
HELPERLIB_API unsigned long long 
vscphlp_getDataCodingInteger(const unsigned char *pCode, int size );
HELPERLIB_API double 
vscphlp_getDataCodingNormalizedInteger(const unsigned char *pCode, int size );
HELPERLIB_API int 
vscphlp_getDataCodingString(const unsigned char *pData,
                              unsigned char dataLength,
                              char *strResult,
                              size_t len );
HELPERLIB_API int 
vscphlp_getVSCPMeasurementAsDouble(const vscpEvent *pEvent, double *pvalue);
HELPERLIB_API int 
vscphlp_getVSCPMeasurementFloat64AsString(const vscpEvent *pEvent,
                                            char *pStrResult,
                                            size_t len );
HELPERLIB_API int 
vscphlp_convertFloatToNormalizedEventData( unsigned char *pdata,
                                            unsigned short *psize,
                                            double value,
                                            unsigned char unit,
                                            unsigned char sensoridx );
HELPERLIB_API int 
vscphlp_convertFloatToFloatEventData( unsigned char *pdata,
                                        unsigned short *psize,
                                        float value,
                                        unsigned char unit,
                                        unsigned char sensoridx );
HELPERLIB_API int 
vscphlp_makeFloatMeasurementEvent( vscpEvent *pEvent,
                                    float value,
                                    unsigned char unit,
                                    unsigned char sensoridx );
HELPERLIB_API int 
vscphlp_makeFloatMeasurementEventEx( vscpEventEx *pEventEx,
                                      float value,
                                      unsigned char unit,
                                      unsigned char sensoridx );    
HELPERLIB_API int   
vscphlp_makeStringMeasurementEvent( vscpEvent *pEvent,
                                      float value,
                                      unsigned char unit,
                                      unsigned char sensoridx );
HELPERLIB_API int 
vscphlp_makeStringMeasurementEventEx( vscpEvent *pEvent,
                                        float value,
                                        unsigned char unit,
                                        unsigned char sensoridx );                                                                                 
HELPERLIB_API int 
vscphlp_getMeasurementAsFloat(const unsigned char *pNorm,
                                unsigned char length,
                                float *pResult );
HELPERLIB_API int 
vscphlp_getMeasurementUnit( const vscpEvent *pEvent );
HELPERLIB_API int 
vscphlp_getMeasuremenSensorIndex( const vscpEvent *pEvent );
HELPERLIB_API int 
vscphlp_getMeasurementZone( const vscpEvent *pEvent );
HELPERLIB_API int 
vscphlp_getMeasurementSubZone( const vscpEvent *pEvent );
HELPERLIB_API int 
vscphlp_isMeasurement( const vscpEvent *pEvent );
HELPERLIB_API int 
vscphlp_convertLevel1MeasuremenToLevel2Double( vscpEvent *pEventLevel1 );
HELPERLIB_API int 
vscphlp_convertLevel1MeasuremenToLevel2DoubleEx( vscpEventEx *pEventEx );
HELPERLIB_API int 
vscphlp_convertLevel1MeasuremenToLevel2String( vscpEvent *pEventLevel1 );
HELPERLIB_API int 
vscphlp_convertLevel1MeasuremenToLevel2StringEx( vscpEventEx *pEventEx );
HELPERLIB_API int 
vscphlp_makeLevel2FloatMeasurementEvent( vscpEvent *pEvent,
                                          uint16_t type,
                                          double value,
                                          uint8_t unit,
                                          uint8_t sensoridx,
                                          uint8_t zone,
                                          uint8_t subzone );
HELPERLIB_API int 
vscphlp_makeLevel2FloatMeasurementEventEx( vscpEventEx *pEventEx,
                                            uint16_t type,
                                            double value,
                                            uint8_t unit,
                                            uint8_t sensoridx,
                                            uint8_t zone,
                                            uint8_t subzone );
HELPERLIB_API int 
vscphlp_makeLevel2StringMeasurementEvent( vscpEvent *pEvent,
                                            uint16_t type,
                                            double value,
                                            uint8_t unit,
                                            uint8_t sensoridx,
                                            uint8_t zone,
                                            uint8_t subzone );
HELPERLIB_API int 
vscphlp_makeLevel2StringMeasurementEventEx( vscpEventEx *pEventEx,
                                              uint16_t type,
                                              double value,
                                              uint8_t unit,
                                              uint8_t sensoridx,
                                              uint8_t zone,
                                              uint8_t subzone );
HELPERLIB_API int 
vscphlp_replaceBackslash( char *pStr );
HELPERLIB_API unsigned char 
vscphlp_getVscpPriority( const vscpEvent *pEvent );
HELPERLIB_API unsigned char 
vscphlp_getVscpPriorityEx( const vscpEventEx *pEvent );
HELPERLIB_API void 
vscphlp_setVscpPriority( vscpEvent *pEvent, unsigned char priority );
HELPERLIB_API void 
vscphlp_setVscpPriorityEx( vscpEventEx *pEvent, unsigned char priority );

// Replaces vscphlp_writeVscpEventToString
HELPERLIB_API int 
vscphlp_convertEventToString( vscpEvent *pEvent, char *p, size_t len );
// Replaces vscphlp_writeVscpEventExToString
HELPERLIB_API int 
vscphlp_convertEventExToString( vscpEventEx *pEventEx, char *p, size_t len );
HELPERLIB_API int 
vscphlp_convertEventToJSON( vscpEvent *pEvent, char *p, size_t len );
HELPERLIB_API int 
vscphlp_convertEventExToJSON( vscpEventEx *pEventEx, char *p, size_t len );
HELPERLIB_API int 
vscphlp_convertEventToXML( vscpEvent *pEvent, char *p, size_t len );
HELPERLIB_API int 
vscphlp_convertEventExToXML( vscpEventEx *pEventEx, char *p, size_t len );
HELPERLIB_API int 
vscphlp_convertEventToHTML( vscpEvent *pEvent, char *p, size_t len );
HELPERLIB_API int 
vscphlp_convertEventExToHTML( vscpEventEx *pEventEx, char *p, size_t len );

// Replaces vscphlp_setVscpEventFromString
HELPERLIB_API int 
vscphlp_convertStringToEvent(vscpEvent* pEvent, const char* p);
// Replaces vscphlp_setVscpEventExFromString
HELPERLIB_API int 
vscphlp_convertStringToEventEx(vscpEventEx* pEventEx, const char* p);

HELPERLIB_API int 
vscphlp_getTimeString( char *buf, size_t buf_len, time_t *t );
HELPERLIB_API int 
vscphlp_getISOTimeString( char *buf, size_t buf_len, time_t *t );

HELPERLIB_API int 
vscphlp_getDateStringFromEvent( char *buf, size_t buf_len, vscpEvent *pEvent );
HELPERLIB_API int 
vscphlp_getDateStringFromEventEx( char *buf, size_t buf_len, vscpEventEx *pEventEx );

HELPERLIB_API int 
vscphlp_setEventToNow( vscpEvent *pEvent  );
HELPERLIB_API int 
vscphlp_setEventExToNow( vscpEventEx *pEventEx );

//-------------------------------------------------------------------------
//                            UDP / Multicast / Encryption
//-------------------------------------------------------------------------

HELPERLIB_API int 
vscphlp_getEncryptionCodeFromToken( const char *pToken, 
                                    int *pEncryptionCode );
HELPERLIB_API int 
vscphlp_getEncryptionTokenFromCode( int nEncryptionCode, 
                                      char *pEncryptionToken, 
                                      size_t len );

HELPERLIB_API int 
vscphlp_encryptVscpUdpFrame( unsigned char *output,
                                unsigned char *input,
                                size_t len,
                                const unsigned char *key,
                                const unsigned char *iv,
                                unsigned char nAlgorithm );

HELPERLIB_API int 
vscphlp_decryptVscpUdpFrame( unsigned char *output,
                                unsigned char *input,
                                size_t len,
                                const unsigned char *key,
                                const unsigned char *iv,
                                unsigned char nAlgorithm );

HELPERLIB_API size_t 
vscphlp_getUDpFrameSizeFromEvent( vscpEvent *pEvent );
HELPERLIB_API size_t 
vscphlp_getUDpFrameSizeFromEventEx( vscpEvent *pEventEx );

HELPERLIB_API int 
vscphlp_writeEventToUdpFrame( unsigned char *frame,
                                  size_t len,
                                  unsigned char pkttype,
                                  const vscpEvent *pEvent );

HELPERLIB_API int 
vscphlp_writeEventExToUdpFrame( unsigned char *frame,
                                  size_t len,
                                  unsigned char pkttype,
                                  const vscpEventEx *pEventEx );

#ifdef __cplusplus
}  // Extern "c"
#endif


/////////////////////////////////////////////////////////////////////////////////////////