#!/bin/sh
# An impl is the largest compiler-facing declaration carrier.  All member
# forms must share a direct SyntaxFile builder; a partial direct impl parser
# that falls back to MemberAst/ImplAst for factories or assoc values would keep
# the value-ownership hot path alive.
set -eu
cd "$(dirname "$0")"

source='../syntax/src/_.pw'

for required in parseSyntaxMethodAfterFn parseSyntaxAssocValMember parseSyntaxImplDecl; do
    if ! rg -q "^inout fn $required\(" "$source"; then
        echo "missing direct impl builder: $required" >&2
        exit 1
    fi
done

body=$(sed -n '/^inout fn parseSyntaxImplDecl(/,/^}$/p' "$source")
if [ -z "$body" ]; then
    echo "missing direct impl parser body" >&2
    exit 1
fi

for legacy in 'ImplAst' 'MemberAst' 'parseImplDecl' 'parseMethodAfterFn' 'parseAssocValMember' 'parseBlockAst' 'parseTypeParamList'; do
    if printf '%s\n' "$body" | rg -q "\b$legacy\b"; then
        echo "direct impl parser still uses value-AST bridge: $legacy" >&2
        exit 1
    fi
done

for direct in 'parseSyntaxMethodAfterFn' 'parseSyntaxAssocValMember' 'parseSyntaxType' 'parseSyntaxWhere' 'pushMemberIdSlice' 'impls.append'; do
    if ! printf '%s\n' "$body" | rg -q "$direct"; then
        echo "direct impl parser is missing direct arena operation: $direct" >&2
        exit 1
    fi
done

echo "PASS syntax-direct-impl-builder" >&2
