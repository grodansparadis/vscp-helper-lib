#!/usr/bin/env python3
"""Synchronize the VSCP Helper Library patch version with Git history."""

from __future__ import annotations

import argparse
from pathlib import Path
import re
import subprocess


VERSION_PATH = Path(__file__).resolve().parents[1] / "src" / "libversion.h"
VERSION_PATTERN = re.compile(
    r'^(#define VSCP_HELPER_LIB_VERSION ")([0-9]+)\.([0-9]+)\.([0-9]+)\.([0-9]+)("[ \t]*)$',
    re.MULTILINE,
)
REVISION_PATTERN = re.compile(
    r"^#define[ \t]+VSCP_HELPER_LIB_VERSION_REVISION[ \t]+(0|[1-9][0-9]*)[ \t]*$",
    re.MULTILINE,
)
PATCH_PATTERN = re.compile(
    r"^(#define VSCP_HELPER_LIB_VERSION_PATCH[ \t]+)([0-9]+)([ \t]*)$",
    re.MULTILINE,
)


def read_version_components(
    content: str, *, allow_unsynchronized_revision: bool = False
) -> tuple[int, int, int, int]:
    version_match = VERSION_PATTERN.search(content)
    revision_match = REVISION_PATTERN.search(content)
    patch_match = PATCH_PATTERN.search(content)
    if version_match is None or patch_match is None:
        raise ValueError(
            "libversion.h must define a four-part VSCP_HELPER_LIB_VERSION, "
            "and VSCP_HELPER_LIB_VERSION_PATCH"
        )
    if revision_match is None:
        raise ValueError(
            "VSCP_HELPER_LIB_VERSION_REVISION must be an unpadded decimal "
            "integer between 0 and 255"
        )

    major, minor, displayed_revision, displayed_patch = (
        int(version_match.group(index)) for index in range(2, 6)
    )
    revision = int(revision_match.group(1))
    if revision > 255:
        raise ValueError("VSCP_HELPER_LIB_VERSION_REVISION must be between 0 and 255")
    if displayed_patch != int(patch_match.group(2)):
        raise ValueError("VSCP_HELPER_LIB_VERSION and VSCP_HELPER_LIB_VERSION_PATCH disagree")
    if not allow_unsynchronized_revision and displayed_revision != revision:
        raise ValueError(
            "VSCP_HELPER_LIB_VERSION and VSCP_HELPER_LIB_VERSION_REVISION disagree; "
            "run python3 tools/update_libversion.py"
        )
    return major, minor, revision, displayed_patch


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
    major, minor, revision, _ = read_version_components(
        content, allow_unsynchronized_revision=True
    )
    patch_version = get_patch_version(arguments.next_commit)
    content = VERSION_PATTERN.sub(
        rf"\g<1>{major}.{minor}.{revision}.{patch_version}\g<6>", content, count=1
    )
    content = PATCH_PATTERN.sub(rf"\g<1>{patch_version}\g<3>", content, count=1)
    VERSION_PATH.write_text(content, encoding="utf-8")


if __name__ == "__main__":
    main()