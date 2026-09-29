#!/usr/bin/env python3
"""Manual native diagnostic: one global owner, separate executable module."""
import argparse
import json
import os
from pathlib import Path
import re
import subprocess

parser = argparse.ArgumentParser(description=__doc__)
parser.add_argument('--requested', action='store_true', help='split each executable body into its own module')
parser.add_argument('--synthetic', action='store_true', help='exercise closure environment drop and existential witness roots')
parser.add_argument('--exposed', action='store_true', help='exercise a C entry and its callee in separate modules')
options = parser.parse_args()
if options.synthetic or options.exposed:
    options.requested = True
root = Path(__file__).resolve().parents[3]
compiler = Path(os.environ.get('PLEWC', root / 'plewc')).absolute()
config = Path(os.environ.get('LLVM_CONFIG', '/opt/homebrew/opt/llvm/bin/llvm-config'))
bindir = Path(subprocess.check_output([str(config), '--bindir'], text=True).strip())
libdir = config.parent.parent / 'lib'
if not (libdir / 'libLLVM.dylib').exists():
    libdir = Path(subprocess.check_output([str(config), '--libdir'], text=True).strip())
evidence = root / ('tmp/lazy-build/synthetic-modules' if options.synthetic else 'tmp/lazy-build/global-modules')
if options.exposed:
    evidence = root / 'tmp/expose/requested-modules'
evidence.mkdir(parents=True, exist_ok=True)


def capture(command, name):
    with (evidence / name).open('wb') as out, (evidence / (name + '.log')).open('wb') as err:
        subprocess.run(list(map(str, command)), cwd=root, stdout=out, stderr=err,
                       timeout=60, check=True)


capture([compiler, root / 'tests/compiler/codegen/GlobalModules.pw'], 'harness.ll')
capture([compiler, '--runtime'], 'runtime.c')
capture([bindir / 'clang++', '-std=c++17', '-O1', '-isystem',
         subprocess.check_output([str(config), '--includedir'], text=True).strip(),
         '-c', root / 'native/llvm_backend.cpp', '-o', evidence / 'backend.o'], 'backend')
capture([bindir / 'clang', '-O0', evidence / 'harness.ll', evidence / 'runtime.c',
         evidence / 'backend.o', '-lc++', '-L' + str(libdir), '-lLLVM',
         '-o', evidence / 'harness'], 'harness.link')
print('PASS global module harness build', flush=True)
results = []
for name in ([] if options.requested else ['global_var', 'global_generic_init', 'global_forward_ref']):
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
if options.requested:
    source = evidence / 'Requested.pw'
    source.write_text('extern(c) { fn putchar(character~: I32) -> I32 }\nval initial: I32 = 65I32\nstruct Letter { val code: I32 }\nimpl Letter { fn get() -> I32 { return self.code } }\nfn read() -> I32 { return initial }\nfn forward() -> I32 { return read() }\nfn main() { val letter = <Letter code=forward() /> val ignored = putchar(letter.get()) }\n')
    if options.synthetic:
        source.write_text('extern(c) { fn putchar(character~: I32) -> I32 }\ntrait Code { fn get() -> I32 }\nstruct Letter { val code: I32 }\nimpl Letter as Code { fn get() -> I32 { return self.code } }\nfn captured(code: I32) -> fn() -> I32 { return fn() -> I32 { return code } }\nfn main() { val closure = captured(code: 65I32) val first = putchar(closure()) val letter: any Code = <Letter code=66I32 /> val second = putchar(letter.get()) }\n')
    if options.exposed:
        source.write_text('extern(c) { fn exerciseExposed() -> I32 }\nfn add(value~: I64) -> I64 { return value + 1I64 }\nexpose fn exposedIncrement(value~: I64) -> I64 { return add(value) }\nfn main() { if exerciseExposed() != 0I32 { panic \"C entry failed\" } }\n')
        (evidence / 'caller.c').write_text('#include <stdint.h>\nextern int64_t exposedIncrement(int64_t);\nint32_t exerciseExposed(void) { return exposedIncrement(41) == 42 ? 0 : 1; }\n')
    capture([evidence / 'harness', source, 'list', str(root / 'std') + '/'], 'requested.ids')
    ids = (evidence / 'requested.ids').read_text().split()
    if not options.synthetic and not options.exposed:
        assert len(ids) == 5, 'fixture covers initialization, main, two functions and one method'
    modules = []
    for mode, body in [('storage', '')] + [('requested', body) for body in ids]:
        name = mode + body
        capture([evidence / 'harness', source, mode, str(root / 'std') + '/', body], name + '.ll')
        module = evidence / (name + '.ll')
        modules.append(module)
        definitions = re.findall(r'^define(?! internal)[^\n]*@([^ (]+)', module.read_text(), re.M)
        expected = (1 if mode == 'requested' else 0)
        if options.exposed and 'exposedIncrement' in definitions:
            expected += 1
        assert len(definitions) == expected, (body, definitions)
        results.append({'body': body, 'definitions': definitions})
    extra_sources = [evidence / 'caller.c'] if options.exposed else []
    if options.exposed:
        assert sum(item['definitions'].count('exposedIncrement') for item in results) == 1
    capture([bindir / 'clang', '-O0', *modules, evidence / 'runtime.c', *extra_sources, '-o', evidence / 'requested-app'], 'requested.link')
    capture([evidence / 'requested-app'], 'requested.stdout')
    assert (evidence / 'requested.stdout').read_bytes() == (b'' if options.exposed else b'AB' if options.synthetic else b'A')
    assert not (evidence / 'requested.stdout.log').read_bytes()
    if options.synthetic:
        symbols = [symbol for item in results for symbol in item['definitions']]
        for prefix in ['__closure', 'pwclodrop', 'pfvt']:
            assert any(symbol.startswith('plew.body.' + prefix) for symbol in symbols), prefix
    print('PASS separately emitted bodies: ' + str(len(ids)), flush=True)
(evidence / ('requested-results.json' if options.requested else 'results.json')).write_text(json.dumps(results, indent=2) + '\n')
