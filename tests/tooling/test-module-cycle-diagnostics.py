"""Check the complete cycle reported by early module admission."""

import argparse
from pathlib import Path
import subprocess


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("--compiler", required=True, type=Path)
    args = parser.parse_args()
    compiler = args.compiler.resolve()
    fixtures = Path(__file__).resolve().parents[1] / "fixtures"
    marker = "module use graph contains a cycle (spec/15): "
    cases = {
        "importcycle": {"A.pw", "B.pw"},
        "selective_reexport_cycle": {"First.pw", "Second.pw"},
        "namespace_import_cycle": {"First.pw", "Second.pw"},
        "namespace_reexport_cycle": {"First.pw", "Second.pw"},
        "namespace_self_import_cycle": {"Main.pw"},
    }
    failed = []
    for case, members in cases.items():
        directory = fixtures / "partreject" / case
        expected = {directory / name for name in members}
        for mode in (("--check",), (), ("--run",)):
            result = subprocess.run(
                [compiler, *mode, directory / "Main.pw"], capture_output=True, text=True
            )
            lines = [line for line in result.stderr.splitlines() if marker in line]
            ring = (
                [Path(path).resolve() for path in lines[0].split(marker, 1)[1].split(" -> ")]
                if len(lines) == 1
                else []
            )
            if (
                result.returncode != 1
                or len(ring) != len(expected) + 1
                or ring[0] != ring[-1]
                or set(ring[:-1]) != expected
            ):
                failed.append(f"{case} {mode or ('AOT',)}: {result.stderr.strip()}")
    for case in ("nsimport", "crossimport", "importalias"):
        result = subprocess.run(
            [compiler, "--check", fixtures / "part" / case / "Main.pw"],
            capture_output=True,
            text=True,
        )
        if result.returncode != 0:
            failed.append(f"{case} check: {result.stderr.strip()}")
    if failed:
        raise SystemExit("\n".join(failed))


if __name__ == "__main__":
    main()
