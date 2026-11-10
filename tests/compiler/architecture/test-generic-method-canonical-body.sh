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
for required in ["self.genMethBody[slot] == bodyId", "c.arena.bodySignature(bodyId: bodyId)",
                 "self.bodyValueAbi(c: inout c, bodyId: bodyId)",
                 "self.valueAbis[abiId - 1U64].logicalSignature",
                 "self.declarePlannedBodyFunction(name: arrayCPtr(nm), abiId: abiId, bodyId: bodyId)",
                 "bodyId: bodyId, fv: self.genMethVal[slot]"]:
    if required not in methods:
        raise SystemExit(f"Method emission lost the frozen body contract: {required}")
ordinary = Path("src/Backend/Llvm/Any.pw").read_text().split("inout fn genLlvmFuncBody(", 1)[1]
if "findBodyInstance(" in ordinary:
    raise SystemExit("Function emission re-queries an already selected body")
# Receiver and parameter lowering belong to the common completed ABI planner,
# not a second method-only path. Preserve the original frozen-signature checks
# at their actual owner after removing that duplicate path.
planner = Path('src/Backend/Llvm/ValueAbi.pw').read_text().split('inout fn bodyValueAbi(', 1)[1].split('\n    inout fn ', 1)[0]
for required in ['c.arena.bodySignature(bodyId: bodyId)', 'signature.receiverPassing',
                 'signature.receiverType', 'signature.parameterTypes', 'signature.parameterPassings',
                 'signature.resultType', 'resultTerm=signature.resultType']:
    assert required in planner, f'common ABI planner lost frozen method facts: {required}'
assert 'self.prepareCanonicalForLlvm(c: inout c, bodyId: bodyId' in ordinary
assert 'self.genLlvmPreparedMidBody(c: inout c, prepared: preparedMid)' in ordinary

if ('appendBytes(into: inout nm, from: "_b".bytes())' not in methods or
        'appendU64Dec(into: inout nm, n: bodyId)' not in methods):
    raise SystemExit("generic-method LLVM symbol omits finalized BodyInstance identity")

print("PASS generic-method-canonical-body")
PY
