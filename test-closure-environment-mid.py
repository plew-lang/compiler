#!/usr/bin/env python3
"""Require verified Mid emission for each closure environment destructor.

The closure function alone is insufficient: the captured values and shared
cells also need an explicit ownership-checked destruction body.
"""
import os
from pathlib import Path
import re
import subprocess
import sys
import tempfile

root = Path(__file__).resolve().parent
compiler = Path(os.environ.get("PLEWC", root / "plewc")).resolve()
cases = ["closure_capture_heap", "closure_mut_capture", "closure_capture_receiver_arc"]
failures = []
with tempfile.TemporaryDirectory(prefix="plew-closure-env-mid-") as directory:
    for index, name in enumerate(cases, 1):
        output = Path(directory) / (name + ".ll")
        with output.open("w") as stream:
            result = subprocess.run(
                [str(compiler), "--require-mid", "--emit-mid-coverage",
                 str(root / "tests" / "run" / (name + ".pw"))],
                cwd=root, stdout=stream, stderr=subprocess.PIPE,
                text=True, timeout=55,
            )
        if result.returncode:
            raise SystemExit(result.stderr or f"{name}: compiler exited {result.returncode}")
        definitions = re.findall(r"^define\b[^\n]*@(pwclodrop[\w.]*)\(", output.read_text(), re.M)
        evidence = re.findall(r"^mid-body symbol=(\S+) canonical=[1-9][0-9]*$", result.stderr, re.M)
        missing = [symbol for symbol in definitions if evidence.count(symbol) != 1]
        if not definitions:
            failures.append(f"{name}: no environment destructor; fixture cannot establish coverage")
        elif missing:
            failures.append(f"{name}: missing unique Mid evidence for {', '.join(missing)}")
        passed = bool(definitions) and not missing
        print(f"[closure-env-mid] {index}/{len(cases)} {'PASS' if passed else 'FAIL'} {name}: {len(definitions)} environment bodies", file=sys.stderr, flush=True)
if failures:
    raise SystemExit("\n".join(failures))
