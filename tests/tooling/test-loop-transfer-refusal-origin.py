#!/usr/bin/env python3
"""Loop-target refusals retain source ownership without eager ORC checking."""
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
    rows, errors = [], []
    modes = [('check', ['--check']), ('aot', []), ('orc', ['--run'])]

    def run(label, path, flags):
        inputs[str(path)] = digest(path)
        result = run_compiler([str(carrier), *flags, str(path)], capture_output=True, timeout=60, cwd=ROOT)
        (out / (label + '.stdout')).write_bytes(result.stdout)
        (out / (label + '.stderr')).write_bytes(result.stderr)
        rows.append({'case': label, **result.record()})
        return result

    cases = {}
    for shape in ['plain', 'binding', 'chain', 'nested_if']:
        for transfer in ['break', 'continue']:
            name = f'while_condition_{shape}_{transfer}'
            path = ROOT / 'tests/fixtures/reject' / (name + '.pw')
            inputs[str(path)] = digest(path)
            cases[name] = (path.read_text(), f'`{transfer}` cannot target a surrounding loop from a while condition'.encode())
    for transfer in ['break', 'continue']:
        name = f'block_{transfer}_outside_loop'
        path = ROOT / 'tests/fixtures/reject' / (name + '.pw')
        inputs[str(path)] = digest(path)
        cases[name] = (path.read_text(), f'`{transfer}` outside a loop'.encode())
        cases['closure_' + transfer] = (
            'fn main() { while true { val action = fn() { ' + transfer + ' } action() break } }\n',
            f'`{transfer}` outside a loop'.encode())

    cases.update({
        'generic_break': ('fn broken[T](value: T) { break }\nfn main() { broken(value: 1I64) }\n', b'`break` outside a loop'),
        'method_continue': ('struct Item {}\nimpl Item { fn broken() { continue } }\nfn main() { val item = <Item /> item.broken() }\n', b'`continue` outside a loop'),
        'provided_break': ('trait Worker { fn basis() -> Bool }\npub impl Worker { fn broken() { break } }\nstruct Item {}\nimpl Item as Worker { fn basis() -> Bool { return false } }\nfn main() { val item = <Item /> item.broken() }\n', b'`break` outside a loop'),
        'default_break': ('fn broken(value: I64 = { break }) {}\nfn main() { broken() }\n', b'`break` outside a loop'),
        'default_continue': ('fn broken(value: I64 = { continue }) {}\nfn main() { broken() }\n', b'`continue` outside a loop'),
    })

    for name, (source, message) in cases.items():
        for demanded in [False, True]:
            path = out / (name + ('-used' if demanded else '-unused') + '.pw')
            # Both variants retain exactly the authored body; only entry demand changes.
            assert source.count('fn main()') == 1
            path.write_text(source if demanded else source.replace('fn main()', 'fn unused()', 1) + '\nfn main() {}\n')
            for mode, flags in modes:
                label = path.stem + '-' + mode
                result = run(label, path, flags)
                if demanded or mode != 'orc':
                    if not result.source_rejection or message not in result.stderr:
                        errors.append(label + ': target refusal lost source ownership')
                elif result.returncode != 0 or result.failure_domain is not None or result.stdout or result.stderr:
                    errors.append(label + ': unrequested transfer was inspected')

    for transfer in ['break', 'continue']:
        path = out / ('global-' + transfer + '.pw')
        path.write_text('val sample: I64 = { ' + transfer + ' }\nfn main() {}\n')
        for mode, flags in modes:
            label = path.stem + '-' + mode
            result = run(label, path, flags)
            if not result.source_rejection or ('`' + transfer + '` outside a loop').encode() not in result.stderr:
                errors.append(label + ': initializer lost owned transfer refusal')

    path = ROOT / 'tests/fixtures/run/while_condition_local_loops.pw'
    golden = path.with_suffix('.out')
    inputs[str(golden)] = digest(golden)
    for mode, flags in modes:
        result = run('condition-local-loop-' + mode, path, flags)
        if result.returncode != 0 or result.failure_domain is not None or (mode == 'orc' and result.stdout != golden.read_bytes()):
            errors.append('condition-local-loop-' + mode + ': valid target changed')
    unchanged = all(digest(Path(path)) == value for path, value in inputs.items())
    if not unchanged:
        errors.append('inputs changed')
    (out / 'result.json').write_text(json.dumps({'cases': rows, 'errors': errors, 'inputs': inputs, 'inputs_unchanged': unchanged}, indent=2) + '\n')
    print(f'{len(rows)} loop target controls; {len(errors)} unmet assertions')
    return int(bool(errors))


if __name__ == '__main__':
    sys.exit(main())
