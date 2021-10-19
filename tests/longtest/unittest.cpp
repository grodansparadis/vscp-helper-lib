
///////////////////////////////////////////////////////////////////////////////
// noop.cpp
//
// https://www.vscp.org   the VSCP project   info@vscp.org
// https://www.vscp.org/docs/vscphelper/doku.php?id=classes_vscpremotetcpipif_metods

#ifdef WIN32
#include <pch.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <vscphelperlib.h>
#include <gtest/gtest.h>

#include <chrono>

// Standard connection (a VSCP daemon must be running here)
//#define INTERFACE1_HOST         "127.0.0.1:9598"
//#define INTERFACE1_HOST         "192.168.1.44:9598"  // pi11
//#define INTERFACE1_HOST       "192.168.1.34:9598"  // pi6

#define INTERFACE1_HOST       "vscp2.vscp.org:9598"
#define INTERFACE1_USER 	    "admin"
#define INTERFACE1_PASSWORD   "secret"

///////////////////////////////////////////////////////////////////////////////
// Open session to host and Send n events using ev
//
/*
int sendEventFromOtherSession(const char *host,
                                const char *user,
                                const char *password,
                                unsigned int count)
{
  int rv;

  VscpRemoteTcpIf vscpif;

  // Send event (Turn on the 'thing(s)' defined by zone/subzone)
  vscpEvent *pev = new vscpEvent;
  pev->pdata = nullptr;
  pev->sizeData = 0;

  memset(pev->GUID, 0, 16);               // Use inteface GUID
  vscp_setEventDateTimeBlockToNow(pev);
  pev->head     = VSCP_HEADER16_DUMB;     // This node does not have registers, mdf etc
  pev->timestamp = vscp_makeTimeStamp();
  pev->vscp_class = VSCP_CLASS1_CONTROL;
  pev->vscp_type = VSCP_TYPE_CONTROL_TURNON;
  pev->sizeData = 3;
  pev->pdata = new uint8_t[3];
  pev->pdata[0] = 0;       // Optional user byte
  pev->pdata[1] = 0x55;    // Zone
  pev->pdata[2] = 0xAA;    // SubZone

  rv = vscpif.doCmdOpen(host, user, password);
  if (VSCP_ERROR_SUCCESS != rv) return rv;
  
  for (unsigned int i=0;i<count; i++) {
    pev->pdata[0] = i;
    rv = vscpif.doCmdSend(pev);
    if (VSCP_ERROR_SUCCESS != rv) return rv;
  }

  vscp_deleteEvent(pev);
  
  rv = vscpif.doCmdClose();
  if (VSCP_ERROR_SUCCESS != rv) return rv;

  return rv;
}



///////////////////////////////////////////////////////////////////////////////
// Open session to host and Send n events using ex
//

int sendEventExFromOtherSession(const char *host,
                                const char *user,
                                const char *password,
                                unsigned int count)
{
  int rv;

  VscpRemoteTcpIf vscpif;

  // Send event (Turn on the 'thing(s)' defined by zone/subzone)
  vscpEventEx ex;
  memset(ex.GUID, 0, 16);                     // Use inteface GUID
  vscp_setEventExDateTimeBlockToNow(&ex);
  ex.head = VSCP_HEADER16_DUMB;               // This node does not have registers, mdf etc
  ex.timestamp = vscp_makeTimeStamp();
  ex.vscp_class = VSCP_CLASS1_CONTROL;
  ex.vscp_type = VSCP_TYPE_CONTROL_TURNON;
  ex.sizeData = 3;
  ex.data[0] = 0;       // Optional user byte
  ex.data[1] = 0x55;    // Zone
  ex.data[2] = 0xAA;    // SubZone

  rv = vscpif.doCmdOpen(host, user, password);
  if (VSCP_ERROR_SUCCESS != rv) return rv;
  
  for (unsigned int i=0;i<count; i++) {
    ex.data[0] = i;
    rv = vscpif.doCmdSendEx(&ex);
    if (VSCP_ERROR_SUCCESS != rv) return rv;
  }
  
  rv = vscpif.doCmdClose();
  if (VSCP_ERROR_SUCCESS != rv) return rv;

  return rv;
}*/


//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------



//-----------------------------------------------------------------------------
TEST(VscpRemoteTcpIf, PollingTestExForOneHour) 
{ 
  int rv;
  long handle1;

  handle1 = vscphlp_newSession();
  ASSERT_NE(0, handle1);

  // Open Channel 1
  rv = vscphlp_open(handle1, 
                        INTERFACE1_HOST, 
                        INTERFACE1_USER, 
                        INTERFACE1_PASSWORD);
  ASSERT_EQ(rv, VSCP_ERROR_SUCCESS);

  // Start measuring time
  std::chrono::seconds elapsed = std::chrono::seconds::zero();
  std::chrono::seconds last = std::chrono::seconds::zero();
  auto begin = std::chrono::high_resolution_clock::now();
  int cnt = 0;

  do {

    unsigned int count;
    rv = vscphlp_isDataAvailable(handle1, &count);
    ASSERT_EQ(VSCP_ERROR_SUCCESS, rv);

    if (count>0) {
      vscpEventEx ex;
      ASSERT_EQ(VSCP_ERROR_SUCCESS, (rv = vscphlp_receiveEventEx(handle1, &ex)));

      printf("Received Event\n");
      cnt++;
      printf("cnt=%d\n",cnt);
    }
    else {
      ASSERT_EQ(0,rv) << "rv=" << rv << " -1 means error\n";
    }

    elapsed = std::chrono::duration_cast<std::chrono::seconds>(std::chrono::high_resolution_clock::now() - begin);
    if ((elapsed-last).count()>=60) {
      last = elapsed;
      printf("------> Elapsed time %d/60\n", (int)elapsed.count()/60 );
    }

  } while (elapsed.count() < 3600);

  rv= vscphlp_close(handle1);
  ASSERT_EQ(rv, VSCP_ERROR_SUCCESS);

  vscphlp_closeSession(handle1);
}


// ===========================================================================
// ===========================================================================
// ===========================================================================


int main(int argc, char **argv) {

#ifdef WIN32
    WORD wVersionRequested;
    WSADATA wsaData;
    int err;

    wVersionRequested = MAKEWORD(2,2);
    err               = WSAStartup(wVersionRequested, &wsaData);
    if (err != 0) {
      /* Tell the user that we could not find a usable */
      /* Winsock DLL.                                  */
      printf("WSAStartup failed with error: %d\n", err);
      exit(1);
    };
#endif

    testing::InitGoogleTest(&argc, argv);
   int rv =  RUN_ALL_TESTS();

#ifdef WIN32
   // Cleanup
   WSACleanup();
#endif

   return rv;
}


