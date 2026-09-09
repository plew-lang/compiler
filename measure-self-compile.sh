#!/bin/sh
# Record one reproducible compiler-source codegen measurement.
#
# This is intentionally observational: it invokes the chosen existing carrier
# with --trace-phases, copies its stderr verbatim, and returns its exact exit
# status.  The timestamped trace is sufficient for P0's coarse phase split;
# it does not add compiler counters or change generated LLVM.  Set
# TRACE_CODEGEN=1 only to map generated LLVM symbols back to semantic bodies;
# that diagnostic run is not a wall-time performance sample.

set -u

cd "$(dirname "$0")"

PLEWC="${PLEWC:?set PLEWC to an explicit existing carrier, for example ./plewc-match-owned-payload}"
SOURCE="${SOURCE:-src/_.pw}"
OUT_DIR="${OUT_DIR:-tmp/perf/$(date +%Y%m%d-%H%M%S)}"
LLVM_CONFIG="${LLVM_CONFIG:-llvm-config}"
TRACE_CODEGEN="${TRACE_CODEGEN:-0}"

if [ ! -x "$PLEWC" ]; then
    echo "measure-self-compile: carrier is not executable: $PLEWC" >&2
    exit 64
fi
if [ ! -f "$SOURCE" ]; then
    echo "measure-self-compile: source does not exist: $SOURCE" >&2
    exit 64
fi
if [ -e "$OUT_DIR" ]; then
    echo "measure-self-compile: output directory already exists: $OUT_DIR" >&2
    exit 64
fi

mkdir -p "$OUT_DIR"

# A dirty compiler worktree is a legitimate development input, but a Git
# revision and a patch hash are not a content-addressed source snapshot.
# Fingerprint every source file passed to the carrier's source root and the
# package-resolution inputs, and retain a per-file manifest for diagnosis.
SOURCE_TREE_SHA256="$(python3 - "$SOURCE" "$OUT_DIR/source-inputs.sha256" <<'PY'
import hashlib
import sys
from pathlib import Path

source = Path(sys.argv[1]).resolve()
manifest = Path(sys.argv[2])
cwd = Path.cwd().resolve()
source_root = source.parent

inputs = {path.resolve() for path in source_root.rglob('*') if path.is_file()}
for name in ('Plew.toml', 'Plew.lock'):
    candidate = cwd / name
    if candidate.is_file():
        inputs.add(candidate.resolve())

def label(path: Path) -> str:
    try:
        return str(path.relative_to(cwd))
    except ValueError:
        return str(path)

ordered_inputs = sorted(inputs, key=label)
total = hashlib.sha256()
rows = []
for path in ordered_inputs:
    data = path.read_bytes()
    input_label = label(path)
    rows.append(f'{hashlib.sha256(data).hexdigest()}  {input_label}\n')
    total.update(input_label.encode())
    total.update(b'\0')
    total.update(data)
    total.update(b'\0')

manifest.write_text(''.join(rows), encoding='utf-8')
print(total.hexdigest())
PY
)"

{
    echo "carrier=$PLEWC"
    shasum -a 256 "$PLEWC"
    echo "source=$SOURCE"
    shasum -a 256 "$SOURCE"
    echo "source_tree_sha256=$SOURCE_TREE_SHA256"
    echo "source_inputs_sha256_manifest=source-inputs.sha256"
    echo "compiler_head=$(git rev-parse HEAD)"
    echo "compiler_worktree=$(git diff --no-ext-diff --binary HEAD | shasum -a 256 | awk '{print $1}')"
    echo "syntax_head=$(git -C ../syntax rev-parse HEAD)"
    echo "syntax_worktree=$(git -C ../syntax diff --no-ext-diff --binary HEAD | shasum -a 256 | awk '{print $1}')"
    echo "syntax_status_begin"
    git -C ../syntax status --short
    echo "syntax_status_end"
    uname -a
    "$LLVM_CONFIG" --version 2>&1 || true
    clang --version 2>&1 | sed -n '1p'
} >"$OUT_DIR/environment.txt"

export PLEW_PERF_CARRIER="$PLEWC"
export PLEW_PERF_SOURCE="$SOURCE"
export PLEW_PERF_OUT_DIR="$OUT_DIR"
export PLEW_PERF_TRACE_CODEGEN="$TRACE_CODEGEN"

python3 - <<'PY'
import os
import selectors
import subprocess
import sys
import time

carrier = os.environ["PLEW_PERF_CARRIER"]
source = os.environ["PLEW_PERF_SOURCE"]
out_dir = os.environ["PLEW_PERF_OUT_DIR"]
trace_codegen = os.environ["PLEW_PERF_TRACE_CODEGEN"] == "1"
trace_path = os.path.join(out_dir, "trace.tsv")
stderr_path = os.path.join(out_dir, "stderr.log")
llvm_path = os.path.join(out_dir, "compiler.ll")

started = time.monotonic()
last_progress = started
last_event = "(no trace event yet)"
event_count = 0
with open(llvm_path, "wb") as llvm, open(trace_path, "w", encoding="utf-8") as trace, open(stderr_path, "wb") as stderr_log:
    trace.write("elapsed_seconds\tstderr\n")
    command = [carrier, "--trace-phases"]
    if trace_codegen:
        command.append("--trace-codegen")
    command.append(source)
    process = subprocess.Popen(
        command,
        stdout=llvm,
        stderr=subprocess.PIPE,
        bufsize=0,
    )
    assert process.stderr is not None
    selector = selectors.DefaultSelector()
    selector.register(process.stderr, selectors.EVENT_READ)
    while selector.get_map():
        ready = selector.select(timeout=5)
        if not ready:
            now = time.monotonic()
            if now - last_progress >= 60:
                process.terminate()
                print(f"[perf] no compiler phase progress for 60s; terminating at last={last_event}", file=sys.stderr)
                break
            continue
        raw = process.stderr.readline()
        if not raw:
            selector.unregister(process.stderr)
            continue
        elapsed = time.monotonic() - started
        stderr_log.write(raw)
        text = raw.decode("utf-8", errors="replace")
        if text.startswith("[trace-phase] "):
            trace.write(f"{elapsed:.6f}\t{text}")
            trace.flush()
            last_event = text.rstrip()
            last_progress = time.monotonic()
            event_count += 1
            # Phase transitions are immediately visible.  Repeated worklist rows
            # are emitted in batches; the displayed counter still proves progress.
            if "=" not in text or event_count % 256 == 0:
                print(f"[perf] t={elapsed:.3f}s {last_event}", file=sys.stderr)
                last_visible = time.monotonic()
        else:
            # Codegen identity tracing is intentionally dense (one line per
            # emitted instance).  Preserve it in stderr.log, while phase and
            # counter rows remain the terminal's bounded progress contract.
            if not trace_codegen:
                sys.stderr.write(text)
                sys.stderr.flush()
    status = process.wait()
elapsed = time.monotonic() - started

with open(os.path.join(out_dir, "summary.txt"), "w", encoding="utf-8") as summary:
    summary.write(f"wall_seconds={elapsed:.6f}\n")
    summary.write(f"exit_status={status}\n")

print(f"[perf] wall_seconds={elapsed:.6f} exit_status={status} artifacts={out_dir}", file=sys.stderr)
raise SystemExit(status)
PY
