#!/bin/sh
# A closure body is a normal semantic body with an environment ABI, not an
# LLVM-side re-parse of Expr.Closure. Keep every body-navigation and ABI fact
# needed by the Mid builder in the frontend-owned descriptor.
set -eu
cd "$(dirname "$0")"

require() {
    if ! grep -F "$1" "$2" >/dev/null; then
        echo "FAIL missing $1 in $2" >&2
        exit 1
    fi
}

require 'export struct SemanticClosureParameter' src/Ir.pw
require 'pub val bindingTarget: U64 = 0U64' src/Ir.pw
require 'pub val bodyBlock: U64 = 0U64' src/Ir.pw
require 'pub val parameters: Array[SemanticClosureParameter] = []' src/Ir.pw
require 'pub val hasReturn: Bool = false' src/Ir.pw
require 'pub val returnTypeTerm: U64 = 0U64' src/Ir.pw
require 'Expr.Closure' src/Codegen/Mono/Call.pw
require 'SemanticClosureParameter bindingTarget=parameter.nameStart' src/Codegen/Mono/Call.pw
require 'parameters=frozenParameters' src/Codegen/Mono/Call.pw
require 'bodyBlock=body' src/Codegen/Mono/Call.pw

echo 'PASS semantic closure body descriptor' >&2
