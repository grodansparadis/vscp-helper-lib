#ifndef VSCP_RAW_TRANSPORT_H
#define VSCP_RAW_TRANSPORT_H

#include <stddef.h>
#include <stdint.h>

#include <openssl/bio.h>

enum sample_io_result {
    SAMPLE_IO_TIMEOUT = -2,
    SAMPLE_IO_ERROR = -1,
    SAMPLE_IO_CLOSED = 0,
    SAMPLE_IO_OK = 1
};

struct sample_endpoint {
    char host[512];
    char connect_host[514];
    char port[6];
};

int sample_parse_endpoint(struct sample_endpoint *endpoint, const char *address);
int sample_initialize(void);
uint64_t sample_millis(void);
int sample_connect(BIO *connection, const struct sample_endpoint *endpoint, uint64_t deadline);
int sample_read(BIO *connection, void *buffer, int length, uint64_t deadline);
int sample_write(BIO *connection, const void *buffer, size_t length, uint64_t deadline);
void sample_report_error(const char *operation);

#endif
