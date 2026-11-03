#ifdef _WIN32
#include <winsock2.h>
#include <ws2tcpip.h>
#else
#include <arpa/inet.h>
#endif

#include <stdio.h>
#include <stdlib.h>

#include <openssl/ssl.h>
#include <openssl/x509.h>

#include "raw_transport.h"

#define TLS_TIMEOUT_MS 5000

int main(int argc, char *argv[])
{
    const char *address = argc > 1 ? argv[1] : "localhost:4433";
    const char *default_ca = getenv(X509_get_default_cert_file_env());
    const char *ca_path = argc > 2 ? argv[2] :
                          (default_ca && *default_ca ? default_ca : X509_get_default_cert_file());
    const char *cert_path = argc > 3 ? argv[3] : NULL;
    const char *key_path = argc > 4 ? argv[4] : cert_path;
    struct sample_endpoint endpoint;
    SSL_CTX *context = NULL;
    SSL *tls = NULL;
    BIO *connection = NULL;
    int result = EXIT_FAILURE;

    if (argc > 5) {
        fprintf(stderr, "Usage: %s [host:port] [ca.pem] [client-cert.pem [client-key.pem]]\n", argv[0]);
        return EXIT_FAILURE;
    }
    if (sample_parse_endpoint(&endpoint, address) != 0 || sample_initialize() != 0) {
        return EXIT_FAILURE;
    }

    context = SSL_CTX_new(TLS_client_method());
    if (!context) {
        sample_report_error("TLS transport error");
        goto cleanup;
    }
    SSL_CTX_set_options(context, SSL_OP_NO_SSLv2 | SSL_OP_NO_SSLv3 |
                                 SSL_OP_NO_TLSv1 | SSL_OP_NO_TLSv1_1);
    SSL_CTX_set_verify(context, SSL_VERIFY_PEER, NULL);
    if (SSL_CTX_load_verify_locations(context, ca_path, NULL) != 1) {
        fprintf(stderr, "Cannot read PEM file: %s\n", ca_path);
        sample_report_error("TLS transport error");
        goto cleanup;
    }
    if (cert_path) {
        if (SSL_CTX_use_certificate_chain_file(context, cert_path) != 1) {
            fprintf(stderr, "Cannot read PEM file: %s\n", cert_path);
            sample_report_error("TLS transport error");
            goto cleanup;
        }
        if (SSL_CTX_use_PrivateKey_file(context, key_path, SSL_FILETYPE_PEM) != 1) {
            fprintf(stderr, "Cannot read PEM file: %s\n", key_path);
            sample_report_error("TLS transport error");
            goto cleanup;
        }
        if (SSL_CTX_check_private_key(context) != 1) {
            sample_report_error("TLS transport error");
            goto cleanup;
        }
    }

    connection = BIO_new_ssl_connect(context);
    if (!connection || BIO_get_ssl(connection, &tls) <= 0 || !tls) {
        sample_report_error("TLS transport error");
        goto cleanup;
    }
    unsigned char address_bytes[16];
    int ipv4 = inet_pton(AF_INET, endpoint.host, address_bytes);
    int ipv6 = ipv4 == 1 ? 0 : inet_pton(AF_INET6, endpoint.host, address_bytes);
    if (ipv4 < 0 || ipv6 < 0) {
        sample_report_error("TLS address error");
        goto cleanup;
    }
    if (ipv4 == 1 || ipv6 == 1) {
        if (X509_VERIFY_PARAM_set1_ip_asc(SSL_get0_param(tls), endpoint.host) != 1) {
            sample_report_error("TLS transport error");
            goto cleanup;
        }
    }
    else {
        if (SSL_set1_host(tls, endpoint.host) != 1 ||
            SSL_set_tlsext_host_name(tls, endpoint.host) != 1) {
            sample_report_error("TLS transport error");
            goto cleanup;
        }
    }

    uint64_t deadline = sample_millis() + TLS_TIMEOUT_MS;
    int status = sample_connect(connection, &endpoint, deadline);
    if (status != SAMPLE_IO_OK) {
        if (status == SAMPLE_IO_TIMEOUT) {
            fprintf(stderr, "Timed out waiting for the TLS response\n");
        }
        else {
            sample_report_error("TLS transport error");
        }
        goto cleanup;
    }
    puts("TLS connection established");

    char buffer[4096];
    status = sample_read(connection, buffer, sizeof(buffer), deadline);
    if (status == SAMPLE_IO_TIMEOUT) {
        fprintf(stderr, "Timed out waiting for the TLS response\n");
    }
    else if (status == SAMPLE_IO_CLOSED) {
        fprintf(stderr, "Server closed the TLS connection before sending data\n");
    }
    else if (status == SAMPLE_IO_ERROR) {
        sample_report_error("TLS transport error");
    }
    else if (fwrite(buffer, 1, (size_t)status, stdout) != (size_t)status) {
        fprintf(stderr, "Failed to print the TLS response\n");
    }
    else {
        result = EXIT_SUCCESS;
    }

cleanup:
    BIO_free_all(connection);
    SSL_CTX_free(context);
    return result;
}
