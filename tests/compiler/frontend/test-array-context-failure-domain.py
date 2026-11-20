#!/usr/bin/env python3
"""Owned array-context rejection controls; raw API provenance has a separate native gate."""
import argparse
import hashlib
import json
from pathlib import Path
import sys

COMPILER = Path(__file__).resolve().parents[3]
sys.path.insert(0, str(COMPILER / 'scripts/support'))
from compiler_failure_result import run_compiler

MESSAGE = b"cannot infer an empty array's element type from a non-array context (spec/02)"
REJECT = {
    'record-field': 'fn main() { val record: (value: I64) = (value: []) }',
    'default-expanded-field': 'struct InvalidDefaultSlot { val value: I64 = [] }\nfn main() { val value = <InvalidDefaultSlot /> }',
    'explicit-closure-return': 'fn main() { val closure = fn() -> I64 { { return [] } } }',
    'contextual-closure-return': 'fn main() { val closure: fn() -> I64 = fn() { { return [] } } }',
    'failed-call-closure-return': 'fn accept(callback: fn() -> I64, other: I64) {}\nfn main() { accept(callback: fn() { { return [] } }, other: false) }',
    'nested-element': 'fn main() { val values: Array[I64] = [[]] }',
    'custom-index': 'use @Std/Core only { Index }\nstruct Grid {}\nimpl Grid as Index[I64] { type Output = I64 fn index(key: I64) -> I64 { return 0I64 } }\nfn main() { val grid = <Grid /> val value = grid[[]] }',
    'named-factory': 'struct Number { val value: I64 }\nimpl Number { factory named(value: I64) { return <Number value=value /> } }\nfn main() { val value = <Number.named value=[] /> }',
    'annotation': 'fn main() { val value: I64 = [] }',
    'return': 'fn value() -> I64 { return [] }\nfn main() { value() }',
    'block': 'fn main() { val value: I64 = { give [] } }',
    'default': 'fn value(input: I64 = []) {}\nfn main() { value() }',
    'failed-call': 'fn value(input: I64) {}\nfn main() { value(input: []) }',
    'explicit-field': 'struct Shelf[T] { val value: T }\nfn main() { val shelf = <Shelf[I64] value=[] /> }',
    'rigid-field': 'struct Shelf[T] { val value: T }\nfn build[T](seed: T) { val shelf = <Shelf[T] value=[] /> }\nfn main() { build(seed: 1I64) }',
    'outer-field': 'struct Shelf[T] { val value: T }\nfn main() { val shelf: Shelf[I64] = <Shelf value=[] /> }',
}
ACCEPT = {
    'inferred-record': 'fn main() { val record = (value: 1I64) }',
    'contextual-record': 'fn main() { val record: (value: I64) = (value: 1I64) }',
    'zero-field': 'struct EmptySlot {}\nfn main() { val value = <EmptySlot /> }',
    'empty-record': 'fn main() { val value: () = () }',
    'generic-zero-explicit': 'struct EmptySlot[T] {}\nfn main() { val value = <EmptySlot[I64] /> }',
    'generic-zero-outer': 'struct EmptySlot[T] {}\nfn main() { val value: EmptySlot[I64] = <EmptySlot /> }',
    'payloadless-enum': 'enum EmptyChoice[T] { Empty Value(value: T) }\nfn main() { val value = <EmptyChoice[I64].Empty /> }',
    'default-expanded-valid': 'struct DefaultSlot { val value: I64 = 1I64 }\nfn main() { val value = <DefaultSlot /> }',
    'nonempty-array': 'fn main() { val values: Array[I64] = [1I64] }',
    'annotation-array': 'fn main() { val value: Array[I64] = [] }',
    'explicit-array-field': 'struct Shelf[T] { val value: T }\nfn main() { val shelf = <Shelf[Array[I64]] value=[] /> }',
    'outer-array-field': 'struct Shelf[T] { val value: T }\nfn main() { val shelf: Shelf[Array[I64]] = <Shelf value=[] /> }',
}


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--carrier', required=True, type=Path)
    parser.add_argument('--output', required=True, type=Path)
    parser.add_argument('--modes', nargs='+', choices=('check', 'aot', 'orc'), default=['check'])
    args = parser.parse_args()
    carrier = args.carrier.resolve()
    output = args.output.resolve()
    output.mkdir(parents=True, exist_ok=True)
    rows = []
    # Success controls deliberately use check only: no machine-code output is
    # needed to prove that the context remains a valid Array context.
    for accepted, cases in ((False, REJECT), (True, ACCEPT)):
        for name, text in cases.items():
            source = output / (name + '.pw')
            source.write_text(text + '\n')
            for mode in (['check'] if accepted else args.modes):
                flags = {'check': ['--check'], 'aot': [], 'orc': ['--run']}[mode]
                result = run_compiler([str(carrier), *flags, str(source)], cwd=COMPILER,
                                      capture_output=True, timeout=60)
                expected = (result.returncode == 0 and result.stdout == b'') if accepted else (
                    result.source_rejection and result.stdout == b'' and MESSAGE in result.stderr)
                # A different error is not a RED for this diagnostic family.
                target = accepted or (result.returncode == 1 and MESSAGE in result.stderr)
                rows.append({'case': name, 'mode': mode, 'accepted_control': accepted,
                             'source_sha256': hashlib.sha256(source.read_bytes()).hexdigest(),
                             **result.record(), 'passed': expected, 'target_reached': target,
                             'stderr': result.stderr.decode(errors='replace')})
    receipt = {'carrier': str(carrier), 'carrier_sha256': hashlib.sha256(carrier.read_bytes()).hexdigest(),
               'rows': rows, 'failed': sum(not row['passed'] for row in rows)}
    (output / 'result.json').write_text(json.dumps(receipt, indent=2) + '\n')
    print(f"array context: {len(rows) - receipt['failed']} passed, {receipt['failed']} failed; "
          f"off-target {sum(not row['target_reached'] for row in rows)}")
    return 1 if receipt['failed'] else 0


if __name__ == '__main__':
    sys.exit(main())
