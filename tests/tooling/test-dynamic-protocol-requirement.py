#!/usr/bin/env python3
"""Synthetic requirements cannot become ordinary dynamic field/interface calls."""
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
    rows, errors = [], []
    fingerprints = {}
    def retain(path):
        path = path.resolve()
        fingerprints[str(path)] = hashlib.sha256(path.read_bytes()).hexdigest()
    retain(args.compiler)
    retain(Path(__file__))
    negative = ['index_callable_field_no_trait', 'index_set_callable_field_no_trait',
                'index_existential_wrong_protocol', 'index_generic_wrong_protocol']
    positive = ['dynamic_protocol_field_calls', 'index_existential_requirement',
                'index_generic_inherited_requirement']
    for name in negative + positive:
        source = ROOT / 'tests/fixtures' / ('reject' if name in negative else 'run') / (name + '.pw')
        retain(source)
        if name in positive:
            retain(source.with_suffix('.out'))
        for mode, flags in [('check', ['--check']), ('aot', []), ('orc', ['--run'])]:
            result = run_compiler([str(args.compiler.resolve()), *flags, str(source)],
                                  capture_output=True, timeout=60, cwd=ROOT)
            label = name + '-' + mode
            (out / (label + '.stdout')).write_bytes(result.stdout)
            (out / (label + '.stderr')).write_bytes(result.stderr)
            rows.append({'case': name, 'mode': mode, **result.record()})
            if name in negative:
                if (result.returncode != 1 or result.channel != 'complete'
                        or result.failure_domain != 'source'
                        or b'subscript requires an Index implementation' not in result.stderr):
                    errors.append(label + ': protocol call bypassed nominal requirement or lost refusal')
            else:
                if result.returncode != 0 or result.failure_domain is not None:
                    errors.append(label + ': valid dispatch rejected')
                if mode == 'orc' and (result.stdout != source.with_suffix('.out').read_bytes() or result.stderr):
                    errors.append(label + ': dispatch/effects changed')
    unchanged = all(hashlib.sha256(Path(path).read_bytes()).hexdigest() == digest
                    for path, digest in fingerprints.items())
    if not unchanged:
        errors.append('compiler/test/fixture inputs changed during controls')
    (out / 'result.json').write_text(json.dumps({'cases': rows, 'errors': errors, 'inputs': fingerprints, 'inputs_unchanged': unchanged}, indent=2) + '\n')
    for error in errors:
        print(error, file=sys.stderr)
    print(f'{len(rows)} dynamic protocol controls; {len(errors)} unmet assertions')
    return 1 if errors else 0


if __name__ == '__main__':
    sys.exit(main())
