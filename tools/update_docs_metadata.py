#!/usr/bin/env python3
"""Refresh documentation metadata after a repository push."""

from __future__ import annotations

from datetime import datetime, timezone
from pathlib import Path
import re

if __package__:
    from .update_libversion import read_version_components
else:
    from update_libversion import read_version_components


REPO_ROOT = Path(__file__).resolve().parents[1]
VARIABLES_PATH = REPO_ROOT / "docs" / "variables.xml"
VERSION_PATH = REPO_ROOT / "src" / "libversion.h"


def get_library_version() -> str:
    components = read_version_components(VERSION_PATH.read_text(encoding="utf-8"))
    return ".".join(str(component) for component in components)


def main() -> None:
    now = datetime.now(timezone.utc)
    content = VARIABLES_PATH.read_text(encoding="utf-8")
    if not re.search(r"<creation-time>.*?</creation-time>", content) or not re.search(
        r"<document-version>.*?</document-version>", content
    ):
        raise ValueError("variables.xml must contain creation-time and document-version elements")

    creation_timestamp = now.strftime("%Y-%m-%d %H:%M UTC")
    version = get_library_version()
    content = re.sub(
        r"<creation-time>.*?</creation-time>",
        f"<creation-time>{creation_timestamp}</creation-time>",
        content,
    )
    content = re.sub(
        r"<document-version>.*?</document-version>",
        f"<document-version>{version}</document-version>",
        content,
    )
    VARIABLES_PATH.write_text(content, encoding="utf-8")


if __name__ == "__main__":
    main()