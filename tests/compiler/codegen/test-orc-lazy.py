#!/usr/bin/env python3
"""Native first-call source callback diagnostic, not the product CLI gate."""
import argparse
import os
from pathlib import Path
import subprocess

parser = argparse.ArgumentParser(description=__doc__)
parser.add_argument('--asan', action='store_true')
options = parser.parse_args()
root = Path(__file__).resolve().parents[3]
default = '/opt/homebrew/opt/' + ('llvm@22' if options.asan else 'llvm') + '/bin/llvm-config'
config = Path(os.environ.get('LLVM_CONFIG', default))


def query(option):
    return subprocess.check_output([str(config), option], text=True, timeout=10).strip()


bindir = Path(query('--bindir'))
libdir = config.parent.parent / 'lib'
if not (libdir / 'libLLVM.dylib').exists():
    libdir = Path(query('--libdir'))
evidence = root / 'tmp/lazy-build/orc-lazy' / ('asan' if options.asan else 'normal')
evidence.mkdir(parents=True, exist_ok=True)
binary = evidence / 'test'
command = [str(bindir / 'clang++'), '-std=c++17', '-O1', '-g', '-isystem', query('--includedir'),
           str(root / 'native/llvm_backend.cpp'), str(root / 'tests/compiler/codegen/OrcLazy.cpp'),
           '-L' + str(libdir), '-lLLVM', '-o', str(binary)]
if options.asan:
    command += ['-fsanitize=address', '-fno-omit-frame-pointer']
with (evidence / 'build.log').open('wb') as log:
    subprocess.run(command, stdout=log, stderr=log, timeout=60, check=True)
print('PASS native ORC build', flush=True)
environment = dict(os.environ)
if options.asan:
    environment.update(ASAN_OPTIONS='detect_leaks=1:halt_on_error=1', LSAN_OPTIONS='exitcode=23')
with (evidence / 'stdout').open('wb') as out, (evidence / 'stderr').open('wb') as err:
    subprocess.run([str(binary)], env=environment, stdout=out, stderr=err, timeout=60, check=True)
errors = (evidence / 'stderr').read_text()
assert not errors, errors
assert 'AddressSanitizer' not in errors and 'LeakSanitizer' not in errors
assert not (evidence / 'stdout').read_bytes()
with (evidence / 'failure.stderr').open('wb') as err:
    failure = subprocess.run([str(binary), 'fail'], env=environment, stderr=err,
                             stdout=subprocess.PIPE, timeout=60)
assert failure.returncode == 1 and not failure.stdout
assert 'lazy compilation failed' in (evidence / 'failure.stderr').read_text()
print('PASS first-call compilation, canonical identity, single-thread callback and terminal failure')
(evidence / 'summary.txt').write_text('status=passed\nllvm=' + query('--version') + '\n')
