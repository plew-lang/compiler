#!/usr/bin/env python3
"""Inherited existential requirements retain their parent instance through execution."""
import argparse
import hashlib
import json
from pathlib import Path
import sys
ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / 'scripts/support'))
from compiler_failure_result import run_compiler

def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--compiler', required=True, type=Path)
    parser.add_argument('--out', required=True, type=Path)
    args = parser.parse_args()
    out = args.out.resolve()
    out.mkdir(exist_ok=False, parents=True)
    fingerprints = {}
    def retain(path):
        path = path.resolve()
        fingerprints[str(path)] = hashlib.sha256(path.read_bytes()).hexdigest()
    retain(args.compiler)
    retain(Path(__file__))
    rows, errors = [], []
    for name in ['index_inherited_existential_requirement', 'inherited_existential_method',
                 'inherited_existential_diamond', 'inherited_existential_generic',
                 'inherited_existential_assoc_order', 'inherited_existential_converging',
                 'inherited_existential_late_binding', 'inherited_existential_converging_bindings',
                 'inherited_existential_unavailable_slot', 'inherited_existential_generic_erasure',
                 'inherited_existential_self_result', 'inherited_existential_inout',
                 'inherited_existential_owned_result',
                 'index_existential_requirement', 'index_generic_inherited_requirement']:
        source = ROOT / 'tests/fixtures/run' / (name + '.pw')
        retain(source)
        retain(source.with_suffix('.out'))
        for mode, flags in [('check', ['--check']), ('aot', []), ('orc', ['--run'])]:
            result = run_compiler([str(args.compiler.resolve()), *flags, str(source)],
                                  capture_output=True, timeout=60, cwd=ROOT)
            label = name + '-' + mode
            (out / (label + '.stdout')).write_bytes(result.stdout)
            (out / (label + '.stderr')).write_bytes(result.stderr)
            rows.append({'case': name, 'mode': mode, **result.record()})
            if result.returncode != 0 or result.failure_domain is not None:
                errors.append(label + ': valid inherited requirement was rejected')
            if mode == 'orc' and (result.stdout != source.with_suffix('.out').read_bytes() or result.stderr):
                errors.append(label + ': inherited dispatch did not execute the expected witness')
    unchanged = all(hashlib.sha256(Path(path).read_bytes()).hexdigest() == digest
                    for path, digest in fingerprints.items())
    if not unchanged:
        errors.append('compiler/tool/fixture input changed')
    (out / 'result.json').write_text(json.dumps({'cases': rows, 'errors': errors,
                                               'inputs': fingerprints, 'inputs_unchanged': unchanged}, indent=2) + '\n')
    for error in errors:
        print(error, file=sys.stderr)
    print(f'{len(rows)} inherited existential controls; {len(errors)} unmet assertions')
    return bool(errors)

if __name__ == '__main__':
    sys.exit(main())
