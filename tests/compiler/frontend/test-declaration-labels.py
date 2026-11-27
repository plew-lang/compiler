#!/usr/bin/env python3
"""Manual declaration admission controls against an explicitly selected carrier."""
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
    'StructField': (False, 'pub struct Bad { pub val value: I64 pub val value: I64 }\n', 'duplicate field name'),
    'VariantField': (False, 'pub enum Bad { V(value: I64, value: I64) }\n', 'duplicate field name'),
    'VariantName': (False, 'pub enum Bad { V V }\n', 'duplicate enum variant name'),
    'DistinctFields': (True, 'pub struct Good { pub val first: I64 pub val second: I64 }\n', ''),
    'SeparateVariants': (True, 'pub enum Good { First(value: I64) Second(value: I64) }\n', ''),
    'SeparateTypes': (True, 'pub struct First { pub val value: I64 }\npub struct Second { pub val value: I64 }\n', ''),
    'GenericFields': (True, 'pub struct Good[T] { pub val first: T pub val second: T }\n', ''),
    'GenericDuplicate': (False, 'pub struct Bad[T] { pub val value: T pub val value: T }\n', 'duplicate field name'),
}

def sha(path):
    return hashlib.sha256(path.read_bytes()).hexdigest()

inputs = {str(p): sha(p) for p in [carrier, Path(__file__), ROOT / 'Plew.toml', ROOT / 'Plew.lock', *carrier.with_name('std').rglob('*.pw')]}
rows = []
for kind, (accepted, definition, reason) in cases.items():
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
            passed = (result.returncode == 0 and (mode != 'orc' or result.stdout == b'')) if accepted else (result.returncode == 1 and result.record()['failure_domain'] == 'source' and reason.encode() in result.stderr)
            rows.append({'case': name, 'mode': mode, 'expected_accept': accepted, 'pass': passed, **result.record(), 'stderr': result.stderr.decode()})
unchanged = all(sha(Path(path)) == value for path, value in inputs.items())
(out / 'result.json').write_text(json.dumps({'inputs': inputs, 'inputs_unchanged': unchanged, 'cases': rows}, indent=2) + '\n')
print({'cases': len(rows), 'pass': sum(row['pass'] for row in rows), 'fail': sum(not row['pass'] for row in rows), 'inputs_unchanged': unchanged, 'failed_cases': sorted({row['case'] for row in rows if not row['pass']})})
if not unchanged or not all(row['pass'] for row in rows):
    sys.exit(1)
