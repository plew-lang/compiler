#!/bin/sh
# The production Mid path is intentionally one-way: build freezes once, then
# instantiation, access elaboration, drop elaboration, verification and LLVM
# emission consume only MidCanonicalBody.  A textual gate is appropriate here:
# it protects this architectural boundary even while fresh WIP candidates
# cannot yet compile every ordinary-function fixture.
set -eu
cd "$(dirname "$0")"

entries="src/Backend/Llvm/Entry.pw src/Backend/Llvm/Any.pw"
legacy='\bMidBody\b|\bMidInstantiation\b|\bMidAccessElaboration\b|\binstantiateMidBody\b|\belaborateMidAccesses\b|\belaborateMidDrops\b|\bverifyMidBody\b|\bmidInitialLlvmPreflight\b|\bgenLlvmMidBody\b'
canonical='MidCanonicalBody instantiateCanonicalMidBody elaborateCanonicalMidAccesses elaborateCanonicalMidDrops verifyExecutableCanonicalMidBody midVerifiedLlvmPreflight genLlvmPreparedMidBody'

if rg -n "$legacy" $entries; then
    echo "legacy Mid consumer remains in a production entry" >&2
    exit 1
fi

for entry in $entries; do
    for symbol in $canonical; do
        if ! rg -q "\b$symbol\b" "$entry"; then
            echo "canonical Mid pipeline is missing $symbol in $entry" >&2
            exit 1
        fi
    done
done

# LLVM ABI argument position and the number of Mid source parameters are
# separate facts. They coincide for ordinary functions only accidentally;
# closures reserve ABI argument 0 for their environment.
# Preflight validates the count once; the Ready value carries that evidence
# to emission instead of passing a second, independently supplied count.
for needle in 'abiParameterCount: abiParameterCount' 'MidLlvmPrepared.Ready canonical=elaborated abiParameterCount=abiParameterCount' 'prepared: preparedMid'; do
    if ! grep -F "$needle" src/Backend/Llvm/Any.pw >/dev/null; then
        echo "ordinary Mid preparation is missing $needle" >&2
        exit 1
    fi
done
for needle in 'prepared: MidLlvmPrepared' 'MidLlvmPrepared.None => { return false }' 'MidLlvmPrepared.Ready(canonical:'; do
    if ! grep -F "$needle" src/Backend/Llvm/Mid.pw >/dev/null; then
        echo "canonical Mid prepared-body contract is missing $needle" >&2
        exit 1
    fi
done

# The admitted count may now be consumed when physical ABI values are supplied.
# Verify the hand-off and rejection guard without pinning the binding's name.
python3 - <<'PYABI'
from pathlib import Path
import re
source = Path('src/Backend/Llvm/Mid.pw').read_text()
body = source.split('inout fn genLlvmPreparedMidBody(', 1)[1]
signature, body = body.split(') -> Bool {', 1)
assert 'abiParameterCount:' not in signature, 'emission must not accept a second count'
ready = re.search(r'MidLlvmPrepared\.Ready\(canonical:\s*val\s+(\w+),\s*abiParameterCount:\s*val\s+(\w+)\)', body)
assert ready, 'Ready must carry the admitted body and parameter count'
canonical, count = ready.groups()
values = re.search(r'(\w+):\s*Array\[LLVMValueRef\]', signature)
assert values, 'physical ABI bindings must be explicit'
array = re.escape(values.group(1))
guard = rf'if\s+{array}\.count\(\)\s*!=\s*0U64\s*&&\s*{array}\.count\(\)\s*!=\s*{re.escape(count)}\s*\{{\s*return false\s*\}}'
assert re.search(guard, body), 'mismatched physical bindings must be rejected'
assert re.search(rf'give\s+{re.escape(canonical)}\b', body), 'emit the admitted canonical body'
PYABI

# Module initialization is also executable Plew code.  It has no user Func
# row, so keep its synthetic body explicit rather than letting Entry.pw grow a
# second AST-to-LLVM path that happens to run before `main`.
global_canonical='declareGlobalStorage buildParametricMidGlobalInit instantiateCanonicalMidBody elaborateCanonicalMidAccesses elaborateCanonicalMidDrops verifyExecutableCanonicalMidBody midVerifiedLlvmPreflight genLlvmPreparedMidBody'
for symbol in $global_canonical; do
    if ! rg -q "\b$symbol\b" src/Backend/Llvm/Entry.pw; then
        echo "global initializer Mid pipeline is missing $symbol" >&2
        exit 1
    fi
done

# `--require-mid` is a soundness gate, not a preference.  Every synthetic-body
# failure shape must enter the same closed coverage table that makes the driver
# reject a legacy fallback.
for symbol in recordMidMissingBodyInstance recordMidBuildError recordMidInstantiate recordMidAccess recordMidVerify recordMidPreflight; do
    if ! rg -q "\b$symbol\b" src/Backend/Llvm/Entry.pw; then
        echo "global initializer fallback is not covered by $symbol" >&2
        exit 1
    fi
done

# Executable verification must preserve the earlier ownership/dataflow pass.
python3 - <<'PYVERIFY'
from pathlib import Path
source = Path('src/Mid/Verify.pw').read_text()
body = source.split('export fn verifyExecutableCanonicalMidBody(', 1)[1].split('export fn verifyCanonicalMidBody(', 1)[0]
assert 'verifyCanonicalMidBodyStage(c: inout c, canonical: canonical, executable: true)' in body
assert 'executable: false' in source
assert 'MissingOwnershipContract' in source
for path in Path('src/Backend').rglob('*.pw'):
    assert 'verifyCanonicalMidBody(' not in path.read_text(), f'{path}: executable admission bypassed'
PYVERIFY

# Async semantic bodies must stay on canonical Mid. Runtime frame/Promise glue
# may emit LLVM directly, but must never evaluate source expressions or clean up
# source scopes itself.
if rg -n '\b(genLlvmExpr|genLlvmStmt|dropScope|curAsync|asyncFieldNext|asyncSlotPtrs)\b' src/Backend/Llvm/Async.pw src/Backend/Llvm/MidAsync.pw; then
    echo 'async emission contains a legacy semantic path' >&2
    exit 1
fi

python3 - <<'PYENTRY'
from pathlib import Path
import re
entry = Path('src/Backend/Llvm/Entry.pw').read_text()
function = Path('src/Backend/Llvm/Any.pw').read_text().split('inout fn genLlvmFuncBody(', 1)[1]
for source in (entry, function):
    assert not re.search(r'\b(genLlvmBlock|genLlvmStmt|genLlvmExpr)\(', source), 'executable entry reopened an AST path'
PYENTRY

# No source expression/statement interpreter or draft Mid LLVM emitter remains.
# This covers helper files as well as the public executable entry points.
if rg -n '\b(genLlvmExpr|genLlvmStmt|genLlvmBlock|genLlvmMidBody|dropScope)\s*\(' src/Backend; then
    echo 'legacy semantic LLVM consumer remains' >&2
    exit 1
fi

# Global storage consumes the frozen Let contract; Mid owns its terminator.
python3 - <<'PYGLOBAL'
from pathlib import Path
entry = Path('src/Backend/Llvm/Entry.pw').read_text()
storage = entry.split('inout fn declareGlobalStorage(', 1)[1].split('inout fn genLlvmInitGlobals(', 1)[0]
assert 'finalStorageIndex(' in storage and '.targetTypeRef' in storage
assert 'arena.stmts' not in storage and 'semanticExprTerm(' not in storage
initializer = entry.split('inout fn genLlvmInitGlobals(', 1)[1].split('inout fn genLlvmMain(', 1)[0]
assert 'LLVMBuildRetVoid(' not in initializer, 'Mid already emits the initializer terminator'
PYGLOBAL

# Enum payload layout is already concrete; emission cannot reopen binders.
python3 - <<'PYENUM'
from pathlib import Path
source = Path('src/Backend/Llvm/Enums.pw').read_text()
layout = source.split('inout fn variantPayloadTy(', 1)[1].split('inout fn ', 1)[0]
for required in ['requireFinalDestruction(', 'variantFieldStarts', 'fieldBoxed', 'fieldTypes']:
    assert required in layout, f'payload layout lost its frozen contract: {required}'
for forbidden in ['groundUnderInst(', 'groundTypeRef(', 'enumVariantAt(', 'fieldLlvmTy(']:
    assert forbidden not in layout, f'payload layout reopens semantic fields: {forbidden}'
mid = Path('src/Backend/Llvm/Mid.pw').read_text()
assert 'c.cur.typeParams =' not in mid and 'c.cur.typeArgs =' not in mid, 'Mid LLVM emitter installs a semantic substitution environment'
PYENUM

# Layout registration consumes the same closed field graph as ownership.
# Neither registration nor sizing can enter frontend discovery/substitution.
python3 - <<'PYLAYOUT'
from pathlib import Path
layout = Path('src/Backend/Llvm/GenericStruct.pw').read_text()
sizing = Path('src/Backend/Llvm/Enums.pw').read_text().split('inout fn variantPayloadTy(', 1)[0]
assert 'c.arena.finalDestructions.count()' in layout
assert 'contract.structLayout' in layout
for source in (layout, sizing):
    for forbidden in ['c.scanType(', 'c.groundTypeRef(', 'c.cur.typeParams =', 'c.cur.typeArgs =', 'c.monoWork.genInsts', 'fieldWordsF(', 'fieldLlvmTy(']:
        assert forbidden not in source, f'layout reopens semantic collection: {forbidden}'
for required in ['contract.fieldTypes', 'contract.fieldBoxed']:
    assert required in layout and required in sizing
PYLAYOUT

# Physical type conversion cannot reopen a frontend substitution environment.
python3 - <<'PYPHYSICAL'
from pathlib import Path
source = Path('src/Backend/Llvm/GenericAny.pw').read_text().split('inout fn llvmTypeOfRef(', 1)[1].split('inout fn extendToI64(', 1)[0]
for required in ['requireFinalDestruction(', 'contract.underlying', 'contract.structLayout', 'contract.isOpaquePointer']:
    assert required in source
for forbidden in ['genericStructIndex(', 'genericEnumIndex(', 'recordStructIndex(', 'c.cur.typeParams', 'c.genMode']:
    assert forbidden not in source
query = Path('src/Backend/Llvm/GenericQuery.pw').read_text()
assert 'requireFinalDestruction(' in query
assert 'localStructIdxFor(' not in query and 'runtimeTypeRef(' not in query
PYPHYSICAL

# Async uses the same reachable body identities and frozen parameter contracts.
# Source declaration flags may select the supported async kind, never rebuild
# its parameter ABI or the copy/move handoff into an activation frame.
if rg -n 'while .*functionCount|funcParamAt|\.params\b|asyncParamTy|findBodyInstance' src/Backend/Llvm/Async.pw src/Backend/Llvm/MidAsync.pw; then
    echo "async emission must consume reachable bodies and frozen signatures" >&2
    exit 1
fi
for symbol in 'monoWork.bodyInstances' 'bodySignature' 'parameterPassings'; do
    if ! grep -F "$symbol" src/Backend/Llvm/Async.pw >/dev/null; then
        echo "async finalized entry contract is missing $symbol" >&2
        exit 1
    fi
done

# An unused async declaration is not an executable root, just like an unused
# synchronous function. This must hold in emitted LLVM, not just the scanner.
async_directory=$(mktemp -d "${TMPDIR:-/tmp}/plew-mid-async-roots.XXXXXX")
trap 'rm -f "$async_directory/input.ll" "$async_directory/diagnostics"; rmdir "$async_directory"' EXIT HUP INT TERM
"${PLEWC:-./plewc}" --require-mid tests/run/async_unreachable.pw >"$async_directory/input.ll" 2>"$async_directory/diagnostics" || {
    cat "$async_directory/diagnostics" >&2
    exit 1
}
if grep -E '^define.*(__af|@pf)' "$async_directory/input.ll"; then
    echo "unused async declaration reached LLVM emission" >&2
    exit 1
fi
echo "PASS async emission consumes only reachable body contracts" >&2

# Literal, aggregate and runtime-call results already carry their selected type.
if rg -n 'stringLlvmTy|arrayInstTy|structRegSlot|\bstrty\b|\barrayTy\b' src/Backend.pw src/Backend/Llvm; then
    echo "LLVM value construction must consume finalized result layouts" >&2
    exit 1
fi

# Physical ownership always selects the concrete instance's layout contract.
# Recursive ownership edges call per-instance witnesses; declaration-level
# recursion suppression can silently skip a nested generic instance.
if rg -n 'isGenericInst|structSlotForSidx|enumRegSlot|arcOnStack|arcPush|arcPop' src/Backend/Llvm; then
    echo "ownership emission must use finalized instance witnesses" >&2
    exit 1
fi
