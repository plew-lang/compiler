#!/bin/sh
# Long-lived parametric call facts are read across Record, finalization, Mid,
# and legacy lowering. Their rows must stay scalar: an inline Array or proof
# tree turns a descriptor lookup into ARC traffic and reopens ownership data.
set -eu
cd "$(dirname "$0")/../../.."

python3 - <<'PY'
from pathlib import Path

ir = Path("src/Ir.pw").read_text()
for required in [
    "pub struct CallTemplateArgumentRange",
    "pub struct CallTemplateTypeArgumentRange",
    "pub struct CallTemplateOperandRange",
    "pub struct CallTemplateViewRange",
    "proofId: U64",
]:
    if required not in ir:
        raise SystemExit(f"missing scalar CallTemplate storage: {required}")

frontend = Path("src/Frontend.pw").read_text()
for field in [
    "callTemplateArgumentPool: Array[CallTemplateArgument]",
    "callTemplateTypeArgumentPool: Array[U64]",
    "callTemplateOperandPool: Array[CallArgumentSource]",
    "callTemplateViewPool: Array[ResolvedViewSource]",
]:
    if "    mut val " + field not in frontend:
        raise SystemExit(f"missing private frontend CallTemplate pool: {field}")
    if "pub mut val " + field in frontend or "pub mut val " + field in ir:
        raise SystemExit(f"CallTemplate pool exposes mutable storage: {field}")

receiver_start = ir.index("pub enum CallTemplateReceiver")
receiver_end = ir.index("pub enum CallArgumentSource", receiver_start)
receiver_shape = ir[receiver_start:receiver_end]
kind_start = ir.index("pub enum CallTemplateKind")
kind_end = ir.index("pub struct CallTemplate {", kind_start)
kind_shape = ir[kind_start:kind_end]
if "views: Array[ResolvedViewSource]" in receiver_shape:
    raise SystemExit("CallTemplate receiver keeps an inline ownership payload")
for forbidden in [
    "args: Array[CallTemplateArgument]",
    "calleeTypeArgs: Array[U64]",
    "proof: StaticConformanceProof",
    "operands: Array[CallArgumentSource]",
]:
    if forbidden in kind_shape:
        raise SystemExit(f"CallTemplate keeps an inline ownership payload: {forbidden}")

print("PASS call-template-scalar-storage")
PY
