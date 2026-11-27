#!/usr/bin/env python3
"""Manual missing projection-member admission and deferred body controls."""
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
preamble = ('pub trait Parser { type Output }\n'
            'pub struct P {}\n'
            'pub impl P as Parser { type Output = I64 }\n')
cases = {
 'Parameter': (False, preamble + 'pub fn entry(value: P#Parser.Missing) {}\n'),
 'Result': (False, preamble + 'pub fn entry() -> P#Parser.Missing { panic("not called") }\n'),
 'Field': (False, preamble + 'pub struct Holder { val value: P#Parser.Missing }\n'),
 'Nested': (False, preamble + 'pub fn entry(value: Optional[P#Parser.Missing]) {}\n'),
 'BodyUsed': (False, preamble + 'pub fn entry() { val value: Optional[P#Parser.Missing] = <Optional.None /> }\n'),
 'BodyUnused': ({'check': False, 'aot': False, 'orc': True}, preamble + 'pub fn unused() { val value: Optional[P#Parser.Missing] = <Optional.None /> }\n'),
 'ValidParameter': (True, preamble + 'pub fn entry(value: P#Parser.Output) {}\n'),
 'BodyDistinct': (True, preamble + 'pub fn entry() { val value: Optional[P#Parser.Output] = <Optional.None /> }\n'),
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
            passed = (result.returncode == 0 and (mode != 'orc' or result.stdout == b'')) if mode_accepted else (result.returncode == 1 and result.record()['failure_domain'] == 'source' and b'associated-type projection names an associated type that is not bound by the selected conformance' in result.stderr)
            rows.append({'case': name, 'mode': mode, 'expected_accept': mode_accepted, 'pass': passed, **result.record(), 'stderr': result.stderr.decode()})
unchanged = all(sha(Path(path)) == value for path, value in inputs.items())
(out / 'result.json').write_text(json.dumps({'inputs': inputs, 'inputs_unchanged': unchanged, 'cases': rows}, indent=2) + '\n')
print({'cases': len(rows), 'pass': sum(row['pass'] for row in rows), 'fail': sum(not row['pass'] for row in rows), 'inputs_unchanged': unchanged, 'failed_cases': sorted({row['case'] for row in rows if not row['pass']})})
if not unchanged or not all(row['pass'] for row in rows):
    sys.exit(1)
