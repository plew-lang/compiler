#!/usr/bin/env python3
"""Relocate only plew, then exercise CLI/resources with an OS-only PATH.

This is a local isolation test, not proof of compatibility with another machine.
The distribution build separately rejects non-OS dynamic library dependencies.
"""
import argparse
import json
import os
from pathlib import Path
import shutil
import subprocess
import sys
import tempfile

ROOT = Path(__file__).resolve().parents[2]


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--binary', type=Path, required=True)
    parser.add_argument('--evidence', type=Path, required=True)
    args = parser.parse_args()
    evidence = args.evidence.resolve()
    evidence.mkdir(parents=True, exist_ok=False)
    environment = {**os.environ, 'PATH': '/usr/bin:/bin:/usr/sbin:/sbin'}
    for name in ('CC', 'PLEW_STD', 'PLEW_TRACE_BUILD'):
        environment.pop(name, None)
    results = []
    wrapper = [sys.executable, str(ROOT / 'scripts/support/watch-command.py'), '--']
    with tempfile.TemporaryDirectory(prefix='plew distribution ') as temporary:
        root = Path(temporary)
        binary = root / 'plew'
        shutil.copy2(args.binary, binary)
        assert list(root.iterdir()) == [binary]

        def run(label, command, expected=0, extra_env=None, data=None):
            result = subprocess.run([*wrapper, *map(str, command)], input=data, cwd=root,
                                    capture_output=True, env={**environment, **(extra_env or {})})
            (evidence / (label + '.stdout')).write_bytes(result.stdout)
            (evidence / (label + '.stderr')).write_bytes(result.stderr)
            assert result.returncode == expected, (label, result.returncode, result.stderr.decode(errors='replace'))
            results.append({'case': label, 'exit': result.returncode})
            print('PASS distribution', label, flush=True)
            return result.stdout

        version = run('version', [binary, '--version'], extra_env={'PATH': ''})
        assert version.startswith(b'plew dev-') and b'LLVM 20.1.1' in version
        notices = run('licenses', [binary, '--licenses'], extra_env={'PATH': ''})
        assert b'Apache License' in notices and b'Zstandard' in notices
        run('help', [binary, '--help'])
        run('missing-command', [binary], expected=1)
        run('missing-source', [binary, 'build', 'Missing.pw'], expected=1)
        source = root / "Source 'quoted'.pw"
        source.write_text('import @Std/Io with { print }\nfn main() { print(42I64) }\n')
        output = root / 'app with spaces'
        run('build', [binary, 'build', source, '-o', output], extra_env={'PLEW_TRACE_BUILD': '1'})
        trace = (evidence / 'build.stderr').read_bytes()
        assert b'backend:drain:done' in trace and b'Running pass:' in trace
        assert b'backend:print-module' not in trace and b'backend:write:' not in trace
        assert run('execute', [output]) == b'42\n'
        assert run('run', [binary, 'run', source]) == b'42\n'
        run('bad-option', [binary, 'build', source, '--wrong'], expected=1)
        before = source.read_bytes()
        run('protect-source', [binary, 'build', source, '-o', root / '.' / source.name], expected=1)
        assert source.read_bytes() == before
        broken = root / 'Broken.pw'
        broken.write_text('fn main() { missing() }\n')
        previous = output.read_bytes()
        run('protect-output', [binary, 'build', broken, '-o', output], expected=1)
        assert output.read_bytes() == previous
        empty_std = root / 'empty-std'
        empty_std.mkdir()
        run('explicit-std-no-fallback', [binary, 'build', source, '-o', output], expected=1,
            extra_env={'PLEW_STD': str(empty_std)})
        alias = root / 'plewc'
        alias.symlink_to(binary.name)
        direct = run('compiler', [binary, '--compiler', source])
        assert run('compiler-alias', [alias, source]) == direct
        assert b'define i32 @main' in direct

        for name in ('async_match', 'unique_enum_arc', 'closure_return_boundaries',
                     'cow_gw_field_array_append'):
            fixture = ROOT / 'tests/fixtures/run' / (name + '.pw')
            shutil.copy2(fixture, root / fixture.name)
            actual = run(name, [binary, 'run', root / fixture.name])
            assert actual.rstrip(b'\n') == fixture.with_suffix('.out').read_bytes().rstrip(b'\n'), name

        source.write_text('import @Std/Process with { argAt, exit }\nimport @Std/Io with { print, readStdin }\nfn main() { print(argAt(1I64)) print(readStdin()) exit(code: 7I64) }\n')
        assert run('arguments-stdin-status', [binary, 'run', source, "one 'argument'"],
                   expected=7, data=b'input') == b"one 'argument'\ninput\n"

        package = root / 'package'
        package.mkdir()
        (package / 'Plew.toml').write_text('name = "Test/App"\n')
        run('resolve', [binary, 'resolve', package])
        assert (package / 'Plew.lock').is_file()
        run('resolve-missing-package', [binary, 'resolve', root / 'Missing'], expected=1)
        run('resolve-missing-child', [binary, 'resolve', package / 'Missing'], expected=1)

        gen = root / 'gen'
        shutil.copytree(ROOT / 'tests/fixtures/gen/fieldnames', gen)
        for generated in gen.glob('*.gen.pw'):
            generated.unlink()
        for name in ('Plew.toml', 'Plew.lock'):
            shutil.copy2(ROOT / name, gen / name)
        run('gen', [binary, 'gen', gen / 'App.pw'])
        assert (gen / 'App.gen.pw').is_file()
        assert run('gen-run', [binary, 'run', gen / 'App.pw']).rstrip(b'\n') == (gen / 'App.out').read_bytes().rstrip(b'\n')
        generated = (gen / 'App.gen.pw').read_bytes()
        (gen / 'App.pw').write_text('this is invalid syntax\n')
        run('gen-preserve-output', [binary, 'gen', gen / 'App.pw'], expected=1)
        assert (gen / 'App.gen.pw').read_bytes() == generated
    (evidence / 'results.json').write_text(json.dumps(results, indent=2) + '\n')


if __name__ == '__main__':
    main()
