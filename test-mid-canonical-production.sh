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
canonical='MidCanonicalBody instantiateCanonicalMidBody elaborateCanonicalMidAccesses elaborateCanonicalMidDrops verifyCanonicalMidBody midCanonicalLlvmPreflight genLlvmCanonicalMidBody'

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
for needle in 'abiParameterCount: U64 = 0U64' 'abiParameterCount: abiParameterCount'; do
    if ! grep -F "$needle" src/Backend/Llvm/Mid.pw >/dev/null; then
        echo "canonical Mid ABI contract is missing $needle" >&2
        exit 1
    fi
done
if ! grep -F 'abiParameterCount: midAbiParameterCount' src/Backend/Llvm/Any.pw >/dev/null; then
    echo "ordinary Mid emission does not carry its preflight ABI count" >&2
    exit 1
fi

# Module initialization is also executable Plew code.  It has no user Func
# row, so keep its synthetic body explicit rather than letting Entry.pw grow a
# second AST-to-LLVM path that happens to run before `main`.
global_canonical='declareGlobalStorage buildParametricMidGlobalInit instantiateCanonicalMidBody elaborateCanonicalMidAccesses elaborateCanonicalMidDrops verifyCanonicalMidBody midCanonicalLlvmPreflight genLlvmCanonicalMidBody'
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
