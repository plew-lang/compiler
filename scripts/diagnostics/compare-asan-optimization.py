#!/usr/bin/env python3
"""Diagnostic only: compare ASan optimization pipelines; never promote a carrier.

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
sys.path.insert(0, str(ROOT / 'scripts/support'))
from llvm_link import PIPELINE


def sha(path):
    return hashlib.sha256(path.read_bytes()).hexdigest()


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('output', type=Path)
    parser.add_argument('--rounds', type=int, default=3)
    parser.add_argument('--prepared', type=Path, help='reuse verified compiler IR/binaries from an earlier diagnostic')
    parser.add_argument('--prepared-evidence', type=Path, help='original meta gate result.json required for reuse')
    parser.add_argument('--preopt', action='store_true', help='compare O1 against shared prepasses before ASan, also linked O1')
    parser.add_argument('--self-compile-check', action='store_true', help='also compare complete compiler-source LLVM output')
    args = parser.parse_args()
    if args.rounds < 2:
        parser.error('at least two alternating rounds are required')
    if bool(args.prepared) != bool(args.prepared_evidence):
        parser.error('--prepared and --prepared-evidence must be supplied together')
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
        if args.prepared_evidence:
            evidence = json.loads(args.prepared_evidence.read_text())
            if evidence.get('inputs_unchanged') is not True:
                raise RuntimeError('prepared build has no unchanged-input evidence')
            for path, expected in evidence['inputs'].items():
                # Diagnostic logic may be corrected between attempts. Compiler,
                # sources, dependencies, toolchain and watchdog must not change.
                if Path(path).resolve() != Path(__file__).resolve() and sha(Path(path)) != expected:
                    raise RuntimeError(f'prepared build input changed: {path}')
            for key, value in [('LLVM_PREFIX', str(llvm)), ('PLEWC', carrier)]:
                if Path(evidence['env'][key]).resolve() != Path(value).resolve():
                    raise RuntimeError(f'prepared build setting changed: {key}')
        _, runtime, _ = run('runtime', [carrier, '--runtime'])
        runtime.rename(out / 'runtime.c')
        _, raw, _ = run('compiler-ir', [carrier, '--trace-phases', '--asan', 'src/_.pw'])
        raw.rename(out / 'compiler.ll')
        ir = out / 'compiler.inst.ll'
        if args.prepared:
            prepared = args.prepared.absolute()
            previous = json.loads((prepared / 'summary.json').read_text())
            for name in ('runtime.c', 'compiler.ll'):
                if sha(out / name) != sha(prepared / name):
                    raise RuntimeError(f'prepared {name} does not match current carrier output')
            ir = prepared / 'compiler.inst.ll'
            if sha(ir) != previous['instrumented_ir_sha256']:
                raise RuntimeError('prepared instrumented LLVM changed')
            binaries = {level: Path(row['path']) for level, row in previous['binaries'].items()}
            for level, binary in binaries.items():
                if sha(binary) != previous['binaries'][level]['sha256']:
                    raise RuntimeError(f'prepared {level} binary changed')
            if set(binaries) != {'O1', 'O2'}:
                raise RuntimeError('prepared comparison requires both O1 and O2')
            state['prepared'] = str(prepared)
        else:
            run('instrument', [opt, '-debug-pass-manager', '-passes=asan', '-S', out / 'compiler.ll', '-o', ir])
        if '__asan_report_' not in ir.read_text():
            raise RuntimeError('compiler LLVM has no ASan access checks')
        state['instrumented_ir_sha256'] = sha(ir)
        candidate_irs = {level: ir for level in binaries}
        if args.preopt:
            binaries = {'O1': binaries['O1'], 'preopt-O1': ROOT / ('plewc-' + out.name + '-preopt-O1')}
            preopt = out / 'compiler.preopt.ll'
            candidate = out / 'compiler.preopt.inst.ll'
            run('preopt', [opt, '-debug-pass-manager', '-passes=' + PIPELINE, '-S', out / 'compiler.ll', '-o', preopt])
            run('preopt-instrument', [opt, '-debug-pass-manager', '-passes=asan', '-S', preopt, '-o', candidate])
            if '__asan_report_' not in candidate.read_text():
                raise RuntimeError('preoptimized compiler LLVM has no ASan access checks')
            candidate_irs = {'O1': ir, 'preopt-O1': candidate}
            state['preopt_pipeline'] = PIPELINE
            state['preopt_instrumented_ir_sha256'] = sha(candidate)
        for level, binary in binaries.items():
            if args.prepared and level != 'preopt-O1':
                continue
            if binary.exists():
                raise RuntimeError(f'refusing to overwrite {binary}')
            run('link-' + level, [clang, '-Xclang', '-fdebug-pass-manager', '-mllvm', '-debug-pass=Executions',
                                 '-O1' if level == 'preopt-O1' else '-' + level, '-fno-omit-frame-pointer', '-fsanitize=address', '-w',
                                 candidate_irs[level], out / 'runtime.c', llvm / 'lib/libLLVM.dylib', '-o', binary])
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
            control_ir = out / 'control.inst.ll'
            if level == 'preopt-O1':
                run('control-preopt', [opt, '-passes=' + PIPELINE, '-S', out / 'control.ll', '-o', out / 'control.preopt.ll'])
                control_ir = out / 'control.preopt.inst.ll'
                run('control-preopt-instrument', [opt, '-passes=asan', '-S', out / 'control.preopt.ll', '-o', control_ir])
            run('control-link-' + level, [clang, '-O1' if level == 'preopt-O1' else '-' + level, '-fno-omit-frame-pointer', '-fsanitize=address',
                                          control_ir, '-o', binary])
            for case, marker in [('clean', None), ('uaf', 'heap-use-after-free'), ('overflow', 'heap-buffer-overflow'),
                                 ('double', 'double-free'), ('leak', 'LeakSanitizer: detected memory leaks')]:
                _, _, log = run('control-' + level + '-' + case, [binary, case],
                                expected=0 if marker is None else 1, leaks=True, quiet=True)
                text = log.read_text()
                if (marker and marker not in text) or (marker is None and 'Sanitizer' in text):
                    raise RuntimeError(f'control detection mismatch: {log}')

        cases = ['tests/fixtures/run/mid_body_type_results.pw', 'tests/fixtures/run/mid_copy_contract_verify.pw',
                 'tests/fixtures/run/access_call_result_nested_index.pw', 'tests/fixtures/reject/unknown_identifier_generic.pw']
        expected_hash = {}
        # Compare candidates linked against the SAME LLVM. The adopted carrier
        # may use another LLVM whose intrinsic attributes print differently.
        for iteration in range(args.rounds):
            for level in (tuple(binaries) if iteration % 2 == 0 else tuple(reversed(binaries))):
                for case in cases:
                    row, output, log = run(f'round{iteration}-{level}-{Path(case).stem}',
                                           [binaries[level], '--trace-phases', case],
                                           expected=1 if '/reject/' in case else 0)
                    expected_hash.setdefault(case, sha(output))
                    if sha(output) != expected_hash[case] or 'ERROR: AddressSanitizer' in log.read_text():
                        raise RuntimeError(f'output or sanitizer mismatch: {log}')
                    if '/reject/' in case and 'plewc: error:' not in log.read_text():
                        raise RuntimeError(f'missing rejection diagnostic: {log}')
                    state['measurements'].append(dict(level=level, case=case, round=iteration, seconds=row['seconds']))
        state['medians'] = {case: {level: statistics.median(r['seconds'] for r in state['measurements']
                            if r['case'] == case and r['level'] == level) for level in binaries} for case in cases}
        if args.self_compile_check:
            outputs = []
            for level, binary in binaries.items():
                _, output, log = run('self-compile-' + level, [binary, '--trace-phases', 'src/_.pw'])
                if 'ERROR: AddressSanitizer' in log.read_text():
                    raise RuntimeError(f'self-compile sanitizer failure: {log}')
                outputs.append(sha(output))
            if len(set(outputs)) != 1:
                raise RuntimeError('self-compile LLVM mismatch')
            state['self_compile_output_sha256'] = outputs[0]
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
