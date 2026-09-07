#!/bin/sh
# A generic "operand" coverage row cannot direct Mid migration: each remaining
# source form needs a different Mid operation. Keep the closed diagnostic
# partition in lockstep with the frontend builder and LLVM coverage renderer.
set -eu
cd "$(dirname "$0")"

build=src/Mid/Build.pw
llvm=src/Backend/Llvm/Mid.pw

for reason in MakeWithoutAggregate UnloweredView UnloweredValueControl UnloweredReference UnloweredClosure UnloweredAwait IndexPlace UnexpectedOperand; do
    if ! rg -q "MidUnsupportedBuild\.$reason|    $reason" "$build"; then
        echo "operand diagnostic is missing $reason" >&2
        exit 1
    fi
    if ! rg -q "MidUnsupportedBuild\.$reason" "$llvm"; then
        echo "LLVM coverage detail is missing $reason" >&2
        exit 1
    fi
done

for shape in 'Expr\.Make' 'Expr\.ExtView' 'Expr\.MatchExpr' 'Expr\.Arrow' 'Expr\.Closure' 'Expr\.Await'; do
    if ! rg -q "$shape" "$build"; then
        echo "operand diagnostic does not classify $shape" >&2
        exit 1
    fi
done

if ! rg -q 'fn midUnsupportedOperandForExpr' "$build"; then
    echo "operand fallback is not centralized" >&2
    exit 1
fi

for label in make-without-aggregate unlowered-view unlowered-value-control unlowered-reference unlowered-closure unlowered-await index-place unexpected-operand; do
    if ! rg -q "text: \"$label\"" "$llvm"; then
        echo "operand coverage renderer is missing $label" >&2
        exit 1
    fi
done
