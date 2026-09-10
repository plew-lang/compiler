#!/usr/bin/env python3
"""Bounded self-host fixed point and repeatable performance measurement."""
from datetime import datetime
import hashlib
import json
import os
from pathlib import Path
import shutil
import statistics
import subprocess
import sys


def digest(path):
    return hashlib.sha256(path.read_bytes()).hexdigest()


def fields(path):
    return dict(line.split('=', 1) for line in path.read_text().splitlines() if '=' in line)


def main():
    carrier = Path(os.environ['CARRIER']).absolute()
    source = Path(os.environ.get('SOURCE', 'src/_.pw')).absolute()
    output = Path(os.environ.get('OUT_DIR', datetime.now().strftime('tmp/perf/%Y%m%d-%H%M%S-self-host'))).absolute()
    runs = int(os.environ.get('RUNS', '3'))
    if runs < 3:
        raise ValueError('RUNS must be at least 3')
    if not carrier.is_file() or not os.access(carrier, os.X_OK) or not source.is_file():
        raise ValueError('CARRIER must be executable and SOURCE must exist')
    if os.environ.get('TRACE_CODEGEN', '0') != '0' or float(os.environ.get('PLEW_PERF_SAMPLE_INTERVAL_SECONDS', '0')) != 0:
        raise ValueError('diagnostic instrumentation is not a performance measurement')
    config = shutil.which(os.environ.get('LLVM_CONFIG', 'llvm-config'))
    if not config:
        config = next((p for p in ['/opt/homebrew/opt/llvm/bin/llvm-config', '/opt/homebrew/opt/llvm@22/bin/llvm-config'] if Path(p).is_file()), None)
    if not config:
        raise ValueError('llvm-config unavailable')
    clang = shutil.which('clang')
    if not clang:
        raise ValueError('clang unavailable')
    libdir = os.environ.get('LLVM_LIBDIR')
    if not libdir:
        prefix = Path(config).parent.parent / 'lib'
        libdir = str(prefix) if (prefix / 'libLLVM.dylib').exists() else subprocess.check_output([config, '--libdir'], text=True).strip()
    output.mkdir(parents=True, exist_ok=False)
    state = dict(schema='self-host-measure-v2', status='running', carrier=str(carrier),
                 carrier_sha256=digest(carrier), source=str(source), runs=runs,
                 link_command=[clang, '-w', '-O2', '<llvm>', '<runtime>', '-L' + libdir, '-lLLVM', '-o', '<compiler>'],
                 llvm_config=config, llvm_version=subprocess.check_output([config, '--version'], text=True).strip(),
                 clang_version=subprocess.check_output([clang, '--version'], text=True).strip(),
                 generations=[], measurements=[])

    def save():
        (output / 'summary.json').write_text(json.dumps(state, indent=2) + '\n')
        # A failed run deliberately has no official timing keys.
        with (output / 'summary.txt').open('w') as stream:
            for key in ('schema', 'status', 'carrier', 'carrier_sha256', 'source', 'runs', 'fixed_point_generation', 'measured_compiler', 'measured_compiler_sha256', 'error', 'exit_status'):
                if key in state:
                    stream.write(f'{key}={state[key]}\n')
            if state['status'] == 'complete':
                times = [row['wall_seconds'] for row in state['measurements']]
                stream.write('self_compile_wall_seconds=' + ','.join(f'{v:.6f}' for v in times) + '\n')
                for name, value in [('min', min(times)), ('median', statistics.median(times)), ('max', max(times))]:
                    stream.write(f'self_compile_{name}_seconds={value:.6f}\n')

    def inputs():
        # Include untracked source and dependency edits, not only Git revisions.
        paths = set(source.parent.rglob('*'))
        for root in (Path('std'), Path('../syntax')):
            paths.update(p for p in root.rglob('*') if p.suffix == '.pw' or p.name in ('Plew.toml', 'Plew.lock'))
        paths.update(Path(p) for p in ('Plew.toml', 'Plew.lock'))
        paths.update((carrier, Path(config), Path(clang)))
        paths.update(Path(libdir).glob('libLLVM*.dylib'))
        return {str(p.absolute()): digest(p) for p in sorted(paths) if p.is_file()}

    snapshot = inputs()
    (output / 'inputs.json').write_text(json.dumps(snapshot, indent=2) + '\n')

    def check_inputs():
        if inputs() != snapshot:
            raise ValueError('source, dependencies, carrier or toolchain changed during measurement')

    def compile_with(executable, name, link):
        directory = output / name
        state['current_artifact'] = name
        save()
        print(f'[self-host] {name}: compile with {executable}', file=sys.stderr, flush=True)
        check_inputs()
        subprocess.run(['./measure-self-compile.sh'], env={**os.environ, 'PLEWC': str(executable), 'SOURCE': str(source), 'OUT_DIR': str(directory), 'LLVM_CONFIG': config}, check=True)
        with (directory / 'runtime.c').open('wb') as stream:
            subprocess.run([str(executable), '--runtime'], stdout=stream, check=True, timeout=60)
        check_inputs()
        row = dict(artifact=name, compiler=str(executable), compiler_sha256=digest(executable),
                   wall_seconds=float(fields(directory / 'summary.txt')['wall_seconds']),
                   llvm_sha256=digest(directory / 'compiler.ll'), runtime_sha256=digest(directory / 'runtime.c'))
        state['current_artifact'] = name
        if link:
            print(f'[self-host] {name}: link successor', file=sys.stderr, flush=True)
            successor = directory / 'next' / 'plewc'
            successor.parent.mkdir()
            subprocess.run([clang, '-w', '-O2', str(directory / 'compiler.ll'), str(directory / 'runtime.c'), '-L' + libdir, '-lLLVM', '-o', str(successor)], check=True, timeout=60)
            (successor.parent / 'std').symlink_to(Path('std').absolute(), target_is_directory=True)
            row['successor'] = str(successor)
            row['successor_sha256'] = digest(successor)
        return row

    def same_materials(previous, current):
        return all(previous[key] == current[key] for key in ('llvm_sha256', 'runtime_sha256'))

    try:
        save()
        previous = compile_with(carrier, 'generation-1', True)
        state['generations'].append(previous)
        save()
        for generation in (2, 3):
            executable = Path(previous['successor'])
            current = compile_with(executable, f'generation-{generation}', True)
            current['matches_previous'] = same_materials(previous, current)
            state['generations'].append(current)
            save()
            if current['matches_previous']:
                state.update(fixed_point_generation=generation, measured_compiler=str(executable), measured_compiler_sha256=digest(executable))
                state['measurements'].append(current)
                print(f'[self-host] fixed point at generation {generation}; measurement 1/{runs}', file=sys.stderr, flush=True)
                break
            previous = current
        else:
            raise ValueError('no fixed point: generation 2 and 3 LLVM/runtime differ')
        for run in range(2, runs + 1):
            current = compile_with(executable, f'measurement-{run}', False)
            state['measurements'].append(current)
            if not same_materials(state['measurements'][0], current):
                raise ValueError(f'fixed-point output changed on measurement {run}')
            save()
        check_inputs()
        state.update(status='complete', exit_status=0)
        save()
        print(f"[self-host] complete: median={statistics.median(row['wall_seconds'] for row in state['measurements']):.6f}s artifacts={output}", file=sys.stderr)
        return 0
    except (ValueError, OSError, subprocess.SubprocessError) as error:
        code = error.returncode if isinstance(error, subprocess.CalledProcessError) else 65
        if code < 0:
            code = 128 - code
        state.update(status='failed', error=str(error), exit_status=code)
        save()
        print(f'[self-host] failed: {error}', file=sys.stderr)
        return code


if __name__ == '__main__':
    try:
        sys.exit(main())
    except (KeyError, ValueError, OSError) as error:
        print(f'measure-self-host: {error}', file=sys.stderr)
        sys.exit(64)
