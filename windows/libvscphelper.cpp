// VSCP helper dll.cpp : Defines the initialization routines for the DLL.
//
// This file is part of the VSCP (http://www.vscp.org) 
//
// The MIT License (MIT)
// 
// Copyright (c) 2000-2021 Ake Hedman, the VSCP Project <info@grodansparadis.com>
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
#include <pch.h>
#endif

#include <map>
#include <string>

#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>

#include <vscphelper.h>
#include <vscpremotetcpif.h>

#include <canal.h>
#include <canal_macro.h>
#include <vscpremotetcpif.h>

#include <libvscphelper.h>

static HANDLE hThisInstDll = NULL;

// This map holds driver handles/objects
static std::map<long, VscpRemoteTcpIf*> g_ifMap;

// Mutex for the map object
static pthread_mutex_t g_mapMutex;

///////////////////////////////////////////////////////////////////////////////
// DllMain
//

BOOL APIENTRY DllMain( HANDLE hInstDll, 
                       DWORD  ul_reason_for_call, 
                       LPVOID lpReserved )
{
	switch( ul_reason_for_call ) {

		case DLL_PROCESS_ATTACH:
      hThisInstDll = hInstDll;
      pthread_mutex_init(&g_mapMutex, NULL);
			break;

		case DLL_THREAD_ATTACH:
			break;

		case DLL_THREAD_DETACH:
      // Clear up orphans if not empty
      if (!g_ifMap.empty()) {

          // Remove orphan objects

          LOCK_MUTEX(g_mapMutex);

          for (std::map<long, VscpRemoteTcpIf*>::iterator it =
                  g_ifMap.begin();
                  it != g_ifMap.end();
                  ++it) {

              VscpRemoteTcpIf* pvscpif = it->second;
              if (NULL != pvscpif) {
                  pvscpif->doCmdClose();
                  delete pvscpif;
                  pvscpif = NULL;
              }
          }

          g_ifMap.clear(); // Remove all items

          UNLOCK_MUTEX(g_mapMutex);
      }

      pthread_mutex_destroy(&g_mapMutex);
 			break;

		case DLL_PROCESS_DETACH:
 			break;
   }

	return TRUE;
}

///////////////////////////////////////////////////////////////////////////////
// addDriverObject
//

long
addDriverObject(VscpRemoteTcpIf* pvscpif)
{
    std::map<long, VscpRemoteTcpIf*>::iterator it;
    long h = 0;

    LOCK_MUTEX(g_mapMutex);

    // Find free handle
    while (!g_ifMap.empty()) {      
      if (g_ifMap.end() == (it = g_ifMap.find(h))) {
        break;
      }
      h++;
    };

    g_ifMap[h] = pvscpif;
    h += 1681;

    UNLOCK_MUTEX(g_mapMutex);

    return h;
}

///////////////////////////////////////////////////////////////////////////////
// getDriverObject
//

VscpRemoteTcpIf*
getDriverObject(long h)
{
    std::map<long, VscpRemoteTcpIf*>::iterator it;
    long idx = h - 1681;

    // Check if valid handle
    if (idx < 0) {
      return NULL;
    }

    it = g_ifMap.find(idx);
    if (it != g_ifMap.end()) {
      return it->second;
    }

    return NULL;
}

///////////////////////////////////////////////////////////////////////////////
// removeDriverObject
//

void
removeDriverObject(long h)
{
    std::map<long, VscpRemoteTcpIf*>::iterator it;
    long idx = h - 1681;

    // Check if valid handle
    if (idx < 0) {
      return;
    }

    LOCK_MUTEX(g_mapMutex);

    it = g_ifMap.find(idx);
    if (it != g_ifMap.end()) {
        VscpRemoteTcpIf* pObj = it->second;
        if (NULL != pObj) {
            delete pObj;
            pObj = NULL;
        }
        g_ifMap.erase(it);
    }

    UNLOCK_MUTEX(g_mapMutex);
}



