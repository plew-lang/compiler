#!/usr/bin/env python3
"""Check emitted activations and lazy execution of standalone async adapters."""
import os
from pathlib import Path
import re
import subprocess

root = Path(__file__).resolve().parents[3]
carrier = os.environ.get("PLEWC", str(root / "bin/plewc"))
fixtures = root / "tests/fixtures/run"
cases = {
    "async_instance_via": 2,
    "async_instance_via_default": 2,
    "async_instance_via_move": 2,
    "async_instance_via_callable_form": 2,
    "async_instance_via_unit": 2,
    "async_instance_via_authored": 3,
}

for name, expected_count in cases.items():
    fixture = fixtures / f"{name}.pw"
    ir = subprocess.run([carrier, str(fixture)], check=True, text=True,
                        stdout=subprocess.PIPE).stdout
    for routine in ("plew_frame_alloc", "plew_promise_new"):
        count = len(re.findall(r"\bcall\s+ptr\s+@" + routine + r"\(", ir))
        if count != expected_count:
            raise SystemExit(f"{name}: {routine}: expected {expected_count} calls, found {count}")
    result = subprocess.run([carrier, "--run", str(fixture)], check=True,
                            stdout=subprocess.PIPE).stdout
    if result != fixture.with_suffix(".out").read_bytes():
        raise SystemExit(f"{name}: unexpected ORC output: {result!r}")
    print(f"PASS {name}: {expected_count} AOT activations and exact ORC output", flush=True)
