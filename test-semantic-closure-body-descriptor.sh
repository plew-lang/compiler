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
# A closure body is lexically inside its enclosing generic body. Its synthetic
# body key distinguishes call rows, but it must retain the enclosing instance
# environment which grounds the captured type terms and body templates.
require 'self.cur.bodyEnvironment = savedBodyEnvironment' src/Codegen/Mono/Call.pw
# The Mid closure-body builder consumes the frozen descriptor; it must not
# reopen Expr.Closure. Environment-bound captures are usable inside a closure
# but are not lexical owners of the environment's value/cell.
require 'buildParametricMidClosureBody' src/Mid/Build.pw
require 'closure.parameters' src/Mid/Build.pw
require 'closure.captures' src/Mid/Build.pw
require 'closure.bodyBlock' src/Mid/Build.pw
require 'if body.locals[local].isBorrowed { }' src/Mid/Drop.pw

echo 'PASS semantic closure body descriptor' >&2
