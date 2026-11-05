#!/usr/bin/env python3
"""Manual real CLI transport probe; negative-consumer admission is separate."""
import argparse
import hashlib
import json
import os
from pathlib import Path
import secrets
import signal
import subprocess
import sys
import tempfile

ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / 'scripts/support'))
from compiler_failure_result import CompilerResult, decode_record

parser = argparse.ArgumentParser(description=__doc__)
parser.add_argument('--compiler', type=Path, required=True)
parser.add_argument('--out', type=Path, required=True)
args = parser.parse_args()
carrier = args.compiler.resolve()
out = args.out.resolve()
out.mkdir(parents=True, exist_ok=False)
sources = {
    'MissingReturn.pw': 'fn missingResult() -> I64 {}\nfn main() {}\n',
    'LazyMissingReturn.pw': 'fn missingResult() -> I64 {}\nfn main() { missingResult() }\n',
    'Malformed.pw': 'fn main(\n',
    'Accepted.pw': 'fn main() {}\n',
}
for name, source in sources.items():
    (out / name).write_text(source)
missing = out / 'MissingReturn.pw'
# Domain and status are separate from the expected diagnostic reason.
cases = [
    ('llvm-source', [str(missing)], 1, 'source', b'can reach the end of its body'),
    ('check-source', ['--check', str(missing)], 1, 'source', b'can reach the end of its body'),
    ('object-source', ['--emit-object', str(out / 'unused.o'), str(missing)], 1, 'source', b'can reach the end of its body'),
    ('run-open-source', ['--run', str(out / 'Malformed.pw')], 1, 'source', b'plewc: error:'),
    ('run-request-source', ['--run', str(out / 'LazyMissingReturn.pw')], 1, 'source', b'can reach the end of its body'),
    ('missing-input', ['--check', str(out / 'Absent.pw')], 1, 'input', b'plewc: error:'),
    ('accepted', ['--check', str(out / 'Accepted.pw')], 0, None, None),
]
carrier_hash = hashlib.sha256(carrier.read_bytes()).hexdigest()
report = {'scope': 'actual CLI producer/terminal transport; not rejection-consumer or whole-task completion',
          'carrier_sha256': carrier_hash,
          'sources': {name: hashlib.sha256(text.encode()).hexdigest() for name, text in sources.items()},
          'cases': []}
for name, arguments, status, domain, reason in cases:
    directory = out / name
    directory.mkdir()
    nonce = secrets.token_hex(16)
    timed_out = False
    with tempfile.TemporaryFile() as channel:
        env = {**os.environ, '_PLEW_COMPILER_FAILURE_FD': str(channel.fileno()),
               '_PLEW_COMPILER_FAILURE_ID': nonce}
        command = [str(carrier), *arguments]
        child = subprocess.Popen(command, cwd=ROOT, env=env,
            pass_fds=(channel.fileno(),), start_new_session=True,
            stdout=subprocess.PIPE, stderr=subprocess.PIPE)
        try:
            stdout, stderr = child.communicate(timeout=60)
        except subprocess.TimeoutExpired:
            timed_out = True
            os.killpg(child.pid, signal.SIGKILL)
            stdout, stderr = child.communicate()
        channel.seek(0)
        payload = channel.read(1025)
    expected = (b'plew.compiler.failure.v1\n' + nonce.encode() + b'\n' + domain.encode() + b'\n') if domain else b''
    actual_domain, state = decode_record(payload, nonce)
    result = CompilerResult(child.returncode, nonce, actual_domain, state)
    control = not timed_out and child.returncode == status and (reason is None or reason in stderr)
    correct = control and payload == expected and result.source_rejection == (domain == 'source')
    row = {'name': name, 'command': command, 'returncode': child.returncode,
           'expected_returncode': status, 'expected_domain': domain,
           'producer_control': control, 'record_matches_current_invocation': payload == expected,
           'consumer_snapshot': result.record(), 'timeout': timed_out,
           'stderr': stderr.decode(errors='replace'), 'result': 'passed' if correct else 'failed'}
    for filename, data in [('stdout', stdout), ('stderr', stderr), ('channel', payload)]:
        (directory / filename).write_bytes(data)
    report['cases'].append(row)
report['carrier_unchanged'] = carrier_hash == hashlib.sha256(carrier.read_bytes()).hexdigest()
report['result'] = 'passed' if report['carrier_unchanged'] and all(row['result'] == 'passed' for row in report['cases']) else 'failed'
(out / 'results.json').write_text(json.dumps(report, indent=2) + '\n')
print(json.dumps({'result': report['result'], 'cases': [{key: row[key] for key in ['name', 'producer_control', 'result']} for row in report['cases']]}), flush=True)
raise SystemExit(0 if report['result'] == 'passed' else 1)
