// bigtest.c
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <unistd.h>
#include <sys/time.h>
#include "../../../src/vscphelperlib.h"

#define USER            "admin"
#define PASSWORD        "secret"
#define PORT            9598

#define HOST            "vscp1.vscp.org" 
//#define HOST          "127.0.0.1"
//#define HOST          "192.168.1.7"
//#define HOST		      "192.168.1.30"   // pi4

#define HOST_PLUS_PORT  "tcp://vscp1.vscp.org:9598"
//#define HOST_PLUS_PORT  "127.0.0.1:9598"
//#define HOST_PLUS_PORT  "tcp://192.168.1.7:9598"
//#define HOST_PLUS_PORT  "tcp://192.168.1.30:9598"

#define INTERFACE       "tcp://vscp1.vscp.org:9598;admin;secret"
//#define INTERFACE       "127.0.0.1:9598;admin;secret"
//#define INTERFACE       "tcp://192.168.1.7:9598;admin;secret"
//#define INTERFACE       "tcp://192.168.1.30:9598;admin;secret"

// Count for number of events sent in burst
#define BURST_SEND_COUNT    2000

// If TEST_RECEIVE_LOOP is uncommented the rcvloop commands
// will be tested. Must send five events externally to test
#define TEST_RECEIVE_LOOP

// Uncomment to test variable handling
#define TEST_VARIABLE_HANDLING

// Uncomment to test helpers
#define TEST_HELPERS

// Uncomment to test measurement functionality
#define TEST_MEASUREMENT


///////////////////////////////////////////////////////////////////////////////
// current_timestamp
//

long long current_timestamp() {
    struct timeval te;
    gettimeofday(&te, NULL); // get current time
    long long milliseconds = te.tv_sec*1000LL + te.tv_usec/1000; // calculate milliseconds
    // printf("milliseconds: %lld\n", milliseconds);
    return milliseconds;
}

///////////////////////////////////////////////////////////////////////////////
// closeAll
//

void closeAll( int h1, int h2 )
{
    if ( VSCP_ERROR_SUCCESS == vscphlp_close( h1 ) ) {
        printf( "vscphlp_close: Success on channel 1\n" );
    }
    else {
        printf( "vscphlp_close: Error on channel 1\n" );
    }

    vscphlp_closeSession( h1 );

    if ( VSCP_ERROR_SUCCESS == vscphlp_close( h2 ) ) {
        printf( "vscphlp_close: Success on channel 2\n" );
    }
    else {
        printf( "vscphlp_close: Error on channel 2\n" );
    }

    vscphlp_closeSession( h2 );
}

///////////////////////////////////////////////////////////////////////////////
// main
//

int main(int argc, char* argv[])
{
    int rv;
    long handle1, handle2;
    long long t1,t2;

    printf("VSCP helperlib test program\n");
    printf("VSCP helperlib test program\n");
    printf("===========================\n");

    handle1 = vscphlp_newSession();
    if (0 != handle1 ) {
        printf( "vscphlp_newSession: Success. handle 1 = %ld\n", handle1 );
    }
    else {
        printf("\avscphlp_newSession: Failure - channel 1\n");
        return -1;
    }

    handle2 = vscphlp_newSession();
    if (0 != handle2 ) {
        printf( "vscphlp_newSession: Success. handle 2 = %ld\n", handle2 );
    }
    else {
        printf("\avscphlp_newSession: Failure - channel 2\n");
        vscphlp_closeSession( handle1 );
        return -1;
    }

    // Open Channel 1
    rv=vscphlp_open( handle1,
                         HOST_PLUS_PORT,
                         USER,
                         PASSWORD );
    if ( VSCP_ERROR_SUCCESS == rv ) {
        printf( "vscphlp_open: Success. - Channel 1\n" );
    }
    else {
        printf("vscphlp_open: Failure - Channel 1, rv = %d\n", rv );
        vscphlp_closeSession( handle1 );
        vscphlp_closeSession( handle2 );
        return -1;
    }

    // OPEN channel 2
    rv=vscphlp_openInterface( handle2, INTERFACE, 0 );
    if ( VSCP_ERROR_SUCCESS == rv ) {
        printf( "vscphlp_open: Success. - Channel 2\n" );
    }
    else {
        printf("vscphlp_open: Failure - Channel 2, rv = %d\n", rv );
        vscphlp_close( handle1 );
        vscphlp_closeSession( handle1 );
        vscphlp_closeSession( handle2 );
        return -1;
    }

    // NOOP on handle1
    if ( VSCP_ERROR_SUCCESS == (rv = vscphlp_noop( handle1 ) ) ) {
        printf( "vscphlp_noop: Success. - Channel 1\n" );
    }
    else {
        printf("vscphlp_noop: Failure - Channel 1, rv = %d\n", rv );
        closeAll( handle1, handle2 );
        return -1;
    }

    // NOOP on handle2
    if ( VSCP_ERROR_SUCCESS == (rv = vscphlp_noop( handle2 ) ) ) {
        printf( "vscphlp_noop: Success. - Channel 2\n" );
    }
    else {
        printf("vscphlp_noop: Failure - Channel 2, rv = %d\n", rv );
        closeAll( handle1, handle2 );
        return -1;
    }

    // Get version on handle1
    unsigned char majorVer, minorVer, subminorVer;
    if ( VSCP_ERROR_SUCCESS == (rv = vscphlp_getVersion( handle1, &majorVer, &minorVer, &subminorVer ) ) ) {
        printf( "vscphlp_getVersion: Success. - Channel 1\n" );
        printf( "channel 1: Major version=%d  Minor version=%d  Sub Minor version=%d\n",
                majorVer,
                minorVer,
                subminorVer );
    }
    else {
        printf("vscphlp_getVersion: Failure - Channel 1, rv = %d\n", rv );
        closeAll( handle1, handle2 );
        return -1;
    }


    // Get version on handle2
    if ( VSCP_ERROR_SUCCESS == (rv = vscphlp_getVersion( handle2, &majorVer, &minorVer, &subminorVer ) ) ) {
        printf( "vscphlp_getVersion: Success. - Channel 2\n" );
        printf( "channel 1: Major version=%d  Minor version=%d  Sub Minor version=%d\n",
                majorVer,
                minorVer,
                subminorVer );
    }
    else {
        printf("vscphlp_getVersion: Failure - Channel 2, rv = %d\n", rv );
        closeAll( handle1, handle2 );
        return -1;
    }


    // Send event on channel 1
    vscpEvent e;
    e.vscp_class = 10;  // CLASS1.MEASUREMENT
    e.vscp_type = 6;    // Temperature
    e.head = 0;
    e.year = 1956;
    e.month = 11;
    e.day = 2;
    e.hour = 12;
    e.minute = 10;
    e.second = 3;
    e.sizeData = 3;
    e.timestamp = 0;
    e.pdata = malloc( sizeof( unsigned char[3] ) );
    e.pdata[0] = 138;  // Six degrees Celsius from sensor 2
    e.pdata[1] = 0;
    e.pdata[2] = 6;
    memset(e.GUID, 0, sizeof(e.GUID) ); // Setting GUID to all zero tell interface to use it's own GUID

    if ( VSCP_ERROR_SUCCESS == (rv = vscphlp_sendEvent( handle1, &e ) ) ) {
        printf( "vscphlp_sendEvent: Success. - Try 1, Channel 1\n" );
    }
    else {
        printf("vscphlp_sendEvent: Failure - Try 1, Channel 1, rv = %d\n", rv );
        closeAll( handle1, handle2 );
        return -1;
    }

    // Do it again
    if ( VSCP_ERROR_SUCCESS == (rv = vscphlp_sendEvent( handle1, &e ) ) ) {
        printf( "vscphlp_sendEvent: Success. - Try 2, Channel 1\n" );
    }
    else {
        printf("vscphlp_sendEvent: Failure - Try 2, Channel 1, rv = %d\n", rv );
        closeAll( handle1, handle2 );
        return -1;
    }

    printf("Giving events time to be deliverd.\n");
    sleep( 1 );

    // Two events should now have been received on handle2
    unsigned int count;
    if ( VSCP_ERROR_SUCCESS == (rv = vscphlp_isDataAvailable( handle2, &count ) ) ) {
        printf( "vscphlp_isDataAvailable: Success. - Channel 2\n" );
        if ( 2 == count ) {
            printf( "Two events waiting to be fetched on channel 2.\n" );
        }
        else if ( count < 2 ) {
            printf( "%u events waiting to be fetched on channel 2.\n", count );
            printf("vscphlp_isDataAvailable: Failure - Number of events in queue should be 2 or greater.\n" );
            closeAll( handle1, handle2 );
            return -1;
        }
        else {
            printf( "%u events waiting to be fetched on channel 2 [Other source is also sending events].\n", count );
        }
    }
    else {
        printf("vscphlp_isDataAvailable: Failure - Channel 1, rv = %d\n", rv );
        closeAll( handle1, handle2 );
        return -1;
    }


    // Clear the event queue on the demon channel 2
    if ( VSCP_ERROR_SUCCESS == (rv = vscphlp_clearDaemonEventQueue( handle2 ) ) ) {
        printf( "vscphlp_clearDaemonEventQueue: Success. - Channel 2\n" );
    }
    else {
        printf("vscphlp_clearDaemonEventQueue: Failure - Channel 2, rv = %d\n", rv );
        closeAll( handle1, handle2 );
        return -1;
    }


    // We should now have an empty queue on channel2
    if ( VSCP_ERROR_SUCCESS == (rv = vscphlp_isDataAvailable( handle2, &count ) ) ) {
        printf( "vscphlp_isDataAvailable: Success. - Channel 2\n" );
        printf( "count = %u\n", count );
        if ( !count ) {
            printf("Which is correct.\n");
        }
        else {
            printf("Which is wrong (can be due to other event source).\n");
        }
    }
    else {
        printf("vscphlp_isDataAvailable: Failure - Channel 2, rv = %d\n", rv );
        closeAll( handle1, handle2 );
        return -1;
    }

    vscpEventEx ex;
    ex.vscp_class = 10; // CLASS1.MEASUREMENT
    ex.vscp_type = 6;   // Temperature
    ex.head = 0;
    ex.year = 1956;
    ex.month = 11;
    ex.day = 2;
    ex.hour = 12;
    ex.minute = 10;
    ex.second = 3;
    ex.timestamp = 0;   // Let interface set it
    ex.sizeData = 3;
    ex.data[0] = 138;   // 6 degrees Celsius from sensor 2
    ex.data[1] = 0;
    ex.data[2] = 6;
    memset(ex.GUID, 0, sizeof(e.GUID) ); // Setting GUID to all zero tell interface to use it's own GUID

    // Send event again
    if ( VSCP_ERROR_SUCCESS == (rv = vscphlp_sendEventEx( handle1, &ex ) ) ) {
        printf( "vscphlp_sendEventEx: Success. - 1 Channel 1\n" );
    }
    else {
        printf("vscphlp_sendEventEx: Failure - 1 Channel 1, rv = %d\n", rv );
        closeAll( handle1, handle2 );
        return -1;
    }

    ex.data[0] = 138;  // 1.11 degrees Celsius from sensor 2
    ex.data[1] = 2;
    ex.data[2] = 111;

    // Send event again
    if ( VSCP_ERROR_SUCCESS == (rv = vscphlp_sendEventEx( handle1, &ex ) ) ) {
        printf( "vscphlp_sendEventEx: Success. - 2 Channel 1\n" );
    }
    else {
        printf("vscphlp_sendEventEx: Failure - 2 Channel 1, rv = %d\n", rv );
        closeAll( handle1, handle2 );
        return -1;
    }


    ex.data[0] = 138;  // -1 degrees Celsius from sensor 2
    ex.data[1] = 0;
    ex.data[2] = 255;

    // Send event again
    if ( VSCP_ERROR_SUCCESS == (rv = vscphlp_sendEventEx( handle1, &ex ) ) ) {
        printf( "vscphlp_sendEventEx: Success. - 3 Channel 1\n" );
    }
    else {
        printf("vscphlp_sendEventEx: Failure - 3 Channel 1, rv = %d\n", rv );
        closeAll( handle1, handle2 );
        return -1;
    }

    printf("Giving events time to be delivered.\n");
    sleep( 1 );

    // We should now have three events in the queue on channel2
    if ( VSCP_ERROR_SUCCESS == (rv = vscphlp_isDataAvailable( handle2, &count ) ) ) {
        printf( "vscphlp_isDataAvailable: Success. - Channel 2\n" );
        printf( "count = %u\n", count );
        if ( 3 == count ) printf("Which is correct.\n");
    }
    else {
        printf("vscphlp_isDataAvailable: Failure - Channel 2, rv = %d\n", rv );
        closeAll( handle1, handle2 );
        return -1;
    }


    // Read event1
    vscpEvent *pEvent = malloc( sizeof( vscpEvent ) );
    pEvent->pdata = NULL;   // A must for a successful delete
    if ( VSCP_ERROR_SUCCESS == (rv = vscphlp_receiveEvent( handle2, pEvent ) ) ) {
        printf( "vscphlp_receiveEvent: Success. - Channel 2\n" );
        printf( "VSCP class=%d VSCP type=%d sizeData=%d\n",
                    pEvent->vscp_class,
                    pEvent->vscp_type,
                    pEvent->sizeData );
        printf("Data = ");
        for ( int i=0; i<pEvent->sizeData; i++ ) {
            printf("%d ", pEvent->pdata[i] );
        }
        printf("\n");
    }
    else {
        printf("vscphlp_receiveEvent: Failure - Channel 2, rv = %d\n", rv );
        closeAll( handle1, handle2 );
        return -1;
    }

    vscphlp_deleteVSCPevent( pEvent );
    pEvent = NULL;



    // Read event2
    pEvent = malloc( sizeof( vscpEvent ) );
    pEvent->pdata = NULL;   // A must for a successful delete
    if ( VSCP_ERROR_SUCCESS == (rv = vscphlp_receiveEvent( handle2, pEvent ) ) ) {
        printf( "vscphlp_receiveEvent: Success. - Channel 2\n" );
        printf( "VSCP class=%d VSCP type=%d sizeData=%d\n",
                    pEvent->vscp_class,
                    pEvent->vscp_type,
                    pEvent->sizeData );
        printf("Data = ");
        for ( int i=0; i<pEvent->sizeData; i++ ) {
            printf("%d ", pEvent->pdata[i] );
        }
        printf("\n");
    }
    else {
        printf("vscphlp_receiveEvent: Failure - Channel 2, rv = %d\n", rv );
        closeAll( handle1, handle2 );
        return -1;
    }

    // Free the event
    vscphlp_deleteVSCPevent( pEvent );
    pEvent = NULL;




    // Read event3   -  Use vscpEventEx
    vscpEventEx ex2;
    if ( VSCP_ERROR_SUCCESS == (rv = vscphlp_receiveEventEx( handle2, &ex2 ) ) ) {
        printf("vscphlp_receiveEventEx: Success - Channel 2, rv = %d\n", rv );
        printf( "VSCP class=%d VSCP type=%d sizeData=%d\n",
                    ex2.vscp_class,
                    ex2.vscp_type,
                    ex2.sizeData );
        printf("Data = ");
        for ( int i=0; i<ex2.sizeData; i++ ) {
            printf("%d ", ex2.data[i] );
        }
        printf("\n");
    }
    else {
        printf("vscphlp_receiveEventEx: Failure - Channel 2, rv = %d\n", rv );
        closeAll( handle1, handle2 );
        return -1;
    }


    // Get status
    VSCPStatus status;
    if ( VSCP_ERROR_SUCCESS == (rv = vscphlp_getStatus( handle2, &status ) ) ) {
        printf( "vscphlp_getStatus: Success. - Channel 2\n" );
    }
    else {
        printf("vscphlp_getStatus: Failure - Channel 2, rv = %d\n", rv );
        closeAll( handle1, handle2 );
        return -1;
    }


    // Get statistics
    VSCPStatistics stat;
    if ( VSCP_ERROR_SUCCESS == (rv = vscphlp_getStatistics( handle2, &stat ) ) ) {
        printf( "vscphlp_getStatistics: Success. - Channel 2\n" );
    }
    else {
        printf("vscphlp_getStatistics: Failure - Channel 2, rv = %d\n", rv );
        closeAll( handle1, handle2 );
        return -1;
    }

    // Set VSCP filter
    vscpEventFilter filter;
    filter.filter_class = 22;           // We are interested  in events with VSCP class=22 only
    filter.mask_class = 0xffff;
    filter.mask_type = 0;               // Any type
    filter.mask_priority = 0;           // Any priority
    memset( filter.mask_GUID, 0, 16 );  // Any GUID
    if ( VSCP_ERROR_SUCCESS == (rv = vscphlp_setFilter( handle2, &filter ) ) ) {
        printf( "vscphlp_setFilter: Success. - Channel 2\n" );
    }
    else {
        printf("vscphlp_setFilter: Failure - Channel 2, rv = %d\n", rv );
        closeAll( handle1, handle2 );
        return -1;
    }


    // Display # events in the queue on channel2
    if ( VSCP_ERROR_SUCCESS == (rv = vscphlp_isDataAvailable( handle2, &count ) ) ) {
        printf( "vscphlp_isDataAvailable: Success. - Channel 2\n" );
        printf( "count before sending two events = %u\n", count );
    }
    else {
        printf("vscphlp_isDataAvailable: Failure - Channel 2, rv = %d\n", rv );
        closeAll( handle1, handle2 );
        return -1;
    }


    // Send event that should not be received
    e.vscp_class = 10;
    if ( VSCP_ERROR_SUCCESS == (rv = vscphlp_sendEvent( handle1, &e ) ) ) {
        printf( "vscphlp_sendEvent: Success. - Channel 1\n" );
    }
    else {
        printf("vscphlp_sendEvent: Failure - Channel 1, rv = %d\n", rv );
        closeAll( handle1, handle2 );
        return -1;
    }


    // Send event that should be received
    e.vscp_class = 22;
    if ( VSCP_ERROR_SUCCESS == (rv = vscphlp_sendEvent( handle1, &e ) ) ) {
        printf( "vscphlp_sendEvent: Success. - Channel 1\n" );
    }
    else {
        printf("vscphlp_sendEvent: Failure - Channel 1, rv = %d\n", rv );
        closeAll( handle1, handle2 );
        return -1;
    }


    // Display # events in the queue on channel2
    if ( VSCP_ERROR_SUCCESS == (rv = vscphlp_isDataAvailable( handle2, &count ) ) ) {
        printf( "vscphlp_isDataAvailable: Success. - Channel 2\n" );
        printf( "count after sending two events (+1) = %u\n", count );
    }
    else {
        printf("vscphlp_isDataAvailable: Failure - Channel 2, rv = %d\n", rv );
        closeAll( handle1, handle2 );
        return -1;
    }


    // Clear the filter
    memset( &filter, 0, sizeof( vscpEventFilter ) );
    if ( VSCP_ERROR_SUCCESS == (rv = vscphlp_setFilter( handle2, &filter ) ) ) {
        printf( "vscphlp_setFilter: Success. - Channel 2\n" );
    }
    else {
        printf("vscphlp_setFilter: Failure - Channel 2, rv = %d\n", rv );
        closeAll( handle1, handle2 );
        return -1;
    }

    // Get server version
    unsigned char v1,v2,v3;
    if ( VSCP_ERROR_SUCCESS == (rv = vscphlp_getVersion( handle2, &v1, &v2, &v3 ) ) ) {
        printf( "vscphlp_getVersion: Success. - Channel 2\n" );
        printf( "Version for VSCP daemon on channel 2 is %d.%d.%d\n", v1,v2,v3 );
    }
    else {
        printf("vscphlp_getVersion: Failure - Channel 2, rv = %d\n", rv );
        closeAll( handle1, handle2 );
        return -1;
    }


    // Get DLL version
    unsigned long dllversion;
    if ( VSCP_ERROR_SUCCESS == (rv = vscphlp_getDLLVersion( handle2, &dllversion ) ) ) {
        printf( "vscphlp_getDLLVersion: Success. - Channel 2\n" );
        printf( "DL(L) version is %08lX\n", dllversion );
    }
    else {
        printf("vscphlp_getDLLVersion: Failure - Channel 2, rv = %d\n", rv );
        closeAll( handle1, handle2 );
        return -1;
    }


    // Get vendorstring
    char buf[120];
    if ( VSCP_ERROR_SUCCESS == (rv = vscphlp_getVendorString( handle2, buf, sizeof(buf) ) ) ) {
        printf( "vscphlp_getVendorString: Success. - Channel 2\n" );
        printf( "Vendorstring = \"%s\"\n", buf );
    }
    else {
        printf("vscphlp_getVendorString: Failure - Channel 2, rv = %d\n", rv );
        closeAll( handle1, handle2 );
        return -1;
    }

    // Get driver info
    if ( VSCP_ERROR_SUCCESS == (rv = vscphlp_getDriverInfo( handle2, buf, sizeof(buf) ) ) ) {
        printf( "vscphlp_getDriverInfo: Success. - Channel 2\n" );
        printf( "Driver info = \"%s\"\n", buf );
    }
    else {
        printf("vscphlp_getDriverInfo: Failure - Channel 2, rv = %d\n", rv );
        closeAll( handle1, handle2 );
        return -1;
    }



// ****************************************************************************
//                            TEST RECEIVE LOOP
// ****************************************************************************



#ifdef TEST_RECEIVE_LOOP

    printf("\n* * * * * Receive loop  * * * * *\n");

    // Enter receiveloop
    if ( VSCP_ERROR_SUCCESS == (rv = vscphlp_enterReceiveLoop( handle2 ) ) ) {
        printf( "vscphlp_enterReceiveLoop: Success. - Channel 2\n" );
    }
    else {
        printf("vscphlp_enterReceiveLoop: Failure - Channel 2, rv = %d\n", rv );
        closeAll( handle1, handle2 );
        return -1;
    }

    printf("* * * * Waiting for 200 received events on channel 2 * * * * *\n");

    // ----

    // Send event on channel 1
	vscpEventEx exa;
    exa.vscp_class = 10;    // CLASS1.MEASUREMENT
    exa.vscp_type = 1;      // Count
    exa.head = 0;
    exa.year = 1867;        // Marie Curie
    exa.month = 11;
    exa.day = 7;
    exa.hour = 12;
    exa.minute = 10;
    exa.second = 3;
    exa.sizeData = 2;
    exa.timestamp = 0;
    exa.data[0] = 0;
    exa.data[1] = 0;
    memset(exa.GUID, 0, sizeof(exa.GUID) ); // Setting GUID to all zero tell interface to use it's own GUID

    t1 = t2 = current_timestamp();
	for ( int i=0; i<BURST_SEND_COUNT; i++ ) {

		exa.data[0] = (i>>8) & 0xff;
    	exa.data[1] = i & 0xff;

    	if ( VSCP_ERROR_SUCCESS == (rv = vscphlp_sendEventEx( handle1, &exa ) ) ) {
        	printf( "vscphlp_sendEvent: Success. %d\n", i );
    	}
    	else {
        	printf("vscphlp_sendEvent: Failure - rv = %d\n", rv );
        	closeAll( handle1, handle2 );
            return -1;
    	}
	}

    t2 = current_timestamp();
    printf("Burst send time %d ms\n", (int)(t2-t1) );

    // ----

    int cntEvents = 0;
    int blockIteration = 0;

    t1 = t2 = current_timestamp();
    while ( cntEvents < BURST_SEND_COUNT ) {
        pEvent = malloc( sizeof( vscpEvent ) );
        pEvent->pdata = NULL;   // NULL a must for a successful delete
        if ( VSCP_ERROR_SUCCESS == ( rv = vscphlp_blockingReceiveEvent( handle2, pEvent, 30000 ) ) ) {
            printf( "vscphlp_blockingReceiveEvent: Success. - Channel 2 " );
            printf(" Event: class=%d Type=%d sizeData=%d ",
                        pEvent->vscp_class,
                        pEvent->vscp_type,
                        pEvent->sizeData );
            if ( pEvent->sizeData && ( NULL != pEvent->pdata ) ) {
                printf("Data = ");
                for ( int i=0; i<pEvent->sizeData; i++ ) {
                    printf("%d ", pEvent->pdata[i] );
                }
                printf("\n");
            }
            cntEvents++;
        }
	    else
	    {
            printf("vscphlp_blockingReceiveEvent: %d Failure - Channel 2, rv = %d\n", blockIteration, rv );
            closeAll( handle1, handle2 );
        return -1;
	    }

        vscphlp_deleteVSCPevent( pEvent );
        pEvent = NULL;
        blockIteration++;

    }

    t2 = current_timestamp();
    printf("Burst receive time %d ms\n", (int)(t2-t1) );

    // Quit receiveloop
    if ( VSCP_ERROR_SUCCESS == (rv = vscphlp_quitReceiveLoop( handle2 ) ) ) {
        printf( "vscphlp_quitReceiveLoop: Success. - Channel 2\n" );
    }
    else {
        printf("vscphlp_quitReceiveLoop: %d Failure - Channel 2, rv = %d\n", blockIteration, rv );
        closeAll( handle1, handle2 );
        return -1;
    }


#endif



//                               Variables












// -------------------------------------------------------------------------------------------------




//return 0;



#ifdef TEST_HELPERS

    printf("\n\n");
    printf("\n\nTesting helpers\n");
    printf("===============\n");


    pEvent = malloc( sizeof( vscpEvent ) );
    if ( NULL == pEvent ) {
        printf("Allocation of event failed!\n");
        closeAll( handle1, handle2 );
        return -1;
    }
    pEvent->head = 0;
    pEvent->vscp_class = 10;
    pEvent->vscp_type = 6;
    pEvent->obid = 0;
    pEvent->timestamp = 0;
    memset( pEvent->GUID, 0, 16 );
    pEvent->sizeData = 3;
    pEvent->pdata = malloc( sizeof( unsigned char[3] ) );
    if ( NULL == pEvent->pdata ) {
        printf("Allocation of event data failed!\n");
        free( pEvent );
        closeAll( handle1, handle2 );
        return -1;
    }
    pEvent->pdata[ 0 ] = 138;
    pEvent->pdata[ 1 ] = 0;
    pEvent->pdata[ 2 ] = 30;

    vscpEventEx ex3;
    ex3.head = 0;
    ex3.vscp_class = 10;
    ex3.vscp_type = 6;
    ex3.obid = 0;
    ex3.timestamp = 0;
    memset( ex3.GUID, 0, 16 );
    ex3.sizeData = 3;
    ex3.data[ 0 ] = 138;
    ex3.data[ 1 ] = 0;
    ex3.data[ 2 ] = 30;

    long readValue = vscphlp_readStringValue("0x22");
    if ( 0x22 == readValue ) {
        printf("vscphlp_readStringValue: Success correct = %ld\n", readValue );
    }
    else {
        printf("vscphlp_readStringValue: Error - readStringValue = %ld\n", readValue );
        closeAll( handle1, handle2 );
        return -1;
    }


    readValue = vscphlp_readStringValue("-00000000099");
    if ( -99 == readValue ) {
        printf("vscphlp_readStringValue: Success  correct = %ld\n", readValue );
    }
    else {
        printf("vscphlp_readStringValue: Error - readStringValue = %ld\n", readValue );
        closeAll( handle1, handle2 );
        return -1;
    }




    unsigned char eventPriority;
    if ( 0 == ( eventPriority = vscphlp_getVscpPriority( pEvent ) ) ) {
        printf("vscphlp_getVscpPriority: Success - Event priority = %d\n", eventPriority );
    }
    else {
        printf("vscphlp_getVscpPriority: Error - Event priority = %d\n", eventPriority );
        closeAll( handle1, handle2 );
        return -1;
    }


    if ( 0 == ( eventPriority = vscphlp_getVscpPriorityEx( &ex3 ) ) ) {
        printf("vscphlp_getVscpPriorityEx: Success - EventEx priority = %d\n", eventPriority );
    }
    else {
        printf("vscphlp_getVscpPriorityEx: Error - Get EventEx priority = %d\n", eventPriority );
        closeAll( handle1, handle2 );
        return -1;
    }


    vscphlp_setVscpPriority( pEvent, 3 );
    if ( 3 == ( eventPriority = vscphlp_getVscpPriority( pEvent ) ) ) {
        printf("vscphlp_setVscpPriority: Success - Event priority = %d\n", eventPriority );
    }
    else {
        printf("vscphlp_setVscpPriority - Error - vscphlp_setVscpPriority = %d\n", eventPriority );
        closeAll( handle1, handle2 );
        return -1;
    }


    vscphlp_setVscpPriorityEx( &ex3, 7 );
    if ( 7 == ( eventPriority = vscphlp_getVscpPriorityEx( &ex3 ) ) ) {
        printf("vscphlp_setVscpPriorityEx: Success - Event priority = %d\n", eventPriority );
    }
    else {
        printf("vscphlp_setVscpPriorityEx: Error - vscphlp_setVscpPriorityEx = %d\n", eventPriority );
        closeAll( handle1, handle2 );
        return -1;
    }

    unsigned char vscphead;
    unsigned long canalid = 0x0c0a0601;
    vscphead = vscphlp_getVSCPheadFromCANALid( canalid );
    if ( 96 == vscphead ) {
        printf("vscphlp_getVSCPheadFromCANALid: Success - VSCP head = %d\n", vscphead );
    }
    else {
        printf("vscphlp_getVSCPheadFromCANALid: Error - vscphlp_getVSCPheadFromCANALid = %d\n", vscphead );
        closeAll( handle1, handle2 );
        return -1;
    }


    unsigned short canal_vscpclass = vscphlp_getVSCPclassFromCANALid( canalid );
    if ( 10 == canal_vscpclass ) {
        printf("vscphlp_getVSCPclassFromCANALid: Success - VSCP Class = %d\n", canal_vscpclass );
    }
    else {
        printf("vscphlp_getVSCPclassFromCANALid: Error - vscphlp_getVSCPclassFromCANALid = %d\n", canal_vscpclass );
        closeAll( handle1, handle2 );
        return -1;
    }


    unsigned short canal_vscptype = vscphlp_getVSCPtypeFromCANALid( canalid );
    if ( 6 == canal_vscptype ) {
        printf("vscphlp_getVSCPtypeFromCANALid: Success - VSCP Type = %d\n", canal_vscptype );
    }
    else {
        printf("vscphlp_getVSCPtypeFromCANALid: Error - vscphlp_getVSCPtypeFromCANALid = %d\n", canal_vscptype );
        closeAll( handle1, handle2 );
        return -1;
    }

    unsigned char canal_nickname = vscphlp_getVSCPnicknameFromCANALid( canalid );
    if ( 1 == canal_nickname ) {
        printf("vscphlp_getVSCPnicknameFromCANALid: Success - Nickname = %d\n", canal_nickname );
    }
    else {
        printf("vscphlp_getVSCPnicknameFromCANALid: - Error - vscphlp_getVSCPnicknameFromCANALid = %d\n", canal_nickname );
        closeAll( handle1, handle2 );
        return -1;
    }

    unsigned long constr_canal_id2 = vscphlp_getCANALidFromData( 3, 10, 6 );
    if ( 0x0c0a0600 == constr_canal_id2 ) {
        printf("vscphlp_getCANALidFromdata: Success - Nickname = %08lX\n", constr_canal_id2 );
    }
    else {
        printf("vscphlp_getCANALidFromdata: Error - vscphlp_getCANALidFromdata = %08lX\n", constr_canal_id2 );
        closeAll( handle1, handle2 );
        return -1;
    }

    constr_canal_id2 = vscphlp_getCANALidFromEvent( pEvent );
    if ( 0x0c0a0600 == constr_canal_id2 ) {
        printf("vscphlp_getCANALidFromEvent: Success - Nickname = %08lX\n", constr_canal_id2 );
    }
    else {
        printf("vscphlp_getCANALidFromEvent: Error - vscphlp_getCANALidFromEvent = %08lX\n", constr_canal_id2 );
        closeAll( handle1, handle2 );
        return -1;
    }

    constr_canal_id2 = vscphlp_getCANALidFromEventEx( &ex3 );
    if ( 0x1c0a0600 == constr_canal_id2 ) {
        printf("vscphlp_getCANALidFromEventEx: Success - Nickname = %08lX\n", constr_canal_id2 );
    }
    else {
        printf("vscphlp_getCANALidFromEventEx: Error - vscphlp_getCANALidFromEventEx = %08lX\n", constr_canal_id2 );
        closeAll( handle1, handle2 );
        return -1;
    }


    // Calculate CRC for event
    unsigned short crc = vscphlp_calc_crc_Event( pEvent, 0 );
    printf("vscphlp_calc_crc_Event: CRC = %04X\n", crc );

    // Calculate CRC for event
    crc = vscphlp_calc_crc_EventEx( pEvent, 0 );
    printf("vscphlp_calc_crc_EventEx: CRC = %04X\n", crc );

    // Calculate CRC for GID array
    unsigned char GUID2[16];
    memset( GUID2, 0, 16 );
    for ( int i=0;i<16; i++ ) {
        GUID2[i] = i;
    }
    unsigned char crc8 = vscphlp_calcCRC4GUIDArray( GUID2 );
    printf("vscphlp_calcCRC4GUIDArray: CRC = %02X\n", crc8 );

    // Calculate GUID for GUID string
    char strguid[64], strguid2[64];
    strcpy( strguid, "FF:FF:FF:FF:FF:FF:FF:00:00:00:00:7F:00:01:01:FD" );
    crc8 = vscphlp_calcCRC4GUIDString( strguid);
    printf("vscphlp_calcCRC4GUIDString: CRC = %02X\n", crc8 );


    if ( VSCP_ERROR_SUCCESS == vscphlp_getGuidFromString( pEvent, strguid ) ) {
        vscphlp_writeGuidToString( pEvent, strguid2, sizeof( strguid2 )-1 );
        printf( "vscphlp_writeGuidToString: Success - GUID=%s\n", strguid2 );
    }
    else {
        printf( "vscphlp_writeGuidToString: Error - vscphlp_writeGuidArrayToString\n");
        closeAll( handle1, handle2 );
        return -1;
    }

    if ( VSCP_ERROR_SUCCESS == vscphlp_getGuidFromStringEx( &ex3, strguid ) ) {
        vscphlp_writeGuidToStringEx( &ex3, strguid2, sizeof( strguid2 )-1 );
        printf( "vscphlp_getGuidFromStringEx: Success -  GUID=%s\n", strguid2 );
    }
    else {
        printf( "vscphlp_getGuidFromStringEx: Error - vscphlp_writeGuidArrayToString\n");
        closeAll( handle1, handle2 );
        return -1;
    }

    if ( VSCP_ERROR_SUCCESS == vscphlp_writeGuidToString4Rows( pEvent, strguid2, sizeof( strguid2 )-1 ) ) {
        printf( "vscphlp_writeGuidToString4Rows: Success - GUID\n%s\n", strguid2 );
    }
    else {
        printf( "vscphlp_writeGuidToString4Rows: Error - vscphlp_writeGuidArrayToString\n");
        closeAll( handle1, handle2 );
        return -1;
    }

    if ( VSCP_ERROR_SUCCESS == vscphlp_writeGuidToString4RowsEx( &ex3, strguid2, sizeof( strguid2 )-1 ) ) {
        printf( "vscphlp_writeGuidToString4Rows: Success - GUID\n%s\n", strguid2 );
    }
    else {
        printf( "vscphlp_writeGuidToString4Rows: Error - vscphlp_writeGuidArrayToString\n");
        closeAll( handle1, handle2 );
        return -1;
    }

    if ( VSCP_ERROR_SUCCESS == vscphlp_writeGuidArrayToString( GUID2, strguid2, sizeof( strguid2 )-1 ) ) {
        printf( "vscphlp_writeGuidToString4Rows: Successs - GUID=%s\n", strguid2 );
    }
    else {
        printf( "vscphlp_writeGuidToString4Rows: Error - vscphlp_writeGuidArrayToString\n");
        closeAll( handle1, handle2 );
        return -1;
    }

    unsigned char emptyGUID[16];
    memset( emptyGUID,0, 16 );
    if ( vscphlp_isGUIDEmpty( emptyGUID ) ) {
        printf( "vscphlp_isGUIDEmpty: Success - GUID is detected as empty as it should be\n" );
    }
    else {
        printf( "vscphlp_isGUIDEmpty: Error -  vscphlp_isGUIDEmpty\n");
        closeAll( handle1, handle2 );
        return -1;
    }

    // GUID that is not empty
    if ( vscphlp_isGUIDEmpty( GUID2 ) ) {
        printf( "vscphlp_isGUIDEmpty: Error - Detected as empty but should NOT be.\n");
        closeAll( handle1, handle2 );
        return -1;
    }
    else {
        printf( "vscphlp_isGUIDEmpty: Success  - GUID is detected as NOT empty as it should be.\n" );
    }

    // GUID's are not the same
    if ( vscphlp_isSameGUID( emptyGUID, GUID2) ) {
        printf( "vscphlp_isSameGUID: Error - vscphlp_isSameGUID\n");
        closeAll( handle1, handle2 );
        return -1;
    }
    else {
        printf( "vscphlp_isSameGUID: Success  - Correct, GUIDs are not the same.\n" );
    }

    vscphlp_writeGuidArrayToString( GUID2, strguid2, sizeof( strguid2 )-1 );
    printf( "vscphlp_writeGuidArrayToString: GUID before reverse = %s\n", strguid2 );
    if ( VSCP_ERROR_SUCCESS == vscphlp_reverseGUID( GUID2 ) ) {
        vscphlp_writeGuidArrayToString( GUID2, strguid2, sizeof( strguid2 )-1 );
        printf( "vscphlp_writeGuidArrayToString: GUID after reverse = %s\n", strguid2 );
    }
    else {
        printf( "vscphlp_writeGuidArrayToString: Error - vscphlp_reverseGUID\n");
        closeAll( handle1, handle2 );
        return -1;
    }

    if ( VSCP_ERROR_SUCCESS == vscphlp_getGuidFromStringToArray( GUID2, strguid ) ) {
        vscphlp_writeGuidArrayToString( GUID2, strguid2, sizeof( strguid2 )-1 );
        printf( "vscphlp_writeGuidArrayToString: GUID  after reverse = %s\n", strguid2 );
    }
    else {
        printf( "vscphlp_writeGuidArrayToString: Error - vscphlp_getGuidFromStringToArray\n");
        closeAll( handle1, handle2 );
        return -1;
    }

    vscpEventEx ex4;
    if ( VSCP_ERROR_SUCCESS != vscphlp_convertVSCPtoEx( &ex4, pEvent ) ) {
        printf( "vscphlp_convertVSCPtoEx: Error - vscphlp_getGuidFromStringToArray\n");
        closeAll( handle1, handle2 );
        return -1;
    }

    vscpEvent *pEvent2 = malloc( sizeof( vscpEvent ) );
    pEvent2->pdata = NULL;
    if ( VSCP_ERROR_SUCCESS != vscphlp_convertVSCPfromEx( pEvent2, &ex4 ) ) {
        printf( "vscphlp_convertVSCPfromEx: Error - vscphlp_convertVSCPfromEx\n");
        closeAll( handle1, handle2 );
        return -1;
    }
    vscphlp_deleteVSCPevent( pEvent2 );
    pEvent2 = NULL;

    //vscpEventFilter filter;
    vscphlp_clearVSCPFilter( &filter );

    if ( VSCP_ERROR_SUCCESS != vscphlp_readFilterFromString( &filter,
                "1,0x0000,0x0006,ff:ff:ff:ff:ff:ff:ff:01:00:00:00:00:00:00:00:00" ) ) {
        printf( "vscphlp_readFilterFromString: Error - vscphlp_readFilterFromString\n");
        closeAll( handle1, handle2 );
        return -1;
    }
    else {
        printf( "vscphlp_readFilterFromString: Success.\n");
    }

    if ( VSCP_ERROR_SUCCESS != vscphlp_readMaskFromString( &filter,
                "1,0x0000,0x0006,ff:ff:ff:ff:ff:ff:ff:01:00:00:00:00:00:00:00:00" ) ) {
        printf( "vscphlp_readMaskFromString: Error - vscphlp_readMaskFromString\n");
        closeAll( handle1, handle2 );
        return -1;
    }
    else {
        printf( "vscphlp_readMaskFromString: Success.\n");
    }


    if ( vscphlp_doLevel2Filter( pEvent, &filter ) ) {
        printf( "vscphlp_doLevel2Filter: Event pass: \n");
    }
    else {
        printf( "vscphlp_doLevel2Filter: Event does NOT pass: \n");
    }

    vscpEvent *pEvent3 = malloc( sizeof( vscpEvent ) );
    pEvent3->pdata = NULL;
    canalMsg canalMsg = { 0 };
    canalMsg.id = 0x0c0a0601;
    canalMsg.sizeData = 3;
    canalMsg.data[0] = 138;
    canalMsg.data[1] = 0;
    canalMsg.data[2] = 30;
    if ( VSCP_ERROR_SUCCESS == vscphlp_convertCanalToEvent( pEvent3,
                                                               &canalMsg,
                                                               GUID2 ) ) {
        printf( "vscphlp_convertCanalToEvent: Success - VSCP class=%d Type=%d\n", pEvent3->vscp_class, pEvent3->vscp_type );
    }
    else {
        printf( "vscphlp_convertCanalToEvent: Error\n");
        closeAll( handle1, handle2 );
        return -1;
    }

    // Free the event
    vscphlp_deleteVSCPevent( pEvent3 );
    pEvent3 = NULL;

    vscpEventEx ex5;
    if ( VSCP_ERROR_SUCCESS == vscphlp_convertCanalToEventEx( &ex5,
                                                                &canalMsg,
                                                                GUID2 ) ) {
        printf( "vscphlp_convertCanalToEventEx: Success - VSCP class=%d Type=%d\n", ex5.vscp_class, ex5.vscp_type );
    }
    else {
        printf( "vscphlp_convertCanalToEvent: Error\n");
        closeAll( handle1, handle2 );
        return -1;
    }


    if ( VSCP_ERROR_SUCCESS == vscphlp_convertEventToCanal( &canalMsg, pEvent ) ) {
        printf( "vscphlp_convertEventToCanal: Success - id=%08lX\n", canalMsg.id );
    }
    else {
        printf( "vscphlp_convertEventToCanal: Error: \n");
        closeAll( handle1, handle2 );
        return -1;
    }

    if ( VSCP_ERROR_SUCCESS == vscphlp_convertEventExToCanal( &canalMsg, &ex5 ) ) {
        printf( "vscphlp_convertEventExToCanal: Success - id=%08lX\n", canalMsg.id );
    }
    else {
        printf( "vscphlp_convertEventExToCanal: Error: \n");
        closeAll( handle1, handle2 );
        return -1;
    }


    printf( "vscphlp_makeTimeStamp  %04lX\n", vscphlp_makeTimeStamp() );


    vscpEvent *pEventFrom = malloc( sizeof( vscpEvent ) );
    vscpEvent *pEventTo = malloc( sizeof( vscpEvent ) );
    pEventFrom->head = 0;
    pEventFrom->vscp_class = 10;
    pEventFrom->vscp_type = 6;
    pEventFrom->obid = 0;
    pEventFrom->timestamp = 0;
    memset( pEventFrom->GUID, 0, 16 );
    pEventFrom->sizeData = 2;
    pEventFrom->pdata = malloc( sizeof( unsigned char[2] ) );
    pEventFrom->pdata[ 0 ] = 0xAA;
    pEventFrom->pdata[ 1 ] = 0x55;

    if ( VSCP_ERROR_SUCCESS == vscphlp_copyVSCPEvent( pEventTo, pEventFrom ) ) {
        printf( "vscphlp_copyVSCPEvent: Success - %02X %02X \n", pEventTo->pdata[0], pEventTo->pdata[1] );
    }
    else {
        printf( "vscphlp_copyVSCPEvent: Error\n");
        closeAll( handle1, handle2 );
        return -1;
    }



    // Free the events
    vscphlp_deleteVSCPevent( pEventFrom );
    pEventFrom = NULL;

    vscphlp_deleteVSCPevent( pEventTo );
    pEventTo = NULL;

    pEvent = malloc( sizeof( vscpEvent ) );
    pEvent->pdata = (uint8_t *)malloc(4);

    char dataBuf[80];
    if ( VSCP_ERROR_SUCCESS == (rv = vscphlp_writeVscpDataToString( dataBuf,
                                                                pEvent,
                                                                sizeof( dataBuf )-1,
                                                                0 ) ) ) {
       printf( "vscphlp_writeVscpDataToString: Success - \n%s \n", dataBuf );
    }
    else {
        printf( "vscphlp_writeVscpDataToString: Error: %d \n", rv);
        closeAll( handle1, handle2 );
        return -1;
    }
    free( pEvent->pdata );
    pEvent->pdata = NULL;
    vscphlp_deleteVSCPevent( pEvent );

    unsigned char dataArray2[32];
    unsigned short sizeData;
    if ( VSCP_ERROR_SUCCESS ==
             vscphlp_setVscpDataArrayFromString( dataArray2,
                                       &sizeData,
                                       "1,2,3,4,5,6,0x07,0x55,3,4,0xaa,0xff,0xff" ) ) {
        printf( "vscphlp_setVscpDataArrayFromString: Success - size=%d Data = \n", sizeData );
        for ( int i=0; i<sizeData; i++ ) {
            printf("%d ", dataArray2[i] );
        }
        printf("\n");
    }
    else {
        printf( "vscphlp_setVscpDataArrayFromString: Error: \n");
        closeAll( handle1, handle2 );
        return -1;
    }


    if ( VSCP_ERROR_SUCCESS ==
             vscphlp_setVscpDataFromString( &e, "1,2,3,4,5,6,0x07,0x55,3,4,0xaa,0xff,0xff" ) ) {
        printf( "vscphlp_setVscpDataFromString: Success -  size=%d Data = \n", e.sizeData );
        for ( int i=0; i<e.sizeData; i++ ) {
            printf("%d ", e.pdata[i] );
        }
        printf("\n");
    }
    else {
        printf( "vscphlp_setVscpDataFromString: Error: \n");
        closeAll( handle1, handle2 );
        return -1;
    }


    char eventBuf[128];
    if ( VSCP_ERROR_SUCCESS == vscphlp_writeVscpEventToString( pEvent, eventBuf, sizeof( eventBuf )-1 ) ) {
        printf( "vscphlp_writeVscpEventToString: Success - Event = %s\n", eventBuf );
    }
    else {
        printf( "vscphlp_writeVscpEventToString: Error: \n");
        closeAll( handle1, handle2 );
        return -1;
    }


    if ( VSCP_ERROR_SUCCESS == vscphlp_writeVscpEventExToString( &ex3, eventBuf, sizeof( eventBuf )-1 ) ) {
        printf( "vscphlp_writeVscpEventToString: Success -  Event = %s\n", eventBuf );
    }
    else {
        printf( "vscphlp_writeVscpEventToString: Error: \n");
        closeAll( handle1, handle2 );
        return -1;
    }


    vscpEvent *pEventString1 = malloc( sizeof( vscpEvent ) );
    pEventString1->pdata = NULL;

    if ( VSCP_ERROR_SUCCESS == vscphlp_setVscpEventFromString( pEventString1,
                             "0,10,6,,,,FF:FF:FF:FF:FF:FF:FF:00:00:00:00:7F:00:01:01:FD,0x8A,0x00,0x1E" ) ) {
        printf( "vscphlp_setVscpEventFromString: Success class=%d Type=%d\n",
                   pEventString1->vscp_class, pEventString1->vscp_type );
    }
    else {
        printf( "vscphlp_setVscpEventFromString: Error: \n");
        closeAll( handle1, handle2 );
        return -1;
    }

    // Free the events
    vscphlp_deleteVSCPevent( pEventString1 );
    pEventString1 = NULL;


    vscpEventEx ex6;
    if ( VSCP_ERROR_SUCCESS == vscphlp_setVscpEventExFromString( &ex6,
                             "0,10,6,,,,FF:FF:FF:FF:FF:FF:FF:00:00:00:00:7F:00:01:01:FD,0x8A,0x00,0x1E" ) ) {
        printf( "vscphlp_setVscpEventExFromString: Success - class=%d Type=%d\n",
                   ex6.vscp_class, ex6.vscp_type );
    }
    else {
        printf( "vscphlp_setVscpEventExFromString: Error: \n");
        closeAll( handle1, handle2 );
        return -1;
    }

    vscphlp_deleteVSCPevent( pEvent );
    pEvent = NULL;


#endif











// -------------------------------------------------------------------------------------------------











#ifdef TEST_MEASUREMENT


    pEvent = malloc( sizeof( vscpEvent ) );
    if ( NULL == pEvent ) {
        printf("Allocation of event failed!\n");
        closeAll( handle1, handle2 );
        return -1;
    }
    pEvent->head = 0;
    pEvent->vscp_class = 10;
    pEvent->vscp_type = 6;
    pEvent->obid = 0;
    pEvent->timestamp = 0;
    memset( pEvent->GUID, 0, 16 );
    pEvent->sizeData = 3;
    pEvent->pdata = malloc( sizeof( unsigned char[3] ) );
    if ( NULL == pEvent->pdata ) {
        printf("Allocation of event data failed!\n");
        free( pEvent );
        closeAll( handle1, handle2 );
        return -1;
    }
    pEvent->pdata[ 0 ] = 138;
    pEvent->pdata[ 1 ] = 0;
    pEvent->pdata[ 2 ] = 30;




    printf("\n\nMeasurement helpers\n");
    printf("===================\n");

    unsigned char dataCoding = vscphlp_getMeasurementDataCoding( pEvent );
    if ( 138 == dataCoding  ) {
        printf("vscphlp_getMeasurementDataCoding: Success - Data Coding = %d\n", dataCoding );
    }
    else {
        printf("vscphlp_getMeasurementDataCoding: Error - Data Coding = %d\n", dataCoding );
        closeAll( handle1, handle2 );
        return -1;
    }


    unsigned char bitarry[3];
    bitarry[0] = VSCP_DATACODING_BIT; // Data coding byte. Default unit, sensoridx=0
    bitarry[1] = 0x55;
    bitarry[2] = 0xAA;
    unsigned long long bitarray64 = vscphlp_getDataCodingBitArray( bitarry, sizeof( bitarry ) );
    if ( bitarray64 ==  0x55AA ) {
        printf("vscphlp_getDataCodingBitArray: Success.\n");
    }
    else {
        printf("vscphlp_getDataCodingBitArray: Error -  [%d]\n", dataCoding );
        closeAll( handle1, handle2 );
        return -1;
    }

    unsigned char normarry[4];
    normarry[0] = 0x89; // Data coding byte: Normalized integer, unit=1, sensoridx=1
    normarry[1] = 0x02;
    normarry[2] = 0x01;
    normarry[3] = 0x36;
    double value =  vscphlp_getDataCodingNormalizedInteger( normarry, sizeof( normarry ) );
    if ( 31000.0 == value ) {
        printf("vscphlp_getDataCodingNormalizedInteger: Success -  Value = %f \n", value );
    }
    else {
        printf("vscphlp_getDataCodingNormalizedInteger: Error - value = %f \n", value );
        closeAll( handle1, handle2 );
        return -1;
    }

    normarry[0] = 0x60; // Data coding byte: Integer, unit=0, sensoridx=0
    normarry[1] = 0xFF;
    normarry[2] = 0xFF;
    normarry[3] = 0xFF;
    unsigned long long val64 = vscphlp_getDataCodingInteger( normarry, sizeof( normarry ) );
    printf("vscphlp_getDataCodingInteger: Success -  value = %llu \n", val64 );

    unsigned char stringarry[6];
    stringarry[0] = VSCP_DATACODING_STRING; // Data cding byte. Default unit, sensoridx=0
    stringarry[1] = 0x32;
    stringarry[2] = 0x33;
    stringarry[3] = 0x34;
    stringarry[4] = 0x2E;
    stringarry[5] = 0x35;
    char stringbuf[2048];
    if ( VSCP_ERROR_SUCCESS == vscphlp_getDataCodingString( stringarry,
                                                              sizeof( stringarry ),
                                                              stringbuf,
                                                              sizeof( stringbuf ) ) ) {
        printf("vscphlp_getDataCodingString: Success -  value = %s \n", stringbuf );
    }
    else {
        printf("vscphlp_getDataCodingString: Error -  value = %s \n", stringbuf );
        closeAll( handle1, handle2 );
        return -1;
    }



    vscpEvent *pEventMeasurement = malloc( sizeof( vscpEvent ) );
    pEventMeasurement->head = 0;
    pEventMeasurement->vscp_class = 10;
    pEventMeasurement->vscp_type = 6;
    pEventMeasurement->obid = 0;
    pEventMeasurement->timestamp = 0;
    memset( pEventMeasurement->GUID, 0, 16 );
    pEventMeasurement->sizeData = 4;
    pEventMeasurement->pdata = malloc( sizeof( unsigned char[ pEventMeasurement->sizeData ] ) );
    pEventMeasurement->pdata[0] = 0x89;
    pEventMeasurement->pdata[1] = 0x02;
    pEventMeasurement->pdata[2] = 0x00;
    pEventMeasurement->pdata[3] = 0xF1;

    if ( VSCP_ERROR_SUCCESS == vscphlp_getVSCPMeasurementAsString( pEventMeasurement,
                                                                    stringbuf,
                                                                    sizeof( stringbuf ) ) ) {
        printf("vscphlp_getVSCPMeasurementAsString: Success -  value = %s \n", stringbuf );
    }
    else {
        printf("vscphlp_getVSCPMeasurementAsString: Error -  value = %s \n", stringbuf );
        closeAll( handle1, handle2 );
        return -1;
    }




    pEventMeasurement->pdata[0] = 0x89;
    pEventMeasurement->pdata[1] = 0x02;
    pEventMeasurement->pdata[2] = 0xFF;
    pEventMeasurement->pdata[3] = 0xF1;

    if ( VSCP_ERROR_SUCCESS == vscphlp_getVSCPMeasurementAsString( pEventMeasurement,
                                                                    stringbuf,
                                                                    sizeof( stringbuf ) ) ) {
        printf("vscphlp_getVSCPMeasurementAsString: Success -  value = %s \n", stringbuf );
    }
    else {
        printf("vscphlp_getVSCPMeasurementAsString: Error -  value = %s \n", stringbuf );
        closeAll( handle1, handle2 );
        return -1;
    }




    pEventMeasurement->pdata[0] = VSCP_DATACODING_BIT;
    pEventMeasurement->pdata[1] = 0x55;
    pEventMeasurement->pdata[2] = 0xAA;
    pEventMeasurement->pdata[3] = 0x55;

    if ( VSCP_ERROR_SUCCESS == vscphlp_getVSCPMeasurementAsString( pEventMeasurement,
                                                                    stringbuf,
                                                                    sizeof( stringbuf ) ) ) {
        printf("vscphlp_getVSCPMeasurementAsString: Success -  value = %s \n", stringbuf );
    }
    else {
        printf("vscphlp_getVSCPMeasurementAsString: Error -  value = %s \n", stringbuf );
        closeAll( handle1, handle2 );
        return -1;
    }



    pEventMeasurement->pdata[0] = VSCP_DATACODING_BYTE;
    pEventMeasurement->pdata[1] = 0x55;
    pEventMeasurement->pdata[2] = 0xAA;
    pEventMeasurement->pdata[3] = 0x55;

    if ( VSCP_ERROR_SUCCESS == vscphlp_getVSCPMeasurementAsString( pEventMeasurement,
                                                                    stringbuf,
                                                                    sizeof( stringbuf ) ) ) {
        printf("vscphlp_getVSCPMeasurementAsString: Success -  value = %s \n", stringbuf );
    }
    else {
        printf("vscphlp_getVSCPMeasurementAsString: Error -  value = %s \n", stringbuf );
        closeAll( handle1, handle2 );
        return -1;
    }


    pEventMeasurement->pdata[0] = VSCP_DATACODING_STRING;
    pEventMeasurement->pdata[1] = 0x33;
    pEventMeasurement->pdata[2] = 0x31;
    pEventMeasurement->pdata[3] = 0x34;

    if ( VSCP_ERROR_SUCCESS == vscphlp_getVSCPMeasurementAsString( pEventMeasurement,
                                                                    stringbuf,
                                                                    sizeof( stringbuf ) ) ) {
        printf("vscphlp_getVSCPMeasurementAsString: Success -  value = %s \n", stringbuf );
    }
    else {
        printf("vscphlp_getVSCPMeasurementAsString: Error -  value = %s \n", stringbuf );
        closeAll( handle1, handle2 );
        return -1;
    }


    pEventMeasurement->pdata[0] = VSCP_DATACODING_INTEGER;
    pEventMeasurement->pdata[1] = 0x00;
    pEventMeasurement->pdata[2] = 0xFF;
    pEventMeasurement->pdata[3] = 0xFF;

    if ( VSCP_ERROR_SUCCESS == vscphlp_getVSCPMeasurementAsString( pEventMeasurement,
                                                                    stringbuf,
                                                                    sizeof( stringbuf ) ) ) {
        printf("vscphlp_getVSCPMeasurementAsString: Success -  value = %s \n", stringbuf );
    }
    else {
        printf("vscphlp_getVSCPMeasurementAsString: Error -  value = %s \n", stringbuf );
        closeAll( handle1, handle2 );
        return -1;
    }



    pEventMeasurement->pdata[0] = VSCP_DATACODING_INTEGER;
    pEventMeasurement->pdata[1] = 0xFF;
    pEventMeasurement->pdata[2] = 0xFF;
    pEventMeasurement->pdata[3] = 0xFF;

    if ( VSCP_ERROR_SUCCESS == vscphlp_getVSCPMeasurementAsString( pEventMeasurement,
                                                                    stringbuf,
                                                                    sizeof( stringbuf ) ) ) {
        printf("vscphlp_getVSCPMeasurementAsString: Success -  value = %s \n", stringbuf );
    }
    else {
        printf("vscphlp_getVSCPMeasurementAsString: Error -  value = %s \n", stringbuf );
        closeAll( handle1, handle2 );
        return -1;
    }



    pEventMeasurement->pdata[0] = VSCP_DATACODING_INTEGER;
    pEventMeasurement->pdata[1] = 0xFF;
    pEventMeasurement->pdata[2] = 0xFF;
    pEventMeasurement->pdata[3] = 0xFF;
    if ( VSCP_ERROR_SUCCESS == vscphlp_getVSCPMeasurementAsDouble( pEventMeasurement, &value ) ) {
        printf("vscphlp_getVSCPMeasurementAsDouble: Success -  value = %lf\n", value );
    }
    else {
        printf("vscphlp_getVSCPMeasurementAsDouble: Error -  value = %lf \n", value );
        closeAll( handle1, handle2 );
        return -1;
    }

    vscpEvent *pEventfloat = malloc( sizeof( vscpEvent ) );
    pEventfloat->head = 0;
    pEventfloat->vscp_class = 10;
    pEventfloat->vscp_type = 6;
    pEventfloat->obid = 0;
    pEventfloat->timestamp = 0;
    memset( pEventfloat->GUID, 0, 16 );
    pEventfloat->sizeData = 8;
    pEventfloat->pdata = malloc( sizeof( unsigned char[ pEventfloat->sizeData ] ) );
    pEventfloat->pdata[0] = 234;
    pEventfloat->pdata[1] = 46;
    pEventfloat->pdata[2] = 68;
    pEventfloat->pdata[3] = 84;
    pEventfloat->pdata[4] = 251;
    pEventfloat->pdata[5] = 33;
    pEventfloat->pdata[6] = 9;
    pEventfloat->pdata[7] = 64;

    if ( VSCP_ERROR_SUCCESS == vscphlp_getVSCPMeasurementFloat64AsString( pEventfloat,
                                                                            stringbuf,
                                                                            sizeof( stringbuf ) ) ) {
        printf("vscphlp_getVSCPMeasurementFloat64AsString: Success -  value = %s \n", stringbuf );
    }
    else {
        printf("vscphlp_getVSCPMeasurementFloat64AsString: Error -  value = %s \n", stringbuf );
        closeAll( handle1, handle2 );
        return -1;
    }

    // Free the event
    vscphlp_deleteVSCPevent( pEventfloat );
    pEventfloat = NULL;

    // Free the event
    vscphlp_deleteVSCPevent( pEventMeasurement );
    pEventMeasurement = NULL;

#endif


    // -------------------------------------------------------------------------------------------------


    // Free the event
    if ( NULL == pEvent ) printf("pEvent is NULL.\n");
    printf("Delete pEvent working event.\n");
    vscphlp_deleteVSCPevent( pEvent );
    pEvent = NULL;

    printf("\n\n\n");




     t1 = t2 = current_timestamp();
	for ( int i=0; i<BURST_SEND_COUNT; i++ ) {

		exa.data[0] = (i>>8) & 0xff;
    	exa.data[1] = i & 0xff;

    	if ( VSCP_ERROR_SUCCESS == (rv = vscphlp_noop( handle1 ) ) ) {
        	printf( "vscphlp_noop: Success. %d\n", i );
    	}
    	else {
        	printf("vscphlp_noop: Failure - rv = %d\n", rv );
        	closeAll( handle1, handle2 );
            return -1;
    	}
	}

    t2 = current_timestamp();
    printf("Burst NOOP time %d ms\n", (int)(t2-t1) );






    // free data
    printf("Free 'e' working event data.\n");
    if ( NULL != pEvent) free( e.pdata );

    if ( VSCP_ERROR_SUCCESS == vscphlp_close( handle1 ) ) {
        printf( "Command success: vscphlp_close on channel 1\n" );
    }

    if ( VSCP_ERROR_SUCCESS == vscphlp_close( handle2 ) ) {
        printf( "Command success: vscphlp_close on channel 2\n" );
    }

    vscphlp_closeSession( handle1 );
    vscphlp_closeSession( handle2 );

    //printf("\n\nHit ENTER to terminate Error Count= %d\n", error_cnt );
    //(void)getchar();



    return 0;
}
