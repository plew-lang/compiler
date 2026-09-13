#!/usr/bin/env python3
"""Inventory positive corpus lowering; this is not a correctness/performance gate.

Keep individual LLVM definitions and fallback rows so a zero fallback count is
never confused with coverage of synthetic/async bodies outside that table.
Reject suites remain the responsibility of test.sh/test-gen.sh/test-deps.sh.
"""
import argparse
from collections import Counter
from concurrent.futures import ThreadPoolExecutor, as_completed
import hashlib
import json
import os
from pathlib import Path
import re
import shutil
import subprocess
import sys


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--compiler", default=os.environ.get("PLEWC", "./plewc"))
    parser.add_argument("--output", required=True)
    parser.add_argument("--jobs", type=int, default=4)
    parser.add_argument("sources", nargs="*")
    args = parser.parse_args()
    root = Path(__file__).resolve().parent
    os.chdir(root)
    compiler = Path(args.compiler).resolve()
    output = Path(args.output).resolve()
    output.mkdir(parents=True, exist_ok=False)
    if args.jobs < 1:
        parser.error("--jobs must be positive")
    if args.sources:
        cases = [(str(Path(source)), []) for source in args.sources]
    else:
        sources = set()
        for pattern in ("tests/run/*.pw", "tests/panic/*.pw",
                        "tests/part/*/Main.pw", "tests/part/Main.pw",
                        "src/_.pw", "resolve/_.pw", "tools/*.pw"):
            sources.update(str(p) for p in root.glob(pattern) if p.is_file())
        cases = [(source, []) for source in sorted(sources)]
        # Match test-gen.sh: prepare generated parts before observing the app.
        # Harness and app are separate executable inputs to the inventory.
        runtime = output / "runtime.c"
        with runtime.open("wb") as stream:
            subprocess.run([str(compiler), "--runtime"], stdout=stream, check=True)
        llvm_config = shutil.which(os.environ.get("LLVM_CONFIG", "llvm-config"))
        if not llvm_config:
            llvm_config = "/opt/homebrew/opt/llvm/bin/llvm-config"
        link_flags = subprocess.check_output([llvm_config, "--ldflags"], text=True).split()
        for source in sorted(root.glob("tests/gen/*/App.pw")):
            work = output / ("gen_" + source.parent.name)
            work.mkdir()
            for item in source.parent.glob("*.pw"):
                if not item.name.endswith(".gen.pw"):
                    shutil.copy2(item, work / item.name)
            for name in ("Plew.toml", "Plew.lock"):
                shutil.copy2(root / name, work / name)
            app = work / "App.pw"
            print(f"mid-inventory: preparing gen/{source.parent.name}", file=sys.stderr, flush=True)
            with (work / "harness.ll").open("wb") as stream:
                subprocess.run([sys.executable, str(root / "trace-command.py"),
                                str(work / "prepare.log"), "--", str(compiler),
                                "--trace-phases", "--gen", str(app)], stdout=stream, check=True)
            subprocess.run([sys.executable, str(root / "trace-command.py"),
                            str(work / "link.log"), "--", "clang", "-w",
                            str(work / "harness.ll"), str(runtime), *link_flags,
                            "-o", str(work / "harness")], check=True)
            with (work / "App.gen.pw").open("wb") as stream:
                subprocess.run([sys.executable, str(root / "trace-command.py"),
                                str(work / "generate.log"), "--", str(work / "harness")],
                               stdout=stream, check=True)
            cases.extend([(str(app), ["--gen"]), (str(app), [])])
    fingerprint = {
        "compiler": str(compiler),
        "compiler_sha256": hashlib.sha256(compiler.read_bytes()).hexdigest(),
        "source_commit": subprocess.check_output(
            ["git", "rev-parse", "HEAD"], text=True).strip(),
        "source_diff": subprocess.check_output(["git", "diff", "HEAD"], text=True),
        "manifest": (root / "Plew.toml").read_text(),
        "lock": (root / "Plew.lock").read_text(),
        "cases": cases,
    }
    (output / "inputs.json").write_text(json.dumps(fingerprint, indent=2) + "\n")

    def observe(index, source, flags):
        directory = output / str(index)
        directory.mkdir()
        command = [sys.executable, str(root / "trace-command.py"),
                   str(directory / "trace.log"), "--", str(compiler),
                   "--trace-phases", "--emit-mid-coverage", *flags, source]
        with (directory / "input.ll").open("wb") as llvm:
            code = subprocess.run(command, stdout=llvm).returncode
        trace = (directory / "trace.log").read_text(errors="replace")
        rows = [line for line in trace.splitlines() if line.startswith("mid-coverage ")]
        categories = Counter()
        for row in rows:
            match = re.search(r" category=(\S+)$", row)
            if not match:
                raise ValueError(f"Malformed coverage row: {row}")
            categories[match[1]] += 1
        definitions = []
        with (directory / "input.ll").open() as llvm:
            for line in llvm:
                if line.startswith("define "):
                    definitions.append(line.rstrip())
        # The per-case LLVM is diagnostic scratch, not retained source history.
        (directory / "input.ll").unlink()
        return {"index": index, "source": source, "flags": flags,
                "exit": code, "fallbacks": rows, "categories": dict(categories),
                "llvm_definitions": definitions}

    results = []
    print(f"mid-inventory: start cases={len(cases)} jobs={args.jobs}", file=sys.stderr, flush=True)
    with ThreadPoolExecutor(max_workers=args.jobs) as pool:
        pending = [pool.submit(observe, i, source, flags)
                   for i, (source, flags) in enumerate(cases)]
        for future in as_completed(pending):
            result = future.result()
            results.append(result)
            (output / str(result["index"]) / "result.json").write_text(
                json.dumps(result, indent=2) + "\n")
            print(f"mid-inventory: completed={len(results)}/{len(cases)} "
                  f"exit={result['exit']} source={result['source']} "
                  f"flags={result['flags']}", file=sys.stderr, flush=True)
    summary = {"cases": len(cases), "compile_failures": sum(r["exit"] != 0 for r in results),
               "cases_with_fallback": sum(bool(r["fallbacks"]) for r in results),
               "results": sorted(results, key=lambda r: r["index"])}
    (output / "summary.json").write_text(json.dumps(summary, indent=2) + "\n")
    print(f"mid-inventory: finished cases={summary['cases']} "
          f"compile-failures={summary['compile_failures']} "
          f"with-fallback={summary['cases_with_fallback']}", file=sys.stderr, flush=True)
    return 1 if summary["compile_failures"] else 0


if __name__ == "__main__":
    sys.exit(main())
