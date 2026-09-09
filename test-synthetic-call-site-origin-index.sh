#!/bin/sh
# Synthetic calls have no source spelling. Their producer records the origin
# once; consumers must use the direct ExprId navigation table rather than
# scanning every synthetic call while finalizing a body.
set -eu
cd "$(dirname "$0")"

python3 - <<'PY'
from pathlib import Path
import re

ir = Path("src/Ir.pw").read_text()
expr = Path("src/Codegen/Resolve/Expr.pw").read_text()
record = Path("src/Codegen/Resolve/Record.pw").read_text()
mono = Path("src/Codegen/Mono/Call.pw").read_text()
sources = list(Path("src").rglob("*.pw"))

if "pub mut val syntheticCallSiteByExpr: Array[U64] = []" not in ir:
    raise SystemExit("missing direct ExprId-to-synthetic-call index")

registration = "inout fn recordSyntheticCallSite(site: SyntheticCallSite)"
reader = "fn syntheticCallSiteIndex(exprId: U64) -> U64"
if registration not in expr or reader not in expr:
    raise SystemExit("missing canonical synthetic-call registration or reader")

for name, signature, source in [
    ("templateCallSiteKey", "inout fn templateCallSiteKey(", expr),
    ("syntheticCallReceiverTerm", "inout fn syntheticCallReceiverTerm(", record),
    ("currentCallSiteKey", "inout fn currentCallSiteKey(", mono),
    ("selectedCallReceiverRef", "inout fn selectedCallReceiverRef(", mono),
]:
    start = source.index(signature)
    body = source[start:source.find("\n    }", start) + 6]
    if "self.syntheticCallSiteIndex(exprId:" not in body:
        raise SystemExit(f"{name} bypasses the canonical synthetic-call reader")

for path in sources:
    text = path.read_text()
    if path.as_posix().endswith("Codegen/Resolve/Expr.pw"):
        start = text.index(registration)
        end = text.find("\n    }", start) + 6
        text = text[:start] + text[end:]
    if ".syntheticCallSites.append(" in text:
        raise SystemExit(f"producer bypasses canonical synthetic-call registration: {path}")
    if re.search(r"while\s+\w+\s*<\s*self\.decls\.syntheticCallSites\.count\(\)", text):
        raise SystemExit(f"consumer scans all synthetic call sites: {path}")

print("PASS synthetic-call-site-origin-index")
PY
