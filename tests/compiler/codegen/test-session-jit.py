#!/usr/bin/env python3
"""Partial-session ORC ownership diagnostic; not the product lazy-run gate."""
import argparse
import os
from pathlib import Path
import subprocess

parser = argparse.ArgumentParser(description=__doc__)
parser.add_argument('--asan', action='store_true')
options = parser.parse_args()
root = Path(__file__).resolve().parents[3]
compiler = Path(os.environ.get('PLEWC', root / 'bin/plewc')).absolute()
config = Path(os.environ.get('LLVM_CONFIG', '/opt/homebrew/opt/' + ('llvm@22' if options.asan else 'llvm') + '/bin/llvm-config'))

def query(option):
    return subprocess.check_output([str(config), option], text=True, timeout=10).strip()

bindir = Path(query('--bindir'))
libdir = config.parent.parent / 'lib'
if not (libdir / 'libLLVM.dylib').exists():
    libdir = Path(query('--libdir'))
evidence = root / 'tmp/lazy-build/session-jit' / ('asan' if options.asan else 'normal')
evidence.mkdir(parents=True, exist_ok=True)

def capture(command, name, environment=None):
    with (evidence / name).open('wb') as out, (evidence / (name + '.log')).open('wb') as err:
        subprocess.run(list(map(str, command)), cwd=root, stdout=out, stderr=err,
                       env=environment, timeout=60, check=True)

capture([compiler, *(['--asan'] if options.asan else []), root / 'tests/compiler/codegen/SessionJit.pw'], 'harness.ll')
capture([compiler, '--runtime'], 'runtime.c')
module = evidence / 'harness.ll'
flags = ['-fsanitize=address', '-fno-omit-frame-pointer'] if options.asan else []
if options.asan:
    capture([bindir / 'opt', '-passes=asan', '-S', module, '-o', evidence / 'instrumented.ll'], 'instrument')
    module = evidence / 'instrumented.ll'
    assert '__asan_report_' in module.read_text(), 'Plew harness must be instrumented'
capture([bindir / 'clang++', '-std=c++17', '-O1', '-g', *flags, '-isystem', query('--includedir'),
         '-c', root / 'native/llvm_backend.cpp', '-o', evidence / 'backend.o'], 'backend')
capture([bindir / 'clang', '-O0', '-g', *flags, module, evidence / 'runtime.c',
         root / 'tests/compiler/codegen/SessionJit.c', evidence / 'backend.o',
         '-L' + str(libdir), '-lLLVM', '-lc++', '-o', evidence / 'harness'], 'link')
print('PASS session JIT harness build', flush=True)
environment = dict(os.environ)
if options.asan:
    environment.update(ASAN_OPTIONS='detect_leaks=1:halt_on_error=1', LSAN_OPTIONS='exitcode=23')
capture([evidence / 'harness'], 'stdout', environment)
assert (evidence / 'stdout').read_bytes() == b'ok\n'
errors = (evidence / 'stdout.log').read_text()
assert 'Symbols not found' in errors, errors
assert 'AddressSanitizer' not in errors and 'LeakSanitizer' not in errors
(evidence / 'summary.txt').write_text('status=passed\nllvm=' + query('--version') + '\nscope=Plew and native ownership bridge; JIT instructions not sanitizer-instrumented\n')
print('PASS partial session JIT execution and success/failure ownership transfer', flush=True)
