#include <windows.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include <chrono>

#include "vscphelperlib.h"

// Standard connection (a VSCP daemon must be running here)
//#define INTERFACE1_HOST         "localhost:9598"
#define INTERFACE1_HOST     "vscp2.vscp.org:9598"    // VSCP Demo server 2
#define INTERFACE1_USER 	"admin"
#define INTERFACE1_PASSWORD "secret"

int main()
{
	printf("Simple windows VSCP Helper lib test\n");

    int rv;
    long handle1;
    long error_cnt = 0;
    WORD wVersionRequested;
    WSADATA wsaData;
    int err;

    wVersionRequested = MAKEWORD(2, 2);
    err = WSAStartup(wVersionRequested, &wsaData);
    if (err != 0) {
        /* Tell the user that we could not find a usable */
        /* Winsock DLL.                                  */
        printf("WSAStartup failed with error: %d\n", err);
        exit(1);
    };

    handle1 = vscphlp_newSession();

    // Open Channel 1
    rv = vscphlp_open(handle1,
                            INTERFACE1_HOST,
                            INTERFACE1_USER,
                            INTERFACE1_PASSWORD);
    if (VSCP_ERROR_SUCCESS != rv) {
        printf("Failed to connect to remote host %s\n", INTERFACE1_HOST);
        exit(1);
    }
    else {
        printf("Connect to remote host %s\n", INTERFACE1_HOST);
    }

    unsigned long version;
    vscphlp_getDLLVersion(handle1, &version);
    printf("Helper DLL Version : %X\n",version);

    // NOOP on handle1
    rv = vscphlp_noop(handle1);
    if (VSCP_ERROR_SUCCESS != rv) {
        printf("Failed to execute noop command\n");
    }
    else{
        printf("Sent noop command\n");
    }

    // Get version on handle1
    unsigned char majorVer, minorVer, subminorVer;
    rv = vscphlp_getVersion(handle1, &majorVer, &minorVer, &subminorVer);
    if (VSCP_ERROR_SUCCESS != rv) {
        printf("Failed to execute get version command\n");
    }
    else {
        printf("Remote interface version = %d.%d.%d\n", majorVer, minorVer, subminorVer);
    }

    // Send event (Turn on the 'thing(s)' defined by zone/subzone)
    vscpEventEx ex;
    memset(ex.GUID, 0, 16);                     // Use inteface GUID
    vscphlp_setEventExDateTimeBlockToNow(&ex);
    ex.head = VSCP_HEADER16_DUMB;               // This node does not have registers, mdf etc
    ex.timestamp = vscphlp_makeTimeStamp();
    ex.vscp_class = VSCP_CLASS1_CONTROL;
    ex.vscp_type = VSCP_TYPE_CONTROL_TURNON;
    ex.sizeData = 3;
    ex.data[0] = 0;     // Optional user byte
    ex.data[1] = 11;    // Zone
    ex.data[2] = 22;    // SubZone
    rv = vscphlp_sendEventEx(handle1, &ex);
    if (VSCP_ERROR_SUCCESS != rv) {
        printf("Faild to send TURN-ON event rv = %d\n", rv);
    }
    else {
        printf("Sent TURN-ON event\n");
    }

    if (0) {

        if (VSCP_ERROR_SUCCESS != (rv = vscphlp_enterReceiveLoop(handle1))) {
            printf("Failed to enter receive loop rv = %d\n", rv);
        }

        printf("Waiting for events for 180 seconds ....\n");
        // Start measuring time
        std::chrono::seconds elapsed = std::chrono::seconds::zero();
        auto begin = std::chrono::high_resolution_clock::now();

        do {
            vscpEventEx ex;
            if (VSCP_ERROR_SUCCESS ==
                (rv = vscphlp_blockingReceiveEventEx(handle1, &ex, 1000))) {
                printf("Event received: Class=%u Type=%u\n",
                       ex.vscp_class,
                       ex.vscp_type);
            } else {
                if (VSCP_ERROR_TIMEOUT != rv) {
                    printf("No event received. rv=%d\n", rv);
                } else {
                    printf("Timeout\n");
                }
            }
            elapsed = std::chrono::duration_cast<std::chrono::seconds>(
              std::chrono::high_resolution_clock::now() - begin);
        } while (elapsed.count() < 180);

        if (VSCP_ERROR_SUCCESS != (rv = vscphlp_quitReceiveLoop(handle1))) {
            printf("Failed to quit receive loop rv = %d\n", rv);
        }
    }
    
    if (1) {
        unsigned int count;
        while (true) {
            if (VSCP_ERROR_SUCCESS !=
                (rv = vscphlp_isDataAvailable(handle1, &count))) {
                printf("Failed to get available data rv = %d\n", rv);
                Sleep(1000);
                continue;
            }

            if (count) {
                printf("There is data count = %u rv = %d\n", count, rv);
                vscpEventEx ex;
                if (VSCP_ERROR_SUCCESS !=
                    (rv = vscphlp_receiveEventEx(handle1, &ex))) {
                    printf("Event received: Class=%ud Type=%d rv=%d\n",
                           ex.vscp_class,
                           ex.vscp_type,
                           rv );
                } else {
                    printf("No event received. rv=%d\n", rv);
                    Sleep(1000);
                }
            }
        }
    }

    rv = vscphlp_close(handle1);
    if (VSCP_ERROR_SUCCESS != rv) {
        printf("Failed to execute close command\n");
    }
    else {
        printf("Sent close command\n");
    }

    vscphlp_closeSession(handle1);

    // Cleanup
    WSACleanup();

	return 0;
}