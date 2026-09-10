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

TEST(GuidParser, ParsesSupportedFormats)
{
    const uint8_t expected[] = { 0xFF, 0xFF, 0xFF, 0xFF,
                                 0xFF, 0xFF, 0xFF, 0xFF,
                                 0x01, 0x02, 0x03, 0xAA,
                                 0xBB, 0x44, 0x01, 0x30 };
    const char* formats[] = {
        "FF:FF:FF:FF:FF:FF:FF:FF:01:02:03:AA:BB:44:01:30",
        "::01:02:03:AA:BB:44:01:30",
        "FFFFFFFF-FFFF-FFFF-0102-03AABB440130",
        "{::0102:03aa:bb440130}"
    };

    for (const char* format : formats) {
        uint8_t guid[16] = {};
        EXPECT_EQ(VSCP_ERROR_SUCCESS, vscphlp_parseGuid(guid, format));
        EXPECT_EQ(0, memcmp(expected, guid, sizeof(guid))) << format;
    }
}

TEST(GuidParser, ParsesSpecialValues)
{
    uint8_t guid[16] = {};

    ASSERT_EQ(VSCP_ERROR_SUCCESS, vscphlp_parseGuid(guid, "-"));
    for (uint8_t value : guid) {
        EXPECT_EQ(0, value);
    }

    ASSERT_EQ(VSCP_ERROR_SUCCESS, vscphlp_parseGuid(guid, "::"));
    for (uint8_t value : guid) {
        EXPECT_EQ(0xFF, value);
    }
}

TEST(GuidParser, RejectsInvalidInput)
{
    uint8_t guid[16] = {};

    EXPECT_EQ(VSCP_ERROR_INVALID_POINTER, vscphlp_parseGuid(nullptr, "::"));
    EXPECT_EQ(VSCP_ERROR_INVALID_POINTER, vscphlp_parseGuid(guid, nullptr));
    EXPECT_EQ(VSCP_ERROR_INVALID_SYNTAX, vscphlp_parseGuid(guid, "not-a-guid"));
    EXPECT_EQ(VSCP_ERROR_INVALID_SYNTAX, vscphlp_parseGuid(guid, "01:02:03"));
}

TEST(tcpif, SessionHandling) { 

    long handle1; 
    long handle2; 
    long handle3; 
    long handle4; 

    handle1 = vscphlp_newSession();
    ASSERT_EQ(1681, handle1);

    handle2 = vscphlp_newSession();
    ASSERT_EQ(1682, handle2);

    handle3 = vscphlp_newSession();
    ASSERT_EQ(1683, handle3);

    vscphlp_closeSession(handle1);

    // Should take the fee idx
    handle4 = vscphlp_newSession();
    ASSERT_EQ(1681, handle4);

    vscphlp_closeSession(handle2);
    vscphlp_closeSession(handle3);
    vscphlp_closeSession(handle4);
}

TEST(tcpif, Connect_to_VSCP_daemon) { 

    int rv;
    long handle1; 
    long error_cnt = 0;

    handle1 = vscphlp_newSession();
    ASSERT_NE(handle1, 0);

    // Open Channel 1
    rv = vscphlp_open(handle1, 
                        INTERFACE1_HOST, 
                        INTERFACE1_USER, 
                        INTERFACE1_PASSWORD);
    ASSERT_EQ(rv, VSCP_ERROR_SUCCESS);

    // NOOP on handle1
    rv = vscphlp_noop( handle1 );
    ASSERT_EQ(rv, VSCP_ERROR_SUCCESS);

    // Get version on handle1
    unsigned char majorVer, minorVer, subminorVer;
    rv = vscphlp_getVersion( handle1, &majorVer, &minorVer, &subminorVer );
    ASSERT_EQ(rv, VSCP_ERROR_SUCCESS);

    rv= vscphlp_close( handle1 );
    ASSERT_EQ(rv, VSCP_ERROR_SUCCESS);

    vscphlp_closeSession( handle1 );    
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
