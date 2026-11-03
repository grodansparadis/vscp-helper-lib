"""Exercise the raw TCP and TLS samples against local test servers."""

import contextlib
import os
from pathlib import Path
import shutil
import socket
import socketserver
import ssl
import subprocess
import sys
import tempfile
import threading
import time
import traceback
import unittest


class CheckedServer(socketserver.ThreadingTCPServer):
    allow_reuse_address = True

    def __init__(self, address, handler):
        self.lock = threading.Lock()
        self.errors = []
        super().__init__((address, 0), handler)

    def handle_error(self, request, client_address):
        with self.lock:
            self.errors.append(traceback.format_exc())


class VscpHandler(socketserver.BaseRequestHandler):
    def reply(self, connection, message):
        if self.server.multiline:
            message = b"Informational line\r\n" + message
        connection.sendall(message[:2])
        time.sleep(0.005)
        connection.sendall(message[2:])

    def handle(self):
        with self.request as connection:
            connection.settimeout(5)
            connection.setsockopt(socket.IPPROTO_TCP, socket.TCP_NODELAY, 1)
            commands = []
            with self.server.lock:
                self.server.sessions.append(commands)
            if self.server.stall:
                time.sleep(5.5)
                return
            if self.server.oversized:
                connection.sendall(b"x" * 16385)
                return
            self.reply(connection, b"+OK - test server\r\n")
            pending = b""
            while True:
                data = connection.recv(4096)
                if not data:
                    return
                pending += data
                while b"\n" in pending:
                    line, pending = pending.split(b"\n", 1)
                    command = line.rstrip(b"\r").decode("ascii")
                    commands.append(command)
                    if self.server.close_after_user and command.startswith("USER "):
                        return
                    if self.server.reject_password and command.startswith("PASS "):
                        self.reply(connection, b"-ERR - rejected\r\n")
                        return
                    self.reply(connection, b"+OK\r\n")
                    if command == "QUIT":
                        return


class VscpServer(CheckedServer):
    def __init__(self, address="127.0.0.1", reject_password=False, multiline=False,
                 stall=False, oversized=False, close_after_user=False):
        self.sessions = []
        self.reject_password = reject_password
        self.multiline = multiline
        self.stall = stall
        self.oversized = oversized
        self.close_after_user = close_after_user
        super().__init__(address, VscpHandler)


class VscpIpv6Server(VscpServer):
    address_family = socket.AF_INET6


class TlsHandler(socketserver.BaseRequestHandler):
    def handle(self):
        self.request.settimeout(5)
        try:
            with self.server.context.wrap_socket(self.request, server_side=True) as connection:
                with self.server.lock:
                    self.server.accepted += 1
                connection.sendall(b"TLS-SAMPLE-OK\r\n")
        except (ssl.SSLError, ConnectionError) as error:
            with self.server.lock:
                self.server.rejections.append(str(error))


class TlsServer(CheckedServer):
    def __init__(self, context, address="127.0.0.1"):
        self.context = context
        self.accepted = 0
        self.rejections = []
        super().__init__(address, TlsHandler)


class TlsIpv6Server(TlsServer):
    address_family = socket.AF_INET6


@contextlib.contextmanager
def running_server(server):
    thread = threading.Thread(target=server.serve_forever, kwargs={"poll_interval": 0.01})
    thread.start()
    try:
        yield server
    finally:
        server.shutdown()
        server.server_close()
        thread.join()
    if server.errors:
        raise AssertionError("\n".join(server.errors))


def run_sample(executable, *args, env=None):
    return subprocess.run([str(executable), *map(str, args)], capture_output=True,
                          text=True, timeout=15, env=env)


class RawTransportSamples(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        executable = shutil.which("openssl")
        if executable is None:
            raise RuntimeError("The openssl command is required for raw TLS sample tests")

        cls.temporary = tempfile.TemporaryDirectory(prefix="vscp-raw-samples-")
        cls.addClassCleanup(cls.temporary.cleanup)
        root = Path(cls.temporary.name)
        cls.certificate = root / "server.pem"
        cls.key = root / "server.key"
        cls.untrusted = root / "untrusted.pem"
        cls.untrusted_key = root / "untrusted.key"
        cls.ip_certificate = root / "ip-server.pem"
        cls.ip_key = root / "ip-server.key"
        cls.dns_ip_certificate = root / "dns-ip-server.pem"
        cls.dns_ip_key = root / "dns-ip-server.key"
        configuration = root / "certificate.cnf"
        configuration.write_text(
            "[req]\n"
            "distinguished_name = dn\n"
            "x509_extensions = extensions\n"
            "prompt = no\n"
            "[dn]\n"
            "CN = localhost\n"
            "[extensions]\n"
            "subjectAltName = DNS:localhost\n"
            "basicConstraints = critical,CA:TRUE\n"
            "keyUsage = critical,digitalSignature,keyCertSign,cRLSign\n",
            encoding="ascii",
        )
        ip_configuration = root / "ip-certificate.cnf"
        ip_configuration.write_text(
            "[req]\n"
            "distinguished_name = dn\n"
            "x509_extensions = extensions\n"
            "prompt = no\n"
            "[dn]\n"
            "CN = test-server\n"
            "[extensions]\n"
            "subjectAltName = @addresses\n"
            "basicConstraints = critical,CA:TRUE\n"
            "keyUsage = critical,digitalSignature,keyCertSign,cRLSign\n"
            "[addresses]\n"
            "IP.1 = 127.0.0.1\n"
            "IP.2 = ::1\n",
            encoding="ascii",
        )
        dns_ip_configuration = root / "dns-ip-certificate.cnf"
        dns_ip_configuration.write_text(
            configuration.read_text(encoding="ascii").replace(
                "subjectAltName = DNS:localhost", "subjectAltName = DNS:127.0.0.1"),
            encoding="ascii",
        )
        for certificate, key, extra in (
            (cls.certificate, cls.key, ["-config", str(configuration)]),
            (cls.untrusted, cls.untrusted_key, ["-subj", "/CN=untrusted"]),
            (cls.ip_certificate, cls.ip_key, ["-config", str(ip_configuration)]),
            (cls.dns_ip_certificate, cls.dns_ip_key, ["-config", str(dns_ip_configuration)]),
        ):
            result = subprocess.run(
                [executable, "req", "-x509", "-newkey", "rsa:2048", "-nodes",
                 "-days", "1", *extra, "-keyout", str(key), "-out", str(certificate)],
                capture_output=True, text=True,
            )
            if result.returncode:
                raise RuntimeError(f"Unable to create TLS test certificate: {result.stderr}")
        cls.combined = root / "combined.pem"
        cls.combined.write_bytes(cls.certificate.read_bytes() + cls.key.read_bytes())

    def assert_sample_success(self, result):
        self.assertEqual(0, result.returncode, result.stdout + result.stderr)

    def check_tcp_sessions(self, server, endpoint):
        with running_server(server):
            result = run_sample(TCP_SAMPLE, endpoint, "test-user", "test-pass")
        self.assert_sample_success(result)
        first = ["USER test-user", "PASS test-pass", "NOOP", "QUIT"]
        second = ["USER test-user", "PASS test-pass"] + ["NOOP"] * 101 + ["QUIT"]
        self.assertEqual([first, second], server.sessions)
        return result

    def test_tcp_ipv4(self):
        server = VscpServer()
        self.check_tcp_sessions(server, f"127.0.0.1:{server.server_address[1]}")

    def test_tcp_ipv6(self):
        if not socket.has_ipv6:
            self.skipTest("IPv6 is unavailable")
        try:
            server = VscpIpv6Server("::1")
        except OSError as error:
            self.skipTest(f"IPv6 loopback is unavailable: {error}")
        self.check_tcp_sessions(server, f"[::1]:{server.server_address[1]}")

    def test_tcp_hostname_scheme_and_multiline_responses(self):
        server = VscpServer(multiline=True)
        result = self.check_tcp_sessions(server, f"tcp://localhost:{server.server_address[1]}")
        self.assertIn("Informational line", result.stdout)

    def test_tcp_rejects_failed_authentication(self):
        server = VscpServer(reject_password=True)
        with running_server(server):
            result = run_sample(TCP_SAMPLE, f"127.0.0.1:{server.server_address[1]}",
                                "test-user", "test-pass")
        self.assertNotEqual(0, result.returncode)
        self.assertIn("rejected", result.stderr)
        self.assertEqual([["USER test-user", "PASS test-pass"]], server.sessions)

    def test_tcp_rejects_oversized_response(self):
        server = VscpServer(oversized=True)
        with running_server(server):
            result = run_sample(TCP_SAMPLE, f"127.0.0.1:{server.server_address[1]}")
        self.assertNotEqual(0, result.returncode)
        self.assertIn("response line is too long", result.stderr)

    def test_tcp_reports_closed_connection(self):
        server = VscpServer(close_after_user=True)
        with running_server(server):
            result = run_sample(TCP_SAMPLE, f"127.0.0.1:{server.server_address[1]}")
        self.assertNotEqual(0, result.returncode)
        self.assertIn("closed the connection", result.stderr)

    def test_tcp_welcome_timeout(self):
        server = VscpServer(stall=True)
        with running_server(server):
            started = time.monotonic()
            result = run_sample(TCP_SAMPLE, f"127.0.0.1:{server.server_address[1]}")
            elapsed = time.monotonic() - started
        self.assertNotEqual(0, result.returncode)
        self.assertIn("Timed out waiting for a VSCP response", result.stderr)
        self.assertGreaterEqual(elapsed, 4)
        self.assertLess(elapsed, 10)

    def test_samples_reject_invalid_input(self):
        for endpoint, message in (
            ("http://localhost:9598", "Unsupported TCP endpoint"),
            ("localhost", "Invalid TCP endpoint"),
            ("localhost:0", "Invalid TCP endpoint"),
            ("localhost:-1", "Invalid TCP endpoint"),
            ("localhost:65536", "Invalid TCP endpoint"),
            ("localhost:65537", "Invalid TCP endpoint"),
            ("localhost:99999999999999999999", "Invalid TCP endpoint"),
            ("localhost:9598extra", "Invalid TCP endpoint"),
            ("[::1]:65536", "Invalid TCP endpoint"),
            ("tcp://user@localhost:9598", "Invalid TCP endpoint"),
            ("tcp://:9598", "Invalid TCP endpoint"),
            ("::1:9598", "Invalid TCP endpoint"),
            ("[::1]:9598/path", "Invalid TCP endpoint"),
            ("localhost :9598", "Invalid TCP endpoint"),
            ("localhost:9598?query", "Invalid TCP endpoint"),
        ):
            for executable in (TCP_SAMPLE, TLS_SAMPLE):
                with self.subTest(executable=executable, endpoint=endpoint):
                    result = run_sample(executable, endpoint)
                    self.assertNotEqual(0, result.returncode)
                    self.assertIn(message, result.stderr)
        result = run_sample(TCP_SAMPLE, "localhost:9598", "test\nuser")
        self.assertNotEqual(0, result.returncode)
        self.assertIn("Credentials must not contain line breaks", result.stderr)

    def tls_server(self, require_client=False, ip_certificate=False, ipv6=False):
        context = ssl.SSLContext(ssl.PROTOCOL_TLS_SERVER)
        context.load_cert_chain(self.ip_certificate if ip_certificate else self.certificate,
                                self.ip_key if ip_certificate else self.key)
        if require_client:
            context.load_verify_locations(self.certificate)
            context.verify_mode = ssl.CERT_REQUIRED
        return TlsIpv6Server(context, "::1") if ipv6 else TlsServer(context)

    def assert_tls_success(self, result):
        self.assert_sample_success(result)
        self.assertIn("TLS connection established", result.stdout)
        self.assertIn("TLS-SAMPLE-OK", result.stdout)

    def test_tls_server_verification(self):
        server = self.tls_server()
        with running_server(server):
            port = server.server_address[1]
            endpoint = f"localhost:{port}"
            self.assert_tls_success(run_sample(TLS_SAMPLE, endpoint, self.certificate))
            environment = dict(os.environ, SSL_CERT_FILE=str(self.certificate))
            self.assert_tls_success(run_sample(TLS_SAMPLE, endpoint, env=environment))
            for args in (
                (endpoint, self.untrusted),
                (f"127.0.0.1:{port}", self.certificate),
            ):
                with self.subTest(args=args):
                    result = run_sample(TLS_SAMPLE, *args)
                    self.assertNotEqual(0, result.returncode)
                    self.assertIn("TLS transport error", result.stderr)
            result = run_sample(TLS_SAMPLE, endpoint, self.certificate.parent / "missing.pem")
            self.assertNotEqual(0, result.returncode)
            self.assertIn("Cannot read PEM file", result.stderr)

    def test_tls_client_authentication(self):
        server = self.tls_server(require_client=True)
        with running_server(server):
            endpoint = f"localhost:{server.server_address[1]}"
            self.assert_tls_success(run_sample(TLS_SAMPLE, endpoint, self.certificate,
                                               self.certificate, self.key))
            self.assert_tls_success(run_sample(TLS_SAMPLE, endpoint, self.certificate,
                                               self.combined))
            result = run_sample(TLS_SAMPLE, endpoint, self.certificate)
            self.assertNotEqual(0, result.returncode)
            self.assertTrue("TLS transport error" in result.stderr or
                            "Server closed the TLS connection before sending data" in result.stderr,
                            result.stderr)
            result = run_sample(TLS_SAMPLE, endpoint, self.certificate,
                                self.certificate, self.untrusted_key)
            self.assertNotEqual(0, result.returncode)
            self.assertIn("TLS transport error", result.stderr)
        self.assertEqual(2, server.accepted)
        self.assertTrue(server.rejections, "Server did not reject the missing client certificate")

    def test_tls_ip_address_verification(self):
        server = self.tls_server(ip_certificate=True)
        with running_server(server):
            port = server.server_address[1]
            self.assert_tls_success(run_sample(TLS_SAMPLE, f"127.0.0.1:{port}",
                                               self.ip_certificate))
            result = run_sample(TLS_SAMPLE, f"localhost:{port}", self.ip_certificate)
            self.assertNotEqual(0, result.returncode)
            self.assertIn("TLS transport error", result.stderr)

    def test_tls_ipv6_address_verification(self):
        if not socket.has_ipv6:
            self.skipTest("IPv6 is unavailable")
        try:
            server = self.tls_server(ip_certificate=True, ipv6=True)
        except OSError as error:
            self.skipTest(f"IPv6 loopback is unavailable: {error}")
        with running_server(server):
            result = run_sample(TLS_SAMPLE, f"[::1]:{server.server_address[1]}",
                                self.ip_certificate)
        self.assert_tls_success(result)

    def test_tls_ip_requires_an_ip_address_san(self):
        context = ssl.SSLContext(ssl.PROTOCOL_TLS_SERVER)
        context.load_cert_chain(self.dns_ip_certificate, self.dns_ip_key)
        server = TlsServer(context)
        with running_server(server):
            result = run_sample(TLS_SAMPLE, f"127.0.0.1:{server.server_address[1]}",
                                self.dns_ip_certificate)
        self.assertNotEqual(0, result.returncode)
        self.assertIn("TLS transport error", result.stderr)

    def test_tls_handshake_timeout(self):
        server = VscpServer(stall=True)
        with running_server(server):
            started = time.monotonic()
            result = run_sample(TLS_SAMPLE, f"127.0.0.1:{server.server_address[1]}",
                                self.certificate)
            elapsed = time.monotonic() - started
        self.assertNotEqual(0, result.returncode)
        self.assertIn("Timed out waiting for the TLS response", result.stderr)
        self.assertGreaterEqual(elapsed, 4)
        self.assertLess(elapsed, 10)


if __name__ == "__main__":
    if len(sys.argv) != 3:
        raise SystemExit("Usage: raw_transport_samples.py <stcptest> <stcp_tls_client>")
    TCP_SAMPLE, TLS_SAMPLE = (Path(path).resolve(strict=True) for path in sys.argv[1:])
    unittest.main(argv=[sys.argv[0]])
