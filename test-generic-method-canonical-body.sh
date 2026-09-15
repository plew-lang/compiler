#!/bin/sh
# Source-level generic receiver calls have a final CallResolution.  LLVM must
# use that selected BodyInstance rather than reconstruct a specialization key.
set -eu
cd "$(dirname "$0")"

python3 - <<'PY'
from pathlib import Path

mid = Path("src/Backend/Llvm/Mid.pw").read_text()
start = mid.index("inout fn midCanonicalEmitDirectCall(")
end = mid.index("\n    inout fn ", start + 1)
call = mid[start:end]
for required in ["bodyId: selected.calleeBodyId", "instRef: selected.recvTypeRef", "selected.calleeTypeArgs"]:
    if required not in call:
        raise SystemExit(f"Mid call does not preserve the finalized method contract: {required}")
if "findBodyInstance(" in call or "enterBodyInstance(" in call:
    raise SystemExit("Mid call reconstructs the finalized body identity")

methods = Path("src/Backend/Llvm/GenMethods.pw").read_text()
if "inout fn ensureFinalGenMethodBody(c: inout Comp, bodyId: U64)" not in methods:
    raise SystemExit("missing canonical generic-method BodyInstance entrypoint")
if "val ownArgs: Array[U64] = self.finalBodyMethodOwnArgs(c: inout c, f: f, environment: body.environment)" not in methods:
    raise SystemExit("canonical generic-method entrypoint does not derive own args from BodyInstance")
if "val instRef: U64 = body.environment.receiverRef" not in methods:
    raise SystemExit("canonical generic-method entrypoint does not derive receiver from BodyInstance")
if ('appendBytes(into: inout nm, from: "_b".bytes())' not in methods or
        'appendU64Dec(into: inout nm, n: bodyId)' not in methods):
    raise SystemExit("generic-method LLVM symbol omits finalized BodyInstance identity")

print("PASS generic-method-canonical-body")
PY
