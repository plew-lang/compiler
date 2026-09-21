"""Own a command, its cancellation, and its semantic-progress deadline."""
import json
import os
from pathlib import Path
import re
import selectors
import signal
import subprocess
import sys
import time
import uuid


def event(identifier, kind, **fields):
    path = os.environ.get('PLEW_WATCH_EVENTS')
    if path:
        data = json.dumps(dict(id=identifier, kind=kind, time=time.time(), **fields)).encode() + b'\n'
        descriptor = os.open(path, os.O_WRONLY | os.O_APPEND | os.O_CREAT, 0o600)
        try:
            os.write(descriptor, data)
        finally:
            os.close(descriptor)


def signal_group(process, number):
    try:
        os.killpg(process.pid, number)
    except ProcessLookupError:
        pass


def exit_status(code):
    return code if code >= 0 else 128 - code


class ProgressEvents:
    """Coalesce notifications without changing the local progress deadline."""
    def __init__(self, identifier, interval=1.0):
        self.identifier = identifier
        self.interval = interval
        self.sent = 0
        self.last_sent = float('-inf')

    def flush(self, counter, now, final=False):
        if counter > self.sent and (final or now - self.last_sent >= self.interval):
            event(self.identifier, 'progress', counter=counter)
            self.sent = counter
            self.last_sent = now


def run(command, log_path=None, traced=False, idle_seconds=60, grace_seconds=1):
    identifier = uuid.uuid4().hex
    notifications = ProgressEvents(identifier, interval=min(1.0, idle_seconds / 4))
    process = None
    requested = [None]
    handlers = {}
    selector = selectors.DefaultSelector()
    log = None
    state = 'error'
    code = None
    error = None
    count = 0
    pending = b''
    last_phase = None
    counters = {}
    stop_at = None
    killed = False
    def cancel(number, frame):
        requested[0] = number
    for number in (signal.SIGINT, signal.SIGTERM):
        handlers[number] = signal.signal(number, cancel)
    try:
        if log_path is not None:
            log_path = Path(log_path)
            log_path.parent.mkdir(parents=True, exist_ok=True)
            log = log_path.open('wb')
        process = subprocess.Popen(command, stderr=subprocess.PIPE, start_new_session=True)
        event(identifier, 'start', pid=process.pid, command=command[0])
        selector.register(process.stderr, selectors.EVENT_READ)
        last = report = time.monotonic()
        state = 'running'
        while selector.get_map() or process.poll() is None:
            now = time.monotonic()
            notifications.flush(count, now)
            if stop_at is None and (requested[0] or now - last >= idle_seconds):
                state = 'interrupted' if requested[0] else 'stalled'
                stop_at = now
                signal_group(process, signal.SIGTERM)
                event(identifier, state)
            if stop_at is not None and not killed and now - stop_at >= grace_seconds:
                signal_group(process, signal.SIGKILL)
                killed = True
            for key, _ in selector.select(0.1):
                data = os.read(key.fileobj.fileno(), 65536)
                if not data:
                    selector.unregister(key.fileobj)
                    continue
                if log:
                    log.write(data)
                    log.flush()
                if not traced:
                    sys.stderr.buffer.write(data)
                    sys.stderr.buffer.flush()
                pending += data
                lines = pending.split(b'\n')
                pending = lines.pop()
                for line in lines:
                    phase = line.startswith(b'[trace-phase]')
                    llvm = line.startswith((b'Running pass:', b'Running analysis:', b'Invalidating analysis:')) or (line.startswith(b'[') and b" Executing Pass '" in line)
                    nested = re.match(rb'\[trace-command log=(.+) events=(\d+)\]', line) if line.startswith(b'[trace-command ') else None
                    progress = llvm or (phase and line != last_phase)
                    if nested:
                        name, value = nested[1], int(nested[2])
                        progress = value > counters.get(name, -1)
                        counters[name] = max(value, counters.get(name, -1))
                    if progress:
                        last = time.monotonic()
                        count += 1
                    if phase:
                        last_phase = line
                    llvm_detail = line.startswith(b'Clearing all analysis results for:') or (line.startswith(b'[') and any(marker in line for marker in (b" Freeing Pass '", b" Made Modification '")))
                    if traced and ((not phase and not llvm and not llvm_detail) or now - report >= 10):
                        print(f'[trace-command log={log_path} events={count}] {line.decode(errors="replace")}', file=sys.stderr, flush=True)
                        report = now
                if len(pending) > 1024 * 1024:
                    pending = b''
        code = process.wait()
        if stop_at is not None:
            # Wrappers below us receive TERM too and get time to reap their own groups.
            remaining = grace_seconds - (time.monotonic() - stop_at)
            if remaining > 0:
                time.sleep(remaining)
            signal_group(process, signal.SIGKILL)
        else:
            state = 'exited'
        if pending and traced:
            print(pending.decode(errors='replace'), file=sys.stderr)
    except BaseException as failure:
        state = 'error'
        error = str(failure)
    finally:
        if process is not None and process.poll() is None:
            try:
                signal_group(process, signal.SIGKILL)
                code = process.wait(timeout=2)
            except OSError as failure:
                error = f'{error or "cleanup"}: {failure}'
            except subprocess.TimeoutExpired:
                error = f'{error or "cleanup"}: child did not exit'
        if process is not None and process.stderr:
            process.stderr.close()
        if log:
            log.close()
        selector.close()
        for number, handler in handlers.items():
            signal.signal(number, handler)
        notifications.flush(count, time.monotonic(), final=True)
        event(identifier, 'end', state=state, exit_code=code, error=error)
    if traced or state != 'exited':
        print(f'trace-command: state={state} exit={code} events={count} log={log_path}' + (f' error={error}' if error else ''), file=sys.stderr, flush=True)
    if state == 'stalled':
        return 124
    if state == 'interrupted':
        return 128 + (requested[0] or signal.SIGTERM)
    if state == 'error' or code is None:
        return 125
    return exit_status(code)
