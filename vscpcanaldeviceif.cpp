// VscpCanalDeviceIf.cpp : Defines the initialization routines for the DLL.
//
// This file is part of the VSCP (http://www.vscp.org)
//
// The MIT License (MIT)
//
// Copyright (C) 2000-2019 Ake Hedman, Grodans Paradis AB
// <info@grodansparadis.com>
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

#include <string>

#include <dlfcn.h>
#include <syslog.h>
#include <unistd.h>

#include <canal.h>
#include <canal_macro.h>
#include <canaldlldef.h>
#include <vscpcanaldeviceif.h>

VscpCanalDeviceIf::VscpCanalDeviceIf()
{
    // Open syslog
    openlog("node-canal", LOG_CONS, LOG_LOCAL0);

    m_openHandle = 0;
}

VscpCanalDeviceIf::~VscpCanalDeviceIf()
{
    // Close syslog
    closelog();
}

///////////////////////////////////////////////////////////////////////////////
// init
//

int
VscpCanalDeviceIf::init(std::string jsonInit)
{
    return CANAL_ERROR_SUCCESS;
}

// -------------------------------------------------

int
VscpCanalDeviceIf::init(std::string strpath,
                        std::string strparam,
                        uint32_t flags,
                        bool bAsync)
{
    const char *dlsym_error;

    m_openHandle = 0;

    // Save config data
    m_strPath      = strpath;
    m_strParameter = strparam;
    m_deviceFlags  = flags;

    // Load dynamic library
    m_hdll = dlopen(strpath.c_str(), RTLD_LAZY);
    if (!m_hdll) {
        syslog(LOG_ERR,
               "Devicethread: Unable to load dynamic library. path = %s",
               m_strPath.c_str());
        return CANAL_ERROR_PARAMETER;
    }

    // Now find methods in library
    syslog(LOG_INFO, "Loading level I driver: %s", m_strPath.c_str());

    // * * * * CANAL OPEN * * * *
    m_proc_CanalOpen = (LPFNDLL_CANALOPEN)dlsym(m_hdll, "CanalOpen");
    dlsym_error      = dlerror();

    if (dlsym_error) {
        // Free the library
        syslog(LOG_DEBUG,
               "%s : Unable to get dl entry for CanalOpen.",
               m_strPath.c_str());
        return CANAL_ERROR_LIBRARY;
    }

    // * * * * CANAL CLOSE * * * *
    m_proc_CanalClose = (LPFNDLL_CANALCLOSE)dlsym(m_hdll, "CanalClose");
    dlsym_error       = dlerror();
    if (dlsym_error) {
        // Free the library
        syslog(LOG_ERR,
               "%s: Unable to get dl entry for CanalClose.",
               m_strPath.c_str());
        dlclose(m_hdll);
        return CANAL_ERROR_LIBRARY;
    }

    // * * * * CANAL GETLEVEL * * * *
    m_proc_CanalGetLevel =
      (LPFNDLL_CANALGETLEVEL)dlsym(m_hdll, "CanalGetLevel");
    dlsym_error = dlerror();
    if (dlsym_error) {
        // Free the library
        syslog(LOG_ERR,
               "%s: Unable to get dl entry for CanalGetLevel.",
               m_strPath.c_str());
        dlclose(m_hdll);
        return CANAL_ERROR_LIBRARY;
    }

    // * * * * CANAL SEND * * * *
    m_proc_CanalSend = (LPFNDLL_CANALSEND)dlsym(m_hdll, "CanalSend");
    dlsym_error      = dlerror();
    if (dlsym_error) {
        // Free the library
        syslog(LOG_ERR,
               "%s: Unable to get dl entry for CanalSend.",
               m_strPath.c_str());
        dlclose(m_hdll);
        return CANAL_ERROR_LIBRARY;
    }

    // * * * * CANAL DATA AVAILABLE * * * *
    m_proc_CanalDataAvailable =
      (LPFNDLL_CANALDATAAVAILABLE)dlsym(m_hdll, "CanalDataAvailable");
    dlsym_error = dlerror();
    if (dlsym_error) {
        // Free the library
        syslog(LOG_ERR,
               "%s: Unable to get dl entry for CanalDataAvailable.",
               m_strPath.c_str());
        dlclose(m_hdll);
        return CANAL_ERROR_LIBRARY;
    }

    // * * * * CANAL RECEIVE * * * *
    m_proc_CanalReceive = (LPFNDLL_CANALRECEIVE)dlsym(m_hdll, "CanalReceive");
    dlsym_error         = dlerror();
    if (dlsym_error) {
        // Free the library
        syslog(LOG_ERR,
               "%s: Unable to get dl entry for CanalReceive.",
               m_strPath.c_str());
        dlclose(m_hdll);
        return CANAL_ERROR_LIBRARY;
    }

    // * * * * CANAL GET STATUS * * * *
    m_proc_CanalGetStatus =
      (LPFNDLL_CANALGETSTATUS)dlsym(m_hdll, "CanalGetStatus");
    dlsym_error = dlerror();
    if (dlsym_error) {
        // Free the library
        syslog(LOG_ERR,
               "%s: Unable to get dl entry for CanalGetStatus.",
               m_strPath.c_str());
        dlclose(m_hdll);
        return CANAL_ERROR_LIBRARY;
    }

    // * * * * CANAL GET STATISTICS * * * *
    m_proc_CanalGetStatistics =
      (LPFNDLL_CANALGETSTATISTICS)dlsym(m_hdll, "CanalGetStatistics");
    dlsym_error = dlerror();
    if (dlsym_error) {
        // Free the library
        syslog(LOG_ERR,
               "%s: Unable to get dl entry for CanalGetStatistics.",
               m_strPath.c_str());
        dlclose(m_hdll);
        return CANAL_ERROR_LIBRARY;
    }

    // * * * * CANAL SET FILTER * * * *
    m_proc_CanalSetFilter =
      (LPFNDLL_CANALSETFILTER)dlsym(m_hdll, "CanalSetFilter");
    dlsym_error = dlerror();
    if (dlsym_error) {
        // Free the library
        syslog(LOG_ERR,
               "%s: Unable to get dl entry for CanalSetFilter.",
               m_strPath.c_str());
        dlclose(m_hdll);
        return CANAL_ERROR_LIBRARY;
    }

    // * * * * CANAL SET MASK * * * *
    m_proc_CanalSetMask = (LPFNDLL_CANALSETMASK)dlsym(m_hdll, "CanalSetMask");
    dlsym_error         = dlerror();
    if (dlsym_error) {
        // Free the library
        syslog(LOG_ERR,
               "%s: Unable to get dl entry for CanalSetMask.",
               m_strPath.c_str());
        dlclose(m_hdll);
        return CANAL_ERROR_LIBRARY;
    }

    // * * * * CANAL GET VERSION * * * *
    m_proc_CanalGetVersion =
      (LPFNDLL_CANALGETVERSION)dlsym(m_hdll, "CanalGetVersion");
    dlsym_error = dlerror();
    if (dlsym_error) {
        // Free the library
        syslog(LOG_ERR,
               "%s: Unable to get dl entry for CanalGetVersion.",
               m_strPath.c_str());
        dlclose(m_hdll);
        return CANAL_ERROR_LIBRARY;
    }

    // * * * * CANAL GET DLL VERSION * * * *
    m_proc_CanalGetDllVersion =
      (LPFNDLL_CANALGETDLLVERSION)dlsym(m_hdll, "CanalGetDllVersion");
    dlsym_error = dlerror();
    if (dlsym_error) {
        // Free the library
        syslog(LOG_ERR,
               "%s: Unable to get dl entry for CanalGetDllVersion.",
               m_strPath.c_str());
        dlclose(m_hdll);
        return CANAL_ERROR_LIBRARY;
    }

    // * * * * CANAL GET VENDOR STRING * * * *
    m_proc_CanalGetVendorString =
      (LPFNDLL_CANALGETVENDORSTRING)dlsym(m_hdll, "CanalGetVendorString");
    dlsym_error = dlerror();
    if (dlsym_error) {
        // Free the library
        syslog(LOG_ERR,
               "%s: Unable to get dl entry for CanalGetVendorString.",
               m_strPath.c_str());
        dlclose(m_hdll);
        return CANAL_ERROR_LIBRARY;
    }

    // ******************************
    //     Generation 2 Methods
    // ******************************

    // * * * * CANAL BLOCKING SEND * * * *
    m_proc_CanalBlockingSend =
      (LPFNDLL_CANALBLOCKINGSEND)dlsym(m_hdll, "CanalBlockingSend");
    dlsym_error = dlerror();
    if (dlsym_error) {
        syslog(LOG_ERR,
               "%s: Unable to get dl entry for CanalBlockingSend. Probably "
               "Generation 1 driver.",
               m_strPath.c_str());
        m_proc_CanalBlockingSend = NULL;
    }

    // * * * * CANAL BLOCKING RECEIVE * * * *
    m_proc_CanalBlockingReceive =
      (LPFNDLL_CANALBLOCKINGRECEIVE)dlsym(m_hdll, "CanalBlockingReceive");
    dlsym_error = dlerror();
    if (dlsym_error) {
        syslog(LOG_ERR,
               "%s: Unable to get dl entry for CanalBlockingReceive. "
               "Probably Generation 1 driver.",
               m_strPath.c_str());
        m_proc_CanalBlockingReceive = NULL;
    }

    // * * * * CANAL GET DRIVER INFO * * * *
    m_proc_CanalGetdriverInfo =
      (LPFNDLL_CANALGETDRIVERINFO)dlsym(m_hdll, "CanalGetDriverInfo");
    dlsym_error = dlerror();
    if (dlsym_error) {
        syslog(LOG_ERR,
               "%s: Unable to get dl entry for CanalGetDriverInfo. "
               "Probably Generation 1 driver.",
               m_strPath.c_str());
        m_proc_CanalGetdriverInfo = NULL;
    }

    return CANAL_ERROR_SUCCESS;
}

///////////////////////////////////////////////////////////////////////////////
// CanalOpen
//

int
VscpCanalDeviceIf::CanalOpen()
{
    // Must NOT be open
    if (0 != m_openHandle) {
        return CANAL_ERROR_NOT_OPEN;
    }

    // Open the device
    m_openHandle =
      m_proc_CanalOpen((const char *)m_strParameter.c_str(), m_deviceFlags);

    // Check if the driver opened properly
    if (m_openHandle <= 0) {
        syslog(LOG_ERR,
               "Failed to open driver. Will not use it! %ld [%s] ",
               m_openHandle,
               m_strPath.c_str());
        dlclose(m_hdll);
        return CANAL_ERROR_NOT_OPEN;
    }

    // Get Driver Level
    // m_driverLevel = m_proc_CanalGetLevel(m_openHandle);

    return CANAL_ERROR_SUCCESS;
}

///////////////////////////////////////////////////////////////////////////////
// CanalClose
//

int
VscpCanalDeviceIf::CanalClose()
{

    // Must be open
    if (0 == m_openHandle) {
        return CANAL_ERROR_NOT_OPEN;
    }

    int rv = m_proc_CanalClose(m_openHandle);
    if (CANAL_ERROR_SUCCESS != rv) {
        return rv;
    }

    return CANAL_ERROR_SUCCESS;
}

///////////////////////////////////////////////////////////////////////////////
// CanalSend
//

int
VscpCanalDeviceIf::CanalSend(const PCANALMSG pCanMsg)
{
    // Must be open
    if (0 == m_openHandle) {
        return CANAL_ERROR_NOT_OPEN;
    }

    int rv = m_proc_CanalSend(m_openHandle, pCanMsg);
    if (CANAL_ERROR_SUCCESS != rv) {
        return rv;
    }
    return CANAL_ERROR_SUCCESS;
}

int
VscpCanalDeviceIf::CanalSend(std::string strObj, uint8_t nFormat)
{
    canalMsg CanMsg;

    // Must be open
    if (0 == m_openHandle) {
        return CANAL_ERROR_NOT_OPEN;
    }

    int rv = m_proc_CanalSend(m_openHandle, &CanMsg);
    if (CANAL_ERROR_SUCCESS != rv) {
        return rv;
    }
    return CANAL_ERROR_SUCCESS;
}

///////////////////////////////////////////////////////////////////////////////
// CanalBlockingSend
//

int
VscpCanalDeviceIf::CanalBlockingSend(std::string &strCanMsg,
                                     uint32_t timeout,
                                     uint8_t nFormat)
{
    canalMsg CanMsg;

    // Check if generation 2
    if (NULL == m_proc_CanalBlockingSend) {
        return CANAL_ERROR_LIBRARY;
    }

    // Must be open
    if (0 == m_openHandle) {
        return CANAL_ERROR_NOT_OPEN;
    }

    int rv = m_proc_CanalBlockingSend(m_openHandle, &CanMsg, timeout);
    if (CANAL_ERROR_SUCCESS != rv) {
        return rv;
    }

    return CANAL_ERROR_SUCCESS;
}

///////////////////////////////////////////////////////////////////////////////
// CanalReceive
//

int
VscpCanalDeviceIf::CanalReceive(std::string &strCanMsg, uint8_t nFormat)
{
    canalMsg CanMsg;

    // Must be open
    if (0 == m_openHandle) {
        return CANAL_ERROR_NOT_OPEN;
    }

    int rv = m_proc_CanalReceive(m_openHandle, &CanMsg);
    if (CANAL_ERROR_SUCCESS != rv) {
        return rv;
    }
    return CANAL_ERROR_SUCCESS;
}

///////////////////////////////////////////////////////////////////////////////
// CanalBlockingReceive
//

int
VscpCanalDeviceIf::CanalBlockingReceive(std::string &strCanMsg,
                                        uint32_t timeout,
                                        uint8_t nFormat)
{
    canalMsg CanMsg;

    // Must be open
    if (0 == m_openHandle) {
        return CANAL_ERROR_NOT_OPEN;
    }

    int rv = m_proc_CanalBlockingReceive(m_openHandle, &CanMsg, timeout);
    if (CANAL_ERROR_SUCCESS != rv) {
        return rv;
    }
    return CANAL_ERROR_SUCCESS;
}

///////////////////////////////////////////////////////////////////////////////
// CanalDataAvailable
//

int
VscpCanalDeviceIf::CanalDataAvailable()
{
    int rv = m_proc_CanalDataAvailable(m_openHandle);
    return rv;
}

///////////////////////////////////////////////////////////////////////////////
// CanalGetStatus
//

int
VscpCanalDeviceIf::CanalGetStatus(std::string &jsonStatus, uint8_t nFormat)
{
    canalStatus CanStatus;

    // Must be open
    if (0 == m_openHandle) {
        return CANAL_ERROR_NOT_OPEN;
    }

    int rv = m_proc_CanalGetStatus(m_openHandle, &CanStatus);
    if (CANAL_ERROR_SUCCESS != rv) {
        return rv;
    }
    return CANAL_ERROR_SUCCESS;
}

///////////////////////////////////////////////////////////////////////////////
// CanalGetStatistics
//

int
VscpCanalDeviceIf::CanalGetStatistics(std::string &jsonStatistics,
                                      uint8_t nFormat)
{
    canalStatistics CanalStatistics;

      // Must be open
      if (0 == m_openHandle)
    {
        return CANAL_ERROR_NOT_OPEN;
    }

    int rv = m_proc_CanalGetStatistics(m_openHandle, &CanalStatistics);
    if (CANAL_ERROR_SUCCESS != rv) {
        return rv;
    }
    return CANAL_ERROR_SUCCESS;
}

///////////////////////////////////////////////////////////////////////////////
// CanalSetFilter
//

int
VscpCanalDeviceIf::CanalSetFilter(uint32_t filter)
{
    // Must be open
    if (0 == m_openHandle) {
        return CANAL_ERROR_NOT_OPEN;
    }

    int rv = m_proc_CanalSetFilter(m_openHandle, filter);
    if (CANAL_ERROR_SUCCESS != rv) {
        return rv;
    }
    return CANAL_ERROR_SUCCESS;
}

///////////////////////////////////////////////////////////////////////////////
// CanalSetMask
//

int
VscpCanalDeviceIf::CanalSetMask(uint32_t mask)
{
    // Must be open
    if (0 == m_openHandle) {
        return CANAL_ERROR_NOT_OPEN;
    }

    int rv = m_proc_CanalSetMask(m_openHandle, mask);
    if (CANAL_ERROR_SUCCESS != rv) {
        return rv;
    }
    return CANAL_ERROR_SUCCESS;
}

///////////////////////////////////////////////////////////////////////////////
// CanalSetBaudrate
//

int
VscpCanalDeviceIf::CanalSetBaudrate(uint32_t baudrate)
{
    // Must be open
    if (0 == m_openHandle) {
        return CANAL_ERROR_NOT_OPEN;
    }

    int rv = m_proc_CanalSetBaudrate(m_openHandle, baudrate);
    if (CANAL_ERROR_SUCCESS != rv) {
        return rv;
    }
    return CANAL_ERROR_SUCCESS;
}

///////////////////////////////////////////////////////////////////////////////
// CanalGetVersion
//

uint32_t
VscpCanalDeviceIf::CanalGetVersion(void)
{
    return m_proc_CanalGetVersion();
}

///////////////////////////////////////////////////////////////////////////////
// CanalGetDllVersion
//

uint32_t
VscpCanalDeviceIf::CanalGetDllVersion(void)
{
    return m_proc_CanalGetDllVersion();
}

///////////////////////////////////////////////////////////////////////////////
// CanalGetVendorString
//

const char *
VscpCanalDeviceIf::CanalGetVendorString(void)
{
    return m_proc_CanalGetVendorString();
}

///////////////////////////////////////////////////////////////////////////////
// CanalGetDriverInfo
//

const char *
VscpCanalDeviceIf::CanalGetDriverInfo(void)
{
    // Check if generation 2
    if (NULL == m_proc_CanalGetdriverInfo) {
        return NULL;
    }

    return m_proc_CanalGetdriverInfo();
}