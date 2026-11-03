#!/usr/bin/env python3
"""Regression tests for library version synchronization."""

from pathlib import Path
import os
import re
import shutil
import subprocess
import sys
import tempfile
import unittest
from unittest import mock


ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT))
from tools import update_docs_metadata, update_libversion


def make_header(
    revision: int = 0,
    displayed_revision: int = 0,
    displayed_patch: int = 249,
    patch: int = 249,
) -> str:
    return (
        f'#define VSCP_HELPER_LIB_VERSION "15.3.{displayed_revision}.{displayed_patch}"\n'
        "#define VSCP_HELPER_LIB_VERSION_MAJOR 15\n"
        "#define VSCP_HELPER_LIB_VERSION_MINOR 3\n"
        f"#define VSCP_HELPER_LIB_VERSION_REVISION {revision}\n"
        f"#define VSCP_HELPER_LIB_VERSION_PATCH {patch}\n"
    )


class VersioningTests(unittest.TestCase):
    def setUp(self) -> None:
        self.temporary_directory = tempfile.TemporaryDirectory()
        self.addCleanup(self.temporary_directory.cleanup)
        self.root = Path(self.temporary_directory.name)
        self.header_path = self.root / "src" / "libversion.h"
        self.header_path.parent.mkdir()
        self.variables_path = self.root / "docs" / "variables.xml"
        self.variables_path.parent.mkdir()
        self.variables_path.write_text(
            "<var><creation-time>old</creation-time>"
            "<document-version>old</document-version></var>\n",
            encoding="utf-8",
        )

    def test_updater_preserves_manual_revision_and_large_patch(self) -> None:
        self.header_path.write_text(make_header(revision=255), encoding="utf-8")
        with mock.patch.object(update_libversion, "VERSION_PATH", self.header_path):
            with mock.patch.object(
                update_libversion, "get_patch_version", return_value=3925
            ) as get_patch:
                with mock.patch.object(
                    sys, "argv", ["update_libversion.py", "--next-commit"]
                ):
                    update_libversion.main()
        get_patch.assert_called_once_with(True)

        updated = self.header_path.read_text(encoding="utf-8")
        self.assertIn('#define VSCP_HELPER_LIB_VERSION "15.3.255.3925"', updated)
        self.assertIn("#define VSCP_HELPER_LIB_VERSION_REVISION 255", updated)
        self.assertIn("#define VSCP_HELPER_LIB_VERSION_PATCH 3925", updated)

        with mock.patch.object(update_docs_metadata, "VERSION_PATH", self.header_path):
            with mock.patch.object(
                update_docs_metadata, "VARIABLES_PATH", self.variables_path
            ):
                update_docs_metadata.main()
        self.assertIn(
            "<document-version>15.3.255.3925</document-version>",
            self.variables_path.read_text(encoding="utf-8"),
        )

    def test_revision_boundaries_and_invalid_definitions(self) -> None:
        for revision in (0, 255):
            with self.subTest(revision=revision):
                header = make_header(revision=revision, displayed_revision=revision)
                self.assertEqual(
                    (15, 3, revision, 249),
                    update_libversion.read_version_components(header),
                )
        for revision in (-1, 256):
            with self.subTest(revision=revision):
                with self.assertRaises(ValueError):
                    update_libversion.read_version_components(
                        make_header(revision=revision)
                    )

        with self.assertRaises(ValueError):
            update_libversion.read_version_components(
                make_header().replace("15.3.0.249", "15.3.249")
            )
        with self.assertRaisesRegex(ValueError, "unpadded decimal"):
            update_libversion.read_version_components(
                make_header(revision=10).replace(
                    "VSCP_HELPER_LIB_VERSION_REVISION 10",
                    "VSCP_HELPER_LIB_VERSION_REVISION 010",
                )
            )
        with self.assertRaisesRegex(ValueError, "PATCH disagree"):
            update_libversion.read_version_components(make_header(patch=250))

    def test_updater_does_not_modify_an_invalid_revision(self) -> None:
        header = make_header(revision=256, displayed_revision=256)
        self.header_path.write_text(header, encoding="utf-8")
        with mock.patch.object(update_libversion, "VERSION_PATH", self.header_path):
            with mock.patch.object(update_libversion, "get_patch_version") as get_patch:
                with mock.patch.object(sys, "argv", ["update_libversion.py"]):
                    with self.assertRaisesRegex(ValueError, "between 0 and 255"):
                        update_libversion.main()
        get_patch.assert_not_called()
        self.assertEqual(header, self.header_path.read_text(encoding="utf-8"))

    def test_documentation_rejects_unsynchronized_revision(self) -> None:
        self.header_path.write_text(make_header(revision=17), encoding="utf-8")
        with mock.patch.object(update_docs_metadata, "VERSION_PATH", self.header_path):
            with self.assertRaisesRegex(ValueError, "REVISION disagree"):
                update_docs_metadata.get_library_version()

    @unittest.skipUnless(shutil.which("git"), "Git is required")
    def test_command_line_workflow_uses_first_parent_count(self) -> None:
        tools = self.root / "tools"
        tools.mkdir()
        for name in ("update_libversion.py", "update_docs_metadata.py"):
            shutil.copy2(ROOT / "tools" / name, tools / name)
        self.header_path.write_text(make_header(revision=17), encoding="utf-8")

        subprocess.run(["git", "init", "--quiet", str(self.root)], check=True)
        git = [
            "git", "-C", str(self.root),
            "-c", f"core.hooksPath={os.devnull}",
            "-c", "user.name=Version Test",
            "-c", "user.email=version-test@example.invalid",
            "-c", "commit.gpgsign=false",
        ]
        subprocess.run(
            git + ["commit", "--allow-empty", "--quiet", "-m", "Initial commit"],
            check=True,
        )
        main_branch = subprocess.check_output(
            git + ["symbolic-ref", "--short", "HEAD"], text=True
        ).strip()
        subprocess.run(git + ["checkout", "--quiet", "-b", "versioning-side"], check=True)
        subprocess.run(
            git + ["commit", "--allow-empty", "--quiet", "-m", "Side commit"],
            check=True,
        )
        subprocess.run(git + ["checkout", "--quiet", main_branch], check=True)
        subprocess.run(
            git + ["commit", "--allow-empty", "--quiet", "-m", "Main commit"],
            check=True,
        )
        subprocess.run(
            git + ["merge", "--quiet", "--no-ff", "-m", "Merge side", "versioning-side"],
            check=True,
        )
        result = subprocess.run(
            [sys.executable, "-B", "tools/update_libversion.py", "--next-commit"],
            cwd=self.root, text=True, capture_output=True,
        )
        self.assertEqual(0, result.returncode, result.stderr)
        self.assertIn(
            '"15.3.17.4"', self.header_path.read_text(encoding="utf-8")
        )

        for arguments in (
            ["tools/update_docs_metadata.py"],
            ["-m", "tools.update_docs_metadata"],
        ):
            with self.subTest(arguments=arguments):
                result = subprocess.run(
                    [sys.executable, "-B", *arguments],
                    cwd=self.root, text=True, capture_output=True,
                )
                self.assertEqual(0, result.returncode, result.stderr)
                self.assertIn(
                    "<document-version>15.3.17.4</document-version>",
                    self.variables_path.read_text(encoding="utf-8"),
                )

        result = subprocess.run(
            [sys.executable, "-B", "tools/update_libversion.py"],
            cwd=self.root, text=True, capture_output=True,
        )
        self.assertEqual(0, result.returncode, result.stderr)
        self.assertIn(
            '"15.3.17.3"', self.header_path.read_text(encoding="utf-8")
        )

    @unittest.skipUnless(
        os.name == "posix" and shutil.which("git") and shutil.which("python3"),
        "Git and python3 are required for the pre-commit hook",
    )
    def test_precommit_hook_stages_the_pending_version(self) -> None:
        tools = self.root / "tools"
        hooks = self.root / ".githooks"
        tools.mkdir()
        hooks.mkdir()
        shutil.copy2(ROOT / "tools" / "update_libversion.py", tools / "update_libversion.py")
        shutil.copy2(ROOT / ".githooks" / "pre-commit", hooks / "pre-commit")
        self.header_path.write_text(make_header(revision=17), encoding="utf-8")
        subprocess.run(["git", "init", "--quiet", str(self.root)], check=True)
        git = [
            "git", "-C", str(self.root),
            "-c", "user.name=Version Test",
            "-c", "user.email=version-test@example.invalid",
            "-c", "commit.gpgsign=false",
        ]
        subprocess.run(
            git + [
                "-c", f"core.hooksPath={os.devnull}",
                "commit", "--allow-empty", "--quiet", "-m", "Initial commit",
            ],
            check=True,
        )
        subprocess.run(git + ["add", "--", "src/libversion.h"], check=True)
        subprocess.run(
            git + [
                "-c", "core.hooksPath=.githooks",
                "commit", "--quiet", "-m", "Update version",
            ],
            check=True,
        )
        committed = subprocess.check_output(
            git + ["show", "HEAD:src/libversion.h"], text=True
        )
        self.assertIn('#define VSCP_HELPER_LIB_VERSION "15.3.17.2"', committed)
        self.assertIn("#define VSCP_HELPER_LIB_VERSION_REVISION 17", committed)
        self.assertIn("#define VSCP_HELPER_LIB_VERSION_PATCH 2", committed)

    def configure_version(self, header: str, *, windows: bool = False) -> subprocess.CompletedProcess:
        cmake_text = (ROOT / "CMakeLists.txt").read_text(encoding="utf-8")
        preamble, marker, _ = cmake_text.partition("# Set compiler options")
        self.assertTrue(marker)
        preamble = preamble.replace("LANGUAGES CXX C", "LANGUAGES NONE")
        (self.root / "CMakeLists.txt").write_text(preamble, encoding="utf-8")
        self.header_path.write_text(header, encoding="utf-8")
        arguments = ["cmake", "-S", str(self.root), "-B", str(self.root / "build")]
        if windows:
            arguments.append("-DCMAKE_SYSTEM_NAME=Windows")
        return subprocess.run(arguments, text=True, capture_output=True)

    @unittest.skipUnless(shutil.which("cmake"), "CMake is required")
    def test_cmake_accepts_maximum_revision_and_large_patch(self) -> None:
        for patch in (3925, 65536):
            with self.subTest(patch=patch):
                result = self.configure_version(
                    make_header(
                        revision=255, displayed_revision=255,
                        displayed_patch=patch, patch=patch,
                    )
                )
                self.assertEqual(0, result.returncode, result.stderr)
                cache = (self.root / "build" / "CMakeCache.txt").read_text(encoding="utf-8")
                self.assertIn(f"CMAKE_PROJECT_VERSION:STATIC=15.3.255.{patch}", cache)
                self.assertIn("CMAKE_PROJECT_VERSION_PATCH:STATIC=255", cache)
                self.assertIn(f"CMAKE_PROJECT_VERSION_TWEAK:STATIC={patch}", cache)

    @unittest.skipUnless(shutil.which("cmake"), "CMake is required")
    def test_cmake_rejects_invalid_or_unsynchronized_revision(self) -> None:
        result = self.configure_version(make_header(revision=256, displayed_revision=256))
        self.assertNotEqual(0, result.returncode)
        self.assertIn("must be between 0 and 255", result.stderr)

        result = self.configure_version(make_header(revision=17))
        self.assertNotEqual(0, result.returncode)
        self.assertIn("manual revision disagree", result.stderr)

        result = self.configure_version(
            make_header(revision=10).replace(
                "VSCP_HELPER_LIB_VERSION_REVISION 10",
                "VSCP_HELPER_LIB_VERSION_REVISION 010",
            )
        )
        self.assertNotEqual(0, result.returncode)
        self.assertIn("unpadded decimal", result.stderr)

    @unittest.skipUnless(
        os.name == "posix" and shutil.which("cmake") and shutil.which("cc") and shutil.which("make"),
        "CMake, a C compiler, and make are required",
    )
    def test_macos_preserves_legacy_compatibility_version(self) -> None:
        cmake_text = (ROOT / "CMakeLists.txt").read_text(encoding="utf-8")
        preamble, marker, _ = cmake_text.partition("# Set compiler options")
        self.assertTrue(marker)
        preamble = preamble.replace("LANGUAGES CXX C", "LANGUAGES C")
        preamble += (
            "\nadd_library(libvscphelper SHARED probe.c)\n"
            "set_target_properties(libvscphelper PROPERTIES NO_SONAME 1 "
            'VERSION "${LIBVSCPHELPER_VERSION}" SOVERSION "${LIBVSCPHELPER_VERSION}")\n'
            "vscp_set_macho_compatibility_version(libvscphelper "
            '"${MAJOR_VERSION}" "${MINOR_VERSION}" "${REVISION_VERSION}" "${PATCH_VERSION}")\n'
        )
        (self.root / "CMakeLists.txt").write_text(preamble, encoding="utf-8")
        (self.root / "probe.c").write_text(
            "int version_probe(void) { return 0; }\n", encoding="utf-8"
        )

        for revision, patch, expected in (
            (0, 249, "15.3.249"),
            (255, 249, "15.3.255"),
            (42, 3925, "15.3.255"),
            (42, 65536, "15.3.255"),
        ):
            with self.subTest(revision=revision, patch=patch):
                self.header_path.write_text(
                    make_header(
                        revision=revision, displayed_revision=revision,
                        displayed_patch=patch, patch=patch,
                    ),
                    encoding="utf-8",
                )
                result = subprocess.run(
                    [
                        "cmake", "-G", "Unix Makefiles",
                        "-S", str(self.root), "-B", str(self.root / "build"),
                        "-DCMAKE_SYSTEM_NAME=Darwin", "-DCMAKE_C_COMPILER_WORKS=TRUE",
                    ],
                    text=True, capture_output=True,
                )
                self.assertEqual(0, result.returncode, result.stderr)
                link_command = (
                    self.root / "build" / "CMakeFiles" / "libvscphelper.dir" / "link.txt"
                ).read_text(encoding="utf-8")
                for flag in ("compatibility_version", "current_version"):
                    self.assertRegex(
                        link_command, rf"-{flag}[ ,]+{re.escape(expected)}(?:[ ,]|$)"
                    )

    @unittest.skipUnless(shutil.which("cmake"), "CMake is required")
    def test_windows_resource_limit_is_explicit(self) -> None:
        result = self.configure_version(
            make_header(displayed_patch=65536, patch=65536), windows=True
        )
        self.assertNotEqual(0, result.returncode)
        self.assertIn("Windows VERSIONINFO cannot store a patch greater than 65535", result.stderr)

    @unittest.skipUnless(shutil.which("cmake"), "CMake is required")
    def test_windows_resource_contains_all_four_components(self) -> None:
        resource = self.root / "vscphelper.rc"
        script = self.root / "resource.cmake"
        template = (ROOT / "windows" / "vscphelper.rc.in").as_posix()
        script.write_text(
            "set(MAJOR_VERSION 15)\n"
            "set(MINOR_VERSION 3)\n"
            "set(REVISION_VERSION 255)\n"
            "set(PATCH_VERSION 3925)\n"
            'set(APP_VERSION "15.3.255.3925")\n'
            f'configure_file("{template}" "{resource.as_posix()}" @ONLY)\n',
            encoding="utf-8",
        )
        result = subprocess.run(
            ["cmake", "-P", str(script)], text=True, capture_output=True
        )
        self.assertEqual(0, result.returncode, result.stderr)
        content = resource.read_text(encoding="utf-8")
        self.assertIn("FILEVERSION 15,3,255,3925", content)
        self.assertIn("PRODUCTVERSION 15,3,255,3925", content)
        self.assertIn('VALUE "FileVersion", "15.3.255.3925"', content)

    @unittest.skipUnless(shutil.which("cc"), "A C compiler is required")
    def test_header_enforces_revision_boundaries(self) -> None:
        original = (ROOT / "src" / "libversion.h").read_text(encoding="utf-8")
        for revision in (255, 256):
            with self.subTest(revision=revision):
                header = re.sub(
                    r"(?m)^(#define VSCP_HELPER_LIB_VERSION_REVISION\s+)\d+$",
                    rf"\g<1>{revision}",
                    original,
                )
                result = subprocess.run(
                    ["cc", "-x", "c", "-fsyntax-only", "-"],
                    input=header, text=True, capture_output=True,
                )
                if revision == 255:
                    self.assertEqual(0, result.returncode, result.stderr)
                else:
                    self.assertNotEqual(0, result.returncode)
                    self.assertIn(
                        "VSCP_HELPER_LIB_VERSION_REVISION must be between 0 and 255",
                        result.stderr,
                    )


if __name__ == "__main__":
    unittest.main()
