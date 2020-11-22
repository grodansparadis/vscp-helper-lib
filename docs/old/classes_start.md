# First project

The first test project, our "Hello World!", will be an application that connect and then logon to a remote VSCP daemon and then execute the NOOP (No Operation) command and then disconnects. Not very exciting in terms of usability but usable as a start point for further development.

The project source is [here](https///github.com/grodansparadis/vscp/tree/master/tests/noop).

The makefile look like this

`<code=make>`
CC = `wx-config --cc`
CXX = `wx-config --cxx`
MONGOOSE_CFLAGS = -DMG_ENABLE_THREADS -DMG_ENABLE_GETADDRINFO -UMG_ENABLE_SSL
CFLAGS = -g -O0 -pthread -D MG_ENABLE_THREADS -I../../src/vscp/common -I../../src/common
CXXFLAGS = -g -O0 
CPPFLAGS =  -I../../src/vscp/common -I../../src/common 
CPPFLAGS += `wx-config --cxxflags base `
CPPFLAGS += $(MONGOOSE_CFLAGS)
LDFLAGS = 
EXTRALIBS =  -lz -lrt -lm -lcrypto -lpthread
EXTRALIBS += `wx-config --libs base`
TEST_OBJECTS =  noop.o \

TEST_SPECIALS = vscphelper.o \
	vscpremotetcpif.o \
	guid.o \
	mongoose.o \
	crc8.o \
	crc.o \

all:	noop

vscphelper.o: ../..//src/vscp/common/vscphelper.o ../../src/vscp/common/vscphelper.h
	$(CXX)  $(CXXFLAGS) $(CPPFLAGS) -c ../../src/vscp/common/vscphelper.cpp -o $@

vscpremotetcpif.o: ../../src/vscp/common/vscpremotetcpif.o ../../src/vscp/common/vscpremotetcpif.h
	$(CXX)  $(CXXFLAGS) $(CPPFLAGS) -c ../../src/vscp/common/vscpremotetcpif.cpp -o $@

guid.o: ../../src/vscp/common/guid.o ../../src/vscp/common/guid.h
	$(CXX)  $(CXXFLAGS) $(CPPFLAGS) -c ../../src/vscp/common/guid.cpp -o $@

crc.o: ../../src/common/crc.o ../../src/common/crc.h 
	$(CC) $(CFLAGS) -c ../../src/common/crc.c -o $@

crc8.o: ../../src/common/crc8.o ../../src/common/crc8.h
	$(CC) $(CFLAGS) -c ../../src/common/crc8.c -o $@	

mongoose.o: ../../src/common/mongoose.o ../../src/common/mongoose.h
	$(CC) $(CFLAGS) $(MONGOOSE_CFLAGS) -c ../../src/common/mongoose.c -o $@ 	

noop: $(TEST_OBJECTS) $(TEST_SPECIALS)
	$(CXX)  -o $@ $(TEST_OBJECTS) $(TEST_SPECIALS) $(LDFLAGS) -L$(LIBDIRNAME)  $(EXTRALIBS)

clean:
	rm -f noop
	rm -f *.o

`</code>`

Noting strange. The **wx-config** is a program that comes with wxWidgets that give paths and other information needed to compile programs. Several of the files are compiled separately because they are built by other parts of the VSCP & Friends system also and if we don't do this we may have them linked together in versions we did not intend to use. You may not need this in your own project.

The code for the program looks like this

`<code=cpp>`
*/*//////////////////////////////////////////////////////////////////////////
// noop.cpp 
//
// https://www.vscp.org   Grodans Paradis AB   info@grodansparadis.com
//

#include `<stdio.h>`

#include `<stdlib.h>`
#include `<string.h>`

#include `<math.h>`

#include `<vscpremotetcpif.h>`

#include `<vscphelper.h>`

// Output text for happy moments if set to one
#define verbose_success         0

// Output text for sad moments if set to one
#define verbose_error           1

// Output text for talky moments if set to 1
#define verbose_info            1

// Standard connection (a VSCP daemon must be running here)
#define INTERFACE1_HOST         "127.0.0.1:9598"

#define INTERFACE1_USER         "admin"
#define INTERFACE1_PASSWORD     "secret"


// Count errors in the test
int error_cnt = 0;

int main(int argc, char* argv[])
{
    int rv;
    char *pHost = (char *)INTERFACE1_HOST;
    char *pUser = (char *)INTERFACE1_USER;
    char *pPassword = (char *)INTERFACE1_PASSWORD;

    VscpRemoteTcpIf m_vscpif;

    if ( !::wxInitialize() ) {
        fprintf(stderr, "Failed to initialize the wxWindows library, aborting.");
        return -1;
    }

    if ( argc > 1 ) {

        // Host ("localhost:9598"")
        if ( argc >= 2 ) {
            pHost = argv[1];
        }

        // Username ("admin)
        if ( argc >= 3 ) {
            pUser = argv[2];
        }

        // Password ("secret")
        if ( argc >= 4 ) {
            pPassword = argv[3];
        }
    }


    if ( verbose_info ) {
       printf("- VSCP remote interface class test program\n");
       printf("- ========================================\n\n\n");
    }

    // Open the interface
    if ( CANAL_ERROR_SUCCESS != m_vscpif.doCmdOpen( pHost, pUser, pPassword ) ) {
        printf("Error: Failed to open interface - closing.\n");
        return -1;
    }

    if ( verbose_info ) printf("- Connected to server.\n");


    // ------ Do work here ------


    // NOOP command
    if ( verbose_info ) printf("- Executing NOOP command on server.\n");
    if ( CANAL_ERROR_SUCCESS != m_vscpif.doCmdNOOP() ) {
        printf("Error: Failed to run NOOP command.\n");
        error_cnt++;
    }


    // ------ Do work here ------

    // Close the connection
    if ( verbose_info ) printf("- Disconnecting from server.\n");
    if ( CANAL_ERROR_SUCCESS != m_vscpif.doCmdClose() ) {
        printf("Error: Failed to close interface\n");
        error_cnt++;
    }

    printf("\n\nHit ENTER to terminate Error Count= %d\n", error_cnt );
    (void)getchar();
   
    return 0;
    
}
`</code>`

Nothing strange here either. You can run the program as

    ./noop host:port user admin

or 

    ./noop 127.0.0.1:9598 admin secret

or just

    ./noop

which will use the default connection parameters as of above.

As you can see a connection is made, the noop command is executed and the connection is closed. To  do fancy stuff just add your own code instead of the noop. It could not be easier.

All methods in the [VscpRemoteTcpIf class](https///github.com/grodansparadis/vscp/blob/master/src/vscp/common/vscpremotetcpif.h) is described [here](classes_vscpremotetcpipif_metods).

\\ 
----
{{  ::copyright.png?600  |}}

`<HTML>``<p style="color:red;text-align:center;">``<a href="https://www.grodansparadis.com">`Grodans Paradis AB`</a>``</p>``</HTML>`
