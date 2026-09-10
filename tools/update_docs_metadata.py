#!/usr/bin/env python3
"""Refresh documentation metadata after a repository push."""

from __future__ import annotations

import subprocess
from datetime import datetime, timezone
from pathlib import Path
import re


REPO_ROOT = Path(__file__).resolve().parents[1]
VARIABLES_PATH = REPO_ROOT / "docs" / "variables.xml"


def get_monthly_commit_count(now: datetime) -> int:
    month_start = now.strftime("%Y-%m-01")
    result = subprocess.run(
        ["git", "-C", str(REPO_ROOT), "rev-list", "--count", "HEAD", f"--since={month_start}"],
        check=True,
        capture_output=True,
        text=True,
    )
    return int(result.stdout.strip())


def main() -> None:
    now = datetime.now(timezone.utc)
    content = VARIABLES_PATH.read_text(encoding="utf-8")
    if not re.search(r"<creation-time>.*?</creation-time>", content) or not re.search(
        r"<document-version>.*?</document-version>", content
    ):
        raise ValueError("variables.xml must contain creation-time and document-version elements")

    creation_timestamp = now.strftime("%Y-%m-%d %H:%M UTC")
    version = f"{now:%y-%m}-{get_monthly_commit_count(now)}"
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