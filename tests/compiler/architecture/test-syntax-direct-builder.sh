#!/bin/sh
# The compiler-facing parser must construct SyntaxFile rows directly.  Macro
# APIs may still construct TopItemAst values, but parseProgramSyntaxInto is the
# compiler entry and may not route through the value-AST freezer.
set -eu
cd "$(dirname "$0")/../../.."

syntax_root=$(python3 -B scripts/support/dependency_inputs.py --git https://github.com/plew-lang/syntax.git)
source="$syntax_root/src/_.pw"
body=$(awk '
    /^pub fn parseProgramSyntaxInto\(/ { inside = 1 }
    inside { print }
    inside && /^}$/ { exit }
' "$source")

if [ -z "$body" ]; then
    echo "missing parseProgramSyntaxInto body" >&2
    exit 1
fi

for legacy in 'parseTopItemsAt' 'TopItemAst' 'freezeTopItem'; do
    if printf '%s\n' "$body" | rg -q "\b$legacy\b"; then
        echo "compiler syntax parser still reaches legacy value-AST path: $legacy" >&2
        exit 1
    fi
done

echo "PASS syntax-direct-builder" >&2
