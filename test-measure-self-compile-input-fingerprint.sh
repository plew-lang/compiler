#!/bin/sh
# A Git revision alone does not identify a dirty compiler worktree.  A
# performance artifact must retain the exact compiler source inputs it used.
set -eu
cd "$(dirname "$0")"

tmp=$(mktemp -d "$(pwd)/tmp/plew-measure-fingerprint.XXXXXX")
trap 'exit_code=$?; rm -rf "$tmp"; exit "$exit_code"' EXIT
mkdir -p "$tmp/src"
printf 'placeholder\n' > "$tmp/src/_.pw"
printf '[package]\nname = "fixture"\n' > "$tmp/Plew.toml"
printf 'lock\n' > "$tmp/Plew.lock"
printf '#!/bin/sh\nprintf "%s\\n" "[trace-phase] fixture:start" >&2\nprintf "fixture llvm\\n"\n' > "$tmp/carrier"
chmod +x "$tmp/carrier"

PLEWC="$tmp/carrier" SOURCE="$tmp/src/_.pw" OUT_DIR="$tmp/out" ./measure-self-compile.sh >/dev/null

grep -E '^source_tree_sha256=[0-9a-f]{64}$' "$tmp/out/environment.txt" >/dev/null
grep -F 'source_inputs_sha256_manifest=source-inputs.sha256' "$tmp/out/environment.txt" >/dev/null
grep -F 'src/_.pw' "$tmp/out/source-inputs.sha256" >/dev/null
grep -F 'Plew.toml' "$tmp/out/source-inputs.sha256" >/dev/null
grep -F 'Plew.lock' "$tmp/out/source-inputs.sha256" >/dev/null
grep -E '^compiler_head=[0-9a-f]{40}$' "$tmp/out/environment.txt" >/dev/null
grep -E '^compiler_worktree=[0-9a-f]{64}$' "$tmp/out/environment.txt" >/dev/null
grep -E '^syntax_head=[0-9a-f]{40}$' "$tmp/out/environment.txt" >/dev/null
grep -E '^syntax_worktree=[0-9a-f]{64}$' "$tmp/out/environment.txt" >/dev/null

# Sampling must be opt-in, write a stack artifact beside the trace, and keep
# the normal carrier output/exit status intact.  A tiny stand-in avoids making
# this shell-level contract depend on Xcode's `sample` tool.
printf '#!/bin/sh\nprintf "%s\\n" "$*" >> "$PLEW_TEST_SAMPLE_LOG"\nprintf sample > "$4"\n' > "$tmp/sample"
chmod +x "$tmp/sample"
printf '#!/usr/bin/env python3\nimport sys, time\nsys.stderr.write("[trace-phase] fixture:start\\n")\nsys.stderr.flush()\ntime.sleep(1)\nsys.stderr.write("[trace-phase] fixture:done\\n")\nsys.stderr.flush()\nsys.stdout.write("fixture llvm\\n")\n' > "$tmp/slow-carrier"
chmod +x "$tmp/slow-carrier"
PLEW_TEST_SAMPLE_LOG="$tmp/sample.log" \
PLEW_PERF_SAMPLE_COMMAND="$tmp/sample" \
PLEW_PERF_SAMPLE_INTERVAL_SECONDS=0.5 \
PLEW_PERF_SAMPLE_DURATION_SECONDS=1 \
PLEWC="$tmp/slow-carrier" SOURCE="$tmp/src/_.pw" OUT_DIR="$tmp/profile" ./measure-self-compile.sh >/dev/null
test -s "$tmp/profile/cpu-sample-001.txt"
grep -F 'fixture llvm' "$tmp/profile/compiler.ll" >/dev/null
grep -F $'sample\telapsed_seconds\tlast_phase\tpath' "$tmp/profile/cpu-samples.tsv" >/dev/null
grep -F 'fixture:start' "$tmp/profile/cpu-samples.tsv" >/dev/null

echo 'PASS measure-self-compile-input-fingerprint'
