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
canonical='MidCanonicalBody instantiateCanonicalMidBody elaborateCanonicalMidAccesses elaborateCanonicalMidDrops verifyCanonicalMidBody midVerifiedLlvmPreflight genLlvmPreparedMidBody'

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
global_canonical='declareGlobalStorage buildParametricMidGlobalInit instantiateCanonicalMidBody elaborateCanonicalMidAccesses elaborateCanonicalMidDrops verifyCanonicalMidBody midVerifiedLlvmPreflight genLlvmPreparedMidBody'
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
