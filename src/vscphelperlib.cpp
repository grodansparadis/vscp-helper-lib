// VSCP helper dll.cpp : Defines the initialization routines for the DLL.
//
// This file is part of the VSCP (http://www.vscp.org)
//
// The MIT License (MIT)
//
// Copyright (C) 2000-2021 Åke Hedman, The VSCP Project,
// <akhe@vscp.org>
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#ifdef WIN32
#include <StdAfx.h>
#endif

#ifdef WIN32
#include <winsock2.h>
#endif

#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#ifndef WIN32
#include <unistd.h>
#endif

#include <canal.h>
#include <canaldlldef.h>
#include <vscp.h>
#include <vscpcanaldeviceif.h>
#include <vscpdatetime.h>
#include <vscphelper.h>
#include <vscpremotetcpif.h>
#ifdef WIN32
#include "dlldrvobj.h"
#include "vscphelperdll.h"
#else
#include "linux/libvscphelper.h"
#endif

#ifdef WIN32
#define DllExport __declspec(dllexport)
#endif

struct vscphlpobj
{

    VscpRemoteTcpIf* m_pvscpif;
    VscpCanalDeviceIf* m_pcanalif;
};

//-----------------------------------------------------------------------------
//                     T C P / I P  I N T E R F A C E
//-----------------------------------------------------------------------------

//-------------------------------------------------------------------------
//
// To use any of the methods below this point you have to
// obtain a handle first with vscphlp_gethandle and remember
// to release it with vscphlp_releasehandle when you are done.
//
//-------------------------------------------------------------------------

///////////////////////////////////////////////////////////////////////////////
// vscphlp_newSession
//

#ifdef WIN32
extern "C" DllExport long WINAPI EXPORT
vscphlp_newSession(void)
#else
extern "C" long EXPORT
vscphlp_newSession(void)
#endif
{
    VscpRemoteTcpIf* pvscpif = new VscpRemoteTcpIf;
    if (NULL == pvscpif) {
        return 0;
    }

    return addDriverObject(pvscpif);
}

///////////////////////////////////////////////////////////////////////////////
// vscphlp_closeSession
//

#ifdef WIN32
extern "C" DllExport void WINAPI EXPORT
vscphlp_closeSession(long handle)
#else
extern "C" void
vscphlp_closeSession(long handle)
#endif
{
    VscpRemoteTcpIf* pvscpif = getDriverObject(handle);
    if (NULL != pvscpif) {
        pvscpif->doCmdClose();
    }

    removeDriverObject(handle);
}

///////////////////////////////////////////////////////////////////////////////
// vscphlp_setResponseTimeout
//
#ifdef WIN32
extern "C" DllExport int WINAPI EXPORT
vscphlp_setResponseTimeout(long handle, unsigned long timeout)
#else
extern "C" int
vscphlp_setResponseTimeout(long handle, unsigned long timeout)
#endif
{
    VscpRemoteTcpIf* pvscpif = getDriverObject(handle);
    if (NULL == pvscpif)
        return VSCP_ERROR_INVALID_HANDLE;

    pvscpif->setResponseTimeout(timeout);

    return VSCP_ERROR_SUCCESS;
}

///////////////////////////////////////////////////////////////////////////////
// vscphlp_setAfterCommandSleep
//
#ifdef WIN32
extern "C" DllExport int WINAPI EXPORT
vscphlp_setAfterCommandSleep(long handle, unsigned short sleeptime)
#else
extern "C" int
vscphlp_setAfterCommandSleep(long handle, unsigned short sleeptime)
#endif
{
    VscpRemoteTcpIf* pvscpif = getDriverObject(handle);
    if (NULL == pvscpif)
        return VSCP_ERROR_INVALID_HANDLE;

    pvscpif->setAfterCommandSleep(sleeptime);

    return VSCP_ERROR_SUCCESS;
}

///////////////////////////////////////////////////////////////////////////////
// vscphlp_isConnected
//
#ifdef WIN32
extern "C" DllExport int WINAPI EXPORT
vscphlp_isConnected(const long handle)
#else
extern "C" int
vscphlp_isConnected(const long handle)
#endif
{
    VscpRemoteTcpIf* pvscpif = getDriverObject(handle);
    if (NULL == pvscpif)
        return VSCP_ERROR_INVALID_HANDLE;

    return pvscpif->isConnected() ? VSCP_ERROR_SUCCESS : VSCP_ERROR_ERROR;
}

///////////////////////////////////////////////////////////////////////////////
// vscphlp_doCommand
//
#ifdef WIN32
extern "C" DllExport int WINAPI EXPORT
vscphlp_doCommand(long handle, const char* cmd)
#else
extern "C" int
vscphlp_doCommand(long handle, const char* cmd)
#endif
{
    VscpRemoteTcpIf* pvscpif = getDriverObject(handle);
    if (NULL == pvscpif)
        return VSCP_ERROR_INVALID_HANDLE;

    // Check that we are connected
    if (!pvscpif->isConnected())
        return VSCP_ERROR_CONNECTION;

    std::string strCmd = std::string(cmd);
    return pvscpif->doCommand(strCmd);
}

///////////////////////////////////////////////////////////////////////////////
// vscphlp_checkReply
//
#ifdef WIN32
extern "C" DllExport int WINAPI EXPORT
vscphlp_checkReply(long handle, int bClear)
#else
extern "C" int
vscphlp_checkReply(long handle, int bClear)
#endif
{
    VscpRemoteTcpIf* pvscpif = getDriverObject(handle);
    if (NULL == pvscpif)
        return VSCP_ERROR_INVALID_HANDLE;

    // Check that we are connected
    if (!pvscpif->isConnected())
        return VSCP_ERROR_CONNECTION;

    return pvscpif->checkReturnValue(bClear ? true : false) ? VSCP_ERROR_SUCCESS
                                                            : VSCP_ERROR_ERROR;
}

///////////////////////////////////////////////////////////////////////////////
// vscphlp_clearLocalInputQueue
//
#ifdef WIN32
extern "C" DllExport int WINAPI EXPORT
vscphlp_clearLocalInputQueue(long handle)
#else
extern "C" int
vscphlp_clearLocalInputQueue(long handle)
#endif
{
    VscpRemoteTcpIf* pvscpif = getDriverObject(handle);
    if (NULL == pvscpif)
        return VSCP_ERROR_INVALID_HANDLE;

    pvscpif->doClrInputQueue();
    return VSCP_ERROR_SUCCESS;
}

///////////////////////////////////////////////////////////////////////////////
// vscphlp_OpenInterface
//
#ifdef WIN32
extern "C" DllExport int WINAPI EXPORT
vscphlp_openInterface(long handle, const char* pInterface, unsigned long flags)
#else
extern "C" int
vscphlp_openInterface(long handle, const char* pInterface, unsigned long flags)
#endif
{
    std::string strInterface;
    VscpRemoteTcpIf* pvscpif = getDriverObject(handle);
    if (NULL == pvscpif)
        return VSCP_ERROR_INVALID_HANDLE;

    strInterface = std::string(pInterface);
    return pvscpif->doCmdOpen(strInterface, flags);
}

///////////////////////////////////////////////////////////////////////////////
// vscphlp_open
//
#ifdef WIN32
extern "C" DllExport int WINAPI EXPORT
vscphlp_open(const long handle,
             const char* pHostname,
             const char* pUsername,
             const char* pPassword)
#else

extern "C" int
vscphlp_open(const long handle,
             const char* pHostname,
             const char* pUsername,
             const char* pPassword)
#endif
{
    std::string strHostname;
    std::string strUsername;
    std::string strPassword;

    VscpRemoteTcpIf* pvscpif = getDriverObject(handle);
    if (NULL == pvscpif)
        return VSCP_ERROR_INVALID_HANDLE;

    strHostname = std::string(pHostname);
    strUsername = std::string(pUsername);
    strPassword = std::string(pPassword);

    return pvscpif->doCmdOpen(strHostname, strUsername, strPassword);
}

///////////////////////////////////////////////////////////////////////////////
// vscphlp_close
//
#ifdef WIN32
extern "C" DllExport int WINAPI EXPORT
vscphlp_close(long handle)
#else
extern "C" int
vscphlp_close(long handle)
#endif
{
    VscpRemoteTcpIf* pvscpif = getDriverObject(handle);
    if (NULL == pvscpif)
        return VSCP_ERROR_INVALID_HANDLE;

    // Check that we are connected
    if (!pvscpif->isConnected())
        return VSCP_ERROR_CONNECTION;

    return pvscpif->doCmdClose();
}

///////////////////////////////////////////////////////////////////////////////
// vscphlp_noop
//
#ifdef WIN32
extern "C" DllExport int WINAPI EXPORT
vscphlp_noop(long handle)
#else
extern "C" int
vscphlp_noop(long handle)
#endif
{
    VscpRemoteTcpIf* pvscpif = getDriverObject(handle);
    if (NULL == pvscpif)
        return VSCP_ERROR_INVALID_HANDLE;

    // Check that we are connected
    if (!pvscpif->isConnected())
        return VSCP_ERROR_CONNECTION;

    return pvscpif->doCmdNOOP();
}

///////////////////////////////////////////////////////////////////////////////
// vscphlp_clearDaemonEventQueue
//

#ifdef WIN32
extern "C" DllExport int WINAPI EXPORT
vscphlp_clearDaemonEventQueue(long handle)
#else
extern "C" int
vscphlp_clearDaemonEventQueue(long handle)
#endif
{
    VscpRemoteTcpIf* pvscpif = getDriverObject(handle);
    if (NULL == pvscpif)
        return VSCP_ERROR_INVALID_HANDLE;

    // Check that we are connected
    if (!pvscpif->isConnected())
        return VSCP_ERROR_CONNECTION;

    return pvscpif->doCmdClear();
}

///////////////////////////////////////////////////////////////////////////////
// vscphlp_sendEvent
//
#ifdef WIN32
extern "C" DllExport int WINAPI EXPORT
vscphlp_sendEvent(long handle, const vscpEvent* pEvent)
#else
extern "C" int
vscphlp_sendEvent(long handle, const vscpEvent* pEvent)
#endif
{
    VscpRemoteTcpIf* pvscpif = getDriverObject(handle);
    if (NULL == pvscpif)
        return VSCP_ERROR_INVALID_HANDLE;

    // Check that we are connected
    if (!pvscpif->isConnected())
        return VSCP_ERROR_CONNECTION;

    return pvscpif->doCmdSend(pEvent);
}

///////////////////////////////////////////////////////////////////////////////
// vscphlp_sendEventEx
//
#ifdef WIN32
extern "C" DllExport int WINAPI EXPORT
vscphlp_sendEventEx(long handle, const vscpEventEx* pEvent)
#else
extern "C" int
vscphlp_sendEventEx(long handle, const vscpEventEx* pEvent)
#endif
{
    VscpRemoteTcpIf* pvscpif = getDriverObject(handle);
    if (NULL == pvscpif)
        return VSCP_ERROR_INVALID_HANDLE;

    // Check that we are connected
    if (!pvscpif->isConnected())
        return VSCP_ERROR_CONNECTION;

    return pvscpif->doCmdSendEx(pEvent);
}

///////////////////////////////////////////////////////////////////////////////
// vscphlp_receiveEvent
//
#ifdef WIN32
extern "C" DllExport int WINAPI EXPORT
vscphlp_receiveEvent(long handle, vscpEvent* pEvent)
#else
extern "C" int
vscphlp_receiveEvent(long handle, vscpEvent* pEvent)
#endif
{
    VscpRemoteTcpIf* pvscpif = getDriverObject(handle);
    if (NULL == pvscpif)
        return VSCP_ERROR_INVALID_HANDLE;

    // Check that we are connected
    if (!pvscpif->isConnected())
        return VSCP_ERROR_CONNECTION;

    return pvscpif->doCmdReceive(pEvent);
}

///////////////////////////////////////////////////////////////////////////////
// vscphlp_receiveEventEx
//

#ifdef WIN32
extern "C" DllExport int WINAPI EXPORT
vscphlp_receiveEventEx(long handle, vscpEventEx* pEvent)
#else
extern "C" int
vscphlp_receiveEventEx(long handle, vscpEventEx* pEvent)
#endif
{
    VscpRemoteTcpIf* pvscpif = getDriverObject(handle);
    if (NULL == pvscpif)
        return VSCP_ERROR_INVALID_HANDLE;

    // Check that we are connected
    if (!pvscpif->isConnected())
        return VSCP_ERROR_CONNECTION;

    return pvscpif->doCmdReceiveEx(pEvent);
}

///////////////////////////////////////////////////////////////////////////////
// vscphlp_blockingReceiveEvent
//
#ifdef WIN32
extern "C" DllExport int WINAPI EXPORT
vscphlp_blockingReceiveEvent(long handle,
                             vscpEvent* pEvent,
                             unsigned long timeout)
#else
extern "C" int
vscphlp_blockingReceiveEvent(long handle,
                             vscpEvent* pEvent,
                             unsigned long timeout)
#endif
{
    VscpRemoteTcpIf* pvscpif = getDriverObject(handle);
    if (NULL == pvscpif)
        return VSCP_ERROR_INVALID_HANDLE;

    // Check that we are connected
    if (!pvscpif->isConnected())
        return VSCP_ERROR_CONNECTION;

    return pvscpif->doCmdBlockingReceive(pEvent, timeout);
}

///////////////////////////////////////////////////////////////////////////////
// vscphlp_blockingReceiveEventEx
//

#ifdef WIN32
extern "C" DllExport int WINAPI EXPORT
vscphlp_blockingReceiveEventEx(long handle,
                               vscpEventEx* pEvent,
                               unsigned long timeout)
#else
extern "C" int
vscphlp_blockingReceiveEventEx(long handle,
                               vscpEventEx* pEvent,
                               unsigned long timeout)
#endif
{
    VscpRemoteTcpIf* pvscpif = getDriverObject(handle);
    if (NULL == pvscpif)
        return VSCP_ERROR_INVALID_HANDLE;

    // Check that we are connected
    if (!pvscpif->isConnected())
        return VSCP_ERROR_CONNECTION;

    return pvscpif->doCmdBlockingReceive(pEvent, timeout);
}

///////////////////////////////////////////////////////////////////////////////
// vscphlp_isDataAvailable
//
#ifdef WIN32
extern "C" DllExport int WINAPI EXPORT
vscphlp_isDataAvailable(long handle, unsigned int* pCount)
#else
extern "C" int
vscphlp_isDataAvailable(long handle, unsigned int* pCount)
#endif
{
    VscpRemoteTcpIf* pvscpif = getDriverObject(handle);
    if (NULL == pvscpif)
        return VSCP_ERROR_INVALID_HANDLE;

    // Check that we are connected
    if (!pvscpif->isConnected())
        return VSCP_ERROR_CONNECTION;

    *pCount = pvscpif->doCmdDataAvailable();

    return VSCP_ERROR_SUCCESS;
}

///////////////////////////////////////////////////////////////////////////////
// vscphlp_getStatus
//

#ifdef WIN32
extern "C" DllExport int WINAPI EXPORT
vscphlp_getStatus(long handle, VSCPStatus* pStatus)
#else
extern "C" int
vscphlp_getStatus(long handle, VSCPStatus* pStatus)
#endif
{
    VscpRemoteTcpIf* pvscpif = getDriverObject(handle);
    if (NULL == pvscpif)
        return VSCP_ERROR_INVALID_HANDLE;

    // Check that we are connected
    if (!pvscpif->isConnected())
        return VSCP_ERROR_CONNECTION;

    return pvscpif->doCmdStatus(pStatus);
}

///////////////////////////////////////////////////////////////////////////////
// vscphlp_getStatistics
//
#ifdef WIN32
extern "C" DllExport int WINAPI EXPORT
vscphlp_getStatistics(long handle, VSCPStatistics* pStatistics)
#else
extern "C" int
vscphlp_getStatistics(long handle, canalStatistics* pStatistics)
#endif
{
    VscpRemoteTcpIf* pvscpif = getDriverObject(handle);
    if (NULL == pvscpif)
        return VSCP_ERROR_INVALID_HANDLE;

    // Check that we are connected
    if (!pvscpif->isConnected())
        return VSCP_ERROR_CONNECTION;

    return pvscpif->doCmdStatistics(pStatistics);
}

///////////////////////////////////////////////////////////////////////////////
// vscphlp_setFilter
//
#ifdef WIN32
extern "C" DllExport int WINAPI EXPORT
vscphlp_setFilter(long handle, const vscpEventFilter* pFilter)
#else
extern "C" int
vscphlp_setFilter(long handle, const vscpEventFilter* pFilter)
#endif
{
    VscpRemoteTcpIf* pvscpif = getDriverObject(handle);
    if (NULL == pvscpif)
        return VSCP_ERROR_INVALID_HANDLE;

    // Check that we are connected
    if (!pvscpif->isConnected())
        return VSCP_ERROR_CONNECTION;

    return pvscpif->doCmdFilter(pFilter);
}

///////////////////////////////////////////////////////////////////////////////
// vscphlp_getVersion
//
#ifdef WIN32
extern "C" DllExport int WINAPI EXPORT
vscphlp_getVersion(long handle,
                   unsigned char* pMajorVer,
                   unsigned char* pMinorVer,
                   unsigned char* pSubMinorVer)
#else
extern "C" int
vscphlp_getVersion(long handle,
                   unsigned char* pMajorVer,
                   unsigned char* pMinorVer,
                   unsigned char* pSubMinorVer)
#endif
{
    VscpRemoteTcpIf* pvscpif = getDriverObject(handle);
    if (NULL == pvscpif)
        return VSCP_ERROR_INVALID_HANDLE;

    // Check that we are connected
    if (!pvscpif->isConnected())
        return VSCP_ERROR_CONNECTION;

    return pvscpif->doCmdVersion(pMajorVer, pMinorVer, pSubMinorVer);
}

///////////////////////////////////////////////////////////////////////////////
// vscphlp_getDLLVersion
//
#ifdef WIN32
extern "C" DllExport int WINAPI EXPORT
vscphlp_getDLLVersion(long handle, unsigned long* pVersion)
#else
extern "C" int
vscphlp_getDLLVersion(long handle, unsigned long* pVersion)
#endif
{
    VscpRemoteTcpIf* pvscpif = getDriverObject(handle);
    if (NULL == pvscpif)
        return VSCP_ERROR_INVALID_HANDLE;

    // Check that we are connected
    if (!pvscpif->isConnected())
        return VSCP_ERROR_CONNECTION;

    *pVersion = pvscpif->doCmdDLLVersion();

    return VSCP_ERROR_SUCCESS;
}

///////////////////////////////////////////////////////////////////////////////
// vscphlp_getVendorString
//
#ifdef WIN32
extern "C" DllExport int WINAPI EXPORT
vscphlp_getVendorString(long handle, char* pVendorStr, size_t len)
#else
extern "C" int
vscphlp_getVendorString(long handle, char* pVendorStr, size_t len)
#endif
{
    if (NULL == pVendorStr)
        return VSCP_ERROR_PARAMETER;

    VscpRemoteTcpIf* pvscpif = getDriverObject(handle);
    if (NULL == pvscpif)
        return VSCP_ERROR_INVALID_HANDLE;

    // Check that we are connected
    if (!pvscpif->isConnected())
        return VSCP_ERROR_CONNECTION;

    std::string str = std::string(pvscpif->doCmdVendorString());
    memset(pVendorStr, 0, len);
    strncpy(pVendorStr, str.c_str(), std::min(strlen(str.c_str()), len));

    return VSCP_ERROR_SUCCESS;
}

///////////////////////////////////////////////////////////////////////////////
// vscphlp_getDriverInfo
//
#ifdef WIN32
extern "C" DllExport int WINAPI EXPORT
vscphlp_getDriverInfo(long handle, char* pInfoStr, size_t len)
#else
extern "C" int
vscphlp_getDriverInfo(long handle, char* pInfoStr, size_t len)
#endif
{
    if (NULL == pInfoStr)
        return VSCP_ERROR_PARAMETER;

    VscpRemoteTcpIf* pvscpif = getDriverObject(handle);
    if (NULL == pvscpif)
        return VSCP_ERROR_INVALID_HANDLE;

    // Check that we are connected
    if (!pvscpif->isConnected())
        return VSCP_ERROR_CONNECTION;

    std::string str = std::string(pvscpif->doCmdGetDriverInfo());
    memset(pInfoStr, 0, len);
    strncpy(pInfoStr, str.c_str(), std::min(strlen(str.c_str()), len));

    return VSCP_ERROR_SUCCESS;
}

///////////////////////////////////////////////////////////////////////////////
// vscphlp_getGUID
//
#ifdef WIN32
extern "C" DllExport int WINAPI EXPORT
vscphlp_getGUID(long handle, unsigned char* pGUID)
#else
extern "C" int
vscphlp_getGUID(long handle, unsigned char* pGUID)
#endif
{
    if (NULL == pGUID)
        return VSCP_ERROR_PARAMETER;

    VscpRemoteTcpIf* pvscpif = getDriverObject(handle);
    if (NULL == pvscpif)
        return VSCP_ERROR_INVALID_HANDLE;

    // Check that we are connected
    if (!pvscpif->isConnected())
        return VSCP_ERROR_CONNECTION;

    cguid GUID;
    int rv = pvscpif->doCmdGetGUID(GUID);
    memcpy(pGUID, GUID.getGUID(), 16);

    return rv;
}

///////////////////////////////////////////////////////////////////////////////
// vscphlp_setGUID
//
#ifdef WIN32
extern "C" DllExport int WINAPI EXPORT
vscphlp_setGUID(long handle, const unsigned char* pGUID)
#else
extern "C" int
vscphlp_setGUID(long handle, const unsigned char* pGUID)
#endif
{
    if (NULL == pGUID)
        return VSCP_ERROR_PARAMETER;

    VscpRemoteTcpIf* pvscpif = getDriverObject(handle);
    if (NULL == pvscpif)
        return VSCP_ERROR_INVALID_HANDLE;

    // Check that we are connected
    if (!pvscpif->isConnected())
        return VSCP_ERROR_CONNECTION;

    cguid guid;
    guid.getFromArray(pGUID);

    return pvscpif->doCmdSetGUID(guid);
}

///////////////////////////////////////////////////////////////////////////////
// vscphlp_shutDownServer
//
#ifdef WIN32
extern "C" DllExport int WINAPI EXPORT
vscphlp_shutDownServer(long handle)
#else
extern "C" int
vscphlp_shutDownServer(long handle)
#endif
{
    VscpRemoteTcpIf* pvscpif = getDriverObject(handle);
    if (NULL == pvscpif)
        return VSCP_ERROR_INVALID_HANDLE;

    // Check that we are connected
    if (!pvscpif->isConnected())
        return VSCP_ERROR_CONNECTION;

    return pvscpif->doCmdShutDown();
}

/*!
    This command sets an open interface in the receive loop (RCVLOOP).
    It does nothing other then putting the interface in the loop mode and
    checking that it went there.

    Note! The only way to terminate this receive loop is to close the session
   with 'CLOSE' or sending 'QUITLOOP' . \param handle to server object \return
   CANAL_ERROR_SUCCESS if success CANAL_ERROR_GENERIC if not.
 */
#ifdef WIN32
extern "C" DllExport int WINAPI EXPORT
vscphlp_enterReceiveLoop(const long handle)
#else
extern "C" int
vscphlp_enterReceiveLoop(const long handle)
#endif
{
    // Get VSCP TCP/IP object
    VscpRemoteTcpIf* pvscpif = getDriverObject(handle);
    if (NULL == pvscpif)
        return VSCP_ERROR_INVALID_HANDLE;

    // Check that we are connected
    if (!pvscpif->isConnected())
        return VSCP_ERROR_CONNECTION;

    return pvscpif->doCmdEnterReceiveLoop();
}

/*!
    Quit the receiveloop
*/
#ifdef WIN32
extern "C" DllExport int WINAPI EXPORT
vscphlp_quitReceiveLoop(const long handle)
#else
extern "C" int
vscphlp_quitReceiveLoop(const long handle)
#endif
{
    // Get VSCP TCP/IP object
    VscpRemoteTcpIf* pvscpif = getDriverObject(handle);
    if (NULL == pvscpif)
        return VSCP_ERROR_INVALID_HANDLE;

    // Check that we are connected
    if (!pvscpif->isConnected())
        return VSCP_ERROR_CONNECTION;

    return pvscpif->doCmdQuitReceiveLoop();
}



////////////////////////////////////////////////////////////////////////////////
//                              H E L P E R S
////////////////////////////////////////////////////////////////////////////////

// * * * * *    G E N E R A L   * * * * *

/*!
    \fn long vscphlp_readStringValue( const char * pStrValue )
    \brief Read a value (decimal or hex) from a string.
        \return The converted number.
*/
#ifdef WIN32
extern "C" DllExport unsigned long WINAPI EXPORT
vscphlp_readStringValue(const char* pStrValue)
#else
extern "C" unsigned long
vscphlp_readStringValue(const char* pStrValue)
#endif
{
    std::string strVal;
    strVal = std::string(pStrValue);

    return vscp_readStringValue(strVal);
}

#ifdef WIN32
extern "C" DllExport int WINAPI EXPORT
vscphlp_replaceBackslash(char* pStr)
#else
extern "C" int
vscphlp_replaceBackslash(char* pStr)
#endif
{
    if (NULL == pStr)
        return VSCP_ERROR_ERROR;

    std::string str = std::string(pStr);
    str = vscp_replaceBackslash(str);
    strcpy(pStr, str.c_str());
    return VSCP_ERROR_SUCCESS;
}

// * * * * *  E V E N T - H E L P E R S * * * * *

/*!
    \fn bool vscphlp_convertVSCPtoEx( vscpEventEx *pEventEx,
                                    const vscpEvent *pEvent )
    \brief Convert VSCP standard event form to ex. form.
*/
#ifdef WIN32
extern "C" DllExport int WINAPI EXPORT
vscphlp_convertVSCPtoEx(vscpEventEx* pEventEx, const vscpEvent* pEvent)
#else
extern "C" int
vscphlp_convertVSCPtoEx(vscpEventEx* pEventEx, const vscpEvent* pEvent)
#endif
{
    return vscp_convertEventToEventEx(pEventEx, pEvent) ? VSCP_ERROR_SUCCESS
                                                        : VSCP_ERROR_ERROR;
}

/*!
    \fn bool vscphlp_convertVSCPfromEx( vscpEvent *pEvent,
                                        const vscpEventEx *pEventEx )
    \brief Convert VSCP ex. event form to standard form.
*/
#ifdef WIN32
extern "C" DllExport int WINAPI EXPORT
vscphlp_convertVSCPfromEx(vscpEvent* pEvent, const vscpEventEx* pEventEx)
#else
extern "C" int
vscphlp_convertVSCPfromEx(vscpEvent* pEvent, const vscpEventEx* pEventEx)
#endif
{
    return vscp_convertEventExToEvent(pEvent, pEventEx) ? VSCP_ERROR_SUCCESS
                                                        : VSCP_ERROR_ERROR;
}

/*!
    \fn int vscphlp_newVSCPevent( vscpEvent **ppEvent )
    \brief Create a new VSCP event.
*/
#ifdef WIN32
extern "C" DllExport int WINAPI EXPORT
vscphlp_newVSCPevent(vscpEvent** ppEvent)
#else
extern "C" int
vscphlp_newVSCPevent(vscpEvent** ppEvent)
#endif
{
    return vscp_newEvent(ppEvent) ? VSCP_ERROR_SUCCESS : VSCP_ERROR_ERROR;
}

/*!
    \fn void vscphlp_deleteVSCPevent( vscpEvent *pEvent )
    \brief Delete VSCP event.
*/
#ifdef WIN32
extern "C" DllExport void WINAPI EXPORT
vscphlp_deleteVSCPevent(vscpEvent* pEvent)
#else
extern "C" void
vscphlp_deleteVSCPevent(vscpEvent* pEvent)
#endif
{
    return vscp_deleteEvent(pEvent);
}

/*!
    \fn void vscphlp_deleteVSCPevent_v2( vscpEvent **ppEvent )
    \brief Delete and null VSCP event.
*/
#ifdef WIN32
extern "C" DllExport void WINAPI EXPORT
vscphlp_deleteVSCPevent_v2(vscpEvent** ppEvent)
#else
extern "C" void
vscphlp_deleteVSCPevent_v2(vscpEvent** ppEvent)
#endif
{
    return vscp_deleteEvent_v2(ppEvent);
}

/*!
    \fn void vscphlp_deleteVSCPeventEx( vscpEventEx *pEventEx )
    \brief Delete VSCP event ex.
*/
#ifdef WIN32
extern "C" DllExport void WINAPI EXPORT
vscphlp_deleteVSCPeventEx(vscpEventEx* pEventEx)
#else
extern "C" void
vscphlp_deleteVSCPeventEx(vscpEventEx* pEventEx)
#endif
{
    return vscp_deleteEventEx(pEventEx);
}

/*!
    \fn unsigned char vscphlp_getVscpPriority( const vscpEvent *pEvent )
    \brief Get VSCP priority.
*/
#ifdef WIN32
extern "C" DllExport unsigned char WINAPI EXPORT
vscphlp_getVscpPriority(const vscpEvent* pEvent)
#else
extern "C" unsigned char
vscphlp_getVscpPriority(const vscpEvent* pEvent)
#endif
{
    return vscp_getEventPriority(pEvent);
}

#ifdef WIN32
extern "C" DllExport unsigned char WINAPI EXPORT
vscphlp_getVscpPriorityEx(const vscpEventEx* pEvent)
#else
extern "C" unsigned char
vscphlp_getVscpPriorityEx(const vscpEventEx* pEvent)
#endif
{
    return vscp_getEventExPriority(pEvent);
}

/*!
    \fn void vscphlp_setVscpPriority( vscpEvent *pEvent, unsigned char priority
   ) \brief Set VSCP priority.
*/
#ifdef WIN32
extern "C" DllExport void WINAPI EXPORT
vscphlp_setVscpPriority(vscpEvent* pEvent, unsigned char priority)
#else
extern "C" void
vscphlp_setVscpPriority(vscpEvent* pEvent, unsigned char priority)
#endif
{
    vscp_setEventPriority(pEvent, priority);
}

#ifdef WIN32
extern "C" DllExport void WINAPI EXPORT
vscphlp_setVscpPriorityEx(vscpEventEx* pEvent, unsigned char priority)
#else
extern "C" void
vscphlp_setVscpPriorityEx(vscpEventEx* pEvent, unsigned char priority)
#endif
{
    vscp_setEventExPriority(pEvent, priority);
}

/*!
    \fn vscphlp_getVSCPheadFromCANALid( const unsigned long id )
    \brief Get the VSCP head from a CANAL message id (CANAL id).
*/
#ifdef WIN32
extern "C" DllExport unsigned char WINAPI EXPORT
vscphlp_getVSCPheadFromCANALid(const unsigned long id)
#else
extern "C" unsigned char
vscphlp_getVSCPheadFromCANALid(const unsigned long id)
#endif
{
    return vscp_getHeadFromCANALid(id);
}

/*!
    \fn vscphlp_getVSCPclassFromCANALid( const unsigned long id )
    \brief Get the VSCP class from a CANAL message id (CANAL id).
*/
#ifdef WIN32
extern "C" DllExport unsigned short WINAPI EXPORT
vscphlp_getVSCPclassFromCANALid(const unsigned long id)
#else
extern "C" unsigned short
vscphlp_getVSCPclassFromCANALid(const unsigned long id)
#endif
{
    return vscp_getVscpClassFromCANALid(id);
}

/*!
    \fn unsigned short vscphlp_getVSCPtypeFromCANALid( const unsigned long id )
    \brief Get the VSCP type from a a CANAL message id (CANAL id).
*/
#ifdef WIN32
extern "C" DllExport unsigned short WINAPI EXPORT
vscphlp_getVSCPtypeFromCANALid(const unsigned long id)
#else
extern "C" unsigned short
vscphlp_getVSCPtypeFromCANALid(const unsigned long id)
#endif
{
    return vscp_getVscpTypeFromCANALid(id);
}

/*!
    \fn unsigned short vscphlp_getVSCPnicknameFromCANALid( const unsigned long
   id ) \brief Get the VSCP nickname from a a CANAL message id (CANAL id).
*/
#ifdef WIN32
extern "C" DllExport unsigned char WINAPI EXPORT
vscphlp_getVSCPnicknameFromCANALid(const unsigned long id)
#else
extern "C" unsigned char
vscphlp_getVSCPnicknameFromCANALid(const unsigned long id)
#endif
{
    return vscp_getNicknameFromCANALid(id);
}

/*!
    \fn unsigned long vscphlp_getCANALidFromVSCPdata( const unsigned char
   priority, const unsigned short vscp_class, const unsigned short vscp_type )
    \brief Construct a CANAL id (CANAL id ) from VSCP.
*/
#ifdef WIN32
extern "C" DllExport unsigned long WINAPI EXPORT
vscphlp_getCANALidFromData(const unsigned char priority,
                           const unsigned short vscp_class,
                           const unsigned short vscp_type)
#else
extern "C" unsigned long
vscphlp_getCANALidFromData(const unsigned char priority,
                           const unsigned short vscp_class,
                           const unsigned short vscp_type)
#endif
{
    return vscp_getCANALidFromData(priority, vscp_class, vscp_type);
}

/*!
    \fn unsigned long vscphlp_getCANALidFromVSCPevent( const vscpEvent *pEvent )
    \brief Get CANAL id (CAN id) from VSCP event.
*/
#ifdef WIN32
extern "C" DllExport unsigned long WINAPI EXPORT
vscphlp_getCANALidFromEvent(const vscpEvent* pEvent)
#else
extern "C" unsigned long
vscphlp_getCANALidFromEvent(const vscpEvent* pEvent)
#endif
{
    return vscp_getCANALidFromEvent(pEvent);
}

/*!
    \fn unsigned long vscphlp_getCANALidFromVSCPevent( const vscpEvent *pEvent )
    \brief Get CANAL id (CAN id) from VSCP event.
*/
#ifdef WIN32
extern "C" DllExport unsigned long WINAPI EXPORT
vscphlp_getCANALidFromEventEx(const vscpEventEx* pEvent)
#else
extern "C" unsigned long
vscphlp_getCANALidFromEventEx(const vscpEventEx* pEvent)
#endif
{
    return vscp_getCANALidFromEventEx(pEvent);
}

/*!
    \fn unsigned short vscphlp_calc_crc_Event( vscpEvent *pEvent, short bSet )
    \brief Calculate VSCP crc.
*/
#ifdef WIN32
extern "C" DllExport unsigned short WINAPI EXPORT
vscphlp_calc_crc_Event(vscpEvent* pEvent, short bSet)
#else
extern "C" unsigned short
vscphlp_calc_crc_Event(vscpEvent* pEvent, short bSet)
#endif
{
    return vscp_calc_crc_Event(pEvent, bSet);
}

/*!
    \fn unsigned short vscphlp_calc_crc_EventEx( vscpEvent *pEvent, short bSet )
    \brief Calculate VSCP crc.
*/
#ifdef WIN32
extern "C" DllExport unsigned short WINAPI EXPORT
vscphlp_calc_crc_EventEx(vscpEventEx* pEvent, short bSet)
#else
extern "C" unsigned short
vscphlp_calc_crc_EventEx(vscpEventEx* pEvent, short bSet)
#endif
{
    return vscp_calc_crc_EventEx(pEvent, bSet);
}

// * * * * *   G U I D  H E L P E R S    * * * * *

/*!
        calcCRC4GUIDArray

        \param Pointer to GUID array (MSB-LSB order)
        \return crc for GUID.
    */
#ifdef WIN32
extern "C" DllExport unsigned char WINAPI EXPORT
vscphlp_calcCRC4GUIDArray(unsigned char* pguid)
#else
extern "C" unsigned char
vscphlp_calcCRC4GUIDArray(unsigned char* pguid)
#endif
{
    return vscp_calcCRC4GUIDArray(pguid);
}

/*!
  calcCRC4GUIDString

  \param Pointer to GUID array (MSB-LSB order)
  \return crc for GUID.
*/
#ifdef WIN32
extern "C" DllExport unsigned char WINAPI EXPORT
vscphlp_calcCRC4GUIDString(const char* strguid)
#else
extern "C" unsigned char
vscphlp_calcCRC4GUIDString(const char* strguid)
#endif
{
    std::string str = std::string(strguid);
    return vscp_calcCRC4GUIDString(str);
}

/*!
    \fn bool vscphlp_getGuidFromString( vscpEvent *pEvent, const char * pGUID )
    \brief Write GUID into VSCP event from string.
*/
#ifdef WIN32
extern "C" DllExport int WINAPI EXPORT
vscphlp_getGuidFromString(vscpEvent* pEvent, const char* pGUID)
#else
extern "C" int
vscphlp_getGuidFromString(vscpEvent* pEvent, const char* pGUID)
#endif
{
    std::string strGUID = std::string(pGUID);
    return vscp_setEventGuidFromString(pEvent, strGUID) ? VSCP_ERROR_SUCCESS
                                                        : VSCP_ERROR_ERROR;
}

/*!
    \fn bool vscphlp_getGuidFromStringEx( vscpEventEx *pEvent, const char *
   pGUID ) \brief Write GUID into VSCP event from string.
*/

#ifdef WIN32
extern "C" DllExport int WINAPI EXPORT
vscphlp_getGuidFromStringEx(vscpEventEx* pEvent, const char* pGUID)
#else
extern "C" int
vscphlp_getGuidFromStringEx(vscpEventEx* pEvent, const char* pGUID)
#endif
{
    std::string strGUID = std::string(pGUID);
    return vscp_setEventExGuidFromString(pEvent, strGUID) ? VSCP_ERROR_SUCCESS
                                                          : VSCP_ERROR_ERROR;
}

/*!
    \fn bool vscphlp_getGuidFromStringToArray( uint8_t *pGUID, const char * pStr
   ) \brief Write GUID from string into array.
*/
#ifdef WIN32
extern "C" DllExport int WINAPI EXPORT
vscphlp_getGuidFromStringToArray(uint8_t* pGUID, const char* pStr)
#else
extern "C" int
vscphlp_getGuidFromStringToArray(uint8_t* pGUID, const char* pStr)
#endif
{
    std::string strGUID = std::string(pStr);
    return vscp_getGuidFromStringToArray(pGUID, strGUID) ? VSCP_ERROR_SUCCESS
                                                         : VSCP_ERROR_ERROR;
}

/*!
    \fn bool vscphlp_writeGuidToString( const vscpEvent *pEvent, char *pStr, int
   size ) \brief Write GUID from VSCP event to string.
*/
#ifdef WIN32
extern "C" DllExport int WINAPI EXPORT
vscphlp_writeGuidToString(const vscpEvent* pEvent, char* pStr, size_t len)
#else
extern "C" int
vscphlp_writeGuidToString(const vscpEvent* pEvent, char* pStr, size_t len)
#endif
{
    bool rv;

    std::string strGUID;
    rv = vscp_writeGuidToString(strGUID, pEvent);
    memset(pStr, 0, len);
    strncpy(pStr, strGUID.c_str(), std::min(strlen(strGUID.c_str()), len));
    return rv ? VSCP_ERROR_SUCCESS : VSCP_ERROR_ERROR;
}

/*!
    \fn bool vscphlp_writeGuidToStringEx( const vscpEventEx *pEvent, char * pStr
   ) \brief Write GUID froom VSCP event to string.
*/
#ifdef WIN32
extern "C" DllExport int WINAPI EXPORT
vscphlp_writeGuidToStringEx(const vscpEventEx* pEvent, char* pStr, size_t len)
#else
extern "C" int
vscphlp_writeGuidToStringEx(const vscpEventEx* pEvent, char* pStr, size_t len)
#endif
{
    bool rv;

    std::string strGUID;
    rv = vscp_writeGuidToStringEx(strGUID, pEvent);
    memset(pStr, 0, len);
    strncpy(pStr, strGUID.c_str(), std::min(strlen(strGUID.c_str()), len));
    return rv ? VSCP_ERROR_SUCCESS : VSCP_ERROR_ERROR;
}

/*!
    \fn bool vscphlp_writeGuidToString4Rows( const vscpEvent *pEvent,
                                            std::string& strGUID )
    \brief Write GUID from VSCP event to string with four bytes on each
    row seperated by \r\n.
*/
#ifdef WIN32
extern "C" DllExport int WINAPI EXPORT
vscphlp_writeGuidToString4Rows(const vscpEvent* pEvent,
                               char* strGUID,
                               size_t len)
#else
extern "C" int
vscphlp_writeGuidToString4Rows(const vscpEvent* pEvent,
                               char* strGUID,
                               size_t len)
#endif
{
    std::string str = std::string(strGUID);
    bool rv = vscp_writeGuidToString4Rows(str, pEvent);
    memset(strGUID, 0, len);
    strncpy(strGUID, str.c_str(), std::min(strlen(str.c_str()), len));

    return rv ? VSCP_ERROR_SUCCESS : VSCP_ERROR_ERROR;
}

/*!
    \fn bool vscphlp_writeGuidToString4RowsEx( const vscpEvent *pEvent,
                                            std::string& strGUID )
    \brief Write GUID from VSCP event to string with four bytes on each
    row seperated by \r\n.
*/
#ifdef WIN32
extern "C" DllExport int WINAPI EXPORT
vscphlp_writeGuidToString4RowsEx(const vscpEventEx* pEvent,
                                 char* strGUID,
                                 size_t len)
#else
extern "C" int
vscphlp_writeGuidToString4RowsEx(const vscpEventEx* pEvent,
                                 char* strGUID,
                                 size_t len)
#endif
{
    std::string str = std::string(strGUID);
    bool rv = vscp_writeGuidToString4RowsEx(str, pEvent);

    memset(strGUID, 0, len);
    strncpy(strGUID, str.c_str(), std::min(strlen(str.c_str()), len));

    return rv ? VSCP_ERROR_SUCCESS : VSCP_ERROR_ERROR;
}

/*!
    \fn bool vscphlp_writeGuidArrayToString( const unsigned char * pGUID,
                                            std::string& strGUID,
                                            int size )
    \brief Write GUID from byte array to string.
*/
#ifdef WIN32
extern "C" DllExport int WINAPI EXPORT
vscphlp_writeGuidArrayToString(const unsigned char* pGUID,
                               char* strGUID,
                               size_t len)
#else
extern "C" int
vscphlp_writeGuidArrayToString(const unsigned char* pGUID,
                               char* strGUID,
                               size_t len)
#endif
{
    std::string str;
    bool rv = vscp_writeGuidArrayToString(str, pGUID);

    memset(strGUID, 0, len);
    strncpy(strGUID, str.c_str(), std::min(strlen(str.c_str()), len));

    return rv ? VSCP_ERROR_SUCCESS : VSCP_ERROR_ERROR;
}

/*!
    \fn bool vscphlp_isGUIDEmpty( unsigned char *pGUID )
    \brief Check if GUID is empty (all nills).
*/
#ifdef WIN32
extern "C" DllExport int WINAPI EXPORT
vscphlp_isGUIDEmpty(unsigned char* pGUID)
#else
extern "C" int
vscphlp_isGUIDEmpty(unsigned char* pGUID)
#endif
{
    return vscp_isGUIDEmpty(pGUID) ? 1 : 0;
}

/*!
    \fn bool vscphlp_isSameGUID( const unsigned char *pGUID1,
                                const unsigned char *pGUID2 )
    \brief Check if two GUID's is equal to each other.
*/
#ifdef WIN32
extern "C" DllExport int WINAPI EXPORT
vscphlp_isSameGUID(const unsigned char* pGUID1, const unsigned char* pGUID2)
#else
extern "C" int
vscphlp_isSameGUID(const unsigned char* pGUID1, const unsigned char* pGUID2)
#endif
{
    return vscp_isSameGUID(pGUID1, pGUID2) ? 1 : 0;
}

/*!
    \fn bool vscphlp_reverseGUID(unsigned char *pGUID)
    \brief Reverse a GUID
*/
#ifdef WIN32
extern "C" DllExport int WINAPI EXPORT
vscphlp_reverseGUID(unsigned char* pGUID)
#else
extern "C" int
vscphlp_reverseGUID(unsigned char* pGUID)
#endif
{
    return vscp_reverseGUID(pGUID) ? VSCP_ERROR_SUCCESS : VSCP_ERROR_ERROR;
}

// * * * * *   F I L T E R  * * * * *

/*!
    \fn void vscphlp_clearVSCPFilter( vscpEventFilter *pFilter )
    \brief Clear VSCP filter.
*/
#ifdef WIN32
extern "C" DllExport void WINAPI EXPORT
vscphlp_clearVSCPFilter(vscpEventFilter* pFilter)
#else
extern "C" void
vscphlp_clearVSCPFilter(vscpEventFilter* pFilter)
#endif
{
    return vscp_clearVSCPFilter(pFilter);
}

/*!
    \fn void vscphlp_clearVSCPFilter( vscpEventFilter *pFilter )
    \brief Clear VSCP filter.
*/
#ifdef WIN32
extern "C" DllExport void WINAPI EXPORT
vscphlp_copyVSCPFilter(vscpEventFilter* pToFilter,
                       const vscpEventFilter* pFromFilter)
#else
extern "C" void
vscphlp_copyVSCPFilter(vscpEventFilter* pToFilter,
                       const vscpEventFilter* pFromFilter)
#endif
{
    return vscp_copyVSCPFilter(pToFilter, pFromFilter);
}

/*!
    \fn bool readFilterFromString( vscpEventFilter *pFilter, std::string&
   strFilter ) \brief Read a filter from a string \param pFilter Filter
   structure to write filter to. \param strFilter Filter in string form
            filter-priority, filter-class, filter-type, filter-GUID
    \return true on success, fals eon failure.
*/
#ifdef WIN32
extern "C" DllExport int WINAPI EXPORT
vscphlp_readFilterFromString(vscpEventFilter* pFilter, const char* strFilter)
#else
extern "C" int
vscphlp_readFilterFromString(vscpEventFilter* pFilter, const char* strFilter)
#endif
{
    std::string str = std::string(strFilter);
    return vscp_readFilterFromString(pFilter, str) ? VSCP_ERROR_SUCCESS
                                                   : VSCP_ERROR_ERROR;
}

/*!
    \fn bool readMaskFromString( vscpEventFilter *pFilter, std::string& strMask
   ) \brief Read a mask from a string \param pFilter Filter structure to write
   mask to. \param strMask Mask in string form mask-priority, mask-class,
   mask-type, mask-GUID \return true on success, fals eon failure.
*/
#ifdef WIN32
extern "C" DllExport int WINAPI EXPORT
vscphlp_readMaskFromString(vscpEventFilter* pFilter, const char* strMask)
#else
extern "C" int
vscphlp_readMaskFromString(vscpEventFilter* pFilter, const char* strMask)
#endif
{
    std::string str = std::string(strMask);
    return vscp_readMaskFromString(pFilter, str) ? VSCP_ERROR_SUCCESS
                                                 : VSCP_ERROR_ERROR;
}

/*!
    \fn bool writeFilterToString( vscpEventFilter *pFilter, std::string&
   strFilter ) \brief Write a filter to a string \param pFilter Filter structure
   to write filter to. \param strFilter Will get filter in string form
            filter-priority, filter-class, filter-type, filter-GUID
    \return true on success, fals eon failure.
*/
#ifdef WIN32
extern "C" DllExport int WINAPI EXPORT
vscphlp_writeFilterToString(vscpEventFilter* pFilter, char* strFilter)
#else
extern "C" int
vscphlp_writeFilterToString(vscpEventFilter* pFilter, char* strFilter)
#endif
{
    int rv;
    std::string str;

    rv = vscp_writeFilterToString(str, pFilter) ? VSCP_ERROR_SUCCESS
                                                : VSCP_ERROR_ERROR;
    if (VSCP_ERROR_SUCCESS == rv)
        memcpy(strFilter, (const char*)str.c_str(), strlen(str.c_str()));

    return rv;
}

/*!
    \fn bool writeMaskToString( vscpEventFilter *pFilter, std::string& strMask )
    \brief Write a mask to a string
    \param pFilter Filter structure to write mask to.
    \param strMask Will get mask in string form
            mask-priority, mask-class, mask-type, mask-GUID
    \return true on success, fals eon failure.
*/
#ifdef WIN32
extern "C" DllExport int WINAPI EXPORT
vscphlp_writeMaskToString(vscpEventFilter* pFilter, char* strMask)
#else
extern "C" int
vscphlp_writeMaskToString(vscpEventFilter* pFilter, char* strMask)
#endif
{
    int rv;
    std::string str;

    rv = vscp_writeMaskToString(str, pFilter) ? VSCP_ERROR_SUCCESS
                                              : VSCP_ERROR_ERROR;
    if (VSCP_ERROR_SUCCESS == rv)
        memcpy(strMask, (const char*)str.c_str(), strlen(str.c_str()));

    return rv;
}

/*!
    \fn bool vscphlp_doLevel2Filter( const vscpEvent *pEvent,
                                    const vscpEventFilter *pFilter )
    \brief Check VSCP filter condition.
*/
#ifdef WIN32
extern "C" DllExport int WINAPI EXPORT
vscphlp_doLevel2Filter(const vscpEvent* pEvent, const vscpEventFilter* pFilter)
#else
extern "C" int
vscphlp_doLevel2Filter(const vscpEvent* pEvent, const vscpEventFilter* pFilter)
#endif
{
    return vscp_doLevel2Filter(pEvent, pFilter) ? VSCP_ERROR_SUCCESS
                                                : VSCP_ERROR_ERROR;
}

/*!
    \fn int vscphlp_convertCanalToEvent( vscpEvent *pvscpEvent,
                                            const canalMsg *pcanalMsg,
                                            unsigned char *pGUID,
                                            bool bCAN )
    \brief Convert CANAL message to VSCP event.
*/
#ifdef WIN32
extern "C" DllExport int WINAPI EXPORT
vscphlp_convertCanalToEvent(vscpEvent* pvscpEvent,
                            const canalMsg* pcanalMsg,
                            unsigned char* pGUID)
#else
extern "C" int
vscphlp_convertCanalToEvent(vscpEvent* pvscpEvent,
                            const canalMsg* pcanalMsg,
                            unsigned char* pGUID)
#endif
{
    return vscp_convertCanalToEvent(pvscpEvent, pcanalMsg, pGUID)
             ? VSCP_ERROR_SUCCESS
             : VSCP_ERROR_ERROR;
}

/*!
    \fn int vscphlp_convertCanalToEvent( vscpEvent *pvscpEvent,
                                            const canalMsg *pcanalMsg,
                                            unsigned char *pGUID,
                                            bool bCAN )
    \brief Convert CANAL message to VSCP event.
*/
#ifdef WIN32
extern "C" DllExport int WINAPI EXPORT
vscphlp_convertCanalToEventEx(vscpEventEx* pvscpEvent,
                              const canalMsg* pcanalMsg,
                              unsigned char* pGUID)
#else
extern "C" int
vscphlp_convertCanalToEventEx(vscpEventEx* pvscpEvent,
                              const canalMsg* pcanalMsg,
                              unsigned char* pGUID)
#endif
{
    return vscp_convertCanalToEventEx(pvscpEvent, pcanalMsg, pGUID)
             ? VSCP_ERROR_SUCCESS
             : VSCP_ERROR_ERROR;
}

/*!
    \fn int vscphlp_convertEventToCanal( canalMsg *pcanalMsg,
                                           const vscpEvent *pvscpEvent )
    \brief Convert VSCP event to CANAL message.
*/
#ifdef WIN32
extern "C" DllExport int WINAPI EXPORT
vscphlp_convertEventToCanal(canalMsg* pcanalMsg, const vscpEvent* pvscpEvent)
#else
extern "C" int
vscphlp_convertEventToCanal(canalMsg* pcanalMsg, const vscpEvent* pvscpEvent)
#endif
{
    return vscp_convertEventToCanal(pcanalMsg, pvscpEvent) ? VSCP_ERROR_SUCCESS
                                                           : VSCP_ERROR_ERROR;
}

/*!
    \fn int vscphlp_convertEventExToCanal( canalMsg *pcanalMsg,
                                            const vscpEventEx *pvscpEvent )
    \brief Convert VSCP event to CANAL message.
*/
#ifdef WIN32
extern "C" DllExport int WINAPI EXPORT
vscphlp_convertEventExToCanal(canalMsg* pcanalMsg,
                              const vscpEventEx* pvscpEvent)
#else
extern "C" int
vscphlp_convertEventExToCanal(canalMsg* pcanalMsg,
                              const vscpEventEx* pvscpEvent)
#endif
{
    return vscp_convertEventExToCanal(pcanalMsg, pvscpEvent)
             ? VSCP_ERROR_SUCCESS
             : VSCP_ERROR_ERROR;
}

/*!
    \fn unsigned long vscphlp_makeTimeStamp( void )
    \brief Get VSCP timestamp.
*/
#ifdef WIN32
extern "C" DllExport unsigned long WINAPI EXPORT
vscphlp_makeTimeStamp(void)
#else
extern "C" unsigned long
vscphlp_makeTimeStamp(void)
#endif
{
    return vscp_makeTimeStamp();
}

/*!
    \fn int vscphlp_setEventDateTimeBlock( vscpEvent *pEvent )
    \brief date/time stamp for event.
*/
#ifdef WIN32
extern "C" DllExport int WINAPI EXPORT
vscphlp_setEventDateTimeBlockToNow(vscpEvent* pEvent)
#else
extern "C" int
vscphlp_setEventDateTimeBlockToNow(vscpEvent* pEvent)
#endif
{
    return vscp_setEventDateTimeBlockToNow(pEvent) ? VSCP_ERROR_SUCCESS
                                                   : VSCP_ERROR_ERROR;
}

/*!
    \fn int vscphlp_setEventDateTimeBlockEx( vscpEventEx *pEventEx )
    \briefSet date/time stamp for Ex event.
*/
#ifdef WIN32
extern "C" DllExport int WINAPI EXPORT
vscphlp_setEventExDateTimeBlockToNow(vscpEventEx* pEventEx)
#else
extern "C" int
vscphlp_setEventExDateTimeBlockToNow(vscpEventEx* pEventEx)
#endif
{
    return vscp_setEventExDateTimeBlockToNow(pEventEx) ? VSCP_ERROR_SUCCESS
                                                       : VSCP_ERROR_ERROR;
}

/*!
    \fn int vscphlp_copyVSCPEvent( vscpEvent *pEventTo,
                                    const vscpEvent *pEventFrom )
    \brief Copy VSCP event.
*/
#ifdef WIN32
extern "C" DllExport int WINAPI EXPORT
vscphlp_copyVSCPEvent(vscpEvent* pEventTo, const vscpEvent* pEventFrom)
#else
extern "C" int
vscphlp_copyVSCPEvent(vscpEvent* pEventTo, const vscpEvent* pEventFrom)
#endif
{
    return vscp_copyEvent(pEventTo, pEventFrom) ? VSCP_ERROR_SUCCESS
                                                : VSCP_ERROR_ERROR;
}

/*!
    \fn int vscphlp_writeVscpDataToString( const vscpEvent *pEvent,
                                                char *pstr,
                                                size_t len,
                                                int bUseHtmlBreak  )
    \brief Write VSCP data in readable form to a (multi line) string.
*/
#ifdef WIN32
extern "C" DllExport int WINAPI EXPORT
vscphlp_writeVscpDataToString(const vscpEvent* pEvent,
                              char* pStr,
                              size_t len,
                              int bUseHtmlBreak)
#else
extern "C" int
vscphlp_writeVscpDataToString(char* pStr,
                              const vscpEvent* pEvent,
                              size_t len,
                              int bUseHtmlBreak)
#endif
{
    std::string str;
    bool rv = vscp_writeDataToString(str, pEvent, bUseHtmlBreak ? true : false);
    memset(pStr, 0, len);
    strncpy(pStr, str.c_str(), std::min(strlen(str.c_str()), len));
    return rv ? VSCP_ERROR_SUCCESS : VSCP_ERROR_ERROR;
}

/*!
    \fn int vscphlp_writeVscpDataWithSizeToString( const unsigned short
   sizeData, const unsigned char *pData, char *pStr, size_t len, int
   bUseHtmlBreak, int bBreak ) \brief Write VSCP data given with size in
   readable form to a (multi line) string.
*/
#ifdef WIN32
extern "C" DllExport int WINAPI EXPORT
vscphlp_writeVscpDataWithSizeToString(char* pStr,
                                      const unsigned char* pData,
                                      const unsigned short sizeData,
                                      size_t len,
                                      int bUseHtmlBreak,
                                      int bBreak)
#else
extern "C" int
vscphlp_writeVscpDataWithSizeToString(char* pStr,
                                      const unsigned char* pData,
                                      const unsigned short sizeData,
                                      size_t len,
                                      int bUseHtmlBreak,
                                      int bBreak)
#endif
{
    std::string str;
    bool rv = vscp_writeDataWithSizeToString(str,
                                             pData,
                                             sizeData,
                                             bUseHtmlBreak ? true : false,
                                             bBreak ? true : false);
    memset(pStr, 0, len);
    strncpy(pStr, str.c_str(), std::min(strlen(str.c_str()), len));
    return rv ? VSCP_ERROR_SUCCESS : VSCP_ERROR_ERROR;
}

/*!
    \fn int vscphlp_getVscpDataFromString( vscpEvent *pEvent,
                                            const std::string& str )
    \brief Set data in VSCP event from a string.
*/
#ifdef WIN32
extern "C" DllExport int WINAPI EXPORT
vscphlp_setVscpDataFromString(vscpEvent* pEvent, const char* pstr)
#else
extern "C" int
vscphlp_setVscpDataFromString(vscpEvent* pEvent, const char* pstr)
#endif
{
    std::string str = std::string(pstr);
    return vscp_setEventDataFromString(pEvent, str) ? VSCP_ERROR_SUCCESS
                                                    : VSCP_ERROR_ERROR;
}

/*!
    \fn int vscphlp_getVscpDataAttayFromString( vscpEvent *pEvent,
                                                     unsigned short *psizeData,
                                                     const char *pstr )
    \brief Set data in VSCP event from a string.
*/
#ifdef WIN32
extern "C" DllExport int WINAPI EXPORT
vscphlp_setVscpDataArrayFromString(unsigned char* pData,
                                   unsigned short* psizeData,
                                   const char* pstr)
#else
extern "C" int
vscphlp_setVscpDataArrayFromString(unsigned char* pData,
                                   unsigned short* psizeData,
                                   const char* pstr)
#endif
{
    std::string str = std::string(pstr);
    return vscp_setDataArrayFromString(pData, psizeData, str)
             ? VSCP_ERROR_SUCCESS
             : VSCP_ERROR_ERROR;
}

/*!
    \fn int vscphlp_writeVscpEventToString( vscpEvent *pEvent,
                                            char *p )
    \brief Write VSCP data to a string.
*/
#ifdef WIN32
extern "C" DllExport int WINAPI EXPORT
vscphlp_writeVscpEventToString(vscpEvent* pEvent, char* p, size_t len)
#else
extern "C" int
vscphlp_writeVscpEventToString(vscpEvent* pEvent, char* p, size_t len)
#endif
{
    bool rv;

    std::string str;
    ;
    if ((rv = vscp_convertEventToString(str, pEvent))) {
        memset(p, 0, len);
        strncpy(p, str.c_str(), std::min(strlen(str.c_str()), len));
    }
    return rv ? VSCP_ERROR_SUCCESS : VSCP_ERROR_ERROR;
}

/*!
    \fn int vscphlp_convertEventToString( vscpEvent *pEvent,
                                            char *p )
    \brief Write VSCP data to a string.
*/
#ifdef WIN32
extern "C" DllExport int WINAPI EXPORT
vscphlp_convertEventToString(vscpEvent* pEvent, char* p, size_t len)
#else
extern "C" int
vscphlp_convertEventToString(vscpEvent* pEvent, char* p, size_t len)
#endif
{
    bool rv;

    std::string str;
    ;
    if ((rv = vscp_convertEventToString(str, pEvent))) {
        memset(p, 0, len);
        strncpy(p, str.c_str(), std::min(strlen(str.c_str()), len));
    }
    return rv ? VSCP_ERROR_SUCCESS : VSCP_ERROR_ERROR;
}

/*!
    \fn int vscphlp_writeVscpEventExToString( vscpEventEx *pEvent,
                                                char *p )
    \brief Write VSCP data to a string.
*/
#ifdef WIN32
extern "C" DllExport int WINAPI EXPORT
vscphlp_writeVscpEventExToString(vscpEventEx* pEvent, char* p, size_t len)
#else
extern "C" int
vscphlp_writeVscpEventExToString(vscpEventEx* pEvent, char* p, size_t len)
#endif
{
    bool rv;

    std::string str;
    if ((rv = vscp_convertEventExToString(str, pEvent))) {
        memset(p, 0, len);
        strncpy(p, str.c_str(), std::min(strlen(str.c_str()), len));
    }
    return rv ? VSCP_ERROR_SUCCESS : VSCP_ERROR_ERROR;
}

/*!
    \fn int vscphlp_convertEventExToString( vscpEventEx *pEvent,
                                                char *p )
    \brief Write VSCP data to a string.
*/
#ifdef WIN32
extern "C" DllExport int WINAPI EXPORT
vscphlp_convertEventExToString(vscpEventEx* pEvent, char* p, size_t len)
#else
extern "C" int
vscphlp_convertEventExToString(vscpEventEx* pEvent, char* p, size_t len)
#endif
{
    bool rv;

    std::string str;
    if ((rv = vscp_convertEventExToString(str, pEvent))) {
        memset(p, 0, len);
        strncpy(p, str.c_str(), std::min(strlen(str.c_str()), len));
    }
    return rv ? VSCP_ERROR_SUCCESS : VSCP_ERROR_ERROR;
}

/*!
    \fn int vscphlp_getVscpEventFromString( vscpEvent *pEvent,
                                            const char *p )
    \brief Get VSCP event from string.
*/
#ifdef WIN32
extern "C" DllExport int WINAPI EXPORT
vscphlp_setVscpEventFromString(vscpEvent* pEvent, const char* p)
#else
extern "C" int
vscphlp_setVscpEventFromString(vscpEvent* pEvent, const char* p)
#endif
{
    std::string str = std::string(p);
    return vscp_convertStringToEvent(pEvent, str) ? VSCP_ERROR_SUCCESS
                                                  : VSCP_ERROR_ERROR;
}

/*!
    \fn int vscphlp_convertStringToEvent( vscpEvent *pEvent,
                                            const char *p )
    \brief Get VSCP event from string.
*/
#ifdef WIN32
extern "C" DllExport int WINAPI EXPORT
vscphlp_convertStringToEvent(vscpEvent* pEvent, const char* p)
#else
extern "C" int
vscphlp_convertStringToEvent(vscpEvent* pEvent, const char* p)
#endif
{
    std::string str = std::string(p);
    return vscp_convertStringToEvent(pEvent, str) ? VSCP_ERROR_SUCCESS
                                                  : VSCP_ERROR_ERROR;
}

/*!
    \fn int vscphlp_setVscpEventExFromString( vscpEventEx *pEvent,
                                            const char *p )
    \brief Get VSCP event from string.
*/
#ifdef WIN32
extern "C" DllExport int WINAPI EXPORT
vscphlp_setVscpEventExFromString(vscpEventEx* pEvent, const char* p)
#else
extern "C" int
vscphlp_setVscpEventExFromString(vscpEventEx* pEvent, const char* p)
#endif
{
    std::string str = std::string(p);
    return vscp_convertStringToEventEx(pEvent, str) ? VSCP_ERROR_SUCCESS
                                                    : VSCP_ERROR_ERROR;
}

/*!
    \fn int vscphlp_convertStringToEventEx( vscpEventEx *pEvent,
                                            const char *p )
    \brief Get VSCP event from string.
*/
#ifdef WIN32
extern "C" DllExport int WINAPI EXPORT
vscphlp_convertStringToEventEx(vscpEventEx* pEventEx, const char* p)
#else
extern "C" int
vscphlp_convertStringToEventEx(vscpEventEx* pEventEx, const char* p)
#endif
{
    std::string str = std::string(p);
    return vscp_convertStringToEventEx(pEventEx, str) ? VSCP_ERROR_SUCCESS
                                                    : VSCP_ERROR_ERROR;
}

// * * * * *    D A T A C O D I N G   * * * * *

///////////////////////////////////////////////////////////////////////////////
//
//

#ifdef WIN32
extern "C" DllExport unsigned char WINAPI EXPORT
vscphlp_getMeasurementDataCoding(const vscpEvent* pEvent)
#else
extern "C" unsigned char
vscphlp_getMeasurementDataCoding(const vscpEvent* pEvent)
#endif
{
    return vscp_getMeasurementDataCoding(pEvent);
}

///////////////////////////////////////////////////////////////////////////////
//
//

#ifdef WIN32
extern "C" DllExport unsigned long long WINAPI EXPORT
vscphlp_getDataCodingBitArray(const unsigned char* pCode, int size)
#else
extern "C" unsigned long long
vscphlp_getDataCodingBitArray(const unsigned char* pCode, int size)
#endif
{
    return vscp_getDataCodingBitArray(pCode, size);
}

///////////////////////////////////////////////////////////////////////////////
//
//

#ifdef WIN32
extern "C" DllExport unsigned long long WINAPI EXPORT
vscphlp_getDataCodingInteger(const unsigned char* pCode, int size)
#else
extern "C" unsigned long long
vscphlp_getDataCodingInteger(const unsigned char* pCode, int size)
#endif
{
    return vscp_getDataCodingInteger(pCode, size);
}

///////////////////////////////////////////////////////////////////////////////
//
//

#ifdef WIN32
extern "C" DllExport double WINAPI EXPORT
vscphlp_getDataCodingNormalizedInteger(const unsigned char* pCode, int size)
#else
extern "C" double
vscphlp_getDataCodingNormalizedInteger(const unsigned char* pCode, int size)
#endif
{
    return vscp_getDataCodingNormalizedInteger(pCode, size);
}

///////////////////////////////////////////////////////////////////////////////
//
//

#ifdef WIN32
extern "C" DllExport int WINAPI EXPORT
vscphlp_getDataCodingString(const unsigned char* pCode,
                            unsigned char dataLength,
                            char* strResult,
                            size_t len)
#else
extern "C" int
vscphlp_getDataCodingString(const unsigned char* pCode,
                            unsigned char dataLength,
                            char* strResult,
                            size_t len)
#endif
{
    std::string str;

    if (NULL == pCode)
        return VSCP_ERROR_ERROR;
    if (NULL == strResult)
        return VSCP_ERROR_ERROR;

    bool rv = vscp_getDataCodingString(str, pCode, dataLength);
    memset(strResult, 0, len);
    strncpy(strResult, str.c_str(), std::min(strlen(str.c_str()), len));
    return rv ? VSCP_ERROR_SUCCESS : VSCP_ERROR_ERROR;
}

///////////////////////////////////////////////////////////////////////////////
//
//

#ifdef WIN32
extern "C" DllExport int WINAPI EXPORT
vscphlp_getVSCPMeasurementAsString(const vscpEvent* pEvent,
                                   char* pResult,
                                   size_t len)
#else
extern "C" int
vscphlp_getVSCPMeasurementAsString(const vscpEvent* pEvent,
                                   char* pResult,
                                   size_t len)
#endif
{
    std::string str;

    if (NULL == pEvent)
        return VSCP_ERROR_ERROR;

    bool rv = vscp_getMeasurementAsString(str, pEvent);
    memset(pResult, 0, len);
    strncpy(pResult, str.c_str(), std::min(strlen(str.c_str()), len));
    return rv ? VSCP_ERROR_SUCCESS : VSCP_ERROR_ERROR;
}

///////////////////////////////////////////////////////////////////////////////
//
//

#ifdef WIN32
extern "C" DllExport int WINAPI EXPORT
vscphlp_getVSCPMeasurementAsDouble(const vscpEvent* pEvent, double* pvalue)
#else
extern "C" int
vscphlp_getVSCPMeasurementAsDouble(const vscpEvent* pEvent, double* pvalue)
#endif
{
    std::string str;

    if (NULL == pEvent)
        return VSCP_ERROR_ERROR;

    return vscp_getMeasurementAsDouble(pvalue, pEvent) ? VSCP_ERROR_SUCCESS
                                                       : VSCP_ERROR_ERROR;
}

///////////////////////////////////////////////////////////////////////////////
//
//

#ifdef WIN32
extern "C" DllExport int WINAPI EXPORT
vscphlp_getVSCPMeasurementFloat64AsString(const vscpEvent* pEvent,
                                          char* pStrResult,
                                          size_t len)
#else
extern "C" int
vscphlp_getVSCPMeasurementFloat64AsString(const vscpEvent* pEvent,
                                          char* pStrResult,
                                          size_t len)
#endif
{
    std::string str;

    if (NULL == pEvent)
        return VSCP_ERROR_ERROR;

    bool rv = vscp_getMeasurementFloat64AsString(str, pEvent);
    memset(pStrResult, 0, len);
    strncpy(pStrResult, str.c_str(), std::min(strlen(str.c_str()), len));
    return rv ? VSCP_ERROR_SUCCESS : VSCP_ERROR_ERROR;
}

///////////////////////////////////////////////////////////////////////////////
//
//

#ifdef WIN32
extern "C" DllExport int WINAPI EXPORT
vscphlp_convertFloatToNormalizedEventData(unsigned char* pdata,
                                          unsigned short* psize,
                                          double value,
                                          unsigned char unit,
                                          unsigned char sensoridx)
#else
extern "C" int
vscphlp_convertFloatToNormalizedEventData(unsigned char* pdata,
                                          unsigned short* psize,
                                          double value,
                                          unsigned char unit,
                                          unsigned char sensoridx)
#endif
{
    std::string str;

    if (NULL == pdata)
        return VSCP_ERROR_ERROR;

    bool rv = vscp_convertFloatToNormalizedEventData(
      pdata, psize, value, unit, sensoridx);
    return rv ? VSCP_ERROR_SUCCESS : VSCP_ERROR_ERROR;
}

///////////////////////////////////////////////////////////////////////////////
//
//

#ifdef WIN32
extern "C" DllExport int WINAPI EXPORT
vscphlp_convertFloatToFloatEventData(unsigned char* pdata,
                                     unsigned short* psize,
                                     float value,
                                     unsigned char unit,
                                     unsigned char sensoridx)
#else
extern "C" int
vscphlp_convertFloatToFloatEventData(unsigned char* pdata,
                                     unsigned short* psize,
                                     float value,
                                     unsigned char unit,
                                     unsigned char sensoridx)
#endif
{
    std::string str;

    if (NULL == pdata)
        return VSCP_ERROR_ERROR;

    bool rv =
      vscp_convertFloatToFloatEventData(pdata, psize, value, unit, sensoridx);
    return rv ? VSCP_ERROR_SUCCESS : VSCP_ERROR_ERROR;
}

///////////////////////////////////////////////////////////////////////////////
// vscphlp_convertIntegerToNormalizedEventData
//

#ifdef WIN32
extern "C" DllExport int WINAPI EXPORT
vscphlp_convertIntegerToNormalizedEventData(unsigned char* pdata,
                                            unsigned short* psize,
                                            unsigned long long val64,
                                            unsigned char unit,
                                            unsigned char sensoridx)
#else
extern "C" int
vscphlp_convertIntegerToNormalizedEventData(unsigned char* pdata,
                                            unsigned short* psize,
                                            unsigned long long val64,
                                            unsigned char unit,
                                            unsigned char sensoridx)
#endif
{
    std::string str;

    if (NULL == pdata)
        return VSCP_ERROR_ERROR;
    if (NULL == psize)
        return VSCP_ERROR_ERROR;

    bool rv = vscp_convertIntegerToNormalizedEventData(
      pdata, psize, val64, unit, sensoridx);
    return rv ? VSCP_ERROR_SUCCESS : VSCP_ERROR_ERROR;
}

///////////////////////////////////////////////////////////////////////////////
// vscphlp_makeFloatMeasurementEvent
//

#ifdef WIN32
extern "C" DllExport int WINAPI EXPORT
vscphlp_makeFloatMeasurementEvent(vscpEvent* pEvent,
                                  float value,
                                  unsigned char unit,
                                  unsigned char sensoridx)
#else
extern "C" int
vscphlp_makeFloatMeasurementEvent(vscpEvent* pEvent,
                                  float value,
                                  unsigned char unit,
                                  unsigned char sensoridx)
#endif
{
    std::string str;

    if (NULL == pEvent) {
        return VSCP_ERROR_ERROR;
    }

    bool rv = vscp_makeFloatMeasurementEvent(pEvent, value, unit, sensoridx);
    return rv ? VSCP_ERROR_SUCCESS : VSCP_ERROR_ERROR;
}

///////////////////////////////////////////////////////////////////////////////
// vscphlp_makeFloatMeasurementEventEx
//

#ifdef WIN32
extern "C" DllExport int WINAPI EXPORT
vscphlp_makeFloatMeasurementEventEx(vscpEventEx* pEventEx,
                                    float value,
                                    unsigned char unit,
                                    unsigned char sensoridx)
#else
extern "C" int
vscphlp_makeFloatMeasurementEventEx(vscpEventEx* pEventEx,
                                    float value,
                                    unsigned char unit,
                                    unsigned char sensoridx)
#endif
{
    if (NULL == pEventEx) {
        return VSCP_ERROR_ERROR;
    }

    bool rv = vscp_makeFloatMeasurementEventEx(pEventEx, value, unit, sensoridx);
    return rv ? VSCP_ERROR_SUCCESS : VSCP_ERROR_ERROR;
}

///////////////////////////////////////////////////////////////////////////////
// vscphlp_makeFloatMeasurementEvent
//

#ifdef WIN32
extern "C" DllExport int WINAPI EXPORT
vscphlp_makeStringMeasurementEvent(vscpEvent* pEvent,
                                  float value,
                                  unsigned char unit,
                                  unsigned char sensoridx)
#else
extern "C" int
vscphlp_makeStringMeasurementEvent(vscpEvent* pEvent,
                                  float value,
                                  unsigned char unit,
                                  unsigned char sensoridx)
#endif
{
    if (NULL == pEvent) {
        return VSCP_ERROR_ERROR;
    }

    bool rv = vscp_makeStringMeasurementEvent(pEvent, value, unit, sensoridx);
    return rv ? VSCP_ERROR_SUCCESS : VSCP_ERROR_ERROR;
}

///////////////////////////////////////////////////////////////////////////////
// vscphlp_makeFloatMeasurementEvent
//

#ifdef WIN32
extern "C" DllExport int WINAPI EXPORT
vscphlp_makeStringMeasurementEventEx(vscpEventEx* pEventEx,
                                  float value,
                                  unsigned char unit,
                                  unsigned char sensoridx)
#else
extern "C" int
vscphlp_makeStringMeasurementEventEx(vscpEventEx* pEventEx,
                                  float value,
                                  unsigned char unit,
                                  unsigned char sensoridx)
#endif
{
    if (NULL == pEventEx) {
        return VSCP_ERROR_ERROR;
    }

    bool rv = vscp_makeStringMeasurementEventEx(pEventEx, value, unit, sensoridx);
    return rv ? VSCP_ERROR_SUCCESS : VSCP_ERROR_ERROR;
}

///////////////////////////////////////////////////////////////////////////////
// vscphlp_getMeasurementAsFloat
//

#ifdef WIN32
extern "C" DllExport int WINAPI EXPORT
vscphlp_getMeasurementAsFloat(const unsigned char* pNorm,
                              unsigned char length,
                              float* pResult)
#else
extern "C" int
vscphlp_getMeasurementAsFloat(const unsigned char* pNorm,
                              unsigned char length,
                              float* pResult)
#endif
{
    if (NULL == pNorm) {
        return VSCP_ERROR_ERROR;
    }

    if (NULL == pResult) {
        return VSCP_ERROR_ERROR;
    }

    *pResult = vscp_getMeasurementAsFloat(pNorm, length);
    return VSCP_ERROR_SUCCESS;
}

///////////////////////////////////////////////////////////////////////////////
// vscp_getMeasurementUnit
//

#ifdef WIN32
extern "C" DllExport int WINAPI EXPORT
vscphlp_getMeasurementUnit(const vscpEvent* pEvent)
#else
extern "C" int
vscphlp_getMeasurementUnit(const vscpEvent* pEvent)
#endif
{
    return vscp_getMeasurementUnit(pEvent);
}

///////////////////////////////////////////////////////////////////////////////
// vscp_getMeasurementSensorIndex
//

#ifdef WIN32
extern "C" DllExport int WINAPI EXPORT
vscphlp_getMeasurementSensorIndex(const vscpEvent* pEvent)
#else
extern "C" int
vscphlp_getMeasurementSensorIndex(const vscpEvent* pEvent)
#endif
{
    return vscp_getMeasurementSensorIndex(pEvent);
}

///////////////////////////////////////////////////////////////////////////////
// vscp_getMeasurementZone
//

#ifdef WIN32
extern "C" DllExport int WINAPI EXPORT
vscphlp_getMeasurementZone(const vscpEvent* pEvent)
#else
extern "C" int
vscphlp_getMeasurementZone(const vscpEvent* pEvent)
#endif
{
    return vscp_getMeasurementZone(pEvent);
}

///////////////////////////////////////////////////////////////////////////////
// vscp_getMeasurementSubZone
//

#ifdef WIN32
extern "C" DllExport int WINAPI EXPORT
vscphlp_getMeasurementSubZone(const vscpEvent* pEvent)
#else
extern "C" int
vscphlp_getMeasurementSubZone(const vscpEvent* pEvent)
#endif
{
    return vscp_getMeasurementSubZone(pEvent);
}

///////////////////////////////////////////////////////////////////////////////
// vscp_isMeasurement
//

#ifdef WIN32
extern "C" DllExport int WINAPI EXPORT
vscphlp_isMeasurement(const vscpEvent* pEvent)
#else
extern "C" int
vscphlp_isMeasurement(const vscpEvent* pEvent)
#endif
{
    return vscp_isMeasurement(pEvent) ? VSCP_ERROR_SUCCESS : VSCP_ERROR_ERROR;
}

///////////////////////////////////////////////////////////////////////////////
// vscphlp_convertEventToJSON
//

#ifdef WIN32
extern "C" DllExport int WINAPI EXPORT
vscphlp_convertEventToJSON(vscpEvent* pEvent, char* p, size_t len)
#else
extern "C" int
vscphlp_convertEventToJSON(vscpEvent* pEvent, char* p, size_t len)
#endif
{
    std::string str;

    // Do the conversion
    vscp_convertEventToJSON(str, pEvent);

    // Check if there is room for the JSON string
    if (len <= strlen(str.c_str()))
        return VSCP_ERROR_BUFFER_TO_SMALL;

    // Copy in JSON string
    memset(p, 0, len);
    strncpy(p, str.c_str(), std::min(strlen(str.c_str()), len));

    return VSCP_ERROR_SUCCESS;
}

///////////////////////////////////////////////////////////////////////////////
// vscphlp_convertEventExToJSON
//

#ifdef WIN32
extern "C" DllExport int WINAPI EXPORT
vscphlp_convertEventExToJSON(vscpEventEx* pEventEx, char* p, size_t len)
#else
extern "C" int
vscphlp_convertEventExToJSON(vscpEventEx* pEventEx, char* p, size_t len)
#endif
{
    std::string str;

    // Do the conversion
    vscp_convertEventExToJSON(str, pEventEx);

    // Check if there is room for the JSON string
    if (len <= strlen(str.c_str()))
        return VSCP_ERROR_BUFFER_TO_SMALL;

    // Copy in JSON string
    memset(p, 0, len);
    strncpy(p, str.c_str(), std::min(strlen(str.c_str()), len));

    return VSCP_ERROR_SUCCESS;
}

///////////////////////////////////////////////////////////////////////////////
// vscphlp_convertEventToXML
//

#ifdef WIN32
extern "C" DllExport int WINAPI EXPORT
vscphlp_convertEventToXML(vscpEvent* pEvent, char* p, size_t len)
#else
extern "C" int
vscphlp_convertEventToXML(vscpEvent* pEvent, char* p, size_t len)
#endif
{
    std::string str;

    // Do the conversion
    vscp_convertEventToXML(str, pEvent);

    // Check if there is room for the XML string
    if (len <= strlen(str.c_str()))
        return VSCP_ERROR_BUFFER_TO_SMALL;

    // Copy in XML string
    memset(p, 0, len);
    strncpy(p, str.c_str(), std::min(strlen(str.c_str()), len));

    return VSCP_ERROR_SUCCESS;
}

///////////////////////////////////////////////////////////////////////////////
// vscphlp_convertEventExToXML
//

#ifdef WIN32
extern "C" DllExport int WINAPI EXPORT
vscphlp_convertEventExToXML(vscpEventEx* pEventEx, char* p, size_t len)
#else
extern "C" int
vscphlp_convertEventExToXML(vscpEventEx* pEventEx, char* p, size_t len)
#endif
{
    std::string str;

    // Do the conversion
    vscp_convertEventExToXML(str, pEventEx);

    // Check if there is room for the XML string
    if (len <= strlen(str.c_str()))
        return VSCP_ERROR_BUFFER_TO_SMALL;

    // Copy in XML string
    memset(p, 0, len);
    strncpy(p, str.c_str(), std::min(strlen(str.c_str()), len));

    return VSCP_ERROR_SUCCESS;
}

///////////////////////////////////////////////////////////////////////////////
// vscphlp_convertEventToHTML
//

#ifdef WIN32
extern "C" DllExport int WINAPI EXPORT
vscphlp_convertEventToHTML(vscpEvent* pEvent, char* p, size_t len)
#else
extern "C" int
vscphlp_convertEventToHTML(vscpEvent* pEvent, char* p, size_t len)
#endif
{
    std::string str;

    // Do the conversion
    vscp_convertEventToHTML(str, pEvent);

    // Check if there is room for the HTML string
    if (len <= strlen(str.c_str()))
        return VSCP_ERROR_BUFFER_TO_SMALL;

    // Copy in HTML string
    memset(p, 0, len);
    strncpy(p, str.c_str(), std::min(strlen(str.c_str()), len));

    return VSCP_ERROR_SUCCESS;
}

///////////////////////////////////////////////////////////////////////////////
// vscphlp_convertEventExToHTML
//

#ifdef WIN32
extern "C" DllExport int WINAPI EXPORT
vscphlp_convertEventExToHTML(vscpEventEx* pEventEx, char* p, size_t len)
#else
extern "C" int
vscphlp_convertEventExToHTML(vscpEventEx* pEventEx, char* p, size_t len)
#endif
{
    std::string str;

    // Do the conversion
    vscp_convertEventExToHTML(str, pEventEx);

    // Check if there is room for the HTML string
    if (len <= strlen(str.c_str()))
        return VSCP_ERROR_BUFFER_TO_SMALL;

    // Copy in HTML string
    memset(p, 0, len);
    strncpy(p, str.c_str(), std::min(strlen(str.c_str()), len));

    return VSCP_ERROR_SUCCESS;
}

///////////////////////////////////////////////////////////////////////////////
// vscphlp_convertLevel1MeasuremenToLevel2Double
//

#ifdef WIN32
extern "C" DllExport int WINAPI EXPORT
vscphlp_convertLevel1MeasuremenToLevel2Double(vscpEvent* pEventLevel1)
#else
extern "C" int
vscphlp_convertLevel1MeasuremenToLevel2Double(vscpEvent* pEventLevel1)
#endif
{
    return (vscp_convertLevel1MeasuremenToLevel2Double(pEventLevel1)
              ? VSCP_ERROR_SUCCESS
              : VSCP_ERROR_ERROR);
}

///////////////////////////////////////////////////////////////////////////////
// vscphlp_convertLevel1MeasuremenToLevel2DoubleEx
//

#ifdef WIN32
extern "C" DllExport int WINAPI EXPORT
vscphlp_convertLevel1MeasuremenToLevel2DoubleEx(vscpEventEx* pEventEx)
#else
extern "C" int
vscphlp_convertLevel1MeasuremenToLevel2DoubleEx(vscpEventEx* pEventEx)
#endif
{
    return (vscp_convertLevel1MeasuremenToLevel2DoubleEx(pEventEx)
              ? VSCP_ERROR_SUCCESS
              : VSCP_ERROR_ERROR);
}

///////////////////////////////////////////////////////////////////////////////
// vscphlp_convertLevel1MeasuremenToLevel2String
//

#ifdef WIN32
extern "C" DllExport int WINAPI EXPORT
vscphlp_convertLevel1MeasuremenToLevel2String(vscpEvent* pEventLevel1)
#else
extern "C" int
vscphlp_convertLevel1MeasuremenToLevel2String(vscpEvent* pEventLevel1)
#endif
{
    return (vscp_convertLevel1MeasuremenToLevel2String(pEventLevel1)
              ? VSCP_ERROR_SUCCESS
              : VSCP_ERROR_ERROR);
}

///////////////////////////////////////////////////////////////////////////////
// vscphlp_convertLevel1MeasuremenToLevel2StringEx
//

#ifdef WIN32
extern "C" DllExport int WINAPI EXPORT
vscphlp_convertLevel1MeasuremenToLevel2StringEx(vscpEventEx* pEventEx)
#else
extern "C" int
vscphlp_convertLevel1MeasuremenToLevel2StringEx(vscpEventEx* pEventEx)
#endif
{
    return (vscp_convertLevel1MeasuremenToLevel2StringEx(pEventEx)
              ? VSCP_ERROR_SUCCESS
              : VSCP_ERROR_ERROR);
}

///////////////////////////////////////////////////////////////////////////////
// vscphlp_makeLevel2FloatMeasurementEvent
//

#ifdef WIN32
extern "C" DllExport int WINAPI EXPORT
vscphlp_makeLevel2FloatMeasurementEvent(vscpEvent* pEvent,
                                        uint16_t type,
                                        double value,
                                        uint8_t unit,
                                        uint8_t sensoridx,
                                        uint8_t zone,
                                        uint8_t subzone)
#else
extern "C" int
vscphlp_makeLevel2FloatMeasurementEvent(vscpEvent* pEvent,
                                        uint16_t type,
                                        double value,
                                        uint8_t unit,
                                        uint8_t sensoridx,
                                        uint8_t zone,
                                        uint8_t subzone)
#endif
{
    return (vscp_makeLevel2FloatMeasurementEvent(
              pEvent, type, value, unit, sensoridx, zone, subzone)
              ? VSCP_ERROR_SUCCESS
              : VSCP_ERROR_ERROR);
}

///////////////////////////////////////////////////////////////////////////////
// vscphlp_makeLevel2FloatMeasurementEventEx
//

#ifdef WIN32
extern "C" DllExport int WINAPI EXPORT
vscphlp_makeLevel2FloatMeasurementEventEx(vscpEventEx* pEventEx,
                                        uint16_t type,
                                        double value,
                                        uint8_t unit,
                                        uint8_t sensoridx,
                                        uint8_t zone,
                                        uint8_t subzone)
#else
extern "C" int
vscphlp_makeLevel2FloatMeasurementEventEx(vscpEventEx* pEventEx,
                                        uint16_t type,
                                        double value,
                                        uint8_t unit,
                                        uint8_t sensoridx,
                                        uint8_t zone,
                                        uint8_t subzone)
#endif
{
    return (vscp_makeLevel2FloatMeasurementEventEx(
              pEventEx, type, value, unit, sensoridx, zone, subzone)
              ? VSCP_ERROR_SUCCESS
              : VSCP_ERROR_ERROR);
}

///////////////////////////////////////////////////////////////////////////////
// vscphlp_makeLevel2StringMeasurementEvent
//

#ifdef WIN32
extern "C" DllExport int WINAPI EXPORT
vscphlp_makeLevel2StringMeasurementEvent(vscpEvent* pEvent,
                                         uint16_t type,
                                         double value,
                                         uint8_t unit,
                                         uint8_t sensoridx,
                                         uint8_t zone,
                                         uint8_t subzone)
#else
extern "C" int
vscphlp_makeLevel2StringMeasurementEvent(vscpEvent* pEvent,
                                         uint16_t type,
                                         double value,
                                         uint8_t unit,
                                         uint8_t sensoridx,
                                         uint8_t zone,
                                         uint8_t subzone)
#endif
{
    return (vscp_makeLevel2FloatMeasurementEvent(
              pEvent, type, value, unit, sensoridx, zone, subzone)
              ? VSCP_ERROR_SUCCESS
              : VSCP_ERROR_ERROR);
}

///////////////////////////////////////////////////////////////////////////////
// vscphlp_makeLevel2StringMeasurementEventEx
//

#ifdef WIN32
extern "C" DllExport int WINAPI EXPORT
vscphlp_makeLevel2StringMeasurementEventEx(vscpEventEx* pEventEx,
                                            uint16_t type,
                                            double value,
                                            uint8_t unit,
                                            uint8_t sensoridx,
                                            uint8_t zone,
                                            uint8_t subzone)
#else
extern "C" int
vscphlp_makeLevel2StringMeasurementEventEx(vscpEvent* pEventEx,
                                            uint16_t type,
                                            double value,
                                            uint8_t unit,
                                            uint8_t sensoridx,
                                            uint8_t zone,
                                            uint8_t subzone)
#endif
{
    return (vscp_makeLevel2FloatMeasurementEvent(
              pEventEx, type, value, unit, sensoridx, zone, subzone)
              ? VSCP_ERROR_SUCCESS
              : VSCP_ERROR_ERROR);
}

///////////////////////////////////////////////////////////////////////////////
// vscphlp_getTimeString
//

#ifdef WIN32
extern "C" DllExport int WINAPI EXPORT
vscphlp_getTimeString(char* buf, size_t buf_len, time_t* t)
#else
extern "C" int
vscphlp_getTimeString(char* buf, size_t buf_len, time_t* t)
#endif
{
    // Check pointers
    if (NULL == buf)
        return VSCP_ERROR_PARAMETER;
    if (NULL == t)
        return VSCP_ERROR_PARAMETER;

    return vscp_getTimeString(buf, buf_len, t) ? VSCP_ERROR_SUCCESS
                                               : VSCP_ERROR_ERROR;
}

///////////////////////////////////////////////////////////////////////////////
// vscphlp_getISOTimeString
//

#ifdef WIN32
extern "C" DllExport int WINAPI EXPORT
vscphlp_getISOTimeString(char* buf, size_t buf_len, time_t* t)
#else
extern "C" int
vscphlp_getISOTimeString(char* buf, size_t buf_len, time_t* t)
#endif
{
    // Check pointers
    if (NULL == buf)
        return VSCP_ERROR_PARAMETER;
    if (NULL == t)
        return VSCP_ERROR_PARAMETER;

    return vscp_getISOTimeString(buf, buf_len, t) ? VSCP_ERROR_SUCCESS
                                                  : VSCP_ERROR_ERROR;
}

///////////////////////////////////////////////////////////////////////////////
// vscphlp_getDateStringFromEvent
//

#ifdef WIN32
extern "C" DllExport int WINAPI EXPORT
vscphlp_getDateStringFromEvent(char* buf, size_t buf_len, vscpEvent* pEvent)
#else
extern "C" int
vscphlp_getDateStringFromEvent(char* buf, size_t buf_len, vscpEvent* pEvent)
#endif
{
    // Check pointers
    if (NULL == buf)
        return VSCP_ERROR_PARAMETER;
    if (NULL == pEvent)
        return VSCP_ERROR_PARAMETER;

    std::string str;
    vscp_getDateStringFromEvent(str, pEvent);
    if (0 == str.length())
        return VSCP_ERROR_ERROR;

    memcpy(buf, (const char*)str.c_str(), std::min(buf_len, str.length()));
    return VSCP_ERROR_SUCCESS;
}

///////////////////////////////////////////////////////////////////////////////
// vscphlp_getDateStringFromEventEx
//

#ifdef WIN32
extern "C" DllExport int WINAPI EXPORT
vscphlp_getDateStringFromEventEx(char* buf,
                                 size_t buf_len,
                                 vscpEventEx* pEventEx)
#else
extern "C" int
vscphlp_getDateStringFromEventEx(char* buf,
                                 size_t buf_len,
                                 vscpEventEx* pEventEx)
#endif
{
    // Check pointers
    if (NULL == buf)
        return VSCP_ERROR_PARAMETER;
    if (NULL == pEventEx)
        return VSCP_ERROR_PARAMETER;

    std::string str;
    vscp_getDateStringFromEventEx(str, pEventEx);
    if (0 == str.length())
        return VSCP_ERROR_ERROR;

    memcpy(buf, (const char*)str.c_str(), std::min(buf_len, str.length()));
    return VSCP_ERROR_SUCCESS;
}