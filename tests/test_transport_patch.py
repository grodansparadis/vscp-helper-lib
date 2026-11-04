#!/usr/bin/env python3
"""Regression tests for build-local patch checkout line endings."""

from pathlib import Path
import shutil
import subprocess
import tempfile
import unittest


ROOT = Path(__file__).resolve().parents[1]
PATCHES = (
    Path("cmake/patches/vscp-authenticated-binary.patch"),
    Path("cmake/patches/vscp-helper-logging.patch"),
)


@unittest.skipUnless(shutil.which("git"), "Git is required")
class TransportPatchTests(unittest.TestCase):
    def test_patches_stay_lf_with_windows_checkout_settings(self) -> None:
        for patch_path in PATCHES:
            original = (ROOT / patch_path).read_bytes().replace(b"\r\n", b"\n")
            for autocrlf in ("true", "false"):
                with self.subTest(patch=patch_path, autocrlf=autocrlf), tempfile.TemporaryDirectory() as directory:
                    root = Path(directory)
                    patch = root / patch_path
                    patch.parent.mkdir(parents=True)
                    patch.write_bytes(original)
                    attributes = ROOT / ".gitattributes"
                    if attributes.exists():
                        shutil.copy2(attributes, root / ".gitattributes")
                    git = [
                        "git", "-C", str(root),
                        "-c", f"core.autocrlf={autocrlf}",
                        "-c", "core.eol=crlf",
                        "-c", "core.safecrlf=false",
                    ]
                    subprocess.run(git + ["init", "--quiet"], check=True)
                    subprocess.run(git + ["add", "."], check=True, capture_output=True)
                    patch.unlink()
                    subprocess.run(
                        git + ["checkout-index", "--all", "--force"], check=True
                    )
                    self.assertEqual(original, patch.read_bytes())


if __name__ == "__main__":
    unittest.main()
