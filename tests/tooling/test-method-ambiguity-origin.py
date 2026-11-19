#!/usr/bin/env python3
"""Scoped rejection-domain controls; selection semantics stay unchanged."""
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
    parser.add_argument('--reference', type=Path)
    args = parser.parse_args()
    out = args.out.resolve()
    out.mkdir(parents=True, exist_ok=False)
    fixtures = [ROOT / 'tests/fixtures/reject' / (name + '.pw') for name in [
        'existential_overload_literal_ambiguous', 'extension_trait_provenance_ambiguous']]
    fixtures += [ROOT / 'tests/compiler/frontend/MethodAmbiguityInputs' / (name + '.pw') for name in ['Global', 'Closure']]
    reasons = [b'ambiguous call: multiple trait requirements match the arguments',
               b'ambiguous source-qualified call: active views provide multiple matching methods',
               b'ambiguous call: multiple trait requirements match the arguments',
               b'ambiguous call: multiple trait requirements match the arguments']
    rows = []
    errors = []
    for index, fixture in enumerate(fixtures):
        source = fixture
        for mode, flags in [('check', ['--check']), ('aot', []), ('orc', ['--run'])]:
            reason = reasons[index]
            label = f'{index}-{mode}'
            result = run_compiler([str(args.compiler.resolve()), *flags, str(source)],
                                  capture_output=True, timeout=60, cwd=ROOT)
            (out / (label + '.stdout')).write_bytes(result.stdout)
            (out / (label + '.stderr')).write_bytes(result.stderr)
            row = {'fixture': str(fixture.relative_to(ROOT)), 'mode': mode, **result.record()}
            rows.append(row)
            if result.returncode not in (0, 1) or (result.returncode == 1 and (result.channel != 'complete' or reason not in result.stderr)):
                errors.append(label + ': not the intended ambiguity refusal')
            if True and result.returncode != 1:
                errors.append(label + ': expected demanded source refusal')
            if result.returncode == 1 and result.failure_domain != 'source':
                errors.append(label + ': expected Source, observed ' + str(result.failure_domain))
            if args.reference:
                reference_rows = json.loads((args.reference / 'result.json').read_text())['cases']
                if reference_rows[len(rows)-1]['returncode'] != result.returncode:
                    errors.append(label + ': return status changed')
                for stream in ('stdout', 'stderr'):
                    assert (out / (label + '.' + stream)).read_bytes() == (args.reference / (label + '.' + stream)).read_bytes(), (label, stream)
    (out / 'result.json').write_text(json.dumps({'cases': rows, 'errors': errors}, indent=2) + '\n')
    for error in errors:
        print(error, file=sys.stderr)
    print(f'{len(rows)} ambiguity controls; {len(errors)} unmet assertions')
    return 1 if errors else 0


if __name__ == '__main__':
    sys.exit(main())
