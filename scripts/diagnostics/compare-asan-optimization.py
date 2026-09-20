#!/usr/bin/env python3
"""Diagnostic only: compare post-instrumentation O1/O2; never promote a carrier.

Run from the compiler root under the meta diagnostic gate for input snapshots.
Every subprocess uses the existing 60-second progress watchdog. Artifacts and
summary are retained; this subset does not replace the full ASan gate.
"""
import argparse
import hashlib
import json
import os
from pathlib import Path
import statistics
import subprocess
import sys
import time

sys.dont_write_bytecode = True
ROOT = Path(__file__).resolve().parents[2]
TRACE = ROOT / 'scripts/support/trace-command.py'


def sha(path):
    return hashlib.sha256(path.read_bytes()).hexdigest()


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('output', type=Path)
    parser.add_argument('--rounds', type=int, default=3)
    args = parser.parse_args()
    if args.rounds < 2:
        parser.error('at least two alternating rounds are required')
    os.chdir(ROOT)
    out = args.output.absolute()
    out.mkdir(parents=True, exist_ok=False)
    llvm = Path(os.environ.get('LLVM_PREFIX', '/opt/homebrew/opt/llvm@22'))
    clang, opt = str(llvm / 'bin/clang'), str(llvm / 'bin/opt')
    carrier = os.environ.get('PLEWC', str(ROOT / 'plewc'))
    env = dict(os.environ, ASAN_OPTIONS='detect_leaks=0:abort_on_error=0', LSAN_OPTIONS='')
    state = dict(status='running', scope='diagnostic subset; no full-gate claim',
                 rounds=args.rounds, commands=[], measurements=[])
    binaries = {level: ROOT / ('plewc-' + out.name + '-' + level) for level in ('O1', 'O2')}

    def save():
        (out / 'summary.json').write_text(json.dumps(state, indent=2) + '\n')

    def run(label, command, expected=0, leaks=False, quiet=False):
        log, stdout = out / (label + '.stderr'), out / (label + '.stdout')
        started = time.monotonic()
        with stdout.open('wb') as output, (out / (label + '.watch.log')).open('wb') as watch:
            result = subprocess.run([sys.executable, '-B', str(TRACE), str(log), '--', *map(str, command)],
                                    stdout=output, stderr=watch if quiet else None,
                                    env=dict(env, ASAN_OPTIONS='detect_leaks=1:abort_on_error=0' if leaks else env['ASAN_OPTIONS']))
        row = dict(label=label, command=list(map(str, command)), exit_code=result.returncode,
                   seconds=time.monotonic() - started, stdout_sha256=sha(stdout))
        state['commands'].append(row)
        save()
        if result.returncode != expected:
            raise RuntimeError(f'{label}: expected exit {expected}, got {result.returncode}; see {log}')
        print(f'[asan-compare] completed={len(state["commands"])} {label}', flush=True)
        return row, stdout, log

    try:
        _, runtime, _ = run('runtime', [carrier, '--runtime'])
        runtime.rename(out / 'runtime.c')
        _, raw, _ = run('compiler-ir', [carrier, '--trace-phases', '--asan', 'src/_.pw'])
        raw.rename(out / 'compiler.ll')
        ir = out / 'compiler.inst.ll'
        run('instrument', [opt, '-debug-pass-manager', '-passes=asan', '-S', out / 'compiler.ll', '-o', ir])
        if '__asan_report_' not in ir.read_text():
            raise RuntimeError('compiler LLVM has no ASan access checks')
        state['instrumented_ir_sha256'] = sha(ir)
        for level, binary in binaries.items():
            if binary.exists():
                raise RuntimeError(f'refusing to overwrite {binary}')
            run('link-' + level, [clang, '-Xclang', '-fdebug-pass-manager', '-mllvm', '-debug-pass=Executions',
                                 '-' + level, '-fno-omit-frame-pointer', '-fsanitize=address', '-w',
                                 ir, out / 'runtime.c', llvm / 'lib/libLLVM.dylib', '-o', binary])
        state['binaries'] = {level: dict(path=str(p), sha256=sha(p)) for level, p in binaries.items()}

        # Volatile accesses keep the deliberate defects observable after optimization.
        # These are detection smoke tests, not a proof of identical detection power.
        control = out / 'control.c'
        control.write_text('''#include <stdlib.h>
static void *volatile lost;
__attribute__((noinline)) static void leak(void) { lost = malloc(123); lost = 0; }
int main(int argc, char **argv) {
  volatile char *p = malloc(8);
  switch (argv[1][0]) {
  case 'u': free((void *)p); return p[0];
  case 'o': p[8] = 1; break;
  case 'd': free((void *)p); free((void *)p); return 0;
  case 'l': free((void *)p); leak(); return 0;
  default: p[0] = 1;
  }
  free((void *)p); return 0;
}
''')
        run('control-ir', [clang, '-O0', '-Xclang', '-disable-O0-optnone', '-Xclang', '-disable-llvm-passes',
                           '-fsanitize=address', '-S', '-emit-llvm', control, '-o', out / 'control.ll'])
        run('control-instrument', [opt, '-passes=asan', '-S', out / 'control.ll', '-o', out / 'control.inst.ll'])
        for level in binaries:
            binary = out / ('control-' + level)
            run('control-link-' + level, [clang, '-' + level, '-fno-omit-frame-pointer', '-fsanitize=address',
                                          out / 'control.inst.ll', '-o', binary])
            for case, marker in [('clean', None), ('uaf', 'heap-use-after-free'), ('overflow', 'heap-buffer-overflow'),
                                 ('double', 'double-free'), ('leak', 'LeakSanitizer: detected memory leaks')]:
                _, _, log = run('control-' + level + '-' + case, [binary, case],
                                expected=0 if marker is None else 1, leaks=True, quiet=True)
                text = log.read_text()
                if (marker and marker not in text) or (marker is None and 'Sanitizer' in text):
                    raise RuntimeError(f'control detection mismatch: {log}')

        cases = ['tests/run/mid_body_type_results.pw', 'tests/run/mid_copy_contract_verify.pw',
                 'tests/run/access_call_result_nested_index.pw', 'tests/reject/unknown_identifier_generic.pw']
        expected_hash = {}
        for case in cases:
            _, output, _ = run('reference-' + Path(case).stem, [carrier, '--trace-phases', case],
                               expected=1 if '/reject/' in case else 0)
            expected_hash[case] = sha(output)
        for iteration in range(args.rounds):
            for level in (('O1', 'O2') if iteration % 2 == 0 else ('O2', 'O1')):
                for case in cases:
                    row, output, log = run(f'round{iteration}-{level}-{Path(case).stem}',
                                           [binaries[level], '--trace-phases', case],
                                           expected=1 if '/reject/' in case else 0)
                    if sha(output) != expected_hash[case] or 'ERROR: AddressSanitizer' in log.read_text():
                        raise RuntimeError(f'output or sanitizer mismatch: {log}')
                    if '/reject/' in case and 'plewc: error:' not in log.read_text():
                        raise RuntimeError(f'missing rejection diagnostic: {log}')
                    state['measurements'].append(dict(level=level, case=case, round=iteration, seconds=row['seconds']))
        state['medians'] = {case: {level: statistics.median(r['seconds'] for r in state['measurements']
                            if r['case'] == case and r['level'] == level) for level in binaries} for case in cases}
        state['status'] = 'passed'
        print('ASan optimization comparison: PASS', flush=True)
    except BaseException as error:
        state['status'] = 'failed'
        state['error'] = str(error)
        raise
    finally:
        save()
        # Keep candidate binaries as diagnostic artifacts; never overwrite plewc.


if __name__ == '__main__':
    main()
