#!/bin/sh
# A final CallResolution is published under its complete semantic key.  Both
# frontend consumers and Mid must read that same derived index; Mid must not
# recover a final answer by scanning the semantic table again.
set -eu
cd "$(dirname "$0")"

python3 - <<'PY'
from pathlib import Path

mono = Path("src/Codegen/Mono/Call.pw").read_text()
mid = Path("src/Mid/Instantiate.pw").read_text()

reader = "fn finalCalleeIndexForKey(bodyId: U64, siteKey: CallSiteKey) -> U64"
if reader not in mono:
    raise SystemExit("missing canonical final-callee key reader")

start = mono.index(reader)
end = mono.index("    // AST navigation adapter", start)
body = mono[start:end]
for required in [
    "self.finalCalleeHash(bodyId: bodyId, siteKey: siteKey)",
    "self.finalCalleeKeyEqual(entry: entry, bodyId: bodyId, siteKey: siteKey)",
    "return self.finalCalleeCount()",
]:
    if required not in body:
        raise SystemExit(f"canonical reader is incomplete: {required}")
for forbidden in ["currentBodyInstanceId", "currentCallSiteKey"]:
    if forbidden in body:
        raise SystemExit(f"canonical reader reconstructs ambient identity: {forbidden}")

adapter = "inout fn bodyCalleeIndex(exprId: U64"
adapter_start = mono.index(adapter)
adapter_end = mono.index("    // A call in a body without substitutions", adapter_start)
adapter_body = mono[adapter_start:adapter_end]
if "self.finalCalleeIndexForKey(bodyId: bodyId, siteKey: siteKey)" not in adapter_body:
    raise SystemExit("AST navigation adapter bypasses canonical key reader")

if "fn midFinalResolution(" in mid:
    raise SystemExit("Mid scans finalCallees instead of using the canonical index")
if mid.count("c.finalCalleeIndexForKey(bodyId: bodyId, siteKey: site)") != 3:
    raise SystemExit("Mid call sites do not all use the canonical key reader")

print("PASS final-callee-canonical-index")
PY
