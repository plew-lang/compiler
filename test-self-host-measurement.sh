#!/bin/sh
set -eu
cd "$(dirname "$0")"
python3 ./test-measure-self-compile-sampling.py
exec python3 ./test-self-host-measurement.py
