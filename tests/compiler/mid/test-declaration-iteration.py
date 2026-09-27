#!/usr/bin/env python3
"""Check closed iteration declarations without executable body discovery."""
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
fixtures = Path(__file__).resolve().parents[2] / 'fixtures'
cases = []
for name in ('unused_for_not_iterable', 'unused_for_float_range',
             'unused_for_call_not_iterable', 'unused_for_generic_call_not_iterable',
             'unused_for_unbound_parameter', 'unused_for_unrelated_bound', 'unused_for_async_result', 'unused_for_static_result', 'unused_for_closure_result', 'unused_for_existential_result'):
    source = (fixtures / 'reject' / (name + '.pw')).read_text()
    expected = (fixtures / 'reject' / (name + '.err')).read_text().strip()
    cases.append((name, source, expected))
    if 'fn unused(' in source:
        cases.append((name + '-generic', source.replace('fn unused(', 'fn unused[Extra](', 1), expected))
for name in ('iter_for_map', 'range_custom_step_arc', 'any_iterator', 'for_call_ref_array',
             'range_literal_context', 'temp_for_iterable_deinit', 'for_record_destructure_arc'):
    source = (fixtures / 'run' / (name + '.pw')).read_text()
    cases.append((name, source, 'ok'))
    cases.append((name + '-unused', source.replace('fn main()', 'fn unused[T]()') + '\nfn main() {}\n', 'ok'))
cases.append(('generic-producer', 'fn identity[T](item: T) -> T { return item }\nfn unused() { for val item in identity(item: [1I64, 2I64]) { item } }\nfn main() {}\n', 'ok'))
cases.append(('method-producer', 'struct Source { val items: Array[I64] }\nimpl Source { factory fn values() -> Array[I64] { return self.items } }\nfn unused() { val source = <Source items=[1I64] /> for val item in source.values() { item } }\nfn main() {}\n', 'ok'))
for name, declaration, call in (
    ('static-array-result', 'trait Maker { fn make() -> Array[I64] }\nfn unused[T](item: T) where T: Maker', 'item.make()'),
    ('closure-array-result', 'fn unused(producer: fn() -> Array[I64])', 'producer()'),
    ('existential-array-result', 'trait Maker { fn make() -> Array[I64] }\nfn unused(item: any Maker)', 'item.make()'),
):
    cases.append((name, declaration + ' { for val value in ' + call + ' { value } }\nfn main() {}\n', 'ok'))
cases.append(('async-promise-value', 'async fn produce() -> Promise[I64] { return 1I64 }\nfn unused() { val value = produce() }\nfn main() {}\n', 'ok'))
for name, prefix, bound in (
    ('iterable-bound', 'import @Std/Core with { Iterable }\n', 'Iterable'),
    ('iterator-bound', 'import @Std/Core with { Iterator }\n', 'Iterator'),
    ('supertrait-bound', 'import @Std/Core with { Iterator }\ntrait Cursor: Iterator {}\n', 'Cursor'),
):
    cases.append((name, prefix + 'fn unused[T](item: T) where T: ' + bound + ' { for val value in item { value } }\nfn main() {}\n', 'ok'))
rows = []
for name, source, expected in cases:
    path = args.out / (name + '.pw')
    path.write_text(source)
    result = subprocess.run([str(args.probe.resolve()), str(path.resolve()), str(args.std.resolve()) + '/'],
                            capture_output=True, text=True, timeout=60)
    passed = result.returncode == 0 and not result.stderr and result.stdout.strip() == expected
    rows.append(dict(case=name, passed=passed, exit=result.returncode,
                     stdout=result.stdout, stderr=result.stderr, expected=expected))
    print(('PASS ' if passed else 'FAIL ') + name, flush=True)
(args.out / 'results.json').write_text(json.dumps(dict(
    probe_sha256=hashlib.sha256(args.probe.read_bytes()).hexdigest(), cases=rows), indent=2))
if not all(row['passed'] for row in rows):
    raise SystemExit(1)
