#!/bin/sh
# The compiler-facing extern parser is a direct SyntaxFile builder.  This is a
# separate gate from the final parseProgramSyntaxInto switch: an extern block
# must not quietly reintroduce ExternAst/SigAst/DirectiveAst as a local bridge.
set -eu
cd "$(dirname "$0")"

source='../syntax/src/_.pw'
body=$(sed -n '/^inout fn parseSyntaxExternDecl(/,/^}$/p' "$source")

if [ -z "$body" ]; then
    echo "missing direct extern parser" >&2
    exit 1
fi

for legacy in 'ExternAst' 'SigAst' 'DirectiveAst' 'parseExternDecl' 'parseDirectiveAst'; do
    if printf '%s\n' "$body" | rg -q "\b$legacy\b"; then
        echo "direct extern parser still uses value-AST bridge: $legacy" >&2
        exit 1
    fi
done

for direct in 'parseSyntaxSig' 'parseSyntaxTypeParams' 'parseSyntaxDirective' 'pushSliceSlice' 'externs.append'; do
    if ! printf '%s\n' "$body" | rg -q "$direct"; then
        echo "direct extern parser is missing direct arena operation: $direct" >&2
        exit 1
    fi
done

echo "PASS syntax-direct-extern-builder" >&2
