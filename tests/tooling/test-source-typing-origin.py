#!/usr/bin/env python3
"""Owned unresolved-array refusals; preserve unused lazy bodies and typed arrays."""
import argparse
import json
from pathlib import Path
import sys

ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / 'scripts/support'))
from compiler_failure_result import run_compiler


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--compiler', type=Path, required=True)
    parser.add_argument('--out', type=Path, required=True)
    args = parser.parse_args()
    out = args.out.resolve()
    out.mkdir(parents=True, exist_ok=False)
    cases = ['source_typing_empty_array', 'source_typing_empty_array_wrapped',
             'source_typing_nested_array', 'source_typing_discarded_empty_array',
             'source_typing_global_empty_array']
    rows, errors = [], []
    for name in cases:
        fixture = ROOT / 'tests/fixtures/reject' / (name + '.pw')
        for mode, flags in [('check', ['--check']), ('aot', []), ('orc', ['--run'])]:
            label = name + '-' + mode
            result = run_compiler([str(args.compiler.resolve()), *flags, str(fixture)],
                                  capture_output=True, timeout=60, cwd=ROOT)
            (out / (label + '.stdout')).write_bytes(result.stdout)
            (out / (label + '.stderr')).write_bytes(result.stderr)
            rejected = mode != 'orc' or name == 'source_typing_global_empty_array'
            rows.append({'case': name, 'mode': mode, 'expected_rejection': rejected,
                         **result.record()})
            if rejected:
                if (result.returncode != 1 or result.channel != 'complete'
                        or result.failure_domain != 'source'
                        or b"cannot infer this expression's type" not in result.stderr):
                    errors.append(label + ': expected owned source typing refusal')
            elif result.returncode != 0 or result.stderr or result.stdout or result.failure_domain is not None:
                errors.append(label + ': unused lazy body was inspected')
    for name in ['empty_array_overload_context', 'generic_empty_array_arg', 'source_typing_context_closure']:
        fixture = ROOT / 'tests/fixtures/run' / (name + '.pw')
        result = run_compiler([str(args.compiler.resolve()), '--run', str(fixture)],
                              capture_output=True, timeout=60, cwd=ROOT)
        rows.append({'case': name, 'mode': 'orc', **result.record()})
        (out / (name + '.stdout')).write_bytes(result.stdout)
        (out / (name + '.stderr')).write_bytes(result.stderr)
        if result.returncode != 0 or result.stderr or result.stdout != fixture.with_suffix('.out').read_bytes() or result.failure_domain is not None:
            errors.append(name + ': typed-array control changed')
    (out / 'result.json').write_text(json.dumps({'cases': rows, 'errors': errors}, indent=2) + '\n')
    for error in errors:
        print(error, file=sys.stderr)
    print(f'{len(rows)} source typing controls; {len(errors)} unmet assertions')
    return 1 if errors else 0


if __name__ == '__main__':
    sys.exit(main())
