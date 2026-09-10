#!/bin/sh
# Verify adjacent generations, then measure the fixed-point compiler.
set -eu
cd "$(dirname "$0")"
exec python3 ./measure-self-host.py
