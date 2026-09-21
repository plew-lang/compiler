#!/usr/bin/env python3
"""Mandatory raw-IR ASan supplement; the complete corpus uses the fast compiler."""
from concurrent.futures import ThreadPoolExecutor, as_completed
import os
from pathlib import Path
import subprocess
import sys

ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / 'scripts/support'))
import clang_environment


def main(mode="all"):
    clang_environment.apply()
    tmp = Path(os.environ['TMP']) / 'ownership'
    tmp.mkdir(parents=True, exist_ok=True)
    opt, clang = os.environ['OPT'], os.environ['CLANG']
    binary = ROOT / 'plewc_asan_ownership'
    trace = [sys.executable, str(ROOT / 'scripts/support/trace-command.py')]

    def command(label, argv, output=subprocess.DEVNULL, expected=0):
        log = tmp / (label + '.log')
        # Expected-failure controls must not publish their diagnostic as a gate failure.
        with (tmp / (label + '.supervisor.log')).open('w') as supervisor:
            result = subprocess.run([*trace, str(log), '--', *map(str, argv)], stdout=output,
                                    stderr=supervisor if expected else None)
        diagnostics = log.read_text(errors='replace')
        if result.returncode != expected:
            raise RuntimeError(f'{label}: exit {result.returncode}, expected {expected}; {log}')
        if expected == 0 and ('ERROR: AddressSanitizer' in diagnostics or 'ERROR: LeakSanitizer' in diagnostics):
            raise RuntimeError(f'{label}: sanitizer diagnostic; {log}')
        return diagnostics

    prepared = False

    # Nonvolatile, unused UAF is optimized away by module O1. This control
    # must be instrumented first, just like the compiler below.
    try:
        if mode != "check":
            binary.unlink(missing_ok=True)
            fixture = ROOT / 'tests/sanitizer/nonvolatile-unused-uaf.ll'
            command('control-instrument', [opt, '-passes=asan', fixture, '-o', tmp / 'control.bc'])
            command('control-link', [clang, '-O1', '-fsanitize=address', tmp / 'control.bc', '-o', tmp / 'control'])
            diagnostics = command('control-run', [tmp / 'control'], expected=1)
            if 'ERROR: AddressSanitizer: heap-use-after-free' not in diagnostics:
                raise RuntimeError('nonvolatile UAF control did not detect heap-use-after-free')
            command('instrument', [opt, '-debug-pass-manager', '-passes=asan', Path(os.environ['TMP']) / 'pc.ll', '-o', tmp / 'compiler.bc'])
            command('link', [clang, '-Xclang', '-fdebug-pass-manager', '-mllvm', '-debug-pass=Executions', '-O1', '-fno-omit-frame-pointer', '-fsanitize=address', '-w', tmp / 'compiler.bc', os.environ['RT'], str(Path(opt).parent.parent / 'lib/libLLVM.dylib'), '-o', binary])
            prepared = True
            if mode == "prepare":
                return
        elif not binary.is_file():
            raise RuntimeError('raw ownership compiler was not prepared')
        cases = [line.strip() for line in (ROOT / 'tests/sanitizer/asan-ownership-cases.txt').read_text().splitlines() if line.strip() and not line.startswith('#')]
        if not cases or len(cases) != len(set(cases)):
            raise RuntimeError('ownership manifest must be nonempty and unique')
        for case in cases:
            if not (ROOT / case).is_file():
                raise RuntimeError(f'missing ownership input: {case}')
        with ThreadPoolExecutor(max_workers=int(os.environ.get('PLEW_TEST_JOBS', os.cpu_count() or 1))) as pool:
            futures = {pool.submit(command, 'compile-' + str(i), [binary, '--trace-phases', ROOT / case]): case for i, case in enumerate(cases)}
            failures = []
            for completed, future in enumerate(as_completed(futures), 1):
                try:
                    future.result()
                    print(f'asan: E completed={completed} OK {futures[future]}', flush=True)
                except Exception as error:
                    failures.append(str(error))
                    print(f'asan: E completed={completed} FAIL {error}', flush=True)
            if failures:
                raise RuntimeError('; '.join(failures))
        print(f'  clean ({len(cases)} files)', flush=True)
    finally:
        if mode != "prepare" or not prepared:
            binary.unlink(missing_ok=True)


if __name__ == '__main__':
    try:
        import argparse
        parser = argparse.ArgumentParser()
        modes = parser.add_mutually_exclusive_group()
        modes.add_argument("--prepare", action="store_true")
        modes.add_argument("--check", action="store_true")
        args = parser.parse_args()
        main("prepare" if args.prepare else "check" if args.check else "all")
    except (OSError, ValueError, RuntimeError) as error:
        print(f'FAIL raw ownership ASan: {error}', flush=True)
        sys.exit(1)
