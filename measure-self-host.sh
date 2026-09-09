#!/bin/sh
# Build a fresh compiler with an existing carrier, then measure that fresh
# compiler compiling the same source.  The measured wall time is deliberately
# the second generation: timing the carrier only measures build latency.
set -eu

cd "$(dirname "$0")"

CARRIER="${CARRIER:?set CARRIER to a known-good compiler executable}"
SOURCE="${SOURCE:-src/_.pw}"
OUT_DIR="${OUT_DIR:-tmp/perf/$(date +%Y%m%d-%H%M%S)-self-host}"
RUNS="${RUNS:-2}"
LLVM_CONFIG="${LLVM_CONFIG:-llvm-config}"

[ -x "$CARRIER" ] || { echo "measure-self-host: carrier is not executable: $CARRIER" >&2; exit 64; }
[ -f "$SOURCE" ] || { echo "measure-self-host: source does not exist: $SOURCE" >&2; exit 64; }
[ ! -e "$OUT_DIR" ] || { echo "measure-self-host: output directory already exists: $OUT_DIR" >&2; exit 64; }
case "$RUNS" in '' | *[!0-9]* | 0) echo "measure-self-host: RUNS must be a positive integer" >&2; exit 64 ;; esac

if ! command -v "$LLVM_CONFIG" >/dev/null 2>&1; then
    if [ -x /opt/homebrew/opt/llvm/bin/llvm-config ]; then
        LLVM_CONFIG=/opt/homebrew/opt/llvm/bin/llvm-config
    elif [ -x /opt/homebrew/opt/llvm@22/bin/llvm-config ]; then
        LLVM_CONFIG=/opt/homebrew/opt/llvm@22/bin/llvm-config
    else
        echo "measure-self-host: llvm-config not found (set LLVM_CONFIG)" >&2
        exit 64
    fi
fi

llvm_libdir="${LLVM_LIBDIR:-$($LLVM_CONFIG --libdir)}"
llvm_config_path="$(command -v "$LLVM_CONFIG")"
llvm_prefix="$(dirname "$(dirname "$llvm_config_path")")"
if [ -f "$llvm_prefix/lib/libLLVM.dylib" ]; then
    llvm_libdir="$llvm_prefix/lib"
fi

mkdir -p "$OUT_DIR"
build_dir="$OUT_DIR/candidate-build"
candidate_dir="$OUT_DIR/candidate"
candidate="$candidate_dir/plewc"
summary="$OUT_DIR/summary.txt"
build_status=not-run
self_statuses=""
outputs_match=not-run

write_summary() {
    {
        echo "schema=self-host-measure-v1"
        echo "carrier=$CARRIER"
        shasum -a 256 "$CARRIER"
        echo "source=$SOURCE"
        echo "candidate_build_exit_status=$build_status"
        echo "self_compile_runs=$RUNS"
        echo "self_compile_exit_statuses=$self_statuses"
        echo "self_compile_outputs_match=$outputs_match"
        if [ -x "$candidate" ]; then
            echo "candidate_sha256=$(shasum -a 256 "$candidate" | awk '{print $1}')"
        fi
    } >"$summary"
}

link_compiler() {
    ll="$1"
    runtime="$2"
    output="$3"
    mkdir -p "$(dirname "$output")"
    clang -w -O2 "$ll" "$runtime" -L"$llvm_libdir" -lLLVM -o "$output"
    ln -s "$(pwd)/std" "$(dirname "$output")/std"
}

echo "[self-host 1/3] carrier compiles source -> candidate LLVM" >&2
if PLEWC="$CARRIER" SOURCE="$SOURCE" OUT_DIR="$build_dir" LLVM_CONFIG="$LLVM_CONFIG" ./measure-self-compile.sh; then
    build_status=0
else
    build_status=$?
    write_summary
    exit "$build_status"
fi

echo "[self-host 2/3] link fresh candidate" >&2
if "$CARRIER" --runtime >"$build_dir/runtime.c"; then
    :
else
    build_status=$?
    write_summary
    exit "$build_status"
fi
if link_compiler "$build_dir/compiler.ll" "$build_dir/runtime.c" "$candidate"; then
    :
else
    build_status=$?
    write_summary
    exit "$build_status"
fi

echo "[self-host 3/3] fresh candidate self-compiles source ($RUNS run(s))" >&2
run=1
reference_ll=""
while [ "$run" -le "$RUNS" ]; do
    run_dir="$OUT_DIR/self-compile-$run"
    if PLEWC="$candidate" SOURCE="$SOURCE" OUT_DIR="$run_dir" LLVM_CONFIG="$LLVM_CONFIG" ./measure-self-compile.sh; then
        status=0
    else
        status=$?
    fi
    if [ -z "$self_statuses" ]; then self_statuses="$status"; else self_statuses="$self_statuses,$status"; fi
    if [ "$status" -ne 0 ]; then
        outputs_match=not-comparable
        write_summary
        exit "$status"
    fi

    if "$candidate" --runtime >"$run_dir/runtime.c"; then
        :
    else
        status=$?
        self_statuses="$self_statuses,runtime=$status"
        outputs_match=not-comparable
        write_summary
        exit "$status"
    fi
    if ! link_compiler "$run_dir/compiler.ll" "$run_dir/runtime.c" "$run_dir/next/plewc"; then
        status=$?
        self_statuses="$self_statuses,link=$status"
        outputs_match=not-comparable
        write_summary
        exit "$status"
    fi

    if [ -z "$reference_ll" ]; then
        reference_ll="$run_dir/compiler.ll"
        outputs_match=yes
    elif ! cmp -s "$reference_ll" "$run_dir/compiler.ll"; then
        outputs_match=no
    fi
    run=$((run + 1))
done

python3 - "$OUT_DIR" "$RUNS" >>"$summary" <<'PY'
import pathlib
import statistics
import sys

root = pathlib.Path(sys.argv[1])
runs = int(sys.argv[2])
times = []
for index in range(1, runs + 1):
    fields = dict(
        line.strip().split("=", 1)
        for line in (root / f"self-compile-{index}" / "summary.txt").read_text().splitlines()
        if "=" in line
    )
    times.append(float(fields["wall_seconds"]))

print("self_compile_wall_seconds=" + ",".join(f"{value:.6f}" for value in times))
print(f"self_compile_min_seconds={min(times):.6f}")
print(f"self_compile_median_seconds={statistics.median(times):.6f}")
print(f"self_compile_max_seconds={max(times):.6f}")
PY

if [ "$outputs_match" != yes ]; then
    write_summary
    echo "measure-self-host: fresh candidate output is not deterministic across runs" >&2
    exit 65
fi

# write_summary owns the header; append the calculated timing rows after it.
timings="$(tail -n 4 "$summary")"
write_summary
printf '%s\n' "$timings" >>"$summary"
echo "[self-host] candidate self-compile completed: $(grep '^self_compile_median_seconds=' "$summary") artifacts=$OUT_DIR" >&2
