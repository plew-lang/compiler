#!/usr/bin/env python3
"""Retain missing concrete operator selection, without inspecting unused bodies."""
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
    parser.add_argument('--compiler', type=Path, required=True)
    parser.add_argument('--out', type=Path, required=True)
    args = parser.parse_args()
    carrier = args.compiler.resolve()
    out = args.out.resolve()
    out.mkdir(parents=True, exist_ok=False)
    digest = lambda path: hashlib.sha256(path.read_bytes()).hexdigest()
    inputs = {str(carrier): digest(carrier), str(Path(__file__).resolve()): digest(Path(__file__).resolve())}
    inputs.update({str(path): digest(path) for path in (ROOT / 'src').rglob('*.pw')})
    rows, errors = [], []

    def run(label, path, mode, flags):
        inputs.setdefault(str(path), digest(path))
        result = run_compiler([str(carrier), *flags, str(path)], capture_output=True, timeout=60, cwd=ROOT)
        (out / (label + '.stdout')).write_bytes(result.stdout)
        (out / (label + '.stderr')).write_bytes(result.stderr)
        rows.append({'case': label, 'mode': mode, **result.record()})
        return result

    programs = {
        'function': 'fn broken() -> String { return "bad" + 1I64 }',
        'closure': 'fn broken() { val action: fn() -> String = fn() -> String { return "bad" + 1I64 } }',
        'global': 'val broken: String = "bad" + 1I64',
    }
    modes = [('check', ['--check']), ('aot', []), ('orc', ['--run'])]
    for name, body in programs.items():
        for demanded in ([True] if name == 'global' else [False, True]):
            source = out / (name + ('-used' if demanded else '-unused') + '.pw')
            source.write_text('use @Std/Io only { print }\n' + body + '\nfn main() { ' + ('broken()' if demanded and name != 'global' else '') + ' }\n')
            for mode, flags in modes:
                label = source.stem + '-' + mode
                result = run(label, source, mode, flags)
                rejected = demanded or mode != 'orc'
                if rejected:
                    if (result.returncode != 1 or result.channel != 'complete' or result.failure_domain != 'source'
                            or b'arithmetic operator needs Add/Sub/Mul/Div/Rem' not in result.stderr):
                        errors.append(label + ': expected owned missing selection')
                elif result.returncode != 0 or result.stdout or result.stderr or result.failure_domain is not None:
                    errors.append(label + ': unused body was inspected')
    controls = ['string_concat', 'generic_operator_output_projection', 'operator_extension_selection',
                'numeric_wrapper_overload_context', 'operator_prim_compare',
                'compound_assign_place_once', 'compound_assign_witness', 'syntax_lower_compound_assign',
                'existing_value_patterns', 'match_value_pattern_snapshot']
    for name in controls:
        source = ROOT / 'tests/fixtures/run' / (name + '.pw')
        golden = source.with_suffix('.out')
        inputs[str(golden)] = digest(golden)
        for mode, flags in modes:
            label = name + '-' + mode
            result = run(label, source, mode, flags)
            if result.returncode != 0 or result.failure_domain is not None or (mode == 'orc' and result.stdout != golden.read_bytes()):
                errors.append(label + ': normal operator control changed')
    ambiguous = ROOT / 'tests/fixtures/reject/operator_ambiguous_int_overload.pw'
    for mode, flags in modes:
        label = 'ambiguous-' + mode
        result = run(label, ambiguous, mode, flags)
        if result.returncode != 1 or b'ambiguous operator' not in result.stderr:
            errors.append(label + ': ambiguity was erased or replaced by missing selection')
    unchanged = all(digest(Path(path)) == expected for path, expected in inputs.items())
    if not unchanged:
        errors.append('inputs changed during execution')
    (out / 'result.json').write_text(json.dumps({'cases': rows, 'errors': errors, 'inputs': inputs, 'inputs_unchanged': unchanged}, indent=2) + '\n')
    for error in errors:
        print(error, file=sys.stderr)
    print(f'{len(rows)} missing operator controls; {len(errors)} unmet assertions')
    return int(bool(errors))


if __name__ == '__main__':
    sys.exit(main())
