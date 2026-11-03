"""Extend the pinned loopback fixtures with independently implemented V1 peers."""

import binascii
import hashlib
import hmac
import importlib.util
import os
from pathlib import Path
import shutil
import subprocess
import sys
import time


def main():
    fixture_path = Path(sys.argv[1]).resolve(strict=True)
    spec = importlib.util.spec_from_file_location("vscp_transport_fixtures", fixture_path)
    if spec is None or spec.loader is None:
        raise ImportError("Cannot load the pinned TCP/TLS test fixtures")
    fixtures = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(fixtures)
    executable = shutil.which("openssl")
    if executable is None:
        raise FileNotFoundError("OpenSSL is required for authenticated frame tests")
    # Public interoperability keys, not production credentials.
    aes_key = bytes(range(32))
    mac_key = bytes(range(32, 64))

    def cipher(data, algorithm, iv, decrypt=False):
        command = [executable, "enc", "-aes-{}-cbc".format(64 * (algorithm + 1)),
                   "-K", aes_key[:8 * (algorithm + 1)].hex(), "-iv", iv.hex(), "-nosalt"]
        if decrypt:
            command.append("-d")
        return subprocess.run(command, input=data, capture_output=True, check=True).stdout

    def with_crc(frame):
        return frame + binascii.crc_hqx(frame[1:], 0xffff).to_bytes(2, "big")

    def encode(frame, algorithm):
        iv = os.urandom(16)
        body = bytes(((frame[0] & 0xf0) | algorithm,)) + cipher(frame[1:], algorithm, iv) + iv
        prefix = b"\x55" + (0x2000 | (len(body) + 16)).to_bytes(2, "big")
        return prefix + body + hmac.new(mac_key, prefix + body, hashlib.sha256).digest()[:16]

    class AuthenticatedHandler(fixtures.Handler):
        def binary(self, connection, pending, scenario):
            if not scenario.startswith(b"secure-"):
                return super().binary(connection, pending, scenario)
            parts = scenario.decode("ascii").split("-", 2)
            algorithm = int(parts[1])
            fault = parts[2] if len(parts) == 3 else ""
            connection.sendall(b"+OK - Binary mode enabled\r\n")
            sample = with_crc(b"\xe0\x00\x07")
            if fault:
                plain = sample[:-1] + bytes((sample[-1] ^ 1,)) if fault == "crc" else sample
                record = bytearray(encode(plain, algorithm))
                if fault == "prefix":
                    record[0] ^= 1
                elif fault == "version":
                    record[1] &= 0x1f
                elif fault == "length":
                    record[2] += 16
                    record += bytes(16)
                elif fault == "type":
                    record[3] ^= 0x10
                elif fault == "algorithm":
                    record[3] = (record[3] & 0xf0) | (1 if algorithm != 1 else 2)
                elif fault == "unencrypted":
                    record[3] &= 0xf0
                elif fault == "ciphertext":
                    record[4] ^= 1
                elif fault == "iv":
                    record[-17] ^= 1
                elif fault == "tag":
                    record[-1] ^= 1
                elif fault == "padding":
                    record[-17] ^= 1
                    record[-16:] = hmac.new(mac_key, record[:-16], hashlib.sha256).digest()[:16]
                elif fault == "legacy":
                    record = bytearray(self.packet(sample))
                elif fault not in ("crc", "coalesced", "partial", "partial-body"):
                    raise ValueError("Unknown authenticated test scenario: " + fault)
                if fault == "coalesced":
                    connection.sendall(record * 2)
                elif fault in ("partial", "partial-body"):
                    split = 2 if fault == "partial" else 10
                    connection.sendall(record[:split])
                    time.sleep(0.15)
                    connection.sendall(record[split:])
                else:
                    connection.sendall(record)
                    return True

            while True:
                while len(pending) < 3:
                    data = connection.recv(8192)
                    if not data:
                        return True
                    pending += data
                word = int.from_bytes(pending[1:3], "big")
                length = word & 0x1fff
                if pending[0] != 0x55 or word >> 13 != 1 or not 49 <= length <= 4096:
                    raise ValueError("Invalid authenticated prefix from client")
                while len(pending) < length + 3:
                    data = connection.recv(8192)
                    if not data:
                        return True
                    pending += data
                record, pending = pending[:length + 3], pending[length + 3:]
                if record[3] & 0x0f != algorithm:
                    raise ValueError("Unexpected client encryption algorithm")
                expected = hmac.new(mac_key, record[:-16], hashlib.sha256).digest()[:16]
                if not hmac.compare_digest(expected, record[-16:]):
                    raise ValueError("Invalid client HMAC")
                frame = bytes((record[3] & 0xf0,)) + cipher(
                    record[4:-32], algorithm, record[-32:-16], decrypt=True)
                if len(frame) < 5 or binascii.crc_hqx(frame[1:], 0xffff):
                    raise ValueError("Invalid authenticated client frame CRC")
                if frame[0] >> 4 in (0, 1):
                    confirmation = with_crc(b"\xf0\xff\xff\x00\x00\x00\x00" + frame[1:3] + frame[-2:])
                    connection.sendall(encode(confirmation, algorithm) + encode(frame, algorithm))
                elif frame[0] == 0xf0 and frame[1:3] == b"\xff\xff":
                    continue
                else:
                    record = encode(frame, algorithm)
                    for fragment in (record[:1], record[1:8], record[8:]):
                        connection.sendall(fragment)
                        time.sleep(0.01)

    fixtures.Handler = AuthenticatedHandler
    sys.argv = [str(fixture_path), *sys.argv[2:]]
    return fixtures.main()


if __name__ == "__main__":
    sys.exit(main())
