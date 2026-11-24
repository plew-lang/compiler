#!/usr/bin/env python3
"""Named callable declarations are not values; retain refusal ownership."""
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
    carrier, out = args.compiler.resolve(), args.out.resolve()
    out.mkdir(parents=True, exist_ok=False)
    digest = lambda path: hashlib.sha256(path.read_bytes()).hexdigest()
    inputs = {str(carrier): digest(carrier), str(Path(__file__).resolve()): digest(Path(__file__).resolve())}
    inputs.update({str(path): digest(path) for path in (ROOT / 'src').rglob('*.pw')})
    rows, errors = [], []
    modes = [('check', ['--check']), ('aot', []), ('orc', ['--run'])]
    def run(label, path, flags):
        inputs[str(path)] = digest(path)
        result = run_compiler([str(carrier), *flags, str(path)], capture_output=True, timeout=60, cwd=ROOT)
        (out / (label + '.stdout')).write_bytes(result.stdout)
        (out / (label + '.stderr')).write_bytes(result.stderr)
        rows.append({'case': label, **result.record()})
        return result
    for name in ['named_fn_value_arg', 'named_fn_value_return', 'named_fn_value_closure', 'named_fn_value_global']:
        path = ROOT / 'tests/fixtures/reject' / (name + '.pw')
        for mode, flags in modes:
            result = run(name + '-' + mode, path, flags)
            if not result.source_rejection or b'a named function declaration cannot be used as a value' not in result.stderr:
                errors.append(name + '-' + mode + ': missing owned non-value declaration refusal')
    for kind, body in {
        'function': 'fn broken() { val value = target }',
        'closure': 'fn broken() { val action: fn() = fn() { val value = target } }',
        'global': 'val broken = target',
        'overload': 'fn target(value: Bool) -> Bool { return value }\nfn broken() { val value = target }',
    }.items():
        for demanded in ([True] if kind == 'global' else [False, True]):
            path = out / (kind + ('-used' if demanded else '-unused') + '.pw')
            path.write_text('fn target() -> I64 { return 1I64 }\n' + body + '\nfn main() { ' + ('broken()' if demanded and kind != 'global' else '') + ' }\n')
            for mode, flags in modes:
                label = path.stem + '-' + mode
                result = run(label, path, flags)
                if demanded or mode != 'orc':
                    if not result.source_rejection or b'a named function declaration cannot be used as a value' not in result.stderr:
                        errors.append(label + ': missing owned declaration refusal')
                elif result.returncode != 0 or result.failure_domain is not None or result.stdout or result.stderr:
                    errors.append(label + ': unused body was inspected')
    # Target0, lexical shadowing and explicit wrappers are all genuine values/calls.
    path = out / 'normal.pw'
    path.write_text('use @Std/Io only { print }\nfn target() -> I64 { return 1I64 }\nfn main() {\n print(target())\n val wrapper: fn() -> I64 = fn() -> I64 { return target() }\n print(wrapper())\n val target: fn() -> I64 = fn() -> I64 { return 2I64 }\n val copied = target\n print(copied())\n}\n')
    for mode, flags in modes:
        result = run('normal-' + mode, path, flags)
        if result.returncode != 0 or result.failure_domain is not None or (mode == 'orc' and result.stdout != b'1\n1\n2\n'):
            errors.append('normal-' + mode + ': callable value or invocation changed')
    library = out / 'Library.pw'
    library.write_text('pub fn target() -> I64 { return 3I64 }\npub fn target(value: Bool) -> Bool { return value }\nfn hidden() -> I64 { return 9I64 }\n')
    inputs[str(library)] = digest(library)
    for invalid in [False, True]:
        path = out / ('alias-bad.pw' if invalid else 'alias-good.pw')
        path.write_text('use ./Library only { target as selected }\n' + ('fn main() { val value: fn() -> I64 = selected }\n' if invalid else 'fn main() { val value: fn() -> I64 = fn() -> I64 { return selected() } value() }\n'))
        for mode, flags in modes:
            result = run(path.stem + '-' + mode, path, flags)
            if invalid:
                if not result.source_rejection or b'a named function declaration cannot be used as a value' not in result.stderr:
                    errors.append(path.stem + '-' + mode + ': aliased overload lost declaration identity')
            elif result.returncode != 0 or result.failure_domain is not None:
                errors.append(path.stem + '-' + mode + ': aliased wrapper changed')
    path = out / 'private-import.pw'
    path.write_text('use ./Library only { hidden }\nfn main() { val value = hidden }\n')
    for mode, flags in modes:
        result = run('private-import-' + mode, path, flags)
        if not result.source_rejection or b'a named function declaration cannot be used as a value' in result.stderr:
            errors.append('private-import-' + mode + ': inaccessible declaration became an admitted Fn binding')
    unchanged = all(digest(Path(path)) == value for path, value in inputs.items())
    if not unchanged:
        errors.append('inputs changed')
    (out / 'result.json').write_text(json.dumps({'cases': rows, 'errors': errors, 'inputs': inputs, 'inputs_unchanged': unchanged}, indent=2) + '\n')
    print(f'{len(rows)} named declaration controls; {len(errors)} unmet assertions')
    return int(bool(errors))

if __name__ == '__main__':
    sys.exit(main())
