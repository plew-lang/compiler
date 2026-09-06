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
