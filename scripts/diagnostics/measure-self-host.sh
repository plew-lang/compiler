#!/bin/sh
# Verify adjacent generations, then measure the fixed-point compiler.
set -eu
cd "$(dirname "$0")/../.."
exec python3 ./scripts/diagnostics/measure-self-host.py
