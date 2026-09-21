#!/bin/sh
set -eu
cd "$(dirname "$0")/../.."
python3 ./tests/tooling/test-asan-ownership.py
python3 ./tests/tooling/test-asan-schedule.py
python3 ./tests/tooling/test-clang-environment.py
python3 ./tests/tooling/test-measure-self-compile-sampling.py
exec python3 ./tests/tooling/test-self-host-measurement.py
