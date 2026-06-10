#!/bin/sh
# plew-gen.sh — deprecated thin wrapper kept for back-compat. The derive-macro
# generator is now a subcommand of the unified, relocatable CLI:
#
#   plew gen <file.pw> [<file.pw> …]
#
# `plew gen` is path-independent and links the harness with libc only (no
# llvm-config), so it works from any path. This wrapper just delegates.
exec "$(dirname "$0")/plew" gen "$@"
