#!/usr/bin/env python3
"""Measure the existing source-to-textual-LLVM path; run under watch-command.py."""
import argparse
import json
import math
import platform
import statistics
import subprocess
import sys
import time
from pathlib import Path
sys.dont_write_bytecode = True
from check import ROOT, digest


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--source', required=True, type=Path)
    parser.add_argument('--out', required=True, type=Path)
    parser.add_argument('--runs', type=int, default=21)
    args = parser.parse_args()
    if args.runs < 3:
        parser.error('--runs must be >= 3')
    source, out = args.source.resolve(), args.out.resolve()
    out.mkdir(parents=True, exist_ok=False)
    compiler = ROOT / 'plewc'
    inputs = [compiler, source, Path(__file__), ROOT / 'Plew.toml', ROOT / 'Plew.lock',
              *sorted((ROOT / 'std').rglob('*.pw'))]
    hashes = {str(p): digest(p) for p in inputs}
    report = dict(status='running', scope='fresh compiler process, source to textual LLVM; no JIT/restart',
                  host=platform.platform(), inputs=hashes, samples=[])
    result = out / 'results.json'
    try:
        reference = None
        for index in range(args.runs):
            ir, err = out / f'{index}.ll', out / f'{index}.stderr'
            with ir.open('wb') as stdout, err.open('wb') as stderr:
                start = time.perf_counter_ns()
                status = subprocess.run([str(compiler), str(source)], cwd=ROOT,
                                        stdout=stdout, stderr=stderr).returncode
                elapsed = (time.perf_counter_ns() - start) / 1e6
            if status:
                raise RuntimeError(f'compile {index}: exit {status}; {err}')
            sha = digest(ir)
            if reference is not None and sha != reference:
                raise RuntimeError('identical source produced different LLVM')
            reference = sha
            report['samples'].append(dict(ms=elapsed, ir_sha=sha, ir_bytes=ir.stat().st_size))
            print(f'[source-baseline] completed {index + 1}/{args.runs}', flush=True)
        if any(digest(Path(p)) != sha for p, sha in hashes.items()):
            raise RuntimeError('measurement inputs changed')
        warm = sorted(s['ms'] for s in report['samples'][1:])
        report.update(status='passed', first_ms=report['samples'][0]['ms'],
                      median_ms=statistics.median(warm), p95_ms=warm[math.ceil(len(warm)*.95)-1])
        print(f'PASS median={report["median_ms"]:.3f} ms p95={report["p95_ms"]:.3f} ms')
        return 0
    except Exception as error:
        report.update(status='failed', error=str(error))
        print(str(error), file=sys.stderr)
        return 1
    finally:
        result.write_text(json.dumps(report, indent=2) + '\n')


if __name__ == '__main__':
    sys.exit(main())
