#!/usr/bin/env python3
"""Run a traced compiler/LLVM command, preserving stdout and stderr evidence."""
import os
from pathlib import Path
import selectors
import signal
import subprocess
import sys
import time

log_path = Path(sys.argv[1])
command = sys.argv[2:]
if command[:1] == ['--']:
    command = command[1:]
log_path.parent.mkdir(parents=True, exist_ok=True)
process = subprocess.Popen(command, stderr=subprocess.PIPE, start_new_session=True)
selector = selectors.DefaultSelector()
selector.register(process.stderr, selectors.EVENT_READ)
last_progress = time.monotonic()
last_report = last_progress
last_phase = None
pending = b''
events_seen = 0
expired = False
with log_path.open('wb') as log:
    while selector.get_map():
        ready = selector.select(timeout=1)
        if time.monotonic() - last_progress > 60:
            print('trace-command: no progress for 60 seconds; terminating', file=sys.stderr, flush=True)
            os.killpg(process.pid, signal.SIGTERM)
            expired = True
            break
        for key, _ in ready:
            data = os.read(key.fileobj.fileno(), 65536)
            if not data:
                selector.unregister(key.fileobj)
                continue
            log.write(data)
            log.flush()
            pending += data
            while b'\n' in pending:
                line, pending = pending.split(b'\n', 1)
                phase = line.startswith(b'[trace-phase]')
                llvm = line.startswith((b'Running pass:', b'Running analysis:', b'Invalidating analysis:'))
                if llvm or (phase and line != last_phase):
                    last_progress = time.monotonic()
                    events_seen += 1
                if phase:
                    last_phase = line
                if (not phase and not llvm) or time.monotonic() - last_report >= 10:
                    print(f'[trace-command events={events_seen}] {line.decode(errors="replace")}', file=sys.stderr, flush=True)
                    last_report = time.monotonic()
    if pending:
        print(pending.decode(errors='replace'), file=sys.stderr, flush=True)
try:
    code = process.wait(timeout=5 if expired else None)
except subprocess.TimeoutExpired:
    os.killpg(process.pid, signal.SIGKILL)
    code = process.wait()
print(f'trace-command: exit={code} events={events_seen} log={log_path}', file=sys.stderr, flush=True)
sys.exit(124 if expired else code if code >= 0 else 128 - code)
