#!/usr/bin/env python3
"""Exercise private proof projection without changing production visibility."""
import hashlib
import json
import os
from pathlib import Path
import re
import shutil
import subprocess
import sys

root = Path(__file__).resolve().parents[3]
compiler = Path(os.environ.get('PLEWC', root / 'bin/plewc')).absolute()
config = os.environ.get('LLVM_CONFIG', '/opt/homebrew/opt/llvm/bin/llvm-config')
out = root / 'tmp/frontend/provided-source-endpoints'
out.mkdir(parents=True, exist_ok=True)
(out / 'summary.json').unlink(missing_ok=True)
snapshot = out / 'source'
if snapshot.exists():
    shutil.rmtree(snapshot)
shutil.copytree(root / 'src', snapshot / 'src')
original = (root / 'src/Frontend.pw').read_bytes()
test = (root / 'tests/compiler/frontend/ProvidedSourceEndpointMain.pw').read_bytes()
entry = snapshot / 'src/Frontend.pw'
entry.write_bytes(original + b'\n' + test)
assert entry.read_bytes()[:len(original)] == original
manifest = (root / 'Plew.toml').read_text()
manifest = re.sub(r'path\s*=\s*"([^"]+)"', lambda m: 'path = ' + json.dumps(os.path.relpath((root / m[1]).resolve(), snapshot)), manifest)
(snapshot / 'Plew.toml').write_text(manifest)
if (root / 'Plew.lock').exists():
    shutil.copy2(root / 'Plew.lock', snapshot / 'Plew.lock')

def sha(path):
    return hashlib.sha256(path.read_bytes()).hexdigest()

inputs = {str(p.relative_to(root / 'src')): sha(p) for p in (root / 'src').rglob('*') if p.is_file()}
(out / 'inputs.json').write_text(json.dumps(inputs, indent=2) + '\n')
support_paths = {root / 'Plew.toml', root / 'Plew.lock', root / 'tests/compiler/frontend/ProvidedSourceEndpointMain.pw', root / 'tests/compiler/frontend/ProvidedSourceEndpointMain.out', Path(__file__).resolve()}
for fixture in ('traitprovidedblanketgeneric', 'traitprovidedblanketassociated'):
    support_paths.update((root / 'tests/fixtures/part' / fixture).iterdir())
for name in ('llvm_backend.cpp', 'compiler_callbacks.cpp', 'compiler_execution.cpp', 'llvm_pipeline.h'):
    support_paths.add(root / 'native' / name)
for name in ('native_build.py', 'llvm_link.py', 'process_watch.py', 'clang_environment.py'):
    support_paths.add(root / 'scripts/support' / name)
for tree in (root / 'std', compiler.parent / 'std'):
    if tree.exists():
        support_paths.update(tree.resolve().rglob('*.pw'))
for match in re.finditer(r'path\s*=\s*"([^\"]+)"', (root / 'Plew.toml').read_text()):
    dependency = (root / match[1]).resolve()
    support_paths.update((dependency / 'src').rglob('*.pw'))
    support_paths.add(dependency / 'Plew.toml')
support_inputs = {str(path.resolve()): sha(path) for path in support_paths if path.is_file()}
(out / 'support-inputs.json').write_text(json.dumps(support_inputs, indent=2) + '\n')

sys.path.insert(0, str(root / 'scripts/support'))
import clang_environment
import llvm_link
import native_build
clang_environment.apply()
os.chdir(root)

def stage(name, command, *, clang=False):
    print('[trace-phase] provided-source-endpoints:' + name, file=sys.stderr, flush=True)
    native_build.logged(command, stdout_path=out / (name + '.stdout'), stderr_path=out / (name + '.stderr'), trace_log=out / (name + '.trace.log'), clang=clang)

stage('compile', [compiler, '--trace-phases', entry])
shutil.copy2(out / 'compile.stdout', out / 'harness.ll')
stage('runtime', [compiler, '--runtime'])
shutil.copy2(out / 'runtime.stdout', out / 'runtime.c')
backend = llvm_link.compiler_backend(config, out / 'backend.o')
clang = llvm_link.selected_clang(config)
libdir = subprocess.check_output([config, '--libdir'], text=True).strip()
stage('link', [clang, '-O0', '-w', out / 'harness.ll', out / 'runtime.c', *backend, '-L' + libdir, '-lLLVM', '-o', out / 'harness'], clang=True)
with (out / 'run.stdout').open('wb') as stdout, (out / 'run.stderr').open('wb') as stderr:
    subprocess.run([str(out / 'harness')], stdout=stdout, stderr=stderr, timeout=60, check=True)
assert (out / 'run.stdout').read_bytes() == (root / 'tests/compiler/frontend/ProvidedSourceEndpointMain.out').read_bytes()
assert not (out / 'run.stderr').read_bytes()
assert all(sha(root / 'src' / p) == value for p, value in inputs.items()), 'source inputs changed during validation'
assert entry.read_bytes() == original + b'\n' + test
assert all(sha(Path(path)) == value for path, value in support_inputs.items()), 'support inputs changed during validation'
(out / 'summary.json').write_text(json.dumps({'status': 'passed', 'source_inputs': inputs, 'support_inputs': support_inputs, 'frontend_prefix_unchanged': True, 'frontend_prefix_sha256': hashlib.sha256(original).hexdigest(), 'test_main_sha256': hashlib.sha256(test).hexdigest(), 'compiler_sha256': sha(compiler), 'scope': 'private endpoint and argument guards, exact instances, strict receivers and generic/associated frontend checks; public native/ORC execution is separate'}, indent=2) + '\n')
print('PASS private provided source endpoint projection')
