#!/usr/bin/env python3
"""Compare direct module consumption with explicit LLVM-text output.

The text path is a diagnostic/reference path, never a fallback for object mode.
"""
import argparse
import os
from pathlib import Path
import subprocess
import shutil
import sys
import tempfile

ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / 'scripts/support'))
import clang_environment


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--compiler', type=Path, default=Path(os.environ.get('PLEWC', ROOT / 'plewc')))
    parser.add_argument('--worker', type=Path)
    parser.add_argument('--sanitizer-output', action='store_true')
    parser.add_argument('--llvm-config', default=os.environ.get('LLVM_CONFIG', 'llvm-config'))
    args = parser.parse_args()
    compiler = args.compiler.absolute()
    clang_environment.apply()
    wrapper = [sys.executable, str(ROOT / 'scripts/support/watch-command.py'), '--']

    def run(command, expected=0):
        result = subprocess.run([*wrapper, *map(str, command)], capture_output=True)
        assert result.returncode == expected, (command, result.returncode, result.stderr.decode(errors='replace'))
        return result

    with tempfile.TemporaryDirectory(prefix='plew direct object ') as temporary:
        directory = Path(temporary)
        worker = args.worker.absolute() if args.worker else directory / 'llvm-object'
        if not args.worker:
            config = shutil.which(args.llvm_config)
            if not config and args.llvm_config == 'llvm-config':
                config = '/opt/homebrew/opt/llvm/bin/llvm-config'
            def query(option):
                return subprocess.check_output([config, option], text=True).strip()
            prefix = Path(config).parent.parent
            library = prefix / 'lib'
            if not (library / 'libLLVM.dylib').is_file():
                library = Path(query('--libdir'))
            run([Path(query('--bindir')) / 'clang++', '-std=c++17', '-O2',
                 '-isystem', query('--includedir'), ROOT / 'native/llvm_backend.cpp',
                 ROOT / 'native/llvm_object_main.cpp', '-L' + str(library), '-lLLVM', '-o', worker])
        runtime = directory / 'runtime.c'
        runtime.write_bytes(run([compiler, '--runtime']).stdout)
        runtime_object = directory / 'runtime.o'
        run(['/usr/bin/clang', '-O2', '-c', runtime, '-o', runtime_object])
        direct, reference = directory / 'direct.o', directory / 'reference.o'
        llvm = directory / 'reference.ll'
        cases = ['run/async_match', 'run/unique_enum_arc', 'run/closure_return_boundaries',
                 'run/cow_gw_field_array_append', 'part/publicapiclosure_reexport/Main']
        for case in cases:
            source = ROOT / 'tests/fixtures' / (case + '.pw')
            result = run([compiler, '--emit-object', direct, '--target-cpu', 'apple-m1', '--trace-phases', source])
            assert result.stdout == b'', case
            assert b'backend:drain:done' in result.stderr and b'Running pass:' in result.stderr, case
            assert b'Executing Pass' in result.stderr, case
            assert b'backend:print-module' not in result.stderr and b'backend:write:' not in result.stderr, case
            text = run([compiler, '--trace-phases', source])
            assert b'backend:print-module:done' in text.stderr, case
            llvm.write_bytes(text.stdout)
            run([worker, llvm, reference, 'apple-m1'])
            expected = source.with_suffix('.out').read_bytes().rstrip(b'\n')
            for object_file in (direct, reference):
                binary = directory / 'app'
                run(['/usr/bin/clang', object_file, runtime_object, '-o', binary])
                assert run([binary]).stdout.rstrip(b'\n') == expected, (case, object_file)
            print('PASS direct-object comparison', case, flush=True)
        broken = directory / 'Broken.pw'
        broken.write_text('fn main() { missing() }\n')
        direct.write_bytes(b'previous object')
        direct_failure = run([compiler, '--emit-object', direct, broken], expected=1)
        text_failure = run([compiler, broken], expected=1)
        assert direct_failure.stderr == text_failure.stderr
        assert direct.read_bytes() == b'previous object'
        print('PASS direct-object frontend error preserves output', flush=True)
        run([compiler, '--emit-object', directory / 'missing/output.o', source], expected=1)
        print('PASS direct-object output error propagates', flush=True)
        if args.sanitizer_output:
            config = shutil.which(args.llvm_config)
            clang = Path(subprocess.check_output([config, '--bindir'], text=True).strip()) / 'clang'
            source = ROOT / 'tests/fixtures/run/unique_enum_arc.pw'
            run([compiler, '--emit-object', direct, '--asan', source])
            symbols = run(['/usr/bin/nm', direct]).stdout
            assert b'__asan_' in symbols
            binary = directory / 'asan-app'
            run([clang, '-fsanitize=address', direct, runtime, '-o', binary])
            assert run([binary]).stdout.rstrip(b'\n') == source.with_suffix('.out').read_bytes().rstrip(b'\n')
            print('PASS direct-object ASan instrumentation and execution', flush=True)


if __name__ == '__main__':
    main()
