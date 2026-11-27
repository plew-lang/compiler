#!/usr/bin/env python3
"""Manual named/requirement parameter-group controls, independent of body demand."""
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
cases = {
    'FreeLabelled': (False, 'pub fn bad(value: I64, value: I64) {}\n'),
    'FreeSuppressed': (False, 'pub fn bad(value~: I64, value~: I64) {}\n'),
    'FreeMixed': (False, 'pub fn bad(value: I64, value~: I64) {}\n'),
    'Generic': (False, 'pub fn bad[T](value: I64, value: I64) {}\n'),
    'Default': (False, 'pub fn bad(value: I64 = 1I64, value: I64 = 2I64) {}\n'),
    'Method': (False, 'pub struct Box {}\npub impl Box { fn bad(value: I64, value: I64) {} }\n'),
    'Associated': (False, 'pub struct Box {}\npub impl Box { assoc fn bad(value: I64, value: I64) {} }\n'),
    'Factory': (False, 'pub struct Box {}\npub impl Box { factory(value: I64, value: I64) { return <Box /> } }\n'),
    'Provided': (False, 'pub trait P {}\npub impl P { fn bad(value: I64, value: I64) {} }\n'),
    'Requirement': (False, 'pub trait P { fn bad(value: I64, value: I64) }\n'),
    'RequirementSuppressed': (False, 'pub trait P { fn bad(value~: I64, value~: I64) }\n'),
    'ExternSuppressed': (False, 'extern(c) { fn bad(value~: I64, value~: I64) }\n'),
    'DistinctLabelled': (True, 'pub fn good(first: I64, second: I64) {}\n'),
    'DistinctSuppressed': (True, 'pub fn good(first~: I64, second~: I64) {}\n'),
    'DistinctMixed': (True, 'pub fn good(first: I64, second~: I64) {}\n'),
    'DistinctRequirement': (True, 'pub trait P { fn good(first: I64, second: I64) }\n'),
    'DistinctExtern': (True, 'extern(c) { fn good(first~: I64, second~: I64) }\n'),
    'DistinctDefault': (True, 'pub fn good(first: I64 = 1I64, second: I64 = 2I64) {}\n'),
    'BodyShadow': (True, 'pub fn good(value: I64) -> I64 {\nval value = 22I64\nreturn value\n}\n'),
}

def sha(path):
    return hashlib.sha256(path.read_bytes()).hexdigest()

inputs = {str(p): sha(p) for p in [carrier, Path(__file__), ROOT / 'Plew.toml', ROOT / 'Plew.lock', *carrier.with_name('std').rglob('*.pw')]}
rows = []
for kind, (accepted, definition) in cases.items():
    for imported in (False, True):
        name = kind + ('Imported' if imported else 'Local')
        directory = out / name
        directory.mkdir()
        (directory / 'Main.pw').write_text(('use ./Dep\n' if imported else definition) + 'fn main() {}\n')
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
