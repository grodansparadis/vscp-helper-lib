
# Debug or Release
##CONFIG = -g3 -ggdb -O0 -DDEBUG=1
CONFIG = -g2 -Os -DNDEBUG=1

OUR_CFLAGS = $(CONFIG) -std=c99 -Wall -Wextra -Wconversion -Wformat -Wformat=2 -Wformat-security -Wno-deprecated-declarations -Wno-unused-function

LIBS =  -lexpat -lssl -lz -lrt -lm  -lcrypto -lpthread -ldl -L../../linux/ -l:libvscphelper.a
CFLAGS = -std=c11 -g -O0
CPPFLAGS = -std=c++11  -g -O0

VSCPHELPER_SRC =  ../../src/vscphelperlib.cpp \
	${VSCP_ROOT}/src/vscp/common/vscpdatetime.cpp\
	${VSCP_ROOT}/src/vscp/common/vscpremotetcpif.cpp \
	${VSCP_ROOT}/src/vscp/common/vscpcanaldeviceif.cpp \
	${VSCP_ROOT}/src/vscp/common/vscphelper.cpp \
	${VSCP_ROOT}/src/common/sockettcp.c \
	${VSCP_ROOT}/src/vscp/common/guid.cpp \
	${VSCP_ROOT}/src/common/crc.c \
	${VSCP_ROOT}/src/common/crc8.c \
	${VSCP_ROOT}/src/common/vscp-aes.c \
	${VSCP_ROOT}/src/common/vscpmd5.c \
	${VSCP_ROOT}/src/common/vscpbase64.c

VSCPHELPER_OBJ =  ../../src/vscphelperlib.o \
	${VSCP_ROOT}/src/vscp/common/vscpdatetime.o\
	${VSCP_ROOT}/src/vscp/common/vscpremotetcpif.o \
	${VSCP_ROOT}/src/vscp/common/vscpcanaldeviceif.o \
	${VSCP_ROOT}/src/vscp/common/vscphelper.o \
	${VSCP_ROOT}/src/common/sockettcp.o \
	${VSCP_ROOT}/src/vscp/common/guid.o \
	${VSCP_ROOT}/src/common/crc.o \
	${VSCP_ROOT}/src/common/crc8.o \
	${VSCP_ROOT}/src/common/vscp_aes.o \
	${VSCP_ROOT}/src/common/vscpmd5.o \
	${VSCP_ROOT}/src/common/vscpbase64.o 

all:	simple

simple:   simple.c
	        $(CXX) $(CPPFLAGS) simple.c $(VSCPHELPER_SRC) -o simple  -I .. -I ../../ -I../../src -I${VSCP_ROOT}/src/common \
			-I${VSCP_ROOT}/src/vscp/common  $(VSCPHELPER_OBJ) $(LIBS) 

clean:
	rm -f simple
