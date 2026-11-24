#!/usr/bin/env python3
"""Qualified callable admission keeps receiver category and source ownership."""
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
    associated = b'an associated function declaration cannot be used as a value'
    cases = {
        'associated': ('struct Item {}\nimpl Item { assoc fn make() -> I64 { return 1I64 } }\nfn broken() -> fn() -> I64 { return Item.make }', associated),
        'instance': ('struct Item {}\nimpl Item { fn read() -> I64 { return 1I64 } }\nfn broken() -> fn() -> I64 { val item = <Item /> return item.read }', b'a method cannot be used as a value'),
        'bound': ('trait Maker { assoc fn make() -> Self }\nstruct Item {}\nimpl Item as Maker { assoc fn make() -> Item { return <Item /> } }\nfn broken[T](seed: T) -> fn() -> T where T: Maker { return T.make }', associated),
    }
    for name, (body, message) in cases.items():
        for demanded in [False, True]:
            path = out / (name + ('-used' if demanded else '-unused') + '.pw')
            call = 'broken(seed: <Item />)' if name == 'bound' else 'broken()'
            path.write_text(body + '\nfn main() { ' + (call if demanded else '') + ' }\n')
            for mode, flags in modes:
                label = path.stem + '-' + mode
                result = run(label, path, flags)
                if demanded or mode != 'orc':
                    if not result.source_rejection or message not in result.stderr:
                        errors.append(label + ': missing owned member-category refusal')
                elif result.returncode != 0 or result.failure_domain is not None or result.stdout or result.stderr:
                    errors.append(label + ': unused body was inspected')
    path = ROOT / 'tests/fixtures/reject/assoc_fn_value_arg.pw'
    for mode, flags in modes:
        result = run('assoc_fn_value_arg-' + mode, path, flags)
        if not result.source_rejection or associated not in result.stderr:
            errors.append('assoc_fn_value_arg-' + mode + ': nonvalue category lost before argument typing')
    library = out / 'Library.pw'
    library.write_text('pub fn target() -> I64 { return 3I64 }\npub val value: I64 = 4I64\n')
    inputs[str(library)] = digest(library)
    path = out / 'namespace-declaration.pw'
    path.write_text('use ./Library\nfn main() { val value: fn() -> I64 = Library.target }\n')
    for mode, flags in modes:
        result = run('namespace-declaration-' + mode, path, flags)
        if not result.source_rejection or b'a named function declaration cannot be used as a value' not in result.stderr:
            errors.append('namespace-declaration-' + mode + ': namespace declaration identity lost')
    # All three owners retain namespace normalization; reexports keep the
    # defining declaration distinct from its namespace surface.
    facade = out / 'Facade.pw'
    facade.write_text('pub use ./Library only { target }\n')
    inputs[str(facade)] = digest(facade)
    for owner, body in {
        'global': 'val broken: fn() -> I64 = Facade.target\nfn main() {}',
        'closure': 'fn main() { val action: fn() = fn() { val value: fn() -> I64 = Facade.target } }',
        'overload': 'fn main() { val value: fn() -> I64 = Facade.target }',
    }.items():
        path = out / ('namespace-' + owner + '.pw')
        path.write_text('use ./Facade\n' + body + '\n')
        for mode, flags in modes:
            result = run('namespace-' + owner + '-' + mode, path, flags)
            if not result.source_rejection or b'a named function declaration cannot be used as a value' not in result.stderr:
                errors.append('namespace-' + owner + '-' + mode + ': normalized owner lost')
    controls = ['assoc_val', 'namespace_import', 'namespace_alias', 'callable_surface_namespaces',
                'lexical_type_binder_callable_receiver', 'member_associated_candidate_conflict', 'member_discovery_label_frontier']
    for name in controls:
        path = ROOT / 'tests/fixtures/run' / (name + '.pw')
        golden = path.with_suffix('.out')
        inputs[str(golden)] = digest(golden)
        for mode, flags in modes:
            result = run(name + '-' + mode, path, flags)
            if result.returncode != 0 or result.failure_domain is not None or (mode == 'orc' and result.stdout != golden.read_bytes()):
                errors.append(name + '-' + mode + ': normal qualified call/value changed')
    unchanged = all(digest(Path(path)) == value for path, value in inputs.items())
    if not unchanged:
        errors.append('inputs changed')
    (out / 'result.json').write_text(json.dumps({'cases': rows, 'errors': errors, 'inputs': inputs, 'inputs_unchanged': unchanged}, indent=2) + '\n')
    print(f'{len(rows)} qualified declaration controls; {len(errors)} unmet assertions')
    return int(bool(errors))

if __name__ == '__main__':
    sys.exit(main())
