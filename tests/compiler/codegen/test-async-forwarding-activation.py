#!/usr/bin/env python3
"""Count frame and Promise allocations in the standalone async via program."""
import os
from pathlib import Path
import re
import subprocess

root = Path(__file__).resolve().parents[3]
carrier = os.environ.get("PLEWC", str(root / "bin/plewc"))
fixture = root / "tests/fixtures/run/async_instance_via.pw"
result = subprocess.run([carrier, str(fixture)], check=True, text=True,
                        stdout=subprocess.PIPE)
for routine in ("plew_frame_alloc", "plew_promise_new"):
    count = len(re.findall(r"\bcall\s+ptr\s+@" + routine + r"\(", result.stdout))
    if count != 2:
        raise SystemExit(f"{routine}: expected 2 calls (main and target), found {count}")
print("PASS async via emits only the main and target activations")
