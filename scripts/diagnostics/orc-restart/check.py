#!/usr/bin/env python3
"""Manual ORC/AOT comparison; does not modify the compiler or seed."""
import argparse
import hashlib
import json
import os
from pathlib import Path
import platform
import shlex
import subprocess
import sys
import time

sys.dont_write_bytecode = True
ROOT = Path(__file__).resolve().parents[3]
HERE = Path(__file__).resolve().parent
sys.path.insert(0, str(ROOT / 'scripts/support'))
from llvm_link import PIPELINE
from clang_environment import apply

CASES = ['cow_struct', 'closure_capture_heap', 'closure_generic_instance_abi',
         'arc_deinit_order', 'generic_deinit', 'async_unique_frame',
         'async_enum_param_arc', 'mid_ffi_intrinsic_calls', 'ffi_extern_c',
         'runtime_intrinsic_process_smoke', 'mid_process_intrinsic_calls']

def digest(path):
    return hashlib.sha256(path.read_bytes()).hexdigest()

def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--out', type=Path, required=True)
    parser.add_argument('--compiler', type=Path, default=ROOT / 'plewc')
    parser.add_argument('--llvm-prefix', type=Path,
                        default=Path('/opt/homebrew/opt/llvm'))
    args = parser.parse_args()
    out = args.out.resolve()
    out.mkdir(parents=True, exist_ok=False)
    compiler = args.compiler.absolute()
    prefix = args.llvm_prefix.resolve()
    config = prefix / 'bin/llvm-config'
    clang = prefix / 'bin/clang'
    apply()
    env = dict(os.environ)
    watch = [sys.executable, '-B', str(ROOT / 'scripts/support/watch-command.py'), '--']
    fixtures = ROOT / 'tests/fixtures/run'
    sources = [fixtures / (name + '.pw') for name in CASES]
    inputs = [compiler, config, clang, prefix / 'lib/libLLVM.dylib',
              ROOT / 'Plew.toml', ROOT / 'Plew.lock', *HERE.glob('*.cpp'), *HERE.glob('*.hpp'),
              *HERE.glob('*.py'), *sources,
              *(source.with_suffix('.out') for source in sources),
              *(source.with_suffix('.c') for source in sources if source.with_suffix('.c').exists()),
              *sorted((ROOT / 'std').rglob('*.pw')),
              ROOT / 'scripts/support/llvm_link.py',
              ROOT / 'scripts/support/process_watch.py',
              ROOT / 'scripts/support/watch-command.py',
              ROOT / 'scripts/support/clang_environment.py']
    hashes = {str(path): digest(path) for path in inputs}
    report = dict(status='running', host=platform.platform(), machine=platform.machine(),
                  compiler=str(compiler), inputs=hashes, cases=[], commands=[],
                  pipeline=PIPELINE, sdkroot=env.get('SDKROOT'),
                  llvm=subprocess.check_output([config, '--version'], text=True).strip())
    def save():
        (out / 'results.json').write_text(json.dumps(report, indent=2) + '\n')
    def run(label, command):
        print(f'[orc-probe] {label}', flush=True)
        report['commands'].append(dict(label=label, argv=list(map(str, command))))
        with (out / (label + '.stdout')).open('wb') as stdout, \
             (out / (label + '.stderr')).open('wb') as stderr:
            status = subprocess.run(watch + list(map(str, command)), cwd=ROOT,
                                    env=env, stdout=stdout, stderr=stderr).returncode
        report['commands'][-1]['exit'] = status
        save()
        if status:
            raise RuntimeError(f'{label}: exit {status}; see {out / (label + ".stderr")}')
        return out / (label + '.stdout')
    try:
        cxxflags = shlex.split(subprocess.check_output([config, '--cxxflags'], text=True))
        runner = out / 'orc-runner'
        run('build-runner', [prefix / 'bin/clang++', *cxxflags, '-O2',
            HERE / 'runner.cpp', '-L' + str(prefix / 'lib'), '-lLLVM', '-o', runner])
        runtime = run('runtime', [compiler, '--runtime'])
        runtime_c = out / 'runtime.c'
        runtime_c.write_bytes(runtime.read_bytes())
        for name, source in zip(CASES, sources):
            llvm = run(name + '-compile', [compiler, source])
            ll = out / (name + '.ll')
            ll.write_bytes(llvm.read_bytes())
            companions = [source.with_suffix('.c')] if source.with_suffix('.c').exists() else []
            dylib = out / (name + '.dylib')
            run(name + '-runtime', [clang, '-O2', '-w', '-dynamiclib', runtime_c,
                                   *companions, '-o', dylib])
            expected = source.with_suffix('.out').read_bytes()
            exact = source.with_suffix('.out.exact').exists()
            normalize = (lambda data: data) if exact else (lambda data: data.rstrip(b'\n'))
            for mode in ['none', 'optimized']:
                pipeline = 'none' if mode == 'none' else PIPELINE + ',default<O2>'
                optimized = ll
                if mode != 'none':
                    optimized = out / (name + '.optimized.ll')
                    run(name + '-opt', [prefix / 'bin/opt', '-passes=' + PIPELINE,
                                       '-S', ll, '-o', optimized])
                binary = out / (name + '-' + mode)
                run(name + '-' + mode + '-link', [clang, '-w',
                    '-O0' if mode == 'none' else '-O2', optimized, runtime_c,
                    *companions, '-o', binary])
                aot = run(name + '-' + mode + '-aot', [binary]).read_bytes()
                jit = run(name + '-' + mode + '-jit', [runner, ll, dylib, pipeline]).read_bytes()
                if normalize(aot) != normalize(expected) or normalize(jit) != normalize(expected):
                    raise RuntimeError(f'{name}/{mode}: AOT/JIT/golden mismatch')
                report['cases'].append(dict(case=name, mode=mode, passed=True,
                    source_sha=digest(source), ir_sha=digest(ll), output_sha=hashlib.sha256(jit).hexdigest()))
                save()
        if any(digest(Path(path)) != value for path, value in hashes.items()):
            raise RuntimeError('verification inputs changed during run')
        report['status'] = 'passed'
        print(f'PASS: {len(report["cases"])} ORC/AOT/golden comparisons; {out / "results.json"}')
    except Exception as error:
        report['status'] = 'failed'
        report['error'] = str(error)
        print(str(error), file=sys.stderr)
        return 1
    finally:
        save()
    return 0

if __name__ == '__main__':
    sys.exit(main())
