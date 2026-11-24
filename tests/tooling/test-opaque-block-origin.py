#!/usr/bin/env python3
"""Opaque numeric block construction keeps source ownership and lazy demand."""
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
    rows, errors = [], []
    programs = {
        'integer': 'fn bad[T]() -> T { return { give 1 } }',
        'float': 'fn bad[T]() -> T { return { give 1.5 } }',
        'nested': 'fn bad[T]() -> T { return { give { give 1 } } }',
    }
    for name, body in programs.items():
        for demanded in (False, True):
            source = out / (name + ('-used' if demanded else '-unused') + '.pw')
            source.write_text(body + '\nfn main() { ' + ('val value: I64 = bad()' if demanded else '') + ' }\n')
            for mode, flags in [('check', ['--check']), ('aot', []), ('orc', ['--run'])]:
                label = source.stem + '-' + mode
                result = run_compiler([str(args.compiler.resolve()), *flags, str(source)],
                                      capture_output=True, timeout=60, cwd=ROOT)
                (out / (label + '.stdout')).write_bytes(result.stdout)
                (out / (label + '.stderr')).write_bytes(result.stderr)
                rejected = demanded or mode != 'orc'
                rows.append({'case': label, 'expected_rejection': rejected, **result.record()})
                if rejected:
                    if (result.returncode != 1 or result.channel != 'complete'
                            or result.failure_domain != 'source'
                            or b'cannot assign a literal to a type parameter' not in result.stderr):
                        errors.append(label + ': expected owned opaque numeric refusal')
                elif result.returncode != 0 or result.stderr or result.stdout or result.failure_domain is not None:
                    errors.append(label + ': unused body was checked')
    source = out / 'context.pw'
    source.write_text('fn identity[T](value: T) -> T { return { give value } }\nfn main() { val value: I64 = { give 1 } val copied = identity(value: value) }\n')
    for mode, flags in [('check', ['--check']), ('aot', []), ('orc', ['--run'])]:
        result = run_compiler([str(args.compiler.resolve()), *flags, str(source)],
                              capture_output=True, timeout=60, cwd=ROOT)
        rows.append({'case': 'context-' + mode, **result.record()})
        (out / ('context-' + mode + '.stderr')).write_bytes(result.stderr)
        if result.returncode != 0 or (mode != 'aot' and result.stdout) or result.failure_domain is not None:
            errors.append('context-' + mode + ': valid numeric context changed')
    (out / 'result.json').write_text(json.dumps({'cases': rows, 'errors': errors}, indent=2) + '\n')
    for error in errors:
        print(error, file=sys.stderr)
    print(f'{len(rows)} opaque block controls; {len(errors)} unmet assertions')
    return int(bool(errors))


if __name__ == '__main__':
    sys.exit(main())
