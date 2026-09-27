#!/usr/bin/env python3
"""Exercise a freshly built DeclarationAccess.pw probe; no compiler promotion."""
import argparse
import hashlib
import json
from pathlib import Path
import subprocess

parser = argparse.ArgumentParser()
parser.add_argument('--probe', type=Path, required=True)
parser.add_argument('--std', type=Path, required=True)
parser.add_argument('--out', type=Path, required=True)
args = parser.parse_args()
args.out.mkdir(parents=True, exist_ok=False)
source = Path(__file__).with_name('DeclarationAccessInput.pw').read_text()
returned = source.replace('fn update(destination: inout I64) {',
                          'fn update(destination: inout I64) -> Observer {')
returned = returned.replace('    destination += 1I64\n',
                            '    destination += 1I64\n    return move observer\n')
returned = returned.replace('    update(destination: inout value)',
                            '    val result = update(destination: inout value)')
transitive = source.replace('fn unused[T]() {',
    'fn relay(destination: inout I64) { update(destination: inout destination) }\nfn unused[T]() {')
transitive = transitive.replace('    update(destination: inout value)',
                                '    relay(destination: inout value)')
nested = source.replace('fn update(destination: inout I64) {',
    'unique struct Owner { val observer: Observer }\npub impl Owner { factory }\nfn update(destination: inout I64) {')
nested = nested.replace('val observer = <Observer unused=0I64 />',
                         'val owner = <Owner observer=<Observer unused=0I64 /> />')
generic_owner = source.replace('unique struct Observer {', 'unique struct Observer[T] {')
generic_owner = generic_owner.replace('pub val unused: I64', 'pub val unused: T')
generic_owner = generic_owner.replace('pub impl Observer {', 'pub impl Observer[T] {')
generic_owner = generic_owner.replace('<Observer unused=', '<Observer[I64] unused=')
cases = {
    'trait-requirement': (source + '\ntrait Reader { fn read() -> I64 }\nfn apply[T](item: T) -> I64 where T: Reader { return item.read() }\n', 'conflict'),
    'dynamic-call': (source + '\nfn apply(action: fn() -> I64) -> I64 { return action() }\n', 'conflict'),
    'closure-creation-only': (source.replace('val observer = <Observer unused=0I64 />', 'val action = fn() { print(value) }'), 'clear'),
    'nested-closure': (source.replace('fn unused[T]() {', 'fn unused() { val outer = fn() { val inner = fn() {').replace('    print(value)\n}', '    print(value)\n} } }'), 'conflict'),
    'unused-closure': (source.replace('fn unused[T]() {', 'fn unused() { val action = fn() {').replace('    print(value)\n}', '    print(value)\n} }'), 'conflict'),
    'global-initializer': (source[:source.index('fn unused[T]()')].replace('fn update(destination: inout I64) {', 'fn update(destination: inout I64) -> I64 {').replace('    destination += 1I64\n', '    destination += 1I64\n    return 0I64\n') + '\nval initialized = update(destination: inout value)\nfn main() {}\n', 'conflict'),
    'generic-unused': (source, 'conflict'),
    'ordinary-unused': (source.replace('fn unused[T]()', 'fn unused()'), 'conflict'),
    'disjoint': (source.replace('mut val value = 7I64',
        'mut val value = 7I64\nmut val other = 0I64').replace(
        'update(destination: inout value)', 'update(destination: inout other)'), 'clear'),
    'returned-owner': (returned, 'clear'),
    'transitive': (transitive, 'conflict'),
    'nested-owner': (nested, 'conflict'),
    'generic-owner': (generic_owner, 'conflict'),
}
results = []
for name, (text, expected) in cases.items():
    path = args.out / (name + '.pw')
    path.write_text(text)
    result = subprocess.run([str(args.probe.resolve()), str(path.resolve()),
                             str(args.std.resolve()) + '/'],
                            capture_output=True, text=True, timeout=50)
    passed = (result.returncode == 0 and result.stdout == expected + '\npending\n'
              and not result.stderr)
    results.append(dict(case=name, expected=expected, exit=result.returncode,
                        stdout=result.stdout, stderr=result.stderr, passed=passed))
    print(('PASS' if passed else 'FAIL') + ' ' + name, flush=True)
report = dict(probe_sha256=hashlib.sha256(args.probe.read_bytes()).hexdigest(),
              cases=results)
(args.out / 'results.json').write_text(json.dumps(report, indent=2))
if not all(row['passed'] for row in results):
    raise SystemExit(1)
