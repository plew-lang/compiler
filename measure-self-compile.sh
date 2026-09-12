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
# Optional CPU sampling is deliberately a diagnostic run, not a performance
# run.  `sample` pauses neither the compiler's semantics nor its output, but
# sampling itself perturbs wall time; keep it opt-in and retain the stacks next
# to the phase trace that says what the compiler was doing.
SAMPLE_INTERVAL_SECONDS="${PLEW_PERF_SAMPLE_INTERVAL_SECONDS:-0}"
SAMPLE_DURATION_SECONDS="${PLEW_PERF_SAMPLE_DURATION_SECONDS:-3}"
SAMPLE_COMMAND="${PLEW_PERF_SAMPLE_COMMAND:-sample}"

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
export PLEW_PERF_SAMPLE_INTERVAL_SECONDS="$SAMPLE_INTERVAL_SECONDS"
export PLEW_PERF_SAMPLE_DURATION_SECONDS="$SAMPLE_DURATION_SECONDS"
export PLEW_PERF_SAMPLE_COMMAND="$SAMPLE_COMMAND"

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
sample_interval_text = os.environ["PLEW_PERF_SAMPLE_INTERVAL_SECONDS"]
sample_duration_text = os.environ["PLEW_PERF_SAMPLE_DURATION_SECONDS"]
sample_command = os.environ["PLEW_PERF_SAMPLE_COMMAND"]

try:
    sample_interval = float(sample_interval_text)
    sample_duration = float(sample_duration_text)
except ValueError as error:
    raise SystemExit(f"measure-self-compile: sample interval and duration must be numbers: {error}")
if sample_interval < 0:
    raise SystemExit("measure-self-compile: PLEW_PERF_SAMPLE_INTERVAL_SECONDS must be zero or positive")
if sample_interval > 0 and sample_duration <= 0:
    raise SystemExit("measure-self-compile: PLEW_PERF_SAMPLE_DURATION_SECONDS must be positive when sampling")
trace_path = os.path.join(out_dir, "trace.tsv")
stderr_path = os.path.join(out_dir, "stderr.log")
llvm_path = os.path.join(out_dir, "compiler.ll")
cpu_samples_path = os.path.join(out_dir, "cpu-samples.tsv")

started = time.monotonic()
last_progress = started
last_event = "(no trace event yet)"
event_count = 0
sample_number = 0
next_sample = started + sample_interval if sample_interval > 0 else None
with open(llvm_path, "wb") as llvm, open(trace_path, "w", encoding="utf-8") as trace, open(stderr_path, "wb") as stderr_log, open(cpu_samples_path, "w", encoding="utf-8") as cpu_samples:
    trace.write("elapsed_seconds\tstderr\n")
    cpu_samples.write("sample\telapsed_seconds\tlast_phase\tpath\n")
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
    def record_line(raw):
        global last_event, last_progress, event_count
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

    def stop_child(child):
        if child.poll() is None:
            child.terminate()
            try:
                child.wait(timeout=3)
            except subprocess.TimeoutExpired:
                child.kill()
        return child.wait()

    selector = selectors.DefaultSelector()
    os.set_blocking(process.stderr.fileno(), False)
    selector.register(process.stderr, selectors.EVENT_READ)
    pending_bytes = b""
    sampler = None
    sampler_started = None
    sampler_timed_out = False
    sample_status = open(os.path.join(out_dir, "cpu-sample-status.tsv"), "w", encoding="utf-8")
    sample_status.write("sample\texit_status\treason\n")
    try:
        while selector.get_map() or process.poll() is None:
            now = time.monotonic()
            if sampler is not None:
                result = sampler.poll()
                if result is None and not sampler_timed_out and now - sampler_started > sample_duration + 5:
                    sampler.kill()
                    sampler_timed_out = True
                reason = "timeout" if sampler_timed_out else "completed"
                if result is not None:
                    sample_status.write(f"{sample_number}\t{result}\t{reason}\n")
                    sample_status.flush()
                    sampler = None
                    next_sample = time.monotonic() + sample_interval
            # Schedule independently of stderr readiness. A continuously verbose
            # compiler must neither starve sampling nor block behind it.
            if sampler is None and next_sample is not None and now >= next_sample:
                if process.poll() is None and last_event != "(no trace event yet)":
                    sample_number += 1
                    sample_path = os.path.join(out_dir, f"cpu-sample-{sample_number:03d}.txt")
                    sampler = subprocess.Popen(
                        [sample_command, str(process.pid), str(sample_duration), "-file", sample_path],
                        stdout=subprocess.DEVNULL, stderr=subprocess.DEVNULL,
                    )
                    sampler_started = time.monotonic()
                    sampler_timed_out = False
                    cpu_samples.write(f"{sample_number}\t{now - started:.6f}\t{last_event}\t{os.path.basename(sample_path)}\n")
                    cpu_samples.flush()
                    print(f"[perf] cpu-sample={sample_number} t={now - started:.3f}s last={last_event}", file=sys.stderr)
                    next_sample = None
                else:
                    next_sample = now + sample_interval
            if now - last_progress >= 60 and process.poll() is None:
                print(f"[perf] no compiler phase progress for 60s; terminating at last={last_event}", file=sys.stderr)
                stop_child(process)
            timeout = 0.1 if sampler is not None else 1
            if next_sample is not None:
                timeout = max(0, min(timeout, next_sample - time.monotonic()))
            if not selector.get_map():
                try:
                    process.wait(timeout=timeout)
                except subprocess.TimeoutExpired:
                    pass
                continue
            for key, _ in selector.select(timeout=timeout):
                chunk = os.read(key.fd, 65536)
                if not chunk:
                    selector.unregister(process.stderr)
                    if pending_bytes:
                        record_line(pending_bytes)
                        pending_bytes = b""
                    continue
                pending_bytes += chunk
                lines = pending_bytes.split(b"\n")
                pending_bytes = lines.pop()
                for line in lines:
                    record_line(line + b"\n")
        status = process.wait()
        compiler_finished = time.monotonic()
    finally:
        if sampler is not None:
            result = stop_child(sampler)
            sample_status.write(f"{sample_number}\t{result}\tcompiler-ended\n")
        sample_status.close()
        selector.close()
        process.stderr.close()
        if process.poll() is None:
            stop_child(process)

elapsed = compiler_finished - started

with open(os.path.join(out_dir, "summary.txt"), "w", encoding="utf-8") as summary:
    summary.write(f"wall_seconds={elapsed:.6f}\n")
    summary.write(f"exit_status={status}\n")

print(f"[perf] wall_seconds={elapsed:.6f} exit_status={status} artifacts={out_dir}", file=sys.stderr)
raise SystemExit(status)
PY
