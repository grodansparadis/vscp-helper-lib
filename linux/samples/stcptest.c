#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "raw_transport.h"

#define RESPONSE_TIMEOUT_MS 5000
#define REPEATED_NOOPS 100

struct response_reader {
    BIO *connection;
    unsigned char buffer[16385];
    size_t used;
};

static int read_response(struct response_reader *reader, uint64_t deadline)
{
    for (;;) {
        const unsigned char *line = reader->buffer;
        const unsigned char *newline = memchr(line, '\n', reader->used);
        if (newline) {
            size_t length = (size_t)(newline - line) + 1;
            bool success = length >= 4 && memcmp(line, "+OK", 3) == 0 &&
                           (line[3] == ' ' || line[3] == '\r' || line[3] == '\n');
            bool error = (length >= 3 && memcmp(line, "-OK", 3) == 0) ||
                         (length >= 4 && (memcmp(line, "-ERR", 4) == 0 ||
                                          memcmp(line, "+ERR", 4) == 0));
            if (fwrite(line, 1, length, stdout) != length) {
                fprintf(stderr, "Failed to print the VSCP response\n");
                return -1;
            }
            reader->used -= length;
            memmove(reader->buffer, reader->buffer + length, reader->used);
            if (error) {
                fprintf(stderr, "VSCP server rejected a command\n");
                return -1;
            }
            if (success) {
                return 0;
            }
            continue;
        }

        if (reader->used == sizeof(reader->buffer)) {
            fprintf(stderr, "VSCP response line is too long\n");
            return -1;
        }
        int result = sample_read(reader->connection, reader->buffer + reader->used,
                                 (int)(sizeof(reader->buffer) - reader->used), deadline);
        if (result > 0) {
            reader->used += (size_t)result;
        }
        else if (result == SAMPLE_IO_TIMEOUT) {
            fprintf(stderr, "Timed out waiting for a VSCP response\n");
            return -1;
        }
        else if (result == SAMPLE_IO_CLOSED) {
            fprintf(stderr, "VSCP server closed the connection\n");
            return -1;
        }
        else {
            sample_report_error("TCP transport error");
            return -1;
        }
    }
}

static int exchange_command(struct response_reader *reader, const char *command, const char *argument)
{
    uint64_t deadline = sample_millis() + RESPONSE_TIMEOUT_MS;
    size_t command_length = strlen(command);
    size_t argument_length = argument ? strlen(argument) : 0;
    size_t separator_length = argument ? 1 : 0;
    if (argument_length > SIZE_MAX - command_length - separator_length - 2) {
        fprintf(stderr, "VSCP command is too long\n");
        return -1;
    }
    size_t length = command_length + separator_length + argument_length + 2;
    char *request = malloc(length);
    if (!request) {
        fprintf(stderr, "Cannot allocate a VSCP command\n");
        return -1;
    }
    memcpy(request, command, command_length);
    if (argument) {
        request[command_length] = ' ';
        memcpy(request + command_length + 1, argument, argument_length);
    }
    memcpy(request + length - 2, "\r\n", 2);
    int result = sample_write(reader->connection, request, length, deadline);
    free(request);
    if (result == SAMPLE_IO_TIMEOUT) {
        fprintf(stderr, "Timed out sending a VSCP command\n");
    }
    else if (result != SAMPLE_IO_OK) {
        sample_report_error("TCP transport error");
    }
    return result == SAMPLE_IO_OK ? read_response(reader, deadline) : -1;
}

static int run_session(const struct sample_endpoint *endpoint, const char *user,
                       const char *password, unsigned int noops)
{
    uint64_t started = sample_millis();
    BIO *connection = BIO_new(BIO_s_connect());
    struct response_reader reader = {0};
    int result = -1;

    if (!connection) {
        sample_report_error("TCP transport error");
        return -1;
    }
    reader.connection = connection;
    int status = sample_connect(connection, endpoint, started + RESPONSE_TIMEOUT_MS);
    if (status != SAMPLE_IO_OK) {
        if (status == SAMPLE_IO_TIMEOUT) {
            fprintf(stderr, "Timed out waiting for a VSCP response\n");
        }
        else {
            sample_report_error("TCP transport error");
        }
        goto cleanup;
    }
    if (read_response(&reader, started + RESPONSE_TIMEOUT_MS) ||
        exchange_command(&reader, "USER", user) ||
        exchange_command(&reader, "PASS", password)) {
        goto cleanup;
    }
    for (unsigned int i = 0; i < noops; i++) {
        if (exchange_command(&reader, "NOOP", NULL)) {
            goto cleanup;
        }
    }
    if (exchange_command(&reader, "QUIT", NULL)) {
        goto cleanup;
    }
    printf("%u NOOP commands completed in %" PRIu64 " ms\n", noops, sample_millis() - started);
    result = 0;

cleanup:
    BIO_free_all(connection);
    return result;
}

int main(int argc, char *argv[])
{
    const char *address = argc > 1 ? argv[1] : "127.0.0.1:9598";
    const char *user = argc > 2 ? argv[2] : "admin";
    const char *password = argc > 3 ? argv[3] : "secret";
    struct sample_endpoint endpoint;

    if (argc > 4) {
        fprintf(stderr, "Usage: %s [host:port] [user] [password]\n", argv[0]);
        return EXIT_FAILURE;
    }
    if (strpbrk(user, "\r\n") || strpbrk(password, "\r\n")) {
        fprintf(stderr, "Credentials must not contain line breaks\n");
        return EXIT_FAILURE;
    }
    if (sample_parse_endpoint(&endpoint, address) != 0 || sample_initialize() != 0) {
        return EXIT_FAILURE;
    }

    puts("Test 1: single NOOP");
    if (run_session(&endpoint, user, password, 1) != 0) {
        return EXIT_FAILURE;
    }
    puts("Test 2: repeated NOOPs");
    if (run_session(&endpoint, user, password, 1 + REPEATED_NOOPS) != 0) {
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
