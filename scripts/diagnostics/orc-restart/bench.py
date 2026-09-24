#!/usr/bin/env python3
"""Measure repeated backend-only updates of real Plew-generated functions."""
import argparse
import hashlib
import json
import os
from pathlib import Path
import platform
import shlex
import statistics
import subprocess
import sys

sys.dont_write_bytecode = True
from check import ROOT, HERE, PIPELINE, digest, apply

def source_text(count, ownership):
    bodies = ['import @Std/Io with { print }']
    for index in range(count):
        marker = 7000000 + index
        if ownership:
            body = (f'mut val values: Array[I64] = [input, {marker}I64]\n'
                    'val snapshot = values\n'
                    'values[0] = 99I64\n'
                    'return snapshot[0] + snapshot[1]')
        else:
            body = f'return input + {marker}I64'
        bodies.append(f'fn update{index}(input: I64) -> I64 {{\n{body}\n}}')
    calls = '\n'.join(f'total += update{index}(input: input)' for index in range(count))
    bodies.append('fn probeTotal(input: I64) -> I64 {\nmut val total = 0I64\n' + calls + '\nreturn total\n}')
    bodies.append('fn main() { print(probeTotal(input: 42I64)) }')
    return '\n\n'.join(bodies) + '\n'

def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--out', type=Path, required=True)
    parser.add_argument('--runs', type=int, default=101)
    parser.add_argument('--llvm-prefix', type=Path, default=Path('/opt/homebrew/opt/llvm'))
    parser.add_argument('--compiler', type=Path, default=ROOT / 'plewc')
    args = parser.parse_args()
    if args.runs < 3:
        parser.error('--runs must be >= 3 (first update is reported separately)')
    out = args.out.resolve()
    out.mkdir(parents=True, exist_ok=False)
    prefix, compiler = args.llvm_prefix.resolve(), args.compiler.absolute()
    config, clang = prefix / 'bin/llvm-config', prefix / 'bin/clang'
    apply()
    watch = [sys.executable, '-B', str(ROOT / 'scripts/support/watch-command.py'), '--']
    inputs = [compiler, config, clang, prefix / 'lib/libLLVM.dylib',
              ROOT / 'Plew.toml', ROOT / 'Plew.lock',
              *sorted(HERE.glob('*.cpp')), *sorted(HERE.glob('*.hpp')), *sorted(HERE.glob('*.py')),
              *sorted((ROOT / 'std').rglob('*.pw')),
              *(ROOT / 'scripts/support' / name for name in
                ['process_watch.py', 'watch-command.py', 'llvm_link.py', 'clang_environment.py'])]
    hashes = {str(path): digest(path) for path in inputs}
    report = dict(status='running', scope='prepared IR backend updates; NOT source-to-restart latency',
                  llvm=subprocess.check_output([config, '--version'], text=True).strip(),
                  host=platform.platform(), machine=platform.machine(), inputs=hashes,
                  sdkroot=os.environ.get('SDKROOT'), commands=[], measurements=[])
    def save():
        (out / 'results.json').write_text(json.dumps(report, indent=2) + '\n')
    def run(label, command):
        print(f'[orc-probe] {label}', flush=True)
        item = dict(label=label, argv=list(map(str, command)))
        report['commands'].append(item)
        with (out / (label + '.stdout')).open('wb') as stdout, \
             (out / (label + '.stderr')).open('wb') as stderr:
            item['exit'] = subprocess.run(watch + item['argv'], cwd=ROOT,
                                         stdout=stdout, stderr=stderr).returncode
        save()
        if item['exit']:
            raise RuntimeError(f'{label}: exit {item["exit"]}; see {out / (label + ".stderr")}')
        return out / (label + '.stdout')
    try:
        flags = shlex.split(subprocess.check_output([config, '--cxxflags'], text=True))
        executable = out / 'orc-delta'
        run('build-delta', [prefix / 'bin/clang++', *flags, '-O2', HERE / 'delta.cpp',
                           '-L' + str(prefix / 'lib'), '-lLLVM', '-o', executable])
        runtime = out / 'runtime.c'
        runtime.write_bytes(run('runtime', [compiler, '--runtime']).read_bytes())
        dylib = out / 'runtime.dylib'
        run('build-runtime', [clang, '-w', '-O2', '-dynamiclib', runtime, '-o', dylib])
        for name, count, ownership in [('arithmetic-1', 1, False), ('arithmetic-10', 10, False),
                                       ('arithmetic-100', 100, False), ('cow-3', 3, True)]:
            source = out / (name + '.pw')
            source.write_text(source_text(count, ownership))
            ll = out / (name + '.ll')
            ll.write_bytes(run(name + '-compile', [compiler, source]).read_bytes())
            binary = out / (name + '-aot')
            run(name + '-link', [clang, '-w', '-O0', ll, runtime, '-o', binary])
            expected = str(count * (7000000 + 42) + count * (count - 1) // 2)
            if run(name + '-oracle', [binary]).read_text().strip() != expected:
                raise RuntimeError(name + ': generated source oracle mismatch')
            for mode in ['none', 'optimized']:
                pipeline = 'none' if mode == 'none' else PIPELINE + ',default<O2>'
                datafile = out / (name + '-' + mode + '.json')
                run(name + '-' + mode, [executable, ll, dylib, pipeline, count, args.runs, datafile])
                data = json.loads(datafile.read_text())
                samples = [json.loads(line) for line in Path(data['samples_path']).read_text().splitlines()]
                warm = samples[1:]
                timing = {}
                for key in ['parse_patch_ms', 'optimize_verify_ms', 'register_ms',
                            'codegen_link_lookup_ms', 'publish_first_call_ms', 'remove_check_ms', 'total_ms']:
                    values = sorted(row[key] for row in warm)
                    timing[key] = dict(median=statistics.median(values),
                                      p95=values[(95 * len(values) + 99) // 100 - 1])
                item = dict(case=name, mode=mode, functions=count, warm_samples=len(warm),
                            first_update_ms=samples[0]['total_ms'], timing=timing,
                            rss_first=warm[0]['rss_bytes'], rss_last=warm[-1]['rss_bytes'],
                            rss_min=min(row['rss_bytes'] for row in warm),
                            rss_max=max(row['rss_bytes'] for row in warm),
                            final_jit_allocations=data['final_jit_allocations'],
                            base_jit_allocations=data['base_jit_allocations'],
                            generated_jit_allocations=data['generated_jit_allocations'],
                            freed_jit_allocations=data['freed_jit_allocations'],
                            source_sha=digest(source), ir_sha=digest(ll),
                            result=str(datafile), runner_sha=digest(executable),
                            runtime_sha=digest(dylib))
                report['measurements'].append(item)
                save()
                print(f'{name}/{mode}: median={timing["total_ms"]["median"]:.3f} ms '
                      f'p95={timing["total_ms"]["p95"]:.3f} ms', flush=True)
        if any(digest(Path(path)) != value for path, value in hashes.items()):
            raise RuntimeError('verification inputs changed during run')
        report['status'] = 'passed'
        print(f'PASS: {len(report["measurements"])} backend update measurements; {out / "results.json"}')
    except Exception as error:
        report.update(status='failed', error=str(error))
        print(str(error), file=sys.stderr)
        return 1
    finally:
        save()
    return 0

if __name__ == '__main__':
    sys.exit(main())
