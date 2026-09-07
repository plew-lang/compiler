#!/bin/sh
# Record one reproducible compiler-source codegen measurement.
#
# This is intentionally observational: it invokes the chosen existing carrier
# with --trace-phases, copies its stderr verbatim, and returns its exact exit
# status.  The timestamped trace is sufficient for P0's coarse phase split;
# it does not add compiler counters or change generated LLVM.

set -u

cd "$(dirname "$0")"

PLEWC="${PLEWC:?set PLEWC to an explicit existing carrier, for example ./plewc-match-owned-payload}"
SOURCE="${SOURCE:-src/_.pw}"
OUT_DIR="${OUT_DIR:-tmp/perf/$(date +%Y%m%d-%H%M%S)}"
LLVM_CONFIG="${LLVM_CONFIG:-llvm-config}"

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

{
    echo "carrier=$PLEWC"
    shasum -a 256 "$PLEWC"
    echo "source=$SOURCE"
    git rev-parse HEAD
    git -C ../syntax rev-parse HEAD
    uname -a
    "$LLVM_CONFIG" --version 2>&1 || true
    clang --version 2>&1 | sed -n '1p'
} >"$OUT_DIR/environment.txt"

export PLEW_PERF_CARRIER="$PLEWC"
export PLEW_PERF_SOURCE="$SOURCE"
export PLEW_PERF_OUT_DIR="$OUT_DIR"

python3 - <<'PY'
import os
import selectors
import subprocess
import sys
import time

carrier = os.environ["PLEW_PERF_CARRIER"]
source = os.environ["PLEW_PERF_SOURCE"]
out_dir = os.environ["PLEW_PERF_OUT_DIR"]
trace_path = os.path.join(out_dir, "trace.tsv")
stderr_path = os.path.join(out_dir, "stderr.log")
llvm_path = os.path.join(out_dir, "compiler.ll")

started = time.monotonic()
last_progress = started
last_event = "(no trace event yet)"
event_count = 0
with open(llvm_path, "wb") as llvm, open(trace_path, "w", encoding="utf-8") as trace, open(stderr_path, "wb") as stderr_log:
    trace.write("elapsed_seconds\tstderr\n")
    process = subprocess.Popen(
        [carrier, "--trace-phases", source],
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
