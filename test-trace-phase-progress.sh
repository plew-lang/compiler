#!/bin/sh
# `--trace-phases` is a bounded observability contract, not a per-node dump.
set -eu
cd "$(dirname "$0")"

require_progress() {
    file="$1"
    label="$2"
    receiver="$3"
    if ! grep -F "tracePhaseProgress(c: inout $receiver, label: \"$label\"" "$file" >/dev/null; then
        echo "missing bounded trace progress for $label" >&2
        exit 1
    fi
}

require_progress src/Codegen/Resolve/Record.pw 'semantic-expression-record:body' self
require_progress src/Backend.pw 'backend:drain:provided-emitting' c
require_progress src/Backend.pw 'backend:drain:generic-method-emitting' c
require_progress src/Backend.pw 'backend:drain:generic-function-emitting' c
require_progress src/Backend/Llvm/GenMethods.pw 'backend:generic-method-emitting' c

methods=src/Backend/Llvm/GenMethods.pw
grep -F 'eprint(text: " body=")' "$methods" >/dev/null
grep -F 'eprint(text: " ownArgs=")' "$methods" >/dev/null

if grep -F '"[trace-phase] semantic-expression-record:body index="' src/Codegen/Resolve/Record.pw >/dev/null; then
    echo 'unbounded semantic-expression trace remains' >&2
    exit 1
fi
if grep -F '"[trace-phase] finalize-callables:body-target="' src/Codegen/Mono/Call.pw >/dev/null; then
    echo 'unbounded final-body diagnostic trace remains' >&2
    exit 1
fi
if grep -F 'tracePhase(c: inout self, label: "finalize-callables:body-' src/Codegen/Mono/Call.pw >/dev/null; then
    echo 'per-body finalization trace remains' >&2
    exit 1
fi

echo 'PASS trace-phase-progress'
