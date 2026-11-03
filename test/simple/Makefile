VSCP_ROOT ?= ../../build/_deps/vscp-src
VSCPHELPER_LIB_DIR ?= ../../build
TARGET ?= simple

VSCPHELPER_MAJOR := $(shell awk '/^#define VSCP_HELPER_LIB_VERSION_MAJOR / {print $$3}' ../../src/libversion.h)

CFLAGS = -std=c11 -g -O0
CPPFLAGS += -I../../src -I$(VSCP_ROOT)/src/vscp/common
LDFLAGS += -L$(VSCPHELPER_LIB_DIR) -Wl,-rpath,$(abspath $(VSCPHELPER_LIB_DIR))
LDLIBS += -lvscphelper$(VSCPHELPER_MAJOR)

all: $(TARGET)

$(TARGET): simple.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $< $(LDFLAGS) $(LDLIBS) -o $@

clean:
	rm -f $(TARGET)
