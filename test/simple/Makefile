
# Debug or Release
##CONFIG = -g3 -ggdb -O0 -DDEBUG=1
CONFIG = -g2 -Os -DNDEBUG=1

OUR_CFLAGS = $(CONFIG) -std=c99 -Wall -Wextra -Wconversion -Wformat -Wformat=2 -Wformat-security -Wno-deprecated-declarations -Wno-unused-function

LIBS =  -lexpat -lssl -lz -lrt -lm -lcrypto -lpthread -ldl -L../../linux/ -l:libvscphelper.a
CFLAGS = -std=c11 -g -O0
CPPFLAGS = -std=c++11  -g -O0
VSCPHELPER_OBJECTS =  ../../linux/vscphelperlib.o \
	../../linux/vscpdatetime.o\
	../../linux/vscpremotetcpif.o \
	../../linux/vscpcanaldeviceif.o \
	../../linux/vscphelper.o \
	../../linux/sockettcp.o \
	../../linux/guid.o \
	../../linux/crc.o \
	../../linux/crc8.o \
	../../linux/vscp_aes.o \
	../../linux/vscpmd5.o \
	../../linux/fastpbkdf2.o \
	../../linux/vscpbase64.o 

all:	simple

simple:   simple.c
	        $(CXX) $(CPPFLAGS) simple.c -o simple  -I .. -I ../.. -I../../vscp/src/common \
			-I../../vscp/src/vscp/common  $(VSCPHELPER_OBJECTS) $(LIBS) 

clean:
	rm -f simple
