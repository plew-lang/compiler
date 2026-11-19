#!/usr/bin/env python3
"""Keep unsupported capture representations separate from source rejection."""
import argparse
from dataclasses import replace
import hashlib
import json
import os
from pathlib import Path
import subprocess
import sys
import tempfile

ROOT = Path(__file__).resolve().parents[3]
sys.path.insert(0, str(ROOT / 'scripts/support'))
from compiler_failure_result import CompilerResult, run_compiler

CASES = ('GenericStruct', 'FunctionValue', 'UnusedGenericStruct',
         'UnusedFunctionValue', 'GenericSubstitution', 'FunctionSubstitution')
SUCCESS = {('UnusedGenericStruct', 'orc'), ('UnusedFunctionValue', 'orc'),
           ('GenericSubstitution', 'check'), ('FunctionSubstitution', 'check')}
MARKERS = (b'ERROR: AddressSanitizer', b'ERROR: LeakSanitizer',
           b'AddressSanitizer:DEADLYSIGNAL', b'watch-command:', b'trace-command: no progress')

def matches(result, reason, success=False):
    stderr = result.stderr or b''
    if any(marker in stderr for marker in MARKERS) or result.stdout:
        return False
    if success:
        return result.returncode == 0 and result.failure_domain is None and result.channel == 'missing'
    return result.implementation_limit and reason in stderr


def controls():
    reason = b'target capture limit'
    valid = CompilerResult(1, 'control', 'limit', 'complete', b'', reason)
    assert matches(valid, reason)
    invalid = [replace(valid, failure_domain=domain) for domain in
               ('source', 'input', 'tool', 'internal', 'unclassified', None)]
    invalid += [replace(valid, returncode=code) for code in (0, 2, 124, -6, 134)]
    invalid += [replace(valid, channel=channel) for channel in
                ('missing', 'malformed', 'unknown-domain', 'foreign-invocation')]
    invalid += [replace(valid, stderr=b'another failure'), replace(valid, stdout=b'unexpected')]
    invalid += [replace(valid, stderr=reason + b'\n' + marker) for marker in MARKERS]
    assert all(not matches(result, reason) for result in invalid)
    success = CompilerResult(0, 'control', None, 'missing', b'', b'')
    assert matches(success, reason, True)
    assert not matches(replace(success, channel='malformed'), reason, True)
    assert not matches(replace(success, stderr=MARKERS[0]), reason, True)
    return len(invalid) + 4


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--compiler', type=Path,
                        default=Path(os.environ.get('PLEWC', ROOT / 'bin/plewc')))
    parser.add_argument('--out', type=Path)
    parser.add_argument('--progress', action='store_true')
    args = parser.parse_args()
    (ROOT / 'tmp').mkdir(exist_ok=True)
    out = args.out.resolve() if args.out else Path(tempfile.mkdtemp(prefix='capture-limits-', dir=ROOT / 'tmp'))
    if args.out:
        out.mkdir(parents=True, exist_ok=False)
    compiler = args.compiler.resolve()
    fixtures = ROOT / 'tests/compiler/frontend/fixtures/ClosureCaptureLimits'
    inputs = [compiler, Path(__file__).resolve(), ROOT / 'scripts/support/compiler_failure_result.py',
              ROOT / 'Plew.toml', ROOT / 'Plew.lock']
    inputs += [fixtures / (name + suffix) for name in CASES for suffix in ('.pw', '.err')]
    inputs += list((compiler.parent / 'std').rglob('*.pw'))
    def hashes():
        return {str(path): hashlib.sha256(path.read_bytes()).hexdigest() for path in inputs}
    frozen = hashes()
    rows, errors = [], []
    control_count = controls()
    for name in CASES:
        reason = (fixtures / (name + '.err')).read_bytes().strip()
        for mode, flags in [('check', ['--check']), ('aot', []), ('orc', ['--run'])]:
            label = name + '-' + mode
            try:
                trace = [] if mode == 'orc' else ['--trace-phases']
                result = run_compiler([str(compiler), *flags, *trace,
                                       str(fixtures / (name + '.pw'))],
                                      capture_output=True, timeout=55, cwd=ROOT)
            except subprocess.TimeoutExpired:
                errors.append(label + ': timeout')
                print('capture-limits: timeout ' + label, file=sys.stderr, flush=True)
                continue
            (out / (label + '.stdout')).write_bytes(result.stdout)
            (out / (label + '.stderr')).write_bytes(result.stderr)
            success = (name, mode) in SUCCESS
            row = {'case': name, 'mode': mode, 'expectation': 'success' if success else 'limit',
                   **result.record()}
            rows.append(row)
            if not matches(result, reason, success):
                errors.append(label + ': expected ' + row['expectation'] + ', observed ' + str(result.record()))
            if args.progress:
                print('capture-limits: completed ' + label, file=sys.stderr, flush=True)
    assert hashes() == frozen, 'capture-limit validation inputs changed'
    (out / 'result.json').write_text(json.dumps({'compiler': str(compiler), 'inputs': frozen,
        'controls': control_count, 'cases': rows, 'errors': errors}, indent=2) + '\n')
    if errors:
        for error in errors:
            print(error, file=sys.stderr)
        return 1
    print('PASS closure-capture-limits: 18 modes, 14 precise Limit refusals and 4 deferred/unrequested successes')
    return 0

if __name__ == '__main__':
    sys.exit(main())
