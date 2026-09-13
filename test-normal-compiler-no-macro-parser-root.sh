#!/bin/sh
# The normal compiler consumes SyntaxFile directly.  Macro value-parser entry
# points remain public for `plew gen`, but importing them into either compiler
# layer makes them roots for self-hosted generic code generation even when no
# normal compiler path calls them.
set -eu
cd "$(dirname "$0")"

for source in src/Frontend.pw src/Backend.pw; do
    imports=$(rg '^import @Plew/Syntax with \{' "$source")
    for endpoint in parseItem parseProgramAst parseExprAst parseBlockAst; do
        if printf '%s\n' "$imports" | rg -q "\\b$endpoint\\b"; then
            echo "normal compiler imports macro value-parser endpoint $endpoint from $source" >&2
            exit 1
        fi
    done
done

# Imports are only the surface symptom.  Final callable construction used to
# seed every non-generic function in every loaded module, which made an unused
# macro parser executable despite no normal compiler call reaching it.  The
# executable root set is globals plus main (or the synthesized gen harness);
# calls then expand it to a closed body-instance graph.
finalizer='src/Codegen/Mono/Call.pw'
if rg -q 'if f\.typeParams\.count\(\) == 0U64 && !\(self\.methodRecvIsTrait\(f: f\)\)' "$finalizer"; then
    echo "final callable construction still roots every non-generic body" >&2
    exit 1
fi
if ! rg -q 'mut val isEntry: Bool = self\.nameIsMain\(f: f\)' "$finalizer"; then
    echo "final callable construction has no explicit executable entry root" >&2
    exit 1
fi
# Ordinary async state machines remain roots until their backend is fully
# demand-driven. Generation must not root unrelated application async bodies.
if ! rg -Fq 'if isEntry || (f.isAsync && !self.genMode) {' "$finalizer"; then
    echo "final callable construction does not isolate generation from application async roots" >&2
    exit 1
fi

if rg -q 'while gi2 < self\.monoWork\.genInsts\.count\(\)' "$finalizer"; then
    echo "final callable construction still roots methods from every discovered generic layout" >&2
    exit 1
fi

# Layout demand is not executable reachability at the backend boundary either.
# Declaring a method from every genInst recreates unfinalized bodies after Mono
# has closed the graph, so this must iterate the same BodyInstance table.
methods='src/Backend/Llvm/GenMethods.pw'
if ! rg -q 'while bodyIndex < c\.arena\.bodyInstanceCount\(\)' "$methods"; then
    echo "generic-method declaration is not driven by final body instances" >&2
    exit 1
fi
if rg -q 'while gi < c\.monoWork\.genInsts\.count\(\)' "$methods"; then
    echo "generic-method declaration still treats every generic layout as executable" >&2
    exit 1
fi
if ! rg -q 'f\.hasRecv && !\(f\.isExtern\) && !\(f\.isProvided\) && !\(c\.methodRecvIsTrait' "$methods"; then
    echo "ordinary method table accepts proof-carrying provided bodies" >&2
    exit 1
fi

# Once finalization closes semantic bodies, LLVM is a consumer.  Re-interning a
# body here fabricates a descriptor key with no recorded calls; broad roots only
# hide that violation and must not be reintroduced as a repair.
if rg -q 'c\.enterBodyInstance\(' src/Backend/Llvm; then
    echo "LLVM backend creates a BodyInstance after finalization" >&2
    exit 1
fi
if ! rg -q 'LLVM attempted to emit a body outside the finalized callable closure' src/Backend/Llvm/Any.pw; then
    echo "LLVM backend does not reject missing frozen body identities" >&2
    exit 1
fi

# Free functions must obey the same rule.  The older `FnInst` table duplicated
# `(Func,args)` beside the frozen body identity and allowed LLVM to reopen a
# generic body after finalization; that is exactly the carrier which hid the
# macro-parser reachability pollution.
free_fns='src/Backend/Llvm/ProvidedFns.pw'
if ! rg -q 'while bodyIndex < c\.monoWork\.bodyInstances\.count\(\)' "$free_fns"; then
    echo "free-function declaration is not driven by the finalized body closure" >&2
    exit 1
fi
if rg -q 'monoWork\.fnInsts' "$free_fns"; then
    echo "free-function declaration still consumes provisional FnInst work" >&2
    exit 1
fi
if ! rg -q 'ensureFinalGenFnBody' src/Backend/Llvm/CallGeneric.pw; then
    echo "free-function calls do not consume frozen body identities" >&2
    exit 1
fi
if rg -q 'ensureFnInst' src/Backend/Llvm; then
    echo "LLVM still has a source-shaped free-function instance fallback" >&2
    exit 1
fi
if rg -q 'finalize-callables:function-instance' "$finalizer"; then
    echo "finalization still expands a second FnInst executable worklist" >&2
    exit 1
fi

closures='src/Backend/Llvm/Closures.pw'
if rg -q 'while fi < c\.arena\.funcs\.count\(\)' "$closures"; then
    echo "closure collection still scans every function declaration" >&2
    exit 1
fi
if ! rg -q 'while bodyI < c\.monoWork\.bodyInstances\.count\(\)' "$closures"; then
    echo "closure collection is not driven by final body instances" >&2
    exit 1
fi

echo "PASS normal-compiler-no-macro-parser-root" >&2
