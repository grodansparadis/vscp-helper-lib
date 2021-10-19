// test_connections.c 
//

// This test do many, many, many connections to the localhost interface,
// stressing it.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <vscphelperlib.h>
#include <gtest/gtest.h>

#define RUN_COUNT 100

// Standard connection (a VSCP daemon must be running here)
//#define INTERFACE1_HOST         "127.0.0.1:9598"
//#define INTERFACE1_HOST         "192.168.1.44:9598"  // pi11
//#define INTERFACE1_HOST       "192.168.1.34:9598"  // pi6

#define INTERFACE1_HOST       "vscp2.vscp.org:9598"
#define INTERFACE1_USER 	    "admin"
#define INTERFACE1_PASSWORD   "secret"

///////////////////////////////////////////////////////////////////////////////
// sendEvents
//
// Send n events on another channel 
//

int sendEvents( const char* host, 
                const char* user, 
                const char *password, 
                int count)
{
  int rv = VSCP_ERROR_SUCCESS;

  long h = vscphlp_newSession();
  if (!h) return VSCP_ERROR_ERROR;
  printf("handle = %ld\n", h);

  h = vscphlp_newSession();
  if (!h) return VSCP_ERROR_ERROR;
  printf("handle = %ld\n", h);

  if ( VSCP_ERROR_SUCCESS != vscphlp_open(h, host, user, password) ) {
    printf("Failed to open new channel");
    return rv;
  }

  vscpEvent ev;
  ev.vscp_class = 10;  // CLASS1.MEASUREMENT
  ev.vscp_type = 6;    // Temperature
  ev.head = 0;
  ev.obid = 0;
  ev.timestamp = 0;
  ev.year = 2018;
  ev.month = 3;
  ev.day = 17;
  ev.hour = 12;
  ev.minute = 13;
  ev.second = 1;
  ev.sizeData = 3;
  ev.pdata = new uint8_t[3];
  ev.pdata[0] = 138;  // Six degrees Celsius from sensor 2
  ev.pdata[1] = 0;
  ev.pdata[2] = 6;
  memset(ev.GUID, 0, sizeof(ev.GUID) ); // Setting GUID to all zero tell interface to use it's own GUID

  for ( int i=0; i<count; i++) {
    printf("Sent event %d\n", i );
    if ( VSCP_ERROR_SUCCESS != (rv = vscphlp_sendEvent(h, &ev) ) ) {
      printf("Failed to send event");
      break;
    }
       
  }

  rv = vscphlp_close(h);
  if ( rv != VSCP_ERROR_SUCCESS ) {
    printf("Failed to close channel");
  } 

  vscphlp_closeSession(h);

end:
  delete  [] ev.pdata;
  ev.pdata = nullptr;
  return rv;
}


TEST(sendEvents, burst) { 

    int rv;
    long handle1; 
    long error_cnt = 0;

    handle1 = vscphlp_newSession();
    ASSERT_NE(handle1, 0) << "vscphlp_newSession failed";
    printf("handle = %ld\n", handle1);
    
    // Open Channel 1
    rv = vscphlp_open( handle1, 
                         INTERFACE1_HOST,
                         INTERFACE1_USER,
                         INTERFACE1_PASSWORD ); 
    ASSERT_EQ(rv, VSCP_ERROR_SUCCESS) << "vscphlp_open failed";

    // NOOP on handle1
    rv = vscphlp_noop( handle1 );
    ASSERT_EQ(rv, VSCP_ERROR_SUCCESS) << "vscphlp_noop failed";

    // Get version on handle1
    unsigned char majorVer, minorVer, subminorVer;
    rv = vscphlp_getVersion( handle1, &majorVer, &minorVer, &subminorVer );
    ASSERT_EQ(rv, VSCP_ERROR_SUCCESS) << "vscphlp_getVersion failed";

    rv = sendEvents(INTERFACE1_HOST,
                    INTERFACE1_USER,
                    INTERFACE1_PASSWORD, 
                    10);
    ASSERT_EQ(rv, VSCP_ERROR_SUCCESS) << "sendEvents failed";

    rv = vscphlp_close(handle1);
    ASSERT_EQ(rv, VSCP_ERROR_SUCCESS) << "vscphlp_close failed";

    vscphlp_closeSession(handle1);    

}

//-----------------------------------------------------------------------------

int main(int argc, char* argv[])
{
    int count = RUN_COUNT;

    if ( argc > 1 ) {
        count = atoi(argv[1]);
    }
    testing::InitGoogleTest(&argc, argv);
    for ( int i=0; i<count; i++ ) {
        printf("\nRunning test %d/%d\n", i, count);
        if ( 1 == RUN_ALL_TESTS() ) {
            printf( "\nFailed at count = %d(%d)\n\n", i, count);
            return 1;
        }
    }
   
}
