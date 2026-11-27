#!/usr/bin/env python3
"""Manual function-type label admission and deferred body controls."""
from pathlib import Path
import argparse
import hashlib
import json
import sys

ROOT = Path(__file__).resolve().parents[3]
sys.path.insert(0, str(ROOT / 'scripts/support'))
from compiler_failure_result import run_compiler

parser = argparse.ArgumentParser()
parser.add_argument('--carrier', type=Path, required=True)
parser.add_argument('--out', type=Path, required=True)
args = parser.parse_args()
carrier = args.carrier.resolve()
out = args.out.resolve()
out.mkdir(exist_ok=False)
cases = {'Parameter': (False, 'pub fn entry(callback: fn(value: I64, value: I64) -> I64) {}\n'),
 'Result': (False, 'pub fn entry() -> fn(value: I64, value: I64) -> I64 { panic("not called") }\n'),
 'Field': (False, 'pub struct Holder { val callback: fn(value: I64, value: I64) -> I64 }\n'),
 'Nested': (False, 'pub fn entry(callback: Optional[fn(value: I64, value: I64) -> I64]) {}\n'),
 'Requirement': (False, 'pub trait P { fn entry(callback: fn(value: I64, value: I64) -> I64) }\n'),
 'Associated': (False,
                'trait P { type Item }\n'
                'struct Holder {}\n'
                'impl Holder as P { type Item = fn(value: I64, value: I64) -> I64 }\n'),
 'Diverging': (False, 'pub fn entry(callback: diverge fn(value: I64, value: I64)) {}\n'),
 'BodyUsed': (False,
              'pub fn entry() { val callback: Optional[fn(value: I64, value: I64) -> I64] = '
              '<Optional.None /> }\n'),
 'BodyUnused': ({'check': False, 'aot': False, 'orc': True},
                'pub fn unused() { val callback: Optional[fn(value: I64, value: I64) -> I64] = '
                '<Optional.None /> }\n'),
 'Distinct': (True, 'pub fn entry(callback: fn(first: I64, second: I64) -> I64) {}\n'),
 'Unlabelled': (True, 'pub fn entry(callback: fn(I64, I64) -> I64) {}\n'),
 'Mixed': (True, 'pub fn entry(callback: fn(value: I64, I64) -> I64) {}\n'),
 'DivergingDistinct': (True, 'pub fn entry(callback: diverge fn(first: I64, second: I64)) {}\n'),
 'BodyDistinct': (True,
                  'pub fn entry() { val callback: Optional[fn(first: I64, second: I64) -> I64] = '
                  '<Optional.None /> }\n')}

def sha(path):
    return hashlib.sha256(path.read_bytes()).hexdigest()

inputs = {str(p): sha(p) for p in [carrier, Path(__file__), ROOT / 'Plew.toml', ROOT / 'Plew.lock', *carrier.with_name('std').rglob('*.pw')]}
rows = []
for kind, (accepted, definition) in cases.items():
    for imported in (False, True):
        name = kind + ('Imported' if imported else 'Local')
        directory = out / name
        directory.mkdir()
        (directory / 'Main.pw').write_text(('use ./Dep only { entry }\n' if imported and kind in ('BodyUsed', 'BodyDistinct') else 'use ./Dep\n' if imported else definition) + ('fn main() { entry() }\n' if kind in ('BodyUsed', 'BodyDistinct') else 'fn main() {}\n'))
        if imported:
            (directory / 'Dep.pw').write_text(definition)
        for path in directory.glob('*.pw'):
            inputs[str(path)] = sha(path)
        for mode, flags in [('check', ['--check']), ('aot', []), ('orc', ['--run'])]:
            result = run_compiler([str(carrier), *flags, str(directory / 'Main.pw')], capture_output=True, timeout=60, cwd=ROOT)
            (directory / (mode + '.stdout')).write_bytes(result.stdout)
            (directory / (mode + '.stderr')).write_bytes(result.stderr)
            mode_accepted = accepted[mode] if isinstance(accepted, dict) else accepted
            passed = (result.returncode == 0 and (mode != 'orc' or result.stdout == b'')) if mode_accepted else (result.returncode == 1 and result.record()['failure_domain'] == 'source' and b'duplicate function type parameter label' in result.stderr)
            rows.append({'case': name, 'mode': mode, 'expected_accept': mode_accepted, 'pass': passed, **result.record(), 'stderr': result.stderr.decode()})
unchanged = all(sha(Path(path)) == value for path, value in inputs.items())
(out / 'result.json').write_text(json.dumps({'inputs': inputs, 'inputs_unchanged': unchanged, 'cases': rows}, indent=2) + '\n')
print({'cases': len(rows), 'pass': sum(row['pass'] for row in rows), 'fail': sum(not row['pass'] for row in rows), 'inputs_unchanged': unchanged, 'failed_cases': sorted({row['case'] for row in rows if not row['pass']})})
if not unchanged or not all(row['pass'] for row in rows):
    sys.exit(1)
