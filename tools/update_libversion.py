#!/usr/bin/env python3
"""Synchronize the VSCP Helper Library patch version with Git history."""

from __future__ import annotations

import argparse
from pathlib import Path
import re
import subprocess


VERSION_PATH = Path(__file__).resolve().parents[1] / "src" / "libversion.h"
VERSION_PATTERN = re.compile(
    r'^(#define VSCP_HELPER_LIB_VERSION ")([0-9]+)\.([0-9]+)\.([0-9]+)("\s*)$',
    re.MULTILINE,
)
PATCH_PATTERN = re.compile(
    r"^(#define VSCP_HELPER_LIB_VERSION_PATCH )([0-9]+)(\s*)$", re.MULTILINE
)


def get_patch_version(include_pending_commit: bool) -> int:
    commit_count = subprocess.check_output(
        ["git", "rev-list", "--first-parent", "--count", "HEAD"],
        cwd=VERSION_PATH.parent.parent,
        text=True,
    ).strip()
    return int(commit_count) + int(include_pending_commit)


def main() -> None:
    parser = argparse.ArgumentParser()
    parser.add_argument(
        "--next-commit",
        action="store_true",
        help="Use the first-parent count of the commit currently being created.",
    )
    arguments = parser.parse_args()

    content = VERSION_PATH.read_text(encoding="utf-8")
    version_match = VERSION_PATTERN.search(content)
    patch_match = PATCH_PATTERN.search(content)
    if version_match is None or patch_match is None:
        raise ValueError("libversion.h must define VSCP_HELPER_LIB_VERSION and its patch component")

    major, minor, current_patch = (
        int(version_match.group(index)) for index in range(2, 5)
    )
    if current_patch != int(patch_match.group(2)):
        raise ValueError("VSCP_HELPER_LIB_VERSION and VSCP_HELPER_LIB_VERSION_PATCH disagree")

    patch_version = get_patch_version(arguments.next_commit)
    content = VERSION_PATTERN.sub(
        rf"\g<1>{major}.{minor}.{patch_version}\g<5>", content, count=1
    )
    content = PATCH_PATTERN.sub(rf"\g<1>{patch_version}\g<3>", content, count=1)
    VERSION_PATH.write_text(content, encoding="utf-8")


if __name__ == "__main__":
    main()