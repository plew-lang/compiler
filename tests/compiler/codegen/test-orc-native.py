#!/usr/bin/env python3
"""Native ORC ownership/host-symbol diagnostic, not the source-lazy run gate."""
import argparse
import hashlib
import json
import os
from pathlib import Path
import subprocess
import sys

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
evidence = root / 'tmp/lazy-build/orc-native' / ('asan' if options.asan else 'normal')
evidence.mkdir(parents=True, exist_ok=True)
for previous in ['summary.txt', 'summary.json']:
    (evidence / previous).unlink(missing_ok=True)
binary = evidence / 'test'
# Keep DWARF in retained objects. Linking sources with -g implicitly runs
# dsymutil on macOS; that packaging step is not part of this ORC diagnostic.
# Supervise actual LLVM work per compile/link through the shared observer.
common = [str(bindir / 'clang++'), '-std=c++17', '-O1', '-g',
          '-Xclang', '-fdebug-pass-manager', '-mllvm', '-debug-pass=Executions',
          '-isystem', query('--includedir')]
sanitizer = ['-fsanitize=address', '-fno-omit-frame-pointer'] if options.asan else []
commands = [
    ('backend', [*common, *sanitizer, '-c', str(root / 'native/llvm_backend.cpp'),
                 '-o', str(evidence / 'backend.o')]),
    ('OrcNative', [*common, *sanitizer, '-c', str(root / 'tests/compiler/codegen/OrcNative.cpp'),
                   '-o', str(evidence / 'OrcNative.o')]),
    ('link', [str(bindir / 'clang++'), str(evidence / 'backend.o'), str(evidence / 'OrcNative.o'),
              *sanitizer, '-L' + str(libdir), '-lLLVM', '-o', str(binary)]),
]
with (evidence / 'build.log').open('wb') as combined:
    for label, command in commands:
        log = evidence / (label + '.build.log')
        try:
            subprocess.run([sys.executable, '-B', str(root / 'scripts/support/trace-command.py'),
                            str(log), '--', *command], check=True)
        finally:
            combined.write(('=== ' + label + ' ===\n').encode())
            if log.exists():
                combined.write(log.read_bytes())
            combined.flush()
print('PASS native ORC build', flush=True)
environment = dict(os.environ)
if options.asan:
    environment.update(ASAN_OPTIONS='detect_leaks=1:halt_on_error=1', LSAN_OPTIONS='exitcode=23')
with (evidence / 'stdout').open('wb') as out, (evidence / 'stderr').open('wb') as err:
    subprocess.run([str(binary), str(evidence / 'layout.o')], env=environment, stdout=out, stderr=err, timeout=60, check=True)
errors = (evidence / 'stderr').read_text()
for expected in ['Symbols not found', 'duplicate definition', 'does not have terminator', 'incompatible LLVM data layout']:
    assert expected.lower() in errors.lower(), expected
for label in ['absent', 'matching', 'incompatible']:
    case = errors.split('CHECK declaration-layout ' + label + '\n', 1)[1].split('END declaration-layout ' + label + '\n', 1)[0]
    assert ('incompatible LLVM data layout' in case) == (label == 'incompatible'), (label, case)
    assert 'declaration module contains executable code' not in case, (label, case)
assert 'AddressSanitizer' not in errors and 'LeakSanitizer' not in errors
assert not (evidence / 'stdout').read_bytes()
(evidence / 'summary.txt').write_text('status=passed\nllvm=' + query('--version') + '\n')
(evidence / 'summary.json').write_text(json.dumps({
    'status': 'passed', 'llvm': query('--version'),
    'build_commands': [command for _, command in commands],
    'debug_objects': ['backend.o', 'OrcNative.o'],
    'native_sha256': hashlib.sha256((root / 'native/llvm_backend.cpp').read_bytes()).hexdigest(),
    'test_sha256': hashlib.sha256((root / 'tests/compiler/codegen/OrcNative.cpp').read_bytes()).hexdigest(),
    'sanitizers': 'ASan/LSan native bridge and host; JIT instructions not instrumented' if options.asan else 'none',
    'layouts': ['absent', 'matching native', 'incompatible nonempty'],
    'paths': ['borrowed object output', 'consuming ORC add', 'signature-only ORC declarations with body metadata and lookup'],
    'declaration_layout_diagnostic_checked_per_case': True,
    'object_failure_preserves_output': True, 'failed_sessions_are_terminal': True,
}, indent=2) + '\n')
print('PASS native ORC: layout admission, modules, shared storage, host callbacks, terminal failures, disposal')
