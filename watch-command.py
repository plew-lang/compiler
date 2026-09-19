#!/usr/bin/env python3
"""Bound one worker command, preserving its stdout, stderr and exit status."""
import sys
sys.dont_write_bytecode = True
from process_watch import run

command = sys.argv[1:]
if command[:1] == ['--']:
    command = command[1:]
sys.exit(run(command))
