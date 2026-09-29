#!/usr/bin/env python3
"""Manual native diagnostic: one global owner, separate executable module."""
import json
import os
from pathlib import Path
import re
import subprocess

root = Path(__file__).resolve().parents[3]
compiler = Path(os.environ.get('PLEWC', root / 'plewc')).absolute()
config = Path(os.environ.get('LLVM_CONFIG', '/opt/homebrew/opt/llvm/bin/llvm-config'))
bindir = Path(subprocess.check_output([str(config), '--bindir'], text=True).strip())
libdir = config.parent.parent / 'lib'
if not (libdir / 'libLLVM.dylib').exists():
    libdir = Path(subprocess.check_output([str(config), '--libdir'], text=True).strip())
evidence = root / 'tmp/lazy-build/global-modules'
evidence.mkdir(parents=True, exist_ok=True)


def capture(command, name):
    with (evidence / name).open('wb') as out, (evidence / (name + '.log')).open('wb') as err:
        subprocess.run(list(map(str, command)), cwd=root, stdout=out, stderr=err,
                       timeout=60, check=True)


capture([compiler, root / 'tests/compiler/codegen/GlobalModules.pw'], 'harness.ll')
capture([compiler, '--runtime'], 'runtime.c')
capture([bindir / 'clang', '-O0', evidence / 'harness.ll', evidence / 'runtime.c',
         '-L' + str(libdir), '-lLLVM', '-o', evidence / 'harness'], 'harness.link')
print('PASS global module harness build', flush=True)
results = []
for name in ['global_var', 'global_generic_init', 'global_forward_ref']:
    source = root / 'tests/fixtures/run' / (name + '.pw')
    for mode in ['storage', 'body']:
        capture([evidence / 'harness', source, mode, str(root / 'std') + '/'],
                name + '.' + mode + '.ll')
    storage = (evidence / (name + '.storage.ll')).read_text()
    body = (evidence / (name + '.body.ll')).read_text()
    assert not re.search(r'^define ', storage, re.M), 'storage module must contain no executable body'
    definitions = re.findall(r'^(@plew\.g\.\d+) = global ', storage, re.M)
    references = re.findall(r'^(@plew\.g\.\d+) = external global ', body, re.M)
    assert definitions and definitions == references, 'global definition/reference identities differ'
    assert not re.search(r'^@plew\.g\.\d+ = (?!external)', body, re.M), 'duplicate storage owner'
    capture([bindir / 'clang', '-O0', evidence / (name + '.storage.ll'),
             evidence / (name + '.body.ll'), evidence / 'runtime.c', '-o', evidence / name],
            name + '.link')
    capture([evidence / name], name + '.stdout')
    assert (evidence / (name + '.stdout')).read_bytes() == source.with_suffix('.out').read_bytes()
    assert not (evidence / (name + '.stdout.log')).read_bytes(), 'unexpected runtime stderr'
    results.append({'fixture': name, 'globals': len(definitions), 'run': 'passed'})
    print('PASS split global module: ' + name, flush=True)
(evidence / 'results.json').write_text(json.dumps(results, indent=2) + '\n')
