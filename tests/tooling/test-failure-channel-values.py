#!/usr/bin/env python3
"""Manual private-channel producer values, including actual post-diagnostic abort."""
import argparse
import hashlib
import json
import os
from pathlib import Path
import secrets
import shutil
import signal
import subprocess
import sys
import tempfile

parser = argparse.ArgumentParser(description=__doc__)
parser.add_argument('--compiler', type=Path, required=True)
parser.add_argument('--out', type=Path, required=True)
args = parser.parse_args()
root = Path(__file__).resolve().parents[2]
out = args.out.resolve()
out.mkdir(parents=True, exist_ok=False)
carrier = args.compiler.resolve()
sys.path.insert(0, str(root / 'scripts/support'))
from clang_environment import apply
apply()
from compiler_failure_result import CompilerResult, decode_record
config = os.environ.get('LLVM_CONFIG') or shutil.which('llvm-config') or '/opt/homebrew/opt/llvm/bin/llvm-config'
clang = Path(subprocess.check_output([config, '--bindir'], text=True).strip()) / 'clang'
watch = [sys.executable, '-B', str(root / 'scripts/support/watch-command.py'), '--']
source = root / 'tests/compiler/frontend/FailureChannel.pw'
with (out / 'probe.ll').open('wb') as output, (out / 'compile.stderr').open('wb') as log:
    subprocess.run([*watch, str(carrier), '--trace-phases', str(source)], cwd=root, stdout=output, stderr=log, check=True)
with (out / 'runtime.c').open('wb') as output:
    subprocess.run([*watch, str(carrier), '--runtime'], stdout=output, check=True)
subprocess.run([*watch, str(clang), '-O0', str(out / 'probe.ll'), str(out / 'runtime.c'), '-o', str(out / 'probe')], check=True)
results = []
def check(mode, expected_domain, *, descriptor=None, identity=None, repeat=1):
    nonce = secrets.token_hex(16)
    with tempfile.TemporaryFile() as stream:
        env = {**os.environ, '_PLEW_COMPILER_FAILURE_FD': descriptor if descriptor is not None else str(stream.fileno()),
               '_PLEW_COMPILER_FAILURE_ID': identity if identity is not None else nonce}
        child = subprocess.Popen([str(out / 'probe'), mode], env=env, pass_fds=(stream.fileno(),),
            start_new_session=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
        try:
            stdout, stderr = child.communicate(timeout=15)
        except subprocess.TimeoutExpired:
            os.killpg(child.pid, signal.SIGKILL)
            child.communicate()
            raise
        stream.seek(0)
        payload = stream.read(1025)
    prefix = b'plewc: warning: ' if mode == 'warning' else b'plewc: error: '
    expected_stderr = (prefix + b'same message\n') * (2 if mode == 'twice' else 1)
    if mode == 'source-panic': expected_stderr += b'panic: controlled after diagnostic\n'
    expected_status = -signal.SIGABRT if mode == 'source-panic' else 2 if mode == 'source-status2' else 1
    expected = b'' if expected_domain is None else (b'plew.compiler.failure.v1\n' + nonce.encode() + b'\n' + expected_domain.encode() + b'\n') * repeat
    assert child.returncode == expected_status, (mode, child.returncode, stderr)
    assert stdout == b'', (mode, stdout)
    assert stderr == expected_stderr, (mode, stderr)
    assert payload == expected, (mode, descriptor, identity, payload, expected)
    domain, state = decode_record(payload, nonce)
    observed = CompilerResult(child.returncode, nonce, domain, state, stdout, stderr)
    assert observed.source_rejection == (expected_domain == 'source' and repeat == 1 and child.returncode == 1), (mode, observed.record())
    results.append({'source_rejection': observed.source_rejection, 'mode': mode, 'descriptor': descriptor, 'identity': identity,
                    'expected_domain': expected_domain, 'record_count': repeat if expected_domain else 0,
                    'returncode': child.returncode, 'result': 'passed'})
for domain in ['source', 'input', 'tool', 'limit', 'internal', 'unclassified']:
    check(domain, domain)
check('warning', 'unclassified')
check('render', None)
check('twice', 'source', repeat=2)
check('source-status2', 'source')
check('source-panic', 'source')
for descriptor in ['', '-1', '0', '1', '2', '2147483648', '99999999999', 'not-a-descriptor', '2147483647']:
    check('source', None, descriptor=descriptor)
for identity in ['', '0' * 31, '0' * 33, 'A' * 32, '0' * 31 + '\n']:
    check('source', None, identity=identity)
report = {'scope': 'producer wire values/IO only, not final consumer acceptance',
          'carrier_sha256': hashlib.sha256(carrier.read_bytes()).hexdigest(),
          'writer_sha256': hashlib.sha256((root / 'src/CompilerFailureOutput.pw').read_bytes()).hexdigest(),
          'cases': results, 'result': 'passed'}
(out / 'results.json').write_text(json.dumps(report, indent=2) + '\n')
print(f'PASS private channel producer: {len(results)} controls', flush=True)
