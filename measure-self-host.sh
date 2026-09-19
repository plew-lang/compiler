#!/bin/sh
# Stable entry point; implementation lives with its role.
exec sh "$(dirname "$0")/scripts/diagnostics/measure-self-host.sh" "$@"
