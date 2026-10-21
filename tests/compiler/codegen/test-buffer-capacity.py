#!/usr/bin/env python3
"""Checked storage arithmetic and failure atomicity in the emitted runtime."""
import argparse
import os
from pathlib import Path
import shutil
import signal
import subprocess
import sys
import tempfile

ROOT = Path(__file__).resolve().parents[3]
sys.path.insert(0, str(ROOT / 'scripts/support'))
import clang_environment
import llvm_link

parser = argparse.ArgumentParser(description=__doc__)
parser.add_argument('--compiler', type=Path, default=Path(os.environ.get('PLEWC', ROOT / 'bin/plewc')))
parser.add_argument('--llvm-config', default=os.environ.get('LLVM_CONFIG') or shutil.which('llvm-config') or '/opt/homebrew/opt/llvm/bin/llvm-config')
parser.add_argument('--asan', action='store_true')
args = parser.parse_args()
compiler = args.compiler.absolute()
clang_environment.apply()
watch = [sys.executable, str(ROOT / 'scripts/support/watch-command.py'), '--']

def run(command):
    return subprocess.run([*watch, *map(str, command)], capture_output=True)

with tempfile.TemporaryDirectory(prefix='buffer-capacity-', dir=ROOT / 'tmp') as temporary:
    directory = Path(temporary)
    emitted = run([compiler, '--runtime'])
    assert emitted.returncode == 0, emitted.stderr
    (directory / 'runtime.c').write_bytes(emitted.stdout)
    for optimization in ('-O0', '-O2'):
        binary = directory / 'runtime-check'
        flags = ['-fsanitize=address,undefined', '-fno-omit-frame-pointer'] if args.asan else []
        linked = run([llvm_link.selected_clang(args.llvm_config), optimization, *flags, '-I', directory,
                      ROOT / 'tests/compiler/codegen/BufferCapacity.c', '-o', binary])
        assert linked.returncode == 0, linked.stderr.decode(errors='replace')
        result = run([binary])
        assert result.returncode == 0, result.stderr.decode(errors='replace')
        assert result.stdout == b'PASS runtime Buffer capacity and transactional failure\n', result.stdout
        assert b'runtime error:' not in result.stderr and b'ERROR: AddressSanitizer' not in result.stderr, result.stderr
        print('PASS Buffer generated runtime ' + optimization, flush=True)
    # AOT coverage comes from the same fixtures in normal/sanitizer harnesses.
    # Lazy execution must resolve and use the common runtime entry as well.
    for name in ('buffer_capacity_cow', 'buffer_capacity_bytes', 'buffer_reserve_overflow'):
        kind = 'run' if name == 'buffer_capacity_cow' else 'panic'
        fixture = ROOT / 'tests/fixtures' / kind / (name + '.pw')
        result = run([compiler, '--run', fixture])
        if kind == 'run':
            assert result.returncode == 0, result.stderr.decode(errors='replace')
            assert result.stdout == fixture.with_suffix('.out').read_bytes(), result.stdout
        else:
            assert result.returncode == 128 + signal.SIGABRT, (name, result.returncode, result.stderr)
            assert b'panic: '+fixture.with_suffix('.panic').read_bytes().strip() in result.stderr, result.stderr
        print('PASS Buffer lazy execution ' + name, flush=True)
