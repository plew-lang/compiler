#!/bin/sh
# Long-lived parametric call facts are read across Record, finalization, Mid,
# and legacy lowering. Their rows must stay scalar: an inline Array or proof
# tree turns a descriptor lookup into ARC traffic and reopens ownership data.
set -eu
cd "$(dirname "$0")"

python3 - <<'PY'
from pathlib import Path

ir = Path("src/Ir.pw").read_text()
for required in [
    "export struct CallTemplateArgumentRange",
    "export struct CallTemplateTypeArgumentRange",
    "export struct CallTemplateOperandRange",
    "export struct CallTemplateViewRange",
    "pub mut val callTemplateArgumentPool: Array[CallTemplateArgument]",
    "pub mut val callTemplateTypeArgumentPool: Array[U64]",
    "pub mut val callTemplateOperandPool: Array[CallArgumentSource]",
    "pub mut val callTemplateViewPool: Array[ResolvedViewSource]",
    "proofId: U64",
]:
    if required not in ir:
        raise SystemExit(f"missing scalar CallTemplate storage: {required}")

for forbidden in [
    "args: Array[CallTemplateArgument]",
    "calleeTypeArgs: Array[U64]",
    "proof: StaticConformanceProof",
    "operands: Array[CallArgumentSource]",
    "views: Array[ResolvedViewSource]",
]:
    if forbidden in ir:
        raise SystemExit(f"CallTemplate keeps an inline ownership payload: {forbidden}")

print("PASS call-template-scalar-storage")
PY
