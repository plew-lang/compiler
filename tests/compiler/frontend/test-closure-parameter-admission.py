#!/usr/bin/env python3
"""Manual closure parameter admission and shadowing controls."""
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
cases = {'LabelledCalled': (False,
                    'pub fn entry() {\n'
                    'val callback = fn(value: I64, value: I64) -> I64 { return value }\n'
                    'val result = callback(value: 11I64, value: 22I64)\n'
                    '}\n'),
 'SuppressedCalled': (False,
                      'pub fn entry() {\n'
                      'val callback = fn(value~: I64, value~: I64) -> I64 { return value }\n'
                      'val result = callback(11I64, 22I64)\n'
                      '}\n'),
 'MixedUnusedCreated': (False,
                        'pub fn entry() {\n'
                        'val callback = fn(value: I64, value~: I64) -> I64 { return value }\n'
                        '}\n'),
 'DifferentTypes': (False,
                    'pub fn entry() {\n'
                    'val callback = fn(value~: I64, value~: Bool) -> Bool { return value }\n'
                    '}\n'),
 'Wrapped': (False,
             'pub fn entry() {\n'
             'val callback = { give fn(value~: I64, value~: I64) -> I64 { return value } }\n'
             '}\n'),
 'Contextual': (True,
                'pub fn entry() {\n'
                'val callback: fn(first: I64, second: I64) -> I64 = fn(first, second) { return '
                'first + second }\n'
                'if callback(first: 11I64, second: 22I64) != 33I64 { panic("context changed") }\n'
                '}\n'),
 'Distinct': (True,
              'pub fn entry() {\n'
              'val callback = fn(first~: I64, second~: I64) -> I64 { return first + second }\n'
              'if callback(11I64, 22I64) != 33I64 { panic("wrong parameters") }\n'
              '}\n'),
 'OuterShadow': (True,
                 'pub fn entry() {\n'
                 'val value = 11I64\n'
                 'val callback = fn(value: I64) -> I64 { return value }\n'
                 'if callback(value: 22I64) != 22I64 || value != 11I64 { panic("outer shadow '
                 'changed") }\n'
                 '}\n'),
 'SequentialShadow': (True,
                      'pub fn entry() {\n'
                      'val value = 11I64\n'
                      'val value = 22I64\n'
                      'if value != 22I64 { panic("sequential shadow changed") }\n'
                      '}\n'),
 'GlobalInitializer': (False,
                       'val callback = fn(value~: I64, value~: I64) -> I64 { return value }\n'
                       'pub fn entry() {}\n'),
 'ParameterDefault': (False,
                      'pub fn entry(callback: fn(I64, I64) -> I64 = fn(value~: I64, value~: I64) '
                      '-> I64 { return value }) {}\n'),
 'WrappedParameterDefault': (False,
                             'pub fn entry(callback: fn(I64, I64) -> I64 = { give fn(value~: I64, '
                             'value~: I64) -> I64 { return value } }) {}\n'),
 'FieldDefault': (False,
                  'struct Holder { val callback: fn(I64, I64) -> I64 = fn(value~: I64, value~: '
                  'I64) -> I64 { return value } }\n'
                  'pub fn entry() { val holder = <Holder /> }\n'),
 'WrappedFieldDefault': (False,
                         'struct Holder { val callback: fn(I64, I64) -> I64 = { give fn(value~: '
                         'I64, value~: I64) -> I64 { return value } } }\n'
                         'pub fn entry() { val holder = <Holder /> }\n'),
 'Provided': (False,
              'trait P {}\n'
              'struct Holder {}\n'
              'pub impl P { fn invoke() { val callback = fn(value~: I64, value~: I64) -> I64 { '
              'return value } } }\n'
              'impl Holder as P {}\n'
              'pub fn entry() { val holder = <Holder />\n'
              'holder.invoke() }\n'),
 'Generic': (False,
             'fn helper[T](value: T) { val callback = fn(value~: I64, value~: I64) -> I64 { return '
             'value } }\n'
             'pub fn entry() { helper(value: 1I64) }\n')}

def sha(path):
    return hashlib.sha256(path.read_bytes()).hexdigest()

inputs = {str(p): sha(p) for p in [carrier, Path(__file__), ROOT / 'Plew.toml', ROOT / 'Plew.lock', *carrier.with_name('std').rglob('*.pw')]}
rows = []
for kind, (accepted, definition) in cases.items():
    for imported in (False, True):
        name = kind + ('Imported' if imported else 'Local')
        directory = out / name
        directory.mkdir()
        (directory / 'Main.pw').write_text(('use ./Dep only { entry }\n' if imported else definition) + 'fn main() { entry() }\n')
        if imported:
            (directory / 'Dep.pw').write_text(definition)
        for path in directory.glob('*.pw'):
            inputs[str(path)] = sha(path)
        for mode, flags in [('check', ['--check']), ('aot', []), ('orc', ['--run'])]:
            result = run_compiler([str(carrier), *flags, str(directory / 'Main.pw')], capture_output=True, timeout=60, cwd=ROOT)
            (directory / (mode + '.stdout')).write_bytes(result.stdout)
            (directory / (mode + '.stderr')).write_bytes(result.stderr)
            passed = (result.returncode == 0 and (mode != 'orc' or result.stdout == b'')) if accepted else (result.returncode == 1 and result.record()['failure_domain'] == 'source' and b'duplicate parameter binding name' in result.stderr)
            rows.append({'case': name, 'mode': mode, 'expected_accept': accepted, 'pass': passed, **result.record(), 'stderr': result.stderr.decode()})
unchanged = all(sha(Path(path)) == value for path, value in inputs.items())
(out / 'result.json').write_text(json.dumps({'inputs': inputs, 'inputs_unchanged': unchanged, 'cases': rows}, indent=2) + '\n')
print({'cases': len(rows), 'pass': sum(row['pass'] for row in rows), 'fail': sum(not row['pass'] for row in rows), 'inputs_unchanged': unchanged, 'failed_cases': sorted({row['case'] for row in rows if not row['pass']})})
if not unchanged or not all(row['pass'] for row in rows):
    sys.exit(1)
