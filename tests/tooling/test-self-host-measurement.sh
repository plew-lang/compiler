#!/bin/sh
set -eu
cd "$(dirname "$0")/../.."
python3 ./tests/tooling/test-measure-self-compile-sampling.py
exec python3 ./tests/tooling/test-self-host-measurement.py
