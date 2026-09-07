#!/bin/sh
# Macro-facing value APIs are adapters over the canonical SyntaxFile parser.
# They must not retain a second recursive-descent grammar merely because their
# result carrier is TopItemAst / ExprAst / BlockAst.  This structural gate is
# intentionally paired with runtime macro fixtures: equal output alone would
# not reveal a duplicate parser reintroduced behind the value boundary.
set -eu
cd "$(dirname "$0")"

source='../syntax/src/_.pw'

body_of() {
    awk -v signature="$1" '
        $0 ~ signature { inside = 1 }
        inside { print }
        inside && /^}$/ { exit }
    ' "$source"
}

check_adapter() {
    name="$1"
    signature="$2"
    body=$(body_of "$signature")
    if [ -z "$body" ]; then
        echo "missing macro value API: $name" >&2
        exit 1
    fi
    if ! printf '%s\n' "$body" | rg -q 'SyntaxFile'; then
        echo "$name does not construct the canonical SyntaxFile carrier" >&2
        exit 1
    fi
    if ! printf '%s\n' "$body" | rg -q 'materialize'; then
        echo "$name does not materialize from SyntaxFile" >&2
        exit 1
    fi
}

check_adapter parseItem '^export fn parseItem\\('
check_adapter parseProgramAst '^export fn parseProgramAst\\('
check_adapter parseExprAst '^export fn parseExprAst\\('
check_adapter parseBlockAst '^export fn parseBlockAst\\('

echo "PASS syntax-value-materializer" >&2
