#!/usr/bin/env python3
"""Plew-owned compiler session -> C callback -> ORC body, with one runtime."""
import argparse
import os
from pathlib import Path
import subprocess

parser = argparse.ArgumentParser(description=__doc__)
parser.add_argument('--asan', action='store_true')
parser.add_argument('--execution', action='store_true')
options = parser.parse_args()
root = Path(__file__).resolve().parents[3]
compiler = Path(os.environ.get('PLEWC', root / 'plewc')).absolute()
config = Path(os.environ.get('LLVM_CONFIG', '/opt/homebrew/opt/' + ('llvm@22' if options.asan else 'llvm') + '/bin/llvm-config'))
def query(option):
    return subprocess.check_output([str(config), option], text=True, timeout=10).strip()
bindir = Path(query('--bindir'))
libdir = config.parent.parent / 'lib'
if not (libdir / 'libLLVM.dylib').exists():
    libdir = Path(query('--libdir'))
evidence = root / ('tmp/lazy-build/compiler-execution' if options.execution else 'tmp/lazy-build/compiler-callback') / ('asan' if options.asan else 'normal')
evidence.mkdir(parents=True, exist_ok=True)
def capture(command, name):
    with (evidence / name).open('wb') as output, (evidence / (name + '.err')).open('wb') as error:
        subprocess.run(list(map(str, command)), cwd=root, stdout=output, stderr=error, timeout=60, check=True)
    print('PASS compiler callback ' + name, flush=True)
flags = ['--asan'] if options.asan else []
host = 'CompilerRun.pw' if options.execution else 'CompilerCallback.pw'
capture([compiler, *flags, root / 'tests/compiler/codegen' / host], 'host.ll')
capture([compiler, '--runtime'], 'runtime.c')
module = evidence / 'host.ll'
if options.asan:
    capture([bindir / 'opt', '-passes=asan', '-S', module, '-o', evidence / 'instrumented.ll'], 'instrument')
    module = evidence / 'instrumented.ll'
    assert '__asan_' in module.read_text()
link_flags = ['-fsanitize=address', '-fno-omit-frame-pointer'] if options.asan else []
objects = []
sources = [('backend', root / 'native/llvm_backend.cpp'), ('adapter', root / 'native/compiler_callbacks.cpp')]
sources += [('execution', root / 'native/compiler_execution.cpp')] if options.execution else [('harness', root / 'tests/compiler/codegen/CompilerCallback.cpp')]
for name, source in sources:
    target = evidence / (name + '.o')
    capture([bindir / 'clang++', '-std=c++17', '-O1', *link_flags, '-isystem', query('--includedir'), '-c', source, '-o', target], name)
    objects.append(target)
capture([bindir / 'clang', '-O0', *link_flags, module, evidence / 'runtime.c', *objects, '-lc++', '-L' + str(libdir), '-lLLVM', '-o', evidence / 'test'], 'link')
if options.asan:
    os.environ['ASAN_OPTIONS'] = 'detect_leaks=1:halt_on_error=1'
    os.environ['LSAN_OPTIONS'] = 'exitcode=23'
target = root / 'tests/compiler/codegen' / ('RunTarget.pw' if options.execution else 'CallbackTarget.pw')
capture([evidence / 'test', str(root / 'std') + '/', target], 'run')
assert (evidence / 'run').read_text() == ('1\n7\n3\n2\nexample\n' if options.execution else '41\n72\nok\n')
assert (evidence / 'run.err').read_text() == ('' if options.execution else 'plew: unknown compiler session ID\n')
if options.execution:
    capture([evidence / 'test', str(root / 'std') + '/', root / 'tests/fixtures/run/async_basic.pw'], 'async')
    assert (evidence / 'async').read_text() == '42\n84\n'
    assert not (evidence / 'async.err').read_text()
(evidence / 'summary.txt').write_text('status=passed\nllvm=' + query('--version') + '\n')
