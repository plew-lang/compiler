#!/usr/bin/env python3
"""Stage-zero lazy ORC probe; no production compiler/runtime behavior is changed."""
import argparse
import hashlib
import json
import subprocess
import sys
from pathlib import Path

sys.dont_write_bytecode = True
ROOT = Path(__file__).resolve().parents[3]
HERE = Path(__file__).resolve().parent
sys.path.insert(0, str(ROOT / 'scripts/support'))
from clang_environment import apply


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--out', type=Path, required=True)
    parser.add_argument('--llvm-prefix', type=Path, default=Path('/opt/homebrew/opt/llvm'))
    args = parser.parse_args()
    apply()
    out = args.out.resolve()
    out.mkdir(parents=True, exist_ok=False)
    prefix = args.llvm_prefix.resolve()
    binary = out / 'lazy-probe'
    inputs = [HERE / 'lazy.cpp', HERE / 'common.hpp', Path(__file__),
              prefix / 'bin/clang++', prefix / 'lib/libLLVM.dylib']
    def hashes():
        return {str(p): hashlib.sha256(p.read_bytes()).hexdigest() for p in inputs}
    before = hashes()
    command = [str(prefix / 'bin/clang++'), '-std=c++17', '-O2',
               '-I' + str(prefix / 'include'), str(HERE / 'lazy.cpp'),
               '-L' + str(prefix / 'lib'), '-lLLVM', '-o', str(binary)]
    watch = [sys.executable, '-B', str(ROOT / 'scripts/support/watch-command.py'), '--']
    with (out / 'build.log').open('wb') as log:
        subprocess.run([*watch, *command], stdout=log, stderr=log, check=True)
    results = []
    for mode, expected in [('success', 0), ('failure', 70), ('spin', None), ('success', 0)]:
        try:
            result = subprocess.run([str(binary), mode], capture_output=True, timeout=2 if mode == 'spin' else 30)
            assert result.returncode == expected, (mode, result.returncode, result.stderr)
            if mode == 'failure':
                assert b'lazy-call-failed' in result.stderr
            results.append(dict(mode=mode, exit=result.returncode, stdout=result.stdout.decode(), stderr=result.stderr.decode()))
        except subprocess.TimeoutExpired:
            # subprocess.run kills and reaps this single-process executor.
            assert mode == 'spin'
            results.append(dict(mode=mode, killed_and_reaped=True))
        print('PASS', mode, flush=True)
    assert before == hashes(), 'inputs changed'
    (out / 'results.json').write_text(json.dumps(dict(status='passed', inputs=before, command=command, cases=results), indent=2) + '\n')


if __name__ == '__main__':
    main()
