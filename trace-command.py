#!/usr/bin/env python3
"""Run a traced compiler/LLVM command, preserving stdout and stderr evidence."""
import sys
sys.dont_write_bytecode = True
from process_watch import run

log_path = sys.argv[1]
command = sys.argv[2:]
if command[:1] == ['--']:
    command = command[1:]
sys.exit(run(command, log_path=log_path, traced=True))
