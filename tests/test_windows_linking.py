#!/usr/bin/env python3
"""Regression tests for platform-specific library linkage."""

from pathlib import Path
import shutil
import subprocess
import tempfile
import unittest


ROOT = Path(__file__).resolve().parents[1]


@unittest.skipUnless(shutil.which("cmake"), "CMake is required")
class WindowsLinkingTests(unittest.TestCase):
    def test_ip_helper_library_is_linked_only_on_windows(self) -> None:
        cmake_text = (ROOT / "CMakeLists.txt").read_text(encoding="utf-8")
        _, marker, linking = cmake_text.partition(
            "if (WIN32)\n    target_link_libraries(libvscphelper PRIVATE"
        )
        self.assertTrue(marker)
        linking, end_marker, _ = linking.partition("\nendif()")
        self.assertTrue(end_marker)
        linking = marker + linking + end_marker

        for windows in ("TRUE", "FALSE"):
            with self.subTest(windows=windows), tempfile.TemporaryDirectory() as directory:
                root = Path(directory)
                (root / "probe.c").write_text("int probe(void) { return 0; }\n", encoding="utf-8")
                (root / "CMakeLists.txt").write_text(
                    "cmake_minimum_required(VERSION 3.14)\n"
                    "project(LinkProbe LANGUAGES C)\n"
                    "add_library(libvscphelper SHARED probe.c)\n"
                    "foreach(dependency PThreads4W::PThreads4W_CXXEXC "
                    "OpenSSL::SSL OpenSSL::Crypto expat::expat Threads::Threads)\n"
                    "  add_library(${dependency} INTERFACE IMPORTED)\n"
                    "endforeach()\n"
                    f"set(WIN32 {windows})\n"
                    + linking
                    + "\nget_target_property(libraries libvscphelper LINK_LIBRARIES)\n"
                    'file(WRITE "${CMAKE_BINARY_DIR}/libraries.txt" "${libraries}")\n',
                    encoding="utf-8",
                )
                build = root / "build"
                result = subprocess.run(
                    ["cmake", "-S", str(root), "-B", str(build)],
                    text=True, capture_output=True,
                )
                self.assertEqual(0, result.returncode, result.stdout + result.stderr)
                libraries = (build / "libraries.txt").read_text(encoding="utf-8").split(";")
                self.assertEqual(windows == "TRUE", "ws2_32" in libraries)
                self.assertEqual(windows == "TRUE", "iphlpapi" in libraries)


if __name__ == "__main__":
    unittest.main()
