#!/bin/sh
# An assign fallback must preserve why its target is unavailable as a Mid
# place.  Index storage is separately classified: a found Index projection is
# SemanticAccess/writeback work, while an Index whose base is not a place is a
# source-target problem.  This structural gate protects that distinction until
# a fresh candidate can collect the corresponding coverage rows.
set -eu
cd "$(dirname "$0")"

build=src/Mid/Build.pw
llvm=src/Backend/Llvm/Mid.pw

for reason in IdentifierNotLocal FieldBaseNotPlace IndexBaseNotPlace OtherNotPlace IndexProjection; do
    if ! rg -q "MidUnsupportedAssign\.$reason|    $reason" "$build"; then
        echo "assign diagnostic is missing $reason" >&2
        exit 1
    fi
    if ! rg -q "MidUnsupportedAssign\.$reason" "$llvm"; then
        echo "LLVM coverage detail is missing $reason" >&2
        exit 1
    fi
done

for shape in 'Expr\.Ident' 'Expr\.Field' 'Expr\.Index'; do
    if ! rg -q "$shape" "$build"; then
        echo "assign diagnostic does not classify $shape" >&2
        exit 1
    fi
done

if ! rg -q 'if !physicalFieldPath' "$build" || ! rg -q 'IndexProjection' "$build"; then
    echo "assign lowering no longer keeps found index projections out of raw stores" >&2
    exit 1
fi

if ! rg -q 'detail >= 20U64 && detail < 25U64' "$llvm"; then
    echo "assign coverage range does not include every closed reason" >&2
    exit 1
fi

for label in identifier-not-local field-base-not-place index-base-not-place other-not-place index-projection; do
    if ! rg -q "text: \"$label\"" "$llvm"; then
        echo "assign coverage renderer is missing $label" >&2
        exit 1
    fi
done
