#!/bin/sh
# Fixed compiler spellings must not silently fall back to kwSpan's source walk.
set -eu
cd "$(dirname "$0")"

python3 - <<'PY'
from pathlib import Path
import re

root = Path("src")
literal_kw_span = []
known = set()
for path in root.rglob("*.pw"):
    text = path.read_text()
    literal_kw_span.extend((path, value) for value in re.findall(r'kwSpan\(kw:\s*"([^"]*)"', text))
    known.update(re.findall(r'wellKnownSpan\(kw:\s*"([^"]*)"', text))

if literal_kw_span:
    rendered = ", ".join(f"{path}:{value!r}" for path, value in literal_kw_span)
    raise SystemExit(f"fixed spelling bypasses wellKnownSpan: {rendered}")

recovery = (root / "Codegen/Resolve/TypeRecovery.pw").read_text()
registered = set(re.findall(r'addKwSpan\(kw:\s*"([^"]*)"', recovery))
missing = sorted(known - registered)
if missing:
    raise SystemExit(f"wellKnownSpan spelling is not registered: {missing}")

print("PASS well-known-span-boundary")
PY
