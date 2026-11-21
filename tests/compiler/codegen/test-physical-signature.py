#!/usr/bin/env python3
"""Production physical signature planner with live LLVM contexts and malformed records."""
import argparse
import os
from pathlib import Path
import subprocess
import sys

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
evidence = root / 'tmp/value-abi/physical-signature' / ('asan' if options.asan else 'normal')
evidence.mkdir(parents=True, exist_ok=True)
for previous in ['summary.txt']:
    (evidence / previous).unlink(missing_ok=True)

sys.path.insert(0, str(root / 'scripts/support'))
import native_build

def capture(command, name, environment=None, *, trace=False, clang=False, bounded=False):
    if bounded:
        with (evidence / name).open("wb") as out, (evidence / (name + ".log")).open("wb") as err:
            subprocess.run(list(map(str, command)), stdout=out, stderr=err, cwd=root,
                           env=environment, timeout=60, check=True)
        return
    native_build.logged(command, stdout_path=evidence / name,
                        stderr_path=evidence / (name + '.log'), cwd=root,
                        env=environment, clang=clang,
                        trace_log=evidence / (name + '.trace.log') if trace else None)

capture([compiler, '--trace-phases', *(['--asan'] if options.asan else []), root / 'tests/compiler/codegen/PhysicalSignature.pw'], 'harness.ll', trace=True)
capture([compiler, '--runtime'], 'runtime.c', bounded=True)
module = evidence / 'harness.ll'
flags = ['-fsanitize=address', '-fno-omit-frame-pointer'] if options.asan else []
if options.asan:
    capture([bindir / 'opt', '-debug-pass-manager', '-passes=asan', '-S', module, '-o', evidence / 'instrumented.ll'], 'instrument', trace=True)
    module = evidence / 'instrumented.ll'
    assert '__asan_report_' in module.read_text(), 'Plew harness must be instrumented'
capture([bindir / 'clang++', '-std=c++17', '-O1', '-g', *flags, '-isystem', query('--includedir'),
         '-c', root / 'native/llvm_backend.cpp', '-o', evidence / 'backend.o'], 'backend', trace=True, clang=True)
objects = [evidence / 'backend.o']
for source, name in [(module, 'module'), (evidence / 'runtime.c', 'runtime'),
                     (root / 'tests/compiler/codegen/PhysicalSignature.c', 'driver')]:
    output = evidence / (name + '.o')
    capture([bindir / 'clang', '-O0', '-g', *flags, '-isystem', query('--includedir'),
             '-c', source, '-o', output], name + '-object', trace=True, clang=True)
    objects.append(output)
capture([bindir / 'clang', '-O0', *flags, *objects,
         '-L' + str(libdir), '-lLLVM', '-lc++', '-o', evidence / 'harness'], 'link')
print('PASS physical signature harness build', flush=True)
environment = dict(os.environ)
if options.asan:
    environment.update(ASAN_OPTIONS='detect_leaks=1:halt_on_error=1', LSAN_OPTIONS='exitcode=23')
capture([evidence / 'harness'], 'stdout', environment, bounded=True)
assert (evidence / 'stdout').read_bytes() == b'ok\n'
errors = (evidence / 'stdout.log').read_text()
assert not errors, errors
assert 'AddressSanitizer' not in errors and 'LeakSanitizer' not in errors
(evidence / 'summary.txt').write_text('status=passed\nllvm=' + query('--version') + '\nscope=production physical signature planner; live LLVM ownership and malformed protocol records\n')
print('PASS physical signature roles, omission, byval, alignment, context, malformed record rejection', flush=True)
