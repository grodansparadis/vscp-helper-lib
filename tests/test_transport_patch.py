#!/usr/bin/env python3
"""Regression tests for transport patch checkout line endings."""

from pathlib import Path
import shutil
import subprocess
import tempfile
import unittest


ROOT = Path(__file__).resolve().parents[1]
PATCH = Path("cmake/patches/vscp-authenticated-binary.patch")


@unittest.skipUnless(shutil.which("git"), "Git is required")
class TransportPatchTests(unittest.TestCase):
    def test_patch_stays_lf_with_windows_checkout_settings(self) -> None:
        original = (ROOT / PATCH).read_bytes().replace(b"\r\n", b"\n")
        for autocrlf in ("true", "false"):
            with self.subTest(autocrlf=autocrlf), tempfile.TemporaryDirectory() as directory:
                root = Path(directory)
                patch = root / PATCH
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
