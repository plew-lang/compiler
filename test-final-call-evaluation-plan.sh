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

llvm = Path("src/Backend/Llvm/Mid.pw").read_text()
start = llvm.index("inout fn midCanonicalEmitDirectCall(")
end = llvm.index("\n    inout fn ", start + 1)
call = llvm[start:end]
for required in ["c.mid.callArguments[term.args.start + argumentI]", "selected.parameterTypeRefs", "selected.argumentPassings"]:
    if required not in call:
        raise SystemExit(f"Mid call does not consume the frozen argument contract: {required}")
for path in Path("src/Backend").rglob("*.pw"):
    text = path.read_text()
    if "bodyCalleeArgumentRange(" in text or "callArgumentRangeForCurrentBody(" in text:
        raise SystemExit(f"LLVM reopens source expression arguments: {path}")

print("PASS final-call-evaluation-plan")
PY
