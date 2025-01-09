// example1.c 
//

#include "stdio.h"
#include "vscphelperlib.h"

#define HOST "vscp2.vscp.org:9598"
//#define HOST "vscp1.vscp.org:9598"
//#define HOST "185.144.156.45:9598"
//#define HOST "127.0.0.1:9598"

int main(int argc, char* argv[])
{
    long handle;
    unsigned long rv;
    unsigned char v1,v2,v3;
    
    // New session
    printf("Starting a new session to [" HOST "] ...\n");
    handle = vscphlp_newSession();
    if ( handle ) {
		printf("vscphlp_newSession: Success!\n");
	}
	else  {
		printf("vscphlp_newSession: Failed. handle = %ld\n", handle );
		vscphlp_closeSession( handle );
		return -1;
	}

    printf("Open channel...\n");
    if ( VSCP_ERROR_SUCCESS == vscphlp_open( handle, 
                 								HOST,
                 								"admin",
    	             							"secret" ) ) {
		
		printf("vscphlp_open: Success!\n");
	
		if ( VSCP_ERROR_SUCCESS == vscphlp_noop( handle ) ) {
			printf("vscphlp_noop: 1 Success!\n");
		}   
		else {
			printf( "vscphlp_noop: 1 Failure %ld\n", rv );
			vscphlp_close( handle );
			vscphlp_closeSession( handle );
			return -1;
		}
    
    
		if ( VSCP_ERROR_SUCCESS == (rv = vscphlp_getVersion( handle, &v1, &v2, &v3 ) ) ) {
			printf( "vscphlp_getVersion: Success\n" );
			printf( "Version for VSCP daemon is %d.%d.%d\n", v1,v2,v3 );
		}
		else {
			printf( "vscphlp_getVersion: Failure %ld\n", rv );
			vscphlp_close( handle );
			vscphlp_closeSession( handle );
			return -1;
		}
    
		if ( VSCP_ERROR_SUCCESS == vscphlp_noop( handle ) ) {
			printf("vscphlp_noop: 2 Success!\n");
		}   
		else {
			printf( "vscphlp_noop: 2 Failure %ld\n", rv );
			vscphlp_close( handle );
			vscphlp_closeSession( handle );
			return -1;
		}

		if ( VSCP_ERROR_SUCCESS == vscphlp_close( handle ) ) {
			printf("vscphlp_close: Success!\n");
		}
		else {
			printf( "vscphlp_close: 2 Failure %ld\n", rv );
		}
	
		vscphlp_closeSession( handle );
	
	
    } 
    else {
        printf( "vscphlp_open: Failure. host %s\n", HOST );
		vscphlp_closeSession( handle ); 
        return -1;
    }
   
	return 0;
}
