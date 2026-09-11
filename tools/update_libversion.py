#!/usr/bin/env python3
"""Increment the VSCP Helper Library patch version."""

from __future__ import annotations

from pathlib import Path
import re


VERSION_PATH = Path(__file__).resolve().parents[1] / "src" / "libversion.h"
VERSION_PATTERN = re.compile(
    r'^(#define VSCP_HELPER_LIB_VERSION ")([0-9]+)\.([0-9]+)\.([0-9]+)("\s*)$',
    re.MULTILINE,
)
PATCH_PATTERN = re.compile(
    r"^(#define VSCP_HELPER_LIB_VERSION_PATCH )([0-9]+)(\s*)$", re.MULTILINE
)


def main() -> None:
    content = VERSION_PATH.read_text(encoding="utf-8")
    version_match = VERSION_PATTERN.search(content)
    patch_match = PATCH_PATTERN.search(content)
    if version_match is None or patch_match is None:
        raise ValueError("libversion.h must define VSCP_HELPER_LIB_VERSION and its patch component")

    major, minor, patch = (int(version_match.group(index)) for index in range(2, 5))
    if patch != int(patch_match.group(2)):
        raise ValueError("VSCP_HELPER_LIB_VERSION and VSCP_HELPER_LIB_VERSION_PATCH disagree")

    next_patch = patch + 1
    content = VERSION_PATTERN.sub(
        rf"\g<1>{major}.{minor}.{next_patch}\g<5>", content, count=1
    )
    content = PATCH_PATTERN.sub(rf"\g<1>{next_patch}\g<3>", content, count=1)
    VERSION_PATH.write_text(content, encoding="utf-8")


if __name__ == "__main__":
    main()