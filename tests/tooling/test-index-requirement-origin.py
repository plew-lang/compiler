#!/usr/bin/env python3
"""Owned Index/IndexSet failed selections, not missing published rows."""
import argparse
import json
import hashlib
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
    errors, rows = [], []
    fingerprints = {}
    def retain(path):
        path = path.resolve()
        fingerprints[str(path)] = hashlib.sha256(path.read_bytes()).hexdigest()
    retain(args.compiler)
    retain(Path(__file__))
    cases = ['generic_index_no_bound', 'generic_index_requires_nominal_bound',
             'index_no_trait', 'index_requires_nominal_conformance',
             'index_set_requires_nominal_conformance']
    for name in cases:
        fixture = ROOT / 'tests/fixtures/reject' / (name + '.pw')
        retain(fixture)
        for mode, flags in [('check', ['--check']), ('aot', []), ('orc', ['--run'])]:
            result = run_compiler([str(args.compiler.resolve()), *flags, str(fixture)],
                                  capture_output=True, timeout=60, cwd=ROOT)
            label = name + '-' + mode
            (out / (label + '.stdout')).write_bytes(result.stdout)
            (out / (label + '.stderr')).write_bytes(result.stderr)
            rejected = mode != 'orc' or not name.startswith('generic_')
            rows.append({'case': name, 'mode': mode, 'expected_rejection': rejected,
                         **result.record()})
            if rejected:
                if (result.returncode != 1 or result.channel != 'complete'
                        or result.failure_domain != 'source'
                        or b'subscript requires an Index implementation' not in result.stderr):
                    errors.append(label + ': missing owned index requirement refusal')
            elif result.returncode != 0 or result.stdout or result.stderr or result.failure_domain is not None:
                errors.append(label + ': unused generic body was inspected')
    for name in ['generic_index_call_template', 'index_writeonly', 'operator_index']:
        fixture = ROOT / 'tests/fixtures/run' / (name + '.pw')
        retain(fixture)
        retain(fixture.with_suffix('.out'))
        result = run_compiler([str(args.compiler.resolve()), '--run', str(fixture)],
                              capture_output=True, timeout=60, cwd=ROOT)
        rows.append({'case': name, 'mode': 'orc', **result.record()})
        (out / (name + '.stdout')).write_bytes(result.stdout)
        (out / (name + '.stderr')).write_bytes(result.stderr)
        if result.returncode != 0 or result.stderr or result.failure_domain is not None or result.stdout != fixture.with_suffix('.out').read_bytes():
            errors.append(name + ': valid indexing control changed')
    unchanged = all(hashlib.sha256(Path(path).read_bytes()).hexdigest() == digest
                    for path, digest in fingerprints.items())
    if not unchanged:
        errors.append('compiler/test/fixture inputs changed during controls')
    (out / 'result.json').write_text(json.dumps({'cases': rows, 'errors': errors, 'inputs': fingerprints, 'inputs_unchanged': unchanged}, indent=2) + '\n')
    for error in errors:
        print(error, file=sys.stderr)
    print(f'{len(rows)} index requirement controls; {len(errors)} unmet assertions')
    return 1 if errors else 0


if __name__ == '__main__':
    sys.exit(main())
