#!/bin/sh
# Normal compiler loading owns one SyntaxFile and must not retain an unused
# parseFile -> Array[TopItemAst] fallback beside parseFileSyntax.  Macro value
# APIs remain in @Plew/Syntax, but they are not a loader escape hatch.
set -eu
cd "$(dirname "$0")"

source='src/Loader.pw'
if rg -q 'inout fn parseFile\(' "$source"; then
    echo "compiler loader still exposes value-AST parseFile fallback" >&2
    exit 1
fi
if rg -q 'parseProgramAst\(' "$source"; then
    echo "compiler loader still calls value-AST program parser" >&2
    exit 1
fi
if rg -q '\bTopItemAst\b' "$source"; then
    echo "compiler loader still retains a value-AST traversal" >&2
    exit 1
fi

echo "PASS loader-no-value-parser-fallback" >&2
