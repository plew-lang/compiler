#!/usr/bin/env python3
"""Overlap one raw compiler preparation with A/B, owning both process groups."""
import os
from pathlib import Path
import signal
import subprocess
import sys
import time

ROOT = Path(__file__).resolve().parents[2]


def run_stages(corpus, prepare, jobs):
    if jobs < 1:
        raise ValueError('PLEW_TEST_JOBS must be positive')
    children = []
    interrupted = [0]
    previous = {}

    def cancel(number, frame):
        interrupted[0] = number

    def launch(command, slots):
        child = subprocess.Popen(command, env={**os.environ, 'PLEW_TEST_JOBS': str(slots)},
                                 start_new_session=True)
        children.append(child)
        return child

    def await_children(active):
        while True:
            if interrupted[0]:
                return 128 + interrupted[0]
            codes = [child.poll() for child in active]
            if any(code is not None and code != 0 for code in codes):
                return 1
            if all(code == 0 for code in codes):
                return 0
            time.sleep(0.05)

    failed = True
    try:
        for number in (signal.SIGINT, signal.SIGTERM):
            previous[number] = signal.signal(number, cancel)
        if jobs == 1:
            code = await_children([launch(corpus, 1)])
            if code:
                return code
            code = await_children([launch(prepare, 1)])
        else:
            code = await_children([launch(prepare, 1), launch(corpus, jobs - 1)])
        failed = code != 0
        return code
    finally:
        if failed:
            # Supervisors in each group receive TERM and reap their own LLVM groups.
            for child in children:
                if child.poll() is not None:
                    continue
                try:
                    os.killpg(child.pid, signal.SIGTERM)
                except ProcessLookupError:
                    pass
            deadline = time.monotonic() + 2
            while time.monotonic() < deadline:
                time.sleep(0.05)
            for child in children:
                if child.poll() is not None:
                    continue
                try:
                    os.killpg(child.pid, signal.SIGKILL)
                except ProcessLookupError:
                    pass
        for child in children:
            child.wait()
        for number, handler in previous.items():
            signal.signal(number, handler)


def main():
    jobs = int(os.environ.get('PLEW_TEST_JOBS', os.cpu_count() or 1))
    binary = ROOT / 'plewc_asan_ownership'
    binary.unlink(missing_ok=True)
    succeeded = False
    try:
        code = run_stages(['sh', str(ROOT / 'tests/harness/asan-compile-corpus.sh')],
                          [sys.executable, '-B', str(ROOT / 'tests/sanitizer/asan-ownership.py'), '--prepare'], jobs)
        succeeded = code == 0
        return code
    finally:
        if not succeeded:
            binary.unlink(missing_ok=True)


if __name__ == '__main__':
    raise SystemExit(main())
