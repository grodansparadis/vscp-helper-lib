// dlldrvobj.cpp : Defines the initialization routines for the DLL.
//
//
// This file is part of the VSCP (http://www.vscp.org)
//
// The MIT License (MIT)
//
// Copyright (c) 2000-2017 Ake Hedman, Grodans Paradis AB <info@grodansparadis.com>
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

#ifdef WIN32
#include <winsock2.h>
#endif

#include "stdio.h"
#include "stdlib.h"
#include "canal_macro.h"
#include "dlldrvobj.h"



////////////////////////////////////////////////////////////////////////////
// CHelpDllObj construction

CHelpDllObj::CHelpDllObj()
{
	m_instanceCounter = 0;

	// Init the driver array
	for ( int i = 0; i<VSCP_HELPER_MAX_OPEN; i++ ) {
		m_drvObjArray[ i ] = NULL;
	}
}


CHelpDllObj::~CHelpDllObj()
{
  LOCK_MUTEX(m_mutex);

	for ( int i = 0; i<VSCP_HELPER_MAX_OPEN; i++ ) {

		if ( NULL != m_drvObjArray[ i ] ) {

			VscpRemoteTcpIf *pdrvObj =  getDriverObject( i );
			if ( NULL != pdrvObj ) {
				pdrvObj->doCmdClose();
				delete m_drvObjArray[ i ];
				m_drvObjArray[ i ] = NULL;
			}
		}
	}

    UNLOCK_MUTEX(m_mutex);

}



///////////////////////////////////////////////////////////////////////////////
// addDriverObject
//

long CHelpDllObj::addDriverObject( VscpRemoteTcpIf *pdrvObj )
{
	long h = 0;

    LOCK_MUTEX(m_mutex);
	for ( int i=0; i<VSCP_HELPER_MAX_OPEN; i++ ) {

		if ( NULL == m_drvObjArray[ i ] ) {

			m_drvObjArray[ i ] = pdrvObj;
			h = i + 1681;
			break;

		}

	}

    UNLOCK_MUTEX(m_mutex);

	return h;
}


///////////////////////////////////////////////////////////////////////////////
// getDriverObject
//

VscpRemoteTcpIf * CHelpDllObj::getDriverObject( long h )
{
	long idx = h - 1681;

	// Check if valid handle
	if ( idx < 0 ) return NULL;
	if ( idx >= VSCP_HELPER_MAX_OPEN ) return NULL;
	return m_drvObjArray[ idx ];
}


///////////////////////////////////////////////////////////////////////////////
// removeDriverObject
//

void CHelpDllObj::removeDriverObject( long h )
{
	long idx = h - 1681;

	// Check if valid handle
	if ( idx < 0 ) return;
	if ( idx >= VSCP_HELPER_MAX_OPEN ) return;

	//LOCK_MUTEX( m_objMutex );
    LOCK_MUTEX(m_mutex);
	if ( NULL != m_drvObjArray[ idx ] )
    {
        delete m_drvObjArray[ idx ];
    }
	m_drvObjArray[ idx ] = NULL;
	//UNLOCK_MUTEX( m_objMutex );
    UNLOCK_MUTEX(m_mutex);
}

///////////////////////////////////////////////////////////////////////////////
// InitInstance

BOOL CHelpDllObj::InitInstance()
{
	m_instanceCounter++;
	return TRUE;
}
