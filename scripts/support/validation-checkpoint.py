#!/usr/bin/env python3
"""Pause bootstrap after dependency materialization for the caller's snapshot."""
import os
from pathlib import Path
import sys
import time

name = os.environ.get('PLEW_INPUT_CHECKPOINT')
if name:
    directory = Path(name)
    directory.mkdir(parents=True, exist_ok=True)
    (directory / 'ready').write_text('dependencies\n')
    deadline = time.monotonic() + 60
    while not (directory / 'ack').exists():
        if (directory / 'error').exists():
            sys.exit('validation-checkpoint: dependency snapshot failed')
        if time.monotonic() >= deadline:
            sys.exit('validation-checkpoint: snapshot acknowledgment timed out')
        time.sleep(0.05)
