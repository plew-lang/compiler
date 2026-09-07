#!/bin/sh
# A mutable closure capture has two independent destructors: replacing its
# logical value must not release the shared cell, while lexical cleanup must.
# Keep that distinction in Mid rather than reconstructing it in LLVM.
set -eu
cd "$(dirname "$0")"

require() {
    if ! grep -F "$1" "$2" >/dev/null; then
        echo "FAIL missing $1 in $2" >&2
        exit 1
    fi
}

require 'InitializeCaptureCell(destination: MidPlace, value: MidRvalue)' src/Mid/Ir.pw
require 'ReleaseCaptureCell(place: MidPlace)' src/Mid/Ir.pw
require 'MidStatement.InitializeCaptureCell' src/Mid/Build.pw
require 'MidStatement.ReleaseCaptureCell' src/Mid/Drop.pw
require 'InitializeCaptureCell' src/Backend/Llvm/Mid.pw
require 'ReleaseCaptureCell' src/Backend/Llvm/Mid.pw

echo 'PASS Mid capture-cell ownership boundary' >&2
