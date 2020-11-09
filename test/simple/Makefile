
# Debug or Release
##CONFIG = -g3 -ggdb -O0 -DDEBUG=1
CONFIG = -g2 -Os -DNDEBUG=1

OUR_CFLAGS = $(CONFIG) -std=c99 -Wall -Wextra -Wconversion -Wformat -Wformat=2 -Wformat-security -Wno-deprecated-declarations -Wno-unused-function

LIBS =  -lexpat -lssl -lz -lrt -lm -lcrypto -lpthread -ldl
CFLAGS = -std=c11 -g -O0
CPPFLAGS = -std=c++11  -g -O0

all:	simple

simple:       simple.c
	        $(CXX) $(CPPFLAGS) simple.c -o simple -I .. -I ../.. -I../../vscp/src/common \
			-I../../vscp/src/vscp/common  $(LIBS) -lvscphelper

clean:
	rm -f simple
