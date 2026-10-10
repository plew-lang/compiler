#!/bin/sh
# Canonical Mid must consume the frozen conversion proof arena directly.  This
# is an architectural gate: a fresh WIP compiler cannot yet execute every
# ordinary-function fixture, but the production reader must never thaw the
# proof back into the draft ValueConversionProof representation.
set -eu
cd "$(dirname "$0")/../../.."

source=src/Backend/Llvm/Mid.pw
canonical=$(sed -n '/fn midCanonicalPlaceTy/,$p' "$source")
conversion=$(sed -n '/fn midCanonicalConversionProofSupported/,/fn midCanonicalPlaceLlvmSupported/p' "$source")
aggregate=$(sed -n '/fn midCanonicalEmitAggregateElement/,/fn midCanonicalEmitAggregate/p' "$source")

for symbol in midCanonicalConversionProofSupported midCanonicalEmitValueConversion midCanonicalEmitBorrowedConversion midCanonicalEmitArrayRepack midCanonicalEmitEnumRepack; do
    if ! printf '%s\n' "$canonical" | rg -q "\b$symbol\b"; then
        echo "canonical conversion reader is missing $symbol" >&2
        exit 1
    fi
done

if ! printf '%s\n' "$canonical" | rg -q 'node\.tag == 2U64'; then
    echo "canonical conversion reader does not admit existential boxing" >&2
    exit 1
fi
if ! printf '%s\n' "$canonical" | rg -q 'node\.tag == 3U64'; then
    echo "canonical conversion reader does not admit array repacking" >&2
    exit 1
fi
if ! printf '%s\n' "$canonical" | rg -q 'node\.tag == 4U64'; then
    echo "canonical conversion reader does not admit enum repacking" >&2
    exit 1
fi
if ! printf '%s\n' "$canonical" | rg -q 'c\.arena\.hasStaticConformanceProof\(id: node\.staticProof\)'; then
    echo "canonical conversion reader does not reject a missing frozen proof" >&2
    exit 1
fi
if ! printf '%s\n' "$canonical" | rg -q '\bboxIntoAny\b'; then
    echo "canonical conversion emitter does not materialize existential boxes" >&2
    exit 1
fi
if printf '%s\n' "$conversion" | rg -q '\bthawValueConversionProof\b'; then
    echo "canonical conversion reader thawed a draft conversion proof" >&2
    exit 1
fi
if ! printf '%s\n' "$aggregate" | rg -q '\bmidCanonicalEmitValueConversion\b'; then
    echo "canonical aggregate elements do not use the frozen conversion emitter" >&2
    exit 1
fi

# The shared reader must reject both invalid IDs and the frozen Missing row.
python3 - <<'PYPROOF'
from pathlib import Path
source = Path("src/Ir/StaticProofs.pw").read_text()
begin = source.index("fn hasStaticConformanceProof(")
end = source.index("\n    }", begin)
reader = source[begin:end]
for required in ["id != 0U64", "id <= self.staticProofs.count()", "self.staticProofs[id - 1U64].tag != 0U64"]:
    if required not in reader:
        raise SystemExit(f"frozen proof reader lacks missing-proof rejection: {required}")
PYPROOF
