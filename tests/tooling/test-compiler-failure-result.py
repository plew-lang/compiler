#!/usr/bin/env python3
"""Private failure record decoder/status and independent invocation controls."""
import os
from pathlib import Path
import subprocess
import sys
import unittest

ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / 'scripts/support'))
from compiler_failure_result import CompilerResult, decode_record, run_compiler

IDENTITY = '0' * 32
FRAME = b'plew.compiler.failure.v1\n' + IDENTITY.encode() + b'\nsource\n'


class FailureResultTests(unittest.TestCase):
    def test_domain_and_status_are_independent(self):
        for domain in ['source', 'input', 'tool', 'limit', 'internal', 'unclassified']:
            data = b'plew.compiler.failure.v1\n' + IDENTITY.encode() + b'\n' + domain.encode() + b'\n'
            self.assertEqual(decode_record(data, IDENTITY), (domain, 'complete'))
            for code in [0, 1, 2, 124, 125, -6, -15]:
                result = CompilerResult(code, IDENTITY, domain, 'complete')
                self.assertEqual(result.source_rejection, domain == 'source' and code == 1)

    def test_missing_wrong_duplicate_partial_and_unknown_fail_closed(self):
        for data in [b'', FRAME[:-1], FRAME + FRAME, FRAME + b'\n',
                     FRAME.replace(b'v1', b'v2'), FRAME.replace(b'source', b'unknown'),
                     FRAME.replace(IDENTITY.encode(), b'1' * 32), FRAME + b'x' * 1025]:
            domain, state = decode_record(data, IDENTITY)
            self.assertFalse(CompilerResult(1, IDENTITY, domain, state).source_rejection)

    def test_real_subprocess_gets_fresh_descriptor_and_identity(self):
        program = "import os,sys; os.write(int(os.environ['_PLEW_COMPILER_FAILURE_FD']), b'plew.compiler.failure.v1\\n'+os.environ['_PLEW_COMPILER_FAILURE_ID'].encode()+b'\\nsource\\n'); print('same diagnostic',file=sys.stderr);sys.exit(1)"
        before = dict(os.environ)
        first = run_compiler([sys.executable, '-c', program], capture_output=True)
        second = run_compiler([sys.executable, '-c', program], capture_output=True)
        self.assertTrue(first.source_rejection)
        self.assertTrue(second.source_rejection)
        self.assertNotEqual(first.invocation, second.invocation)
        self.assertEqual(first.stderr, b'same diagnostic\n')
        self.assertEqual(dict(os.environ), before)

    def test_report_then_signal_is_not_source_rejection(self):
        program = "import os,signal; os.write(int(os.environ['_PLEW_COMPILER_FAILURE_FD']), b'plew.compiler.failure.v1\\n'+os.environ['_PLEW_COMPILER_FAILURE_ID'].encode()+b'\\nsource\\n');os.kill(os.getpid(), signal.SIGTERM)"
        result = run_compiler([sys.executable, '-c', program], capture_output=True)
        self.assertEqual(result.returncode, -15)
        self.assertEqual(result.failure_domain, 'source')
        self.assertFalse(result.source_rejection)

    def test_cli_assertion_preserves_failed_status_and_rejects_acceptance(self):
        helper = ROOT / 'scripts/support/compiler_failure_result.py'
        for code, expected in [(0, 1), (1, 0), (2, 2), (124, 124), (125, 125)]:
            program = "import os,sys;os.write(int(os.environ['_PLEW_COMPILER_FAILURE_FD']), b'plew.compiler.failure.v1\\n'+os.environ['_PLEW_COMPILER_FAILURE_ID'].encode()+b'\\nsource\\n');sys.exit(" + str(code) + ")"
            result = subprocess.run([sys.executable, '-B', str(helper), '--require-source-rejection', '--', sys.executable, '-c', program], capture_output=True, timeout=10)
            self.assertEqual(result.returncode, expected, result.stderr)

    def test_record_before_watchdog_timeout_does_not_complete_assertion(self):
        helper = ROOT / 'scripts/support/compiler_failure_result.py'
        program = "import os,time;os.write(int(os.environ['_PLEW_COMPILER_FAILURE_FD']), b'plew.compiler.failure.v1\\n'+os.environ['_PLEW_COMPILER_FAILURE_ID'].encode()+b'\\nsource\\n');time.sleep(20)"
        supervisor = "import sys;from process_watch import run;sys.exit(run(sys.argv[1:],idle_seconds=0.2,grace_seconds=0.1))"
        result = subprocess.run([sys.executable, '-B', '-c', supervisor, sys.executable, '-B', str(helper), '--require-source-rejection', '--', sys.executable, '-c', program], cwd=ROOT / 'scripts/support', capture_output=True, timeout=10)
        self.assertEqual(result.returncode, 124, result.stderr)

    def test_rendered_text_never_supplies_domain(self):
        result = run_compiler([sys.executable, '-c', "import sys;print('plewc: error: intended source rejection',file=sys.stderr);sys.exit(1)"], capture_output=True)
        self.assertEqual(result.channel, 'missing')
        self.assertFalse(result.source_rejection)


if __name__ == '__main__':
    unittest.main()
