#!/usr/bin/env python3
"""Native first-call source callback diagnostic, not the product CLI gate."""
import argparse
import os
import re
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
with (evidence / 'trace.stderr').open('wb') as err:
    traced = subprocess.run([str(binary), 'trace'], env=environment, stderr=err,
                            stdout=subprocess.PIPE, timeout=60, check=True)
assert not traced.stdout
lines = (evidence / 'trace.stderr').read_text().splitlines()
events = [re.fullmatch(r'\[trace-phase\] jit=(0x[0-9a-f]+) session=(\d+) body=(\d+) completed=(\d+) (source:prepared|module:submitted)', line)
          for line in lines]
assert len(events) == 14 and all(events), lines
assert len({event[1] for event in events}) == 1
assert all(int(event[2]) == 0xf000000100000003 for event in events)
assert [int(event[4]) for event in events] == list(range(1, 15))
assert {int(event[3]) for event in events} == {0, 1, 2, 3, 4, 6, 7}
for prepared, submitted in zip(events[::2], events[1::2]):
    assert prepared[3] == submitted[3]
    assert (prepared[5], submitted[5]) == ('source:prepared', 'module:submitted')
print('PASS first-call compilation, canonical identity, single-thread callback and terminal failure')
print('PASS opt-in progress: completed new bodies only; repeat calls and unused bodies stay quiet')
(evidence / 'summary.txt').write_text('status=passed\nllvm=' + query('--version') + '\n')
