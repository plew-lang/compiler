#!/bin/sh
# Source-level generic receiver calls have a final CallResolution.  LLVM must
# use that selected BodyInstance rather than reconstruct a specialization key.
set -eu
cd "$(dirname "$0")/../../.."

python3 - <<'PY'
from pathlib import Path

mid = Path("src/Backend/Llvm/Mid.pw").read_text()
start = mid.index("inout fn midCanonicalEmitDirectCall(")
end = mid.index("\n    inout fn ", start + 1)
call = mid[start:end]
if "ensureFinalGenMethodBody(c: inout c, bodyId: selected.calleeBodyId)" not in call:
    raise SystemExit("Mid call does not consume the finalized method body")
for forbidden in ["recvParamCount(", "copyFinalCalleeTypeArgs(", "findBodyInstance(", "enterBodyInstance("]:
    if forbidden in call:
        raise SystemExit(f"Mid call reconstructs the finalized body identity: {forbidden}")

methods = Path("src/Backend/Llvm/GenMethods.pw").read_text()
for forbidden in ["bodyInstanceEnvironment(", "findBodyInstance(", "recvParamCount(", "ensureGenMethodDeclared(", "genMethOwn", "finalBodyMethodOwnArgs", "body.environment.params", "body.environment.args"]:
    if forbidden in methods:
        raise SystemExit(f"Method emission reconstructs specialization state: {forbidden}")
for required in ["self.genMethBody[slot] == bodyId", "c.arena.bodySignature(bodyId: bodyId)", "signature.receiverPassing",
                 "signature.receiverType", "bodyReturnLlvmTy(c: inout c, bodyId: bodyId)",
                 "bodyId: bodyId, fv: self.genMethVal[slot]", "bodyId: bodyId, index: pi"]:
    if required not in methods:
        raise SystemExit(f"Method emission lost the frozen body contract: {required}")
ordinary = Path("src/Backend/Llvm/Any.pw").read_text().split("inout fn genLlvmFuncBody(", 1)[1]
if "findBodyInstance(" in ordinary:
    raise SystemExit("Function emission re-queries an already selected body")

if ('appendBytes(into: inout nm, from: "_b".bytes())' not in methods or
        'appendU64Dec(into: inout nm, n: bodyId)' not in methods):
    raise SystemExit("generic-method LLVM symbol omits finalized BodyInstance identity")

print("PASS generic-method-canonical-body")
PY
