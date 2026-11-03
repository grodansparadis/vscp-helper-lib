#ifndef _WIN32
#ifndef _POSIX_C_SOURCE
#define _POSIX_C_SOURCE 200809L
#endif
#endif

#ifdef _WIN32
#include <winsock2.h>
#include <windows.h>
#else
#include <errno.h>
#include <poll.h>
#include <signal.h>
#include <time.h>
#endif

#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <openssl/err.h>

#include "raw_transport.h"

int sample_parse_endpoint(struct sample_endpoint *endpoint, const char *address)
{
    const char *original = address;
    const char *scheme = strstr(address, "://");
    const char *host;
    const char *separator;
    const char *digit;
    size_t host_length;
    size_t address_length = strlen(address);
    unsigned int port = 0;
    int bracketed;

    if (scheme && strncmp(address, "tcp://", 6) != 0) {
        fprintf(stderr, "Unsupported TCP endpoint: %s\n", original);
        return -1;
    }
    if (address_length + (scheme ? 0 : 6) >= 512) {
        goto invalid;
    }
    if (scheme) {
        address += 6;
    }

    bracketed = *address == '[';
    host = address + (bracketed ? 1 : 0);
    separator = bracketed ? strchr(host, ']') : strchr(host, ':');
    if (!separator || separator == host || (bracketed && separator[1] != ':')) {
        goto invalid;
    }
    host_length = (size_t)(separator - host);
    if (host_length >= sizeof(endpoint->host)) {
        goto invalid;
    }
    for (const char *character = host; character < separator; character++) {
        if ((unsigned char)*character <= ' ' || strchr("@/?#;\\[]", *character) ||
            (!bracketed && *character == ':')) {
            goto invalid;
        }
    }

    digit = separator + (bracketed ? 2 : 1);
    if (!*digit) {
        goto invalid;
    }
    for (; *digit; digit++) {
        if (*digit < '0' || *digit > '9' || port > 6553U ||
            (port == 6553U && *digit > '5')) {
            goto invalid;
        }
        port = port * 10U + (unsigned int)(*digit - '0');
    }
    if (!port) {
        goto invalid;
    }

    memcpy(endpoint->host, host, host_length);
    endpoint->host[host_length] = '\0';
    snprintf(endpoint->connect_host, sizeof(endpoint->connect_host),
             bracketed ? "[%s]" : "%s", endpoint->host);
    snprintf(endpoint->port, sizeof(endpoint->port), "%u", port);
    return 0;

invalid:
    fprintf(stderr, "Invalid TCP endpoint (expected host:port): %s\n", original);
    return -1;
}

int sample_initialize(void)
{
#ifndef _WIN32
    if (signal(SIGPIPE, SIG_IGN) == SIG_ERR) {
        perror("Cannot ignore SIGPIPE");
        return -1;
    }
#endif
    if (BIO_sock_init() != 1) {
        sample_report_error("Cannot initialize sockets");
        return -1;
    }
    return 0;
}

uint64_t sample_millis(void)
{
#ifdef _WIN32
    return (uint64_t)GetTickCount64();
#else
    struct timespec now;
    if (clock_gettime(CLOCK_MONOTONIC, &now) != 0) {
        perror("Cannot read the monotonic clock");
        exit(EXIT_FAILURE);
    }
    return (uint64_t)now.tv_sec * 1000U + (uint64_t)now.tv_nsec / 1000000U;
#endif
}

static int sample_wait(BIO *connection, uint64_t deadline)
{
    int descriptor = BIO_get_fd(connection, NULL);
    int want_read = BIO_should_read(connection);
    int want_write = BIO_should_write(connection) || BIO_should_io_special(connection);

    if (descriptor < 0 || (!want_read && !want_write)) {
        fprintf(stderr, "Cannot wait for the connection\n");
        return SAMPLE_IO_ERROR;
    }

    for (;;) {
        uint64_t now = sample_millis();
        if (now >= deadline) {
            return SAMPLE_IO_TIMEOUT;
        }
        uint64_t remaining = deadline - now;
        int timeout = remaining > INT_MAX ? INT_MAX : (int)remaining;
#ifdef _WIN32
        fd_set read_set, write_set, error_set;
        struct timeval interval = {timeout / 1000, (timeout % 1000) * 1000};
        FD_ZERO(&read_set);
        FD_ZERO(&write_set);
        FD_ZERO(&error_set);
        if (want_read) {
            FD_SET((SOCKET)descriptor, &read_set);
        }
        if (want_write) {
            FD_SET((SOCKET)descriptor, &write_set);
        }
        FD_SET((SOCKET)descriptor, &error_set);
        int result = select(0, &read_set, &write_set, &error_set, &interval);
        if (result < 0 && WSAGetLastError() == WSAEINTR) {
            continue;
        }
        if (result < 0) {
            fprintf(stderr, "Socket wait failed: %d\n", WSAGetLastError());
            return SAMPLE_IO_ERROR;
        }
#else
        struct pollfd poll_descriptor = {
            descriptor, (short)((want_read ? POLLIN : 0) | (want_write ? POLLOUT : 0)), 0
        };
        int result = poll(&poll_descriptor, 1, timeout);
        if (result < 0 && errno == EINTR) {
            continue;
        }
        if (result < 0) {
            perror("Socket wait failed");
            return SAMPLE_IO_ERROR;
        }
        if (result > 0 && (poll_descriptor.revents & POLLNVAL)) {
            fprintf(stderr, "Socket wait failed: invalid descriptor\n");
            return SAMPLE_IO_ERROR;
        }
#endif
        return result > 0 ? SAMPLE_IO_OK : SAMPLE_IO_TIMEOUT;
    }
}

int sample_connect(BIO *connection, const struct sample_endpoint *endpoint, uint64_t deadline)
{
    if (BIO_set_conn_hostname(connection, endpoint->connect_host) <= 0 ||
        BIO_set_conn_port(connection, endpoint->port) <= 0 ||
        BIO_set_nbio(connection, 1) <= 0) {
        return SAMPLE_IO_ERROR;
    }

    for (;;) {
        if (sample_millis() >= deadline) {
            return SAMPLE_IO_TIMEOUT;
        }
        ERR_clear_error();
        if (BIO_do_connect(connection) > 0) {
            return SAMPLE_IO_OK;
        }
        if (!BIO_should_retry(connection)) {
            return SAMPLE_IO_ERROR;
        }
        int result = sample_wait(connection, deadline);
        if (result != SAMPLE_IO_OK) {
            return result;
        }
    }
}

int sample_read(BIO *connection, void *buffer, int length, uint64_t deadline)
{
    for (;;) {
        if (sample_millis() >= deadline) {
            return SAMPLE_IO_TIMEOUT;
        }
        ERR_clear_error();
        int result = BIO_read(connection, buffer, length);
        if (result > 0) {
            return result;
        }
        if (!BIO_should_retry(connection)) {
            return result == 0 && !ERR_peek_error() ? SAMPLE_IO_CLOSED : SAMPLE_IO_ERROR;
        }
        result = sample_wait(connection, deadline);
        if (result != SAMPLE_IO_OK) {
            return result;
        }
    }
}

int sample_write(BIO *connection, const void *buffer, size_t length, uint64_t deadline)
{
    const unsigned char *data = buffer;
    while (length) {
        if (sample_millis() >= deadline) {
            return SAMPLE_IO_TIMEOUT;
        }
        int chunk = length > INT_MAX ? INT_MAX : (int)length;
        ERR_clear_error();
        int result = BIO_write(connection, data, chunk);
        if (result > 0) {
            data += result;
            length -= (size_t)result;
            continue;
        }
        if (!BIO_should_retry(connection)) {
            return SAMPLE_IO_ERROR;
        }
        result = sample_wait(connection, deadline);
        if (result != SAMPLE_IO_OK) {
            return result;
        }
    }
    return SAMPLE_IO_OK;
}

void sample_report_error(const char *operation)
{
    unsigned long error = ERR_peek_last_error();
    if (error) {
        char detail[256];
        ERR_error_string_n(error, detail, sizeof(detail));
        fprintf(stderr, "%s: %s\n", operation, detail);
    }
#ifdef _WIN32
    else {
        fprintf(stderr, "%s: socket error %d\n", operation, WSAGetLastError());
    }
#else
    else {
        fprintf(stderr, "%s: %s\n", operation, errno ? strerror(errno) : "I/O failure");
    }
#endif
    ERR_clear_error();
}
