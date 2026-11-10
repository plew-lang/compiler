#!/usr/bin/env python3
"""Native ORC publication compares structural ABI across consumed contexts."""
import os
from pathlib import Path
import subprocess
import sys
root = Path(__file__).resolve().parents[3]
config = os.environ.get('LLVM_CONFIG', '/opt/homebrew/opt/llvm/bin/llvm-config')
def query(flag):
    return subprocess.check_output([config, flag], text=True, timeout=10).strip()
bindir = Path(query('--bindir'))
out = root / 'tmp/value-abi/source-entry-abi'
out.mkdir(parents=True, exist_ok=True)
(out / 'summary.txt').unlink(missing_ok=True)
def stage(name, command, expected=0, diagnostic=None):
    print('[trace-phase] source-entry-abi:' + name, file=sys.stderr, flush=True)
    with (out / (name + '.stdout')).open('wb') as stdout, (out / (name + '.stderr')).open('wb') as stderr:
        result = subprocess.run(list(map(str, command)), stdout=stdout, stderr=stderr, timeout=55)
    assert result.returncode == expected, (name, result.returncode)
    if diagnostic:
        assert diagnostic in (out / (name + '.stderr')).read_bytes(), name
        assert not (out / (name + '.stdout')).read_bytes(), name
    elif name != 'compile':
        assert (out / (name + '.stdout')).read_bytes() == b'ok\n', name
        if name != 'registration':
            assert not (out / (name + '.stderr')).read_bytes(), name
stage('compile', [bindir / 'clang++', '-std=c++17', '-O1', '-isystem', query('--includedir'),
                  root / 'native/llvm_backend.cpp', root / 'tests/compiler/codegen/SourceEntryAbi.cpp',
                  '-L' + query('--libdir'), '-lLLVM', '-o', out / 'harness'])
stage('registration', [out / 'harness'])
registration_errors = (out / 'registration.stderr').read_bytes()
assert registration_errors.count(b'conflicting source entry ABI: entry') == 9
assert registration_errors.count(b'prepared source entry lacks body identity:') == 2
assert registration_errors.count(b'unsupported source entry ABI attribute payload') == 1
stage('requested-good', [out / 'harness', '--requested-good'])
stage('requested-bad', [out / 'harness', '--requested-bad'], 1, b'conflicting source entry ABI')
stage('requested-missing-identity', [out / 'harness', '--requested-missing-identity'], 1, b'prepared source entry lacks body identity')
stage('requested-dependency-bad', [out / 'harness', '--requested-dependency-bad'], 1, b'conflicting source entry ABI')
stage('requested-dependency-missing-identity', [out / 'harness', '--requested-dependency-missing-identity'], 1, b'prepared source entry lacks body identity')
stage('requested-dependency-host', [out / 'harness', '--requested-dependency-host'], 1, b'prepared source entry lacks body identity')
(out / 'summary.txt').write_text('status=passed\ncontext-independent registration and requested ABI comparison\n')
print('PASS source entry structural ABI across contexts and requested definitions')
