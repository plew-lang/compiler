#!/bin/sh
# A mutable closure capture has two independent destructors: replacing its
# logical value must not release the shared cell, while lexical cleanup must.
# Keep that distinction in Mid rather than reconstructing it in LLVM.
set -eu
cd "$(dirname "$0")/../../.."

require() {
    if ! grep -F "$1" "$2" >/dev/null; then
        echo "FAIL missing $1 in $2" >&2
        exit 1
    fi
}

require 'InitializeCaptureCell(destination: MidPlace, value: MidRvalue)' src/Mid/Ir.pw
require 'ReleaseCaptureCell(place: MidPlace)' src/Mid/Ir.pw
require 'MidStatement.InitializeCaptureCell' src/Mid/Build.pw
# Canonical storage uses tags, not the draft enum at the LLVM boundary.
python3 - <<'PYCELL'
from pathlib import Path
import re
drop = Path('src/Mid/Drop.pw').read_text()
# Cleanup must release the cell itself; allow destination materialization and
# formatting within the branch rather than pinning a source line verbatim.
cell_cleanup = re.findall(r'else if declaration\.isCaptureCell\s*\{([^{}]*)\}', drop)
assert cell_cleanup, 'capture-cell cleanup branch'
for cleanup in cell_cleanup:
    assert re.search(r'arena\.statements\.append\(<MidStatementNode\s+tag=10U64\s+destination=place\s*/>\)', cleanup), 'capture-cell release operation'
    assert 'tag=3U64' not in cleanup, 'logical drop cannot replace cell release'
ir = Path('src/Mid/Ir.pw').read_text()
llvm = Path('src/Backend/Llvm/Mid.pw').read_text()
for operation, tag in [('InitializeCaptureCell', 9), ('ReleaseCaptureCell', 10)]:
    assert re.search(r'MidStatement\.' + operation + r'[^\n]+MidStatementNode tag=' + str(tag) + r'U64', ir), operation
emit = llvm.split('inout fn midCanonicalEmitStatement(', 1)[1].split('\n    inout fn ', 1)[0]
initialize = emit.split('if statement.tag == 9U64 {', 1)[1].split('} else {', 1)[0]
assert 'self.rawbufAlloc(' in initialize
assert 'llvmStore(self.b, cell, self.midCanonicalLocalPtr(' in initialize
assert 'llvmStore(self.b, value, cell)' in initialize
release = emit.split('if statement.tag == 10U64 {', 1)[1].split('return <Result.Ok value=true />', 1)[0]
assert '!c.mid.locals[body.locals.start + place.local].isCaptureCell' in release
assert 'return <Result.Ok value=false />' in release
assert 'self.emitCellRelease(' in release
PYCELL

echo 'PASS Mid capture-cell ownership boundary' >&2
