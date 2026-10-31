#!/usr/bin/env python3
"""Own normal-suite dispatch status and exactly-once case-result reconciliation."""
import os
from pathlib import Path
import selectors
import signal
import subprocess
import sys
import tempfile
import time

sys.dont_write_bytecode = True
from process_watch import exit_status, signal_group


def case_label(phase, path):
    name = path.parent.name if phase in ('part', 'partreject') else path.stem
    return name if phase == 'run' else f'{phase}/{name}'


def dispatch(phase, paths):
    cases = [Path(p) for p in paths if Path(p).is_file()]
    expected = {case_label(phase, p): p for p in cases}
    if not cases or len(expected) != len(cases):
        print(f'plewc: {phase} dispatch: empty selection or duplicate case identities', file=sys.stderr)
        return 1
    try:
        jobs = int(os.environ.get('PLEW_TEST_JOBS', os.environ.get('JOBS', '1')))
        if jobs <= 0:
            raise ValueError()
    except ValueError:
        print(f'plewc: {phase} dispatch: invalid worker count', file=sys.stderr)
        return 1
    progress = os.environ.get('PLEW_TEST_PROGRESS', '1') != '0'
    if progress:
        print(f'plewc: {phase} started ({len(cases)} cases; {jobs} workers)', file=sys.stderr, flush=True)
    worker = Path(__file__).resolve().parents[2] / 'tests/harness/case-phase.sh'
    command = ['xargs', '-0', '-P', str(jobs), '-n', '1', 'sh', str(worker), '--worker', phase]
    seen = set()
    invalid = False
    process = None
    handlers = {}
    requested = None
    completed = False
    selector = selectors.DefaultSelector()
    def cancel(number, frame):
        nonlocal requested
        requested = number
    def accept(raw, terminated=True):
        nonlocal invalid
        line = raw.decode('utf-8')
        label = None
        if terminated:
            if line.startswith('PASS '):
                candidate = line[5:]
                if candidate in expected:
                    label = candidate
            elif line.startswith('FAIL '):
                matches = [name for name in expected if line[5:] == name or
                           (line.startswith('FAIL ' + name + '(') and line.endswith(')'))]
                if len(matches) == 1:
                    label = matches[0]
        if label is None or label in seen:
            print(f'plewc: {phase} dispatch: invalid or duplicate result: {line!r}', file=sys.stderr)
            invalid = True
            return
        seen.add(label)
        print(line, flush=True)
        if progress:
            print(f'plewc: {phase} {len(seen)}/{len(cases)} complete: {line}',
                  file=sys.stderr, flush=True)
    try:
        for number in (signal.SIGHUP, signal.SIGINT, signal.SIGTERM):
            handlers[number] = signal.signal(number, cancel)
        with tempfile.TemporaryFile() as inputs:
            inputs.write(b'\0'.join(os.fsencode(p) for p in cases) + b'\0')
            inputs.seek(0)
            process = subprocess.Popen(command, stdin=inputs, stdout=subprocess.PIPE,
                                       start_new_session=True)
            selector.register(process.stdout, selectors.EVENT_READ)
            pending = b''
            while selector.get_map() or process.poll() is None:
                if requested:
                    print(f'plewc: {phase} dispatch: interrupted by signal {requested}', file=sys.stderr)
                    return 128 + requested
                for key, _ in selector.select(0.1):
                    data = os.read(key.fd, 65536)
                    if not data:
                        selector.unregister(key.fileobj)
                        if pending:
                            accept(pending, terminated=False)
                            pending = b''
                        continue
                    pending += data
                    while b'\n' in pending:
                        line, pending = pending.split(b'\n', 1)
                        accept(line)
            code = process.wait()
            completed = True
        missing = sorted(expected.keys() - seen)
        if missing:
            print(f'plewc: {phase} dispatch: missing results: {", ".join(missing)}', file=sys.stderr)
        if code:
            print(f'plewc: {phase} dispatch: dispatcher exited {exit_status(code)}', file=sys.stderr)
        # A valid FAIL record is not a dispatch failure; test.sh owns case totals.
        return 1 if invalid or missing or code else 0
    except (OSError, UnicodeError) as error:
        print(f'plewc: {phase} dispatch: {error}', file=sys.stderr)
        return 1
    finally:
        if process is not None:
            if not completed:
                # Like the existing supervisor, allow a bounded cancellation grace
                # before killing the group; nested supervisors can reap their children.
                stopped = time.monotonic()
                signal_group(process, signal.SIGTERM)
                try:
                    process.wait(timeout=1)
                except subprocess.TimeoutExpired:
                    pass
                time.sleep(max(0, 1 - (time.monotonic() - stopped)))
                signal_group(process, signal.SIGKILL)
                process.wait()
            process.stdout.close()
        selector.close()
        for number, handler in handlers.items():
            signal.signal(number, handler)


if __name__ == '__main__':
    if len(sys.argv) < 3 or sys.argv[1] not in ('run', 'panic', 'reject', 'part', 'partreject'):
        raise SystemExit('usage: normal-case-dispatch.py PHASE CASE...')
    raise SystemExit(dispatch(sys.argv[1], sys.argv[2:]))
