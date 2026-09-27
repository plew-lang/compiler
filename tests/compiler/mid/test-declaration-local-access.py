#!/usr/bin/env python3
"""Compare demand-selected local access checks with conservative whole-body checks."""
import argparse
import hashlib
import json
from pathlib import Path
import re
import subprocess

parser = argparse.ArgumentParser()
parser.add_argument('--probe', type=Path, required=True)
parser.add_argument('--std', type=Path, required=True)
parser.add_argument('--out', type=Path, required=True)
args = parser.parse_args()
args.out.mkdir(parents=True, exist_ok=False)
fixtures = Path(__file__).resolve().parents[2] / 'fixtures'
cases = []
for path in sorted((fixtures / 'reject').glob('unused_*inout*.pw')):
    if not (path.stem.startswith('unused_borrow_') or path.stem.startswith('unused_receiver_')):
        continue
    expected = 1 if path.stem.startswith('unused_borrow_') else 2
    source = path.read_text()
    for generic in (False, True):
        replacement = 'fn unused[T]()' if generic else 'fn unused()'
        text = re.sub(r'fn unused(?:\[T\])?\(\)', replacement, source)
        cases.append((path.stem + ('-generic' if generic else '-ordinary'), text, expected))
for name in ('receiver_preparation', 'receiver_shared_access', 'generic_unique_argument_temporary',
             'unused_generic_bounds', 'global_access_try', 'generic_operator_output_projection',
             'mid_float_operand_context', 'operator_literal_nested', 'mid_operator_call_cfg_lowering'):
    source = (fixtures / 'run' / (name + '.pw')).read_text()
    cases.append((name, source, 0))
    cases.append((name + '-unused', source.replace('fn main()', 'fn uncalled[T]()') + '\nfn main() {}\n', 0))
source = (fixtures / 'reject' / 'unused_borrow_inout_argument.pw').read_text()
cases.append(('unused-closure', source.replace('fn unused() {', 'fn unused() { val action = fn() {')
              .replace('\nfn main() {}', '\n}\nfn main() {}'), 1))
rows = []
for name, source, expected in cases:
    path = args.out / (name + '.pw')
    path.write_text(source)
    result = subprocess.run([str(args.probe.resolve()), str(path.resolve()), str(args.std.resolve()) + '/'],
                            capture_output=True, text=True, timeout=45)
    lines = result.stdout.splitlines()
    counts = [int(line) for line in lines] if len(lines) == 3 and all(line.isdigit() for line in lines) else []
    passed = result.returncode == 0 and not result.stderr and len(counts) == 3 and counts[0] == expected
    rows.append(dict(case=name, expected=expected, passed=passed, exit=result.returncode,
                     stdout=result.stdout, stderr=result.stderr))
    print(('PASS ' if passed else 'FAIL ') + name, flush=True)
report = dict(probe_sha256=hashlib.sha256(args.probe.read_bytes()).hexdigest(), cases=rows)
(args.out / 'results.json').write_text(json.dumps(report, indent=2))
if not rows or not all(row['passed'] for row in rows):
    raise SystemExit(1)
