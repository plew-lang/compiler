#!/bin/sh
# A final CallResolution is the complete source-to-ABI contract. LLVM may use
# its ExprIds as navigation anchors, but must not reopen a shared CallTemplate
# to rediscover which expressions/labels supplied that selected call.
set -eu
cd "$(dirname "$0")"

python3 - <<'PY'
from pathlib import Path

ir = Path("src/Ir.pw").read_text()
for required in [
    "export struct CallResolutionArgumentRange",
    "export struct CallEvaluationArgument",
    "pub val arguments: CallResolutionArgumentRange",
    "pub mut val finalCalleeArgumentPool: Array[CallEvaluationArgument]",
]:
    if required not in ir:
        raise SystemExit(f"final call evaluation plan is missing: {required}")

mono = Path("src/Codegen/Mono/Call.pw").read_text()
for required in [
    "inout fn pushFinalCalleeArguments(arguments: Array[CallTemplateArgument])",
    "inout fn bodyCalleeArgumentRange(exprId: U64",
    "arguments: selection.argumentSources",
    "arguments: argumentSources",
]:
    if required not in mono:
        raise SystemExit(f"final call evaluation plan is not published: {required}")

start = mono.index("inout fn bodyCalleeArgumentRange(exprId: U64")
end = mono.index("inout fn bodyCalleeResultRef", start)
if "callTemplate" in mono[start:end]:
    raise SystemExit("backend argument adapter reopens CallTemplate")

llvm = Path("src/Backend/Llvm/Expr.pw").read_text()
if llvm.count("c.bodyCalleeArgumentRange(exprId: id)") != 3:
    raise SystemExit("direct/method LLVM calls do not all use the final evaluation plan")
if "callArgumentRangeForCurrentBody(exprId: id" in llvm:
    raise SystemExit("LLVM expression lowering reopens parametric call arguments")

print("PASS final-call-evaluation-plan")
PY
